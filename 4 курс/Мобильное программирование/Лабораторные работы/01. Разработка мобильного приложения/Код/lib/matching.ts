import { Film } from './groups';

export interface Vote {
  filmId: number;
  vote: 'like' | 'dislike';
  timestamp: number;
  participantId: string;
}

export interface MatchResult {
  film: Film;
  participants: string[];
  matchPercentage: number;
  totalVotes: number;
  likes: number;
  dislikes: number;
}

export interface MatchingStats {
  totalParticipants: number;
  votedParticipants: number;
  totalFilms: number;
  matches: MatchResult[];
  partialMatches: MatchResult[];
}

/**
 * Алгоритм поиска совпадений в голосовании
 * @param votes - массив всех голосов участников
 * @param films - массив фильмов в группе
 * @param participants - список участников группы
 * @returns статистика матчинга
 */
export function findMatches(
  votes: Vote[],
  films: Film[],
  participants: string[]
): MatchingStats {
  const totalParticipants = participants.length;
  const votedParticipants = new Set(votes.map(v => v.participantId)).size;
  const totalFilms = films.length;

  // Группируем голоса по фильмам
  const votesByFilm = new Map<number, Vote[]>();
  votes.forEach(vote => {
    if (!votesByFilm.has(vote.filmId)) {
      votesByFilm.set(vote.filmId, []);
    }
    votesByFilm.get(vote.filmId)!.push(vote);
  });

  const matches: MatchResult[] = [];
  const partialMatches: MatchResult[] = [];

  // Анализируем каждый фильм
  films.forEach(film => {
    const filmVotes = votesByFilm.get(parseInt(film.id.split('_')[1])) || [];
    
    if (filmVotes.length === 0) {
      return; // Фильм не голосовался
    }

    const likes = filmVotes.filter(v => v.vote === 'like').length;
    const dislikes = filmVotes.filter(v => v.vote === 'dislike').length;
    const totalVotes = likes + dislikes;
    
    // Участники, которые лайкнули этот фильм
    const likedParticipants = filmVotes
      .filter(v => v.vote === 'like')
      .map(v => v.participantId);

    const matchPercentage = (likes / totalParticipants) * 100;

    const matchResult: MatchResult = {
      film,
      participants: likedParticipants,
      matchPercentage,
      totalVotes,
      likes,
      dislikes
    };

    // Полное совпадение - все участники лайкнули
    if (likes === totalParticipants && dislikes === 0) {
      matches.push(matchResult);
    }
    // Частичное совпадение - больше 50% лайков
    else if (likes > dislikes && matchPercentage >= 50) {
      partialMatches.push(matchResult);
    }
  });

  // Сортируем по проценту совпадения
  matches.sort((a, b) => b.matchPercentage - a.matchPercentage);
  partialMatches.sort((a, b) => b.matchPercentage - a.matchPercentage);

  return {
    totalParticipants,
    votedParticipants,
    totalFilms,
    matches,
    partialMatches
  };
}

/**
 * Проверяет, завершено ли голосование всеми участниками
 */
export function isVotingComplete(
  votes: Vote[],
  participants: string[]
): boolean {
  const votedParticipants = new Set(votes.map(v => v.participantId));
  return votedParticipants.size === participants.length;
}

/**
 * Получает статистику голосования для конкретного участника
 */
export function getParticipantStats(
  votes: Vote[],
  participantId: string
): { totalVotes: number; likes: number; dislikes: number } {
  const participantVotes = votes.filter(v => v.participantId === participantId);
  
  return {
    totalVotes: participantVotes.length,
    likes: participantVotes.filter(v => v.vote === 'like').length,
    dislikes: participantVotes.filter(v => v.vote === 'dislike').length
  };
}
