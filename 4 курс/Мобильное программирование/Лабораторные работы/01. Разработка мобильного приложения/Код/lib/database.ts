import { 
  collection, 
  doc,
  addDoc, 
  getDocs, 
  updateDoc,
  deleteDoc,
  query, 
  where, 
  orderBy,
  serverTimestamp 
} from 'firebase/firestore';
import { db } from './firebase';
import { getAdminDb } from './firebaseAdmin';
import { Group, Vote } from './groups';

// Интерфейс для фильма из Firebase
export interface Film {
  id: string;
  kinopoiskId: number;
  title: string;
  year: number;
  poster?: string;
  description?: string;
  rating?: number;
  addedBy: string;
  addedAt: Date;
}

// Коллекции Firestore
const GROUPS_COLLECTION = 'groups';
const FILMS_COLLECTION = 'films';
const VOTES_COLLECTION = 'votes';

// ===== ГРУППЫ =====

export interface GroupData {
  code: string;
  participants: string[];
  createdAt: unknown; // serverTimestamp
  isActive: boolean;
  createdBy: string;
}

export async function createGroup(groupData: Omit<GroupData, 'createdAt'>): Promise<string> {
  try {
    const docRef = await addDoc(collection(db, GROUPS_COLLECTION), {
      ...groupData,
      createdAt: serverTimestamp()
    });
    return docRef.id;
  } catch (error) {
    console.error('Ошибка создания группы:', error);
    throw new Error('Не удалось создать группу');
  }
}

export async function getGroupByCode(code: string): Promise<Group | null> {
  try {
    // Нормализуем код группы (верхний регистр, без пробелов)
    const normalizedCode = code?.toUpperCase().trim();
    
    if (!normalizedCode) {
      console.error('Empty or invalid group code');
      return null;
    }
    
    console.log('Searching for group with code:', normalizedCode);
    
    const q = query(collection(db, GROUPS_COLLECTION), where('code', '==', normalizedCode));
    const querySnapshot = await getDocs(q);
    
    if (querySnapshot.empty) {
      return null;
    }
    
    const doc = querySnapshot.docs[0];
    const data = doc.data();
    
    return {
      id: doc.id,
      code: data.code,
      participants: data.participants || [],
      films: [], // Будем загружать отдельно
      votes: [], // Будем загружать отдельно
      createdAt: data.createdAt?.toDate() || new Date(),
      isActive: data.isActive ?? true,
      createdBy: data.createdBy || ''
    };
  } catch (error) {
    console.error('Ошибка получения группы:', error);
    throw new Error('Не удалось получить группу');
  }
}

export async function updateGroup(groupId: string, updates: Partial<GroupData>): Promise<void> {
  try {
    const groupRef = doc(db, GROUPS_COLLECTION, groupId);
    await updateDoc(groupRef, updates);
  } catch (error) {
    console.error('Ошибка обновления группы:', error);
    throw new Error('Не удалось обновить группу');
  }
}

// ===== ФИЛЬМЫ =====

export interface FilmData {
  groupId: string;
  kinopoiskId: number;
  title: string;
  year: number;
  poster?: string;
  description?: string;
  rating?: number;
  addedBy: string;
  addedAt: unknown; // serverTimestamp
}

export async function addFilmToGroup(filmData: Omit<FilmData, 'addedAt'>): Promise<string> {
  try {
    // Проверяем, не существует ли уже такой фильм в группе
    const existingFilms = await getFilmsByGroup(filmData.groupId);
    const isDuplicate = existingFilms.some(film => 
      film.kinopoiskId === filmData.kinopoiskId
    );
    
    if (isDuplicate) {
      throw new Error('Этот фильм уже добавлен в группу');
    }

    const docRef = await addDoc(collection(db, FILMS_COLLECTION), {
      ...filmData,
      addedAt: serverTimestamp()
    });
    return docRef.id;
  } catch (error) {
    console.error('Ошибка добавления фильма:', error);
    if (error instanceof Error) {
      throw error; // Передаем оригинальную ошибку
    }
    throw new Error('Не удалось добавить фильм');
  }
}

export async function getFilmsByGroup(groupId: string): Promise<Film[]> {
  try {
    // Упрощенный запрос без orderBy для избежания необходимости в индексах
    const q = query(
      collection(db, FILMS_COLLECTION), 
      where('groupId', '==', groupId)
    );
    const querySnapshot = await getDocs(q);
    
    const films = querySnapshot.docs.map(doc => {
      const data = doc.data();
      return {
        id: doc.id,
        kinopoiskId: data.kinopoiskId,
        title: data.title,
        year: data.year,
        poster: data.poster,
        description: data.description,
        rating: data.rating,
        addedBy: data.addedBy,
        addedAt: data.addedAt?.toDate() || new Date()
      };
    });

    // Сортируем на клиенте
    return films.sort((a, b) => b.addedAt.getTime() - a.addedAt.getTime());
  } catch (error) {
    console.error('Ошибка получения фильмов:', error);
    throw new Error('Не удалось получить фильмы');
  }
}

// ===== ГОЛОСА =====

export interface VoteData {
  groupId: string;
  filmId: number;
  vote: 'like' | 'dislike';
  participantId: string;
  timestamp: unknown; // serverTimestamp
}

export async function addVotes(votes: Omit<VoteData, 'timestamp'>[]): Promise<void> {
  try {
    const batch = votes.map(vote => 
      addDoc(collection(db, VOTES_COLLECTION), {
        ...vote,
        timestamp: serverTimestamp()
      })
    );
    
    await Promise.all(batch);
  } catch (error) {
    console.error('Ошибка добавления голосов:', error);
    throw new Error('Не удалось добавить голоса');
  }
}

export async function getVotesByGroup(groupId: string): Promise<Vote[]> {
  try {
    const q = query(collection(db, VOTES_COLLECTION), where('groupId', '==', groupId));
    const querySnapshot = await getDocs(q);
    
    return querySnapshot.docs.map(doc => {
      const data = doc.data();
      return {
        filmId: data.filmId,
        vote: data.vote,
        timestamp: data.timestamp?.toDate() || new Date(),
        participantId: data.participantId
      };
    });
  } catch (error) {
    console.error('Ошибка получения голосов:', error);
    throw new Error('Не удалось получить голоса');
  }
}

export async function deleteVotesByGroup(groupId: string): Promise<void> {
  try {
    let deletedCount = 0;
    const admin = getAdminDb();
    if (admin) {
      const snap = await admin.collection(VOTES_COLLECTION).where('groupId', '==', groupId).get();
      deletedCount = snap.docs.length;
      const batch = admin.batch();
      snap.docs.forEach((d: any) => batch.delete(d.ref));
      await batch.commit();
    } else {
      const q = query(collection(db, VOTES_COLLECTION), where('groupId', '==', groupId));
      const querySnapshot = await getDocs(q);
      deletedCount = querySnapshot.docs.length;
      const deletePromises = querySnapshot.docs.map(doc => deleteDoc(doc.ref));
      await Promise.all(deletePromises);
    }
    
    console.log(`Удалено ${deletedCount} голосов для группы ${groupId}`);
  } catch (error) {
    console.error('Ошибка удаления голосов:', error);
    throw new Error('Не удалось удалить голоса');
  }
}

export async function deleteFilmsByGroup(groupId: string): Promise<void> {
  try {
    let deletedCount = 0;
    const admin = getAdminDb();
    if (admin) {
      const snap = await admin.collection(FILMS_COLLECTION).where('groupId', '==', groupId).get();
      deletedCount = snap.docs.length;
      const batch = admin.batch();
      snap.docs.forEach((d: any) => batch.delete(d.ref));
      await batch.commit();
    } else {
      const q = query(collection(db, FILMS_COLLECTION), where('groupId', '==', groupId));
      const querySnapshot = await getDocs(q);
      deletedCount = querySnapshot.docs.length;
      const deletePromises = querySnapshot.docs.map(doc => deleteDoc(doc.ref));
      await Promise.all(deletePromises);
    }
    
    console.log(`Удалено ${deletedCount} фильмов для группы ${groupId}`);
  } catch (error) {
    console.error('Ошибка удаления фильмов:', error);
    throw new Error('Не удалось удалить фильмы');
  }
}

export async function deleteGroup(groupId: string): Promise<void> {
  try {
    // Сначала удаляем все связанные данные (фильмы и голоса)
    await deleteFilmsByGroup(groupId);
    await deleteVotesByGroup(groupId);
    
    // Затем удаляем саму группу
    const admin = getAdminDb();
    if (admin) {
      await admin.collection(GROUPS_COLLECTION).doc(groupId).delete();
    } else {
      const groupRef = doc(db, GROUPS_COLLECTION, groupId);
      await deleteDoc(groupRef);
    }
    
    console.log(`Группа ${groupId} и все связанные данные успешно удалены`);
  } catch (error) {
    console.error('Ошибка удаления группы:', error);
    throw new Error('Не удалось удалить группу');
  }
}

// Автоматическая очистка заброшенных групп (старше 24 часов)
export async function cleanupOldGroups(): Promise<number> {
  try {
    const now = new Date();
    const dayAgo = new Date(now.getTime() - 24 * 60 * 60 * 1000); // 24 часа назад
    
    const q = query(collection(db, GROUPS_COLLECTION));
    const querySnapshot = await getDocs(q);
    
    let deletedCount = 0;
    const deletePromises: Promise<void>[] = [];
    
    querySnapshot.docs.forEach(docSnap => {
      const data = docSnap.data();
      const createdAt = data.createdAt?.toDate();
      
      if (createdAt && createdAt < dayAgo) {
        deletePromises.push(deleteGroup(docSnap.id));
        deletedCount++;
      }
    });
    
    await Promise.all(deletePromises);
    
    if (deletedCount > 0) {
      console.log(`Автоочистка: удалено ${deletedCount} старых групп`);
    }
    
    return deletedCount;
  } catch (error) {
    console.error('Ошибка автоочистки групп:', error);
    return 0;
  }
}

// ===== УТИЛИТЫ =====

export async function getGroupWithData(code: string): Promise<Group | null> {
  try {
    const group = await getGroupByCode(code);
    if (!group) {
      return null;
    }
    
    // Загружаем фильмы и голоса
    const [films, votes] = await Promise.all([
      getFilmsByGroup(group.id),
      getVotesByGroup(group.id)
    ]);
    
    return {
      ...group,
      films,
      votes
    };
  } catch (error) {
    console.error('Ошибка получения полных данных группы:', error);
    throw new Error('Не удалось получить данные группы');
  }
}
