import { NextApiRequest } from 'next';
import { NextApiResponseServerIO } from '@/lib/socket';
import { Server as SocketIOServer } from 'socket.io';
import { addFilmToGroup, getFilmsByGroup, getGroupByCode, getVotesByGroup, deleteGroup, deleteFilmsByGroup, deleteVotesByGroup, updateGroup, Film, Vote } from '@/lib/database';
import { addParticipantToGroup, removeParticipantFromGroup, getGroupParticipants, addSocketToGroup, removeSocketFromGroup } from '@/lib/socket';

// Интерфейс для результатов голосования
interface VotingResults {
  superMatch: { film: Film; voters: string[] } | null;
  bestMatch: { film: Film; likes: number; voters: string[] } | null;
  totalParticipants: number;
  votedParticipants: number;
}

// Функция для вычисления результатов голосования
function calculateResults(votes: Vote[], films: Film[], participants: string[]): VotingResults {
  // Группируем голоса по фильмам
  const votesByFilm = new Map<number, { likes: number; dislikes: number; voters: string[] }>();
  
  votes.forEach(vote => {
    if (!votesByFilm.has(vote.filmId)) {
      votesByFilm.set(vote.filmId, { likes: 0, dislikes: 0, voters: [] });
    }
    const filmVotes = votesByFilm.get(vote.filmId)!;
    if (vote.vote === 'like') {
      filmVotes.likes++;
    } else {
      filmVotes.dislikes++;
    }
    if (!filmVotes.voters.includes(vote.participantId)) {
      filmVotes.voters.push(vote.participantId);
    }
  });

  let superMatch: { film: Film; voters: string[] } | null = null;
  let bestMatch: { film: Film; likes: number; voters: string[] } | null = null;

  films.forEach(film => {
    const filmVotes = votesByFilm.get(film.kinopoiskId);
    if (!filmVotes) return;

    // Проверяем SUPER MATCH: все участники лайкнули
    if (filmVotes.likes === participants.length && filmVotes.dislikes === 0) {
      superMatch = { film, voters: filmVotes.voters };
    }

    // Ищем фильм с наибольшим количеством лайков
    if (!bestMatch || filmVotes.likes > bestMatch.likes) {
      bestMatch = { film, likes: filmVotes.likes, voters: filmVotes.voters };
    }
  });

  return {
    superMatch,
    bestMatch,
    totalParticipants: participants.length,
    votedParticipants: votes.length > 0 ? new Set(votes.map(v => v.participantId)).size : 0
  };
}

export default function SocketHandler(req: NextApiRequest, res: NextApiResponseServerIO) {
  if (res.socket.server.io) {
    console.log('Socket is already running');
    res.end();
    return;
  }

  console.log('Socket is initializing');
  const io = new SocketIOServer(res.socket.server, {
    path: '/api/socket',
    addTrailingSlash: false,
    cors: {
      origin: '*', // Разрешаем подключения с любых доменов (для разработки и локальной сети)
      methods: ['GET', 'POST'],
      credentials: true,
    },
    transports: ['websocket', 'polling'],
  });

  res.socket.server.io = io;

  io.on('connection', (socket) => {
    console.log('New client connected:', socket.id);

    // Подключение к группе
    socket.on('group:join', async (data) => {
      try {
        const { groupCode, participantName } = data;
        
        // Проверяем, существует ли группа
        const group = await getGroupByCode(groupCode);
        if (!group) {
          socket.emit('notification:error', { message: 'Группа не найдена' });
          return;
        }

        // Получаем список участников из базы данных (включая создателя)
        const dbParticipants = group.participants || [];
        
        // ВАЖНО: Проверяем ДО добавления, было ли уже активное WebSocket соединение для этого участника
        // Если участник уже был в активных WebSocket соединениях - это переподключение
        // Если нет - это новое присоединение (даже если он уже в БД, он только что добавился через API)
        const currentWebSocketParticipants = getGroupParticipants(groupCode);
        const wasAlreadyConnected = currentWebSocketParticipants.includes(participantName);
        
        // Добавляем участника в группу (в память для WebSocket), если еще не добавлен
        if (!wasAlreadyConnected) {
          addParticipantToGroup(groupCode, participantName);
        }
        addSocketToGroup(groupCode, socket.id);
        
        // Сохраняем данные в socket
        socket.data.groupCode = groupCode;
        socket.data.participantName = participantName;

        // Присоединяем socket к комнате группы
        socket.join(groupCode);

        // Обновляем список других участников из БД в памяти WebSocket
        dbParticipants.forEach(p => {
          if (!getGroupParticipants(groupCode).includes(p)) {
            addParticipantToGroup(groupCode, p);
          }
        });

        // Обновляем финальный список участников
        const finalParticipants = Array.from(new Set([
          ...dbParticipants,
          ...getGroupParticipants(groupCode)
        ]));

        // Уведомляем других участников группы только если это новое WebSocket соединение
        // (не переподключение существующего участника)
        if (!wasAlreadyConnected) {
          socket.to(groupCode).emit('group:participant-joined', {
            participant: participantName,
            participants: finalParticipants
          });
        }

        // Отправляем текущий список участников (всегда, чтобы синхронизировать состояние)
        socket.emit('group:participant-joined', {
          participant: participantName,
          participants: finalParticipants
        });

        // Загружаем и отправляем текущие фильмы новому участнику
        try {
          const films = await getFilmsByGroup(group.id);
          socket.emit('group:film-added', {
            films: films.map(f => ({
              id: f.id,
              kinopoiskId: f.kinopoiskId,
              title: f.title,
              year: f.year,
              poster: f.poster,
              description: f.description,
              rating: f.rating,
              addedBy: f.addedBy,
              addedAt: f.addedAt
            }))
          });
        } catch (error) {
          console.error('Error loading initial films:', error);
        }

        console.log(`Participant ${participantName} joined group ${groupCode}`);
      } catch (error) {
        console.error('Error joining group:', error);
        socket.emit('notification:error', { message: 'Ошибка присоединения к группе' });
      }
    });

    // Покидание группы
    socket.on('group:leave', (data) => {
      const { groupCode, participantName } = data;
      
      removeParticipantFromGroup(groupCode, participantName);
      removeSocketFromGroup(groupCode, socket.id);
      
      socket.leave(groupCode);
      
      // Уведомляем остальных участников
      const participants = getGroupParticipants(groupCode);
      socket.to(groupCode).emit('group:participant-left', {
        participant: participantName,
        participants
      });

      console.log(`Participant ${participantName} left group ${groupCode}`);
    });

    // Добавление фильма
    socket.on('film:add', async (data) => {
      try {
        const { groupCode, film } = data;
        
        // Добавляем фильм в базу данных
        const group = await getGroupByCode(groupCode);
        if (!group) {
          socket.emit('notification:error', { message: 'Группа не найдена' });
          return;
        }

        await addFilmToGroup({
          groupId: group.id,
          kinopoiskId: film.kinopoiskId,
          title: film.nameRu,
          year: film.year,
          poster: film.posterUrl,
          description: film.description,
          rating: film.ratingKinopoisk,
          addedBy: socket.data.participantName || 'Участник'
        });

        // Получаем обновленный список фильмов
        const films = await getFilmsByGroup(group.id);

        // Уведомляем всех участников группы
        io.to(groupCode).emit('group:film-added', {
          film,
          films
        });

        console.log(`Film added to group ${groupCode}:`, film.nameRu);
      } catch (error) {
        console.error('Error adding film:', error);
        socket.emit('notification:error', { 
          message: error instanceof Error ? error.message : 'Ошибка добавления фильма' 
        });
      }
    });

    // Начало голосования (только создатель может начать)
    socket.on('voting:start', async (data) => {
      try {
        const { groupCode, films } = data;
        
        // Проверяем, существует ли группа и является ли пользователь создателем
        const group = await getGroupByCode(groupCode);
        if (!group) {
          socket.emit('notification:error', { message: 'Группа не найдена' });
          return;
        }

        // Проверяем, является ли пользователь создателем группы
        if (group.createdBy !== socket.data.participantName) {
          socket.emit('notification:error', { message: 'Только создатель группы может начать голосование' });
          return;
        }

        // Уведомляем всех участников группы о начале голосования
        io.to(groupCode).emit('voting:started', { films });

        console.log(`Voting started in group ${groupCode} by ${socket.data.participantName}`);
      } catch (error) {
        console.error('Error starting voting:', error);
        socket.emit('notification:error', { message: 'Ошибка начала голосования' });
      }
    });

    // Сброс голосования и очистка фильмов/голосов (только создатель)
    socket.on('group:reset', async (data: { groupCode: string }) => {
      try {
        const { groupCode } = data;
        const requester = socket.data.participantName;
        if (!groupCode || !requester) return;

        const group = await getGroupByCode(groupCode);
        if (!group) {
          socket.emit('notification:error', { message: 'Группа не найдена' });
          return;
        }

        if (group.createdBy !== requester) {
          socket.emit('notification:error', { message: 'Только создатель может начать новое голосование' });
          return;
        }

        await deleteFilmsByGroup(group.id);
        await deleteVotesByGroup(group.id);

        io.to(groupCode).emit('group:reset', { message: 'Голосование сброшено создателем' });
      } catch (error) {
        console.error('Error resetting group:', error);
        socket.emit('notification:error', { message: 'Не удалось сбросить голосование' });
      }
    });

    // Голосование
    socket.on('voting:vote', (data) => {
      const { groupCode, filmId, vote } = data;
      
      // Уведомляем всех участников группы о голосе
      socket.to(groupCode).emit('voting:vote-cast', {
        participant: socket.data.participantName,
        filmId,
        vote
      });

      console.log(`Vote cast in group ${groupCode}: ${socket.data.participantName} voted ${vote} for film ${filmId}`);
    });

    // Завершение голосования участником
    socket.on('voting:completed', async (data) => {
      try {
        const { groupCode, participantName } = data;
        
        // Проверяем, все ли участники завершили голосование
        const group = await getGroupByCode(groupCode);
        if (!group) {
          return;
        }

        const allParticipants = Array.from(new Set([
          ...group.participants,
          ...getGroupParticipants(groupCode)
        ]));
        
        // Проверяем голоса в базе данных
        const votes = await getVotesByGroup(group.id);
        const films = await getFilmsByGroup(group.id);
        
        // Считаем, сколько фильмов проголосовано каждым участником
        const votesByParticipant = new Map<string, Set<number>>();
        votes.forEach(vote => {
          if (!votesByParticipant.has(vote.participantId)) {
            votesByParticipant.set(vote.participantId, new Set());
          }
          votesByParticipant.get(vote.participantId)!.add(vote.filmId);
        });

        // Добавляем текущего участника (предполагаем, что он проголосовал за все фильмы)
        // Нужно проверить реально через API, но пока считаем, что если он сохранил голоса, то завершил
        const completedParticipants = new Set<string>(votesByParticipant.keys());
        completedParticipants.add(participantName);

        console.log(`Voting completed by ${participantName} in group ${groupCode}`);
        console.log(`Participants: ${allParticipants.join(', ')}`);
        console.log(`Completed: ${Array.from(completedParticipants).join(', ')}`);
        console.log(`Progress: ${completedParticipants.size}/${allParticipants.length}`);

        // Если все участники завершили голосование (проголосовали за все фильмы)
        // Проверяем, что каждый участник проголосовал за каждый фильм
        const allCompleted = allParticipants.every(participant => {
          const participantVotes = votesByParticipant.get(participant);
          // Если это текущий участник, который только что завершил, считаем его завершившим
          if (participant === participantName) return true;
          // Иначе проверяем, что он проголосовал за все фильмы
          return participantVotes && participantVotes.size === films.length;
        });

        if (allCompleted && completedParticipants.size >= allParticipants.length) {
          // Вычисляем результаты (films уже загружены выше)
          const results = calculateResults(votes, films, allParticipants);
          
          // Уведомляем всех участников
          io.to(groupCode).emit('voting:all-completed', { results });
          
          console.log(`All participants completed voting in group ${groupCode}`);
        } else {
          // Уведомляем всех о прогрессе (включая отправителя)
          io.to(groupCode).emit('voting:completed', { participant: participantName });
        }
      } catch (error) {
        console.error('Error processing voting completion:', error);
      }
    });

    // Отключение клиента
    socket.on('disconnect', async () => {
      const { groupCode, participantName } = socket.data;
      
      if (groupCode && participantName) {
        try {
          // Получаем информацию о группе из базы данных
          const group = await getGroupByCode(groupCode);
          
          if (group) {
            // Проверяем, является ли отключившийся участник создателем группы
            if (group.createdBy === participantName) {
              // Получаем список участников из базы данных
              const dbParticipants = group.participants || [];
              
              // Удаляем создателя из списка участников
              const remainingParticipants = dbParticipants.filter(p => p !== participantName);
              
              // Если есть другие участники, передаем права создателя следующему участнику
              if (remainingParticipants.length > 0) {
                const newCreator = remainingParticipants[0]; // Первый участник после создателя
                
                // Обновляем группу в базе данных: убираем создателя из участников и назначаем нового создателя
                await updateGroup(group.id, {
                  participants: remainingParticipants,
                  createdBy: newCreator
                });
                
                console.log(`Creator ${participantName} left, transferred ownership to ${newCreator} in group ${groupCode}`);
                
                // Уведомляем всех участников об изменении создателя
                io.to(groupCode).emit('group:creator-changed', {
                  newCreator,
                  message: `${newCreator} теперь создатель группы`
                });
              } else {
                // Если больше нет участников, удаляем группу
                console.log(`Creator ${participantName} left and no participants remain, deleting group ${groupCode}`);
                await deleteGroup(group.id);
                
                io.to(groupCode).emit('group:closed', {
                  message: 'Группа была закрыта, так как все участники покинули её'
                });
              }
            } else {
              // Обычный участник - просто удаляем из списка
              const dbParticipants = group.participants || [];
              const remainingParticipants = dbParticipants.filter(p => p !== participantName);
              
              // Обновляем список участников в базе данных
              await updateGroup(group.id, {
                participants: remainingParticipants
              });
            }
          }
          
          // Удаляем участника из памяти WebSocket
          removeParticipantFromGroup(groupCode, participantName);
          removeSocketFromGroup(groupCode, socket.id);
          
          // Уведомляем остальных участников об уходе
          const participants = getGroupParticipants(groupCode);
          socket.to(groupCode).emit('group:participant-left', {
            participant: participantName,
            participants
          });
        } catch (error) {
          console.error('Error handling disconnect:', error);
          // В случае ошибки все равно удаляем из памяти
          removeParticipantFromGroup(groupCode, participantName);
          removeSocketFromGroup(groupCode, socket.id);
        }

        console.log(`Participant ${participantName} disconnected from group ${groupCode}`);
      }
    });
  });

  res.end();
}
