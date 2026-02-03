'use client';

import React, { useState, useEffect } from 'react';
import { motion } from 'framer-motion';
import { ArrowLeft, Users, Trophy, Heart, X, RotateCcw, CheckCircle, AlertCircle } from 'lucide-react';
import { Button } from '@/components/ui/button';
import { findMatches, MatchingStats, Vote } from '@/lib/matching';
import { Film } from '@/lib/groups';
import { Film as DatabaseFilm } from '@/lib/database';
import { useGroupSocket } from '@/hooks/useSocket';

interface ResultsPageClientProps {
  groupCode: string;
}

export default function ResultsPageClient({ groupCode }: ResultsPageClientProps) {
  const [group, setGroup] = useState<{ participants: string[]; films: Film[]; createdBy?: string } | null>(null);
  const [votes, setVotes] = useState<Vote[]>([]);
  const [matchingStats, setMatchingStats] = useState<MatchingStats | null>(null);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  
  // Получаем никнейм из URL или sessionStorage
  const getParticipantName = (): string => {
    if (typeof window !== 'undefined') {
      const urlParams = new URLSearchParams(window.location.search);
      const nicknameFromUrl = urlParams.get('nickname');
      
      if (nicknameFromUrl) {
        sessionStorage.setItem(`nickname_${groupCode}`, nicknameFromUrl);
        return nicknameFromUrl;
      }
      
      const nicknameFromStorage = sessionStorage.getItem(`nickname_${groupCode}`);
      return nicknameFromStorage || 'Участник';
    }
    return 'Участник';
  };

  // Загрузка данных группы и голосов
  useEffect(() => {
    const loadData = async () => {
      try {
        setIsLoading(true);
        
        // Нормализуем код группы
        const normalizedCode = groupCode?.toUpperCase().trim() || groupCode;
        
        // Загружаем данные группы
        const groupResponse = await fetch(`/api/groups-firebase?code=${encodeURIComponent(normalizedCode)}`);
        const groupData = await groupResponse.json();
        
        if (!groupData.success) {
          setError(groupData.error || 'Группа не найдена');
          return;
        }

        setGroup(groupData.data);

        // Загружаем голоса
        const votesResponse = await fetch(`/api/groups-firebase/${normalizedCode}/votes`);
        const votesData = await votesResponse.json();
        
        if (votesData.success) {
          setVotes(votesData.data.votes || []);
        }

        // Вычисляем совпадения и результаты
        if (groupData.data.films && groupData.data.participants) {
          const votes = votesData.data.votes || [];
          const films = groupData.data.films;
          const participants = groupData.data.participants;
          
          // Проверяем SUPER MATCH: все участники выбрали один фильм
          const votesByFilm = new Map<number, { likes: number; dislikes: number; voters: string[] }>();
          votes.forEach((vote: Vote) => {
            const filmId = Number(vote.filmId);
            if (!votesByFilm.has(filmId)) {
              votesByFilm.set(filmId, { likes: 0, dislikes: 0, voters: [] });
            }
            const filmVotes = votesByFilm.get(filmId)!;
            if (vote.vote === 'like') {
              filmVotes.likes++;
            } else {
              filmVotes.dislikes++;
            }
            if (!filmVotes.voters.includes(vote.participantId)) {
              filmVotes.voters.push(vote.participantId);
            }
          });

          // Находим SUPER MATCH и лучший фильм
          let superMatch: any = null;
          let bestMatch: any = null;

          films.forEach((film: DatabaseFilm) => {
            const filmVotes = votesByFilm.get(Number(film.kinopoiskId));
            if (!filmVotes) return;

            // SUPER MATCH: все участники лайкнули
            if (filmVotes.likes === participants.length && filmVotes.dislikes === 0) {
              superMatch = { film, voters: filmVotes.voters, likes: filmVotes.likes };
            }

            // Лучший фильм по количеству лайков
            if (!bestMatch || filmVotes.likes > bestMatch.likes) {
              bestMatch = { film, likes: filmVotes.likes, dislikes: filmVotes.dislikes, voters: filmVotes.voters };
            }
          });

          // Создаем расширенную статистику
          const stats = findMatches(votes, films, participants);
          setMatchingStats({
            ...(stats as any),
            superMatch,
            bestMatch
          } as any);
        }

      } catch (err) {
        setError('Ошибка загрузки данных');
        console.error('Ошибка загрузки данных:', err);
      } finally {
        setIsLoading(false);
      }
    };

    loadData();
  }, [groupCode]);

  // Удаляем фильмы и голоса после загрузки результатов (с задержкой, чтобы результаты успели отобразиться)
  useEffect(() => {
    if (!isLoading && matchingStats) {
      // Удаляем через 30 секунд после показа результатов (достаточно времени для просмотра)
      const cleanupTimer = setTimeout(async () => {
        try {
          const response = await fetch(`/api/groups-firebase/${groupCode}/cleanup`, {
            method: 'POST',
          });
          
          if (!response.ok) {
            console.error('Ошибка очистки данных группы:', await response.text());
          } else {
            console.log('Данные группы (фильмы и голоса) успешно удалены');
          }
        } catch (error) {
          console.error('Ошибка при очистке данных группы:', error);
        }
      }, 30000); // 30 секунд задержка
      
      return () => clearTimeout(cleanupTimer);
    }
  }, [isLoading, matchingStats, groupCode]);

  // Инициализируем сокет для возможности широковещательного сброса
  const { resetGroup } = useGroupSocket(groupCode, getParticipantName());

  const handleNewVoting = async () => {
    // Создатель запускает сброс через сокет — сервер очистит фильмы/голоса и сообщит всем
    resetGroup();
  };

  if (isLoading) {
    return (
      <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 flex items-center justify-center">
        <div className="text-center">
          <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-pink-500 mx-auto mb-4"></div>
          <p className="text-white text-lg">Анализ результатов...</p>
        </div>
      </div>
    );
  }

  if (error) {
    return (
      <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 flex items-center justify-center">
        <div className="text-center max-w-md mx-auto px-4">
          <AlertCircle className="h-16 w-16 text-red-500 mx-auto mb-4" />
          <h1 className="text-2xl font-bold text-white mb-4">Ошибка</h1>
          <p className="text-gray-300 mb-6">{error}</p>
          <Button
            onClick={() => window.location.href = '/'}
            className="bg-pink-600 hover:bg-pink-700"
          >
            <ArrowLeft className="h-4 w-4 mr-2" />
            На главную
          </Button>
        </div>
      </div>
    );
  }

  if (!matchingStats) {
    return (
      <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 flex items-center justify-center">
        <div className="text-center max-w-md mx-auto px-4">
          <AlertCircle className="h-16 w-16 text-yellow-500 mx-auto mb-4" />
          <h1 className="text-2xl font-bold text-white mb-4">Нет данных</h1>
          <p className="text-gray-300 mb-6">
            Не удалось загрузить результаты голосования.
          </p>
          <Button
            onClick={() => window.location.href = '/'}
            className="bg-pink-600 hover:bg-pink-700"
          >
            <ArrowLeft className="h-4 w-4 mr-2" />
            На главную
          </Button>
        </div>
      </div>
    );
  }

  const hasPerfectMatch = matchingStats.matches.length > 0;
  const hasPartialMatch = matchingStats.partialMatches.length > 0;

  return (
    <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 text-white">
      {/* Заголовок */}
      <div className="container mx-auto px-4 py-4 md:py-6">
        <div className="flex flex-col md:flex-row md:items-center md:justify-center gap-4 mb-6 md:mb-8">
          <div className="text-center md:text-left md:flex-1 md:px-4">
            <h1 className="text-2xl md:text-3xl font-bold">Результаты голосования</h1>
          </div>
        </div>

        {/* Результаты */}
        {matchingStats && (matchingStats as any).superMatch ? (
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            className="mb-8"
          >
            <h2 className="text-2xl md:text-4xl font-bold text-yellow-400 mb-6 flex flex-col md:flex-row items-center justify-center gap-2 md:gap-3">
              <Trophy className="h-6 w-6 md:h-8 md:w-8" />
              <span className="text-center whitespace-nowrap">🎉 СУПЕР СОВПАДЕНИЕ! 🎉</span>
            </h2>
            
            <div className="bg-gradient-to-r from-yellow-900 via-yellow-800 to-yellow-900 rounded-2xl p-6 md:p-8 border-4 border-yellow-500 shadow-2xl">
              {/* Постер */}
              <div className="flex justify-center mb-6">
                <img
                  src={(matchingStats as any).superMatch.film.poster || '/placeholder-poster.jpg'}
                  alt={(matchingStats as any).superMatch.film.title}
                  className="w-48 md:w-40 h-72 md:h-60 object-cover rounded-xl shadow-lg"
                  onError={(e) => {
                    const target = e.target as HTMLImageElement;
                    target.src = '/placeholder-poster.jpg';
                  }}
                />
              </div>
              
              {/* Информация о фильме */}
              <div className="text-center md:text-left">
                <h3 className="text-2xl md:text-3xl font-bold text-white mb-2">{(matchingStats as any).superMatch.film.title}</h3>
                <p className="text-yellow-200 text-lg md:text-xl mb-6">{(matchingStats as any).superMatch.film.year}</p>
                
                <div className="bg-yellow-700 bg-opacity-70 rounded-lg p-4 mb-6">
                  <p className="text-yellow-100 text-base md:text-lg font-semibold">
                    ✨ Все {(matchingStats as any).superMatch.voters.length} участников выбрали этот фильм!
                  </p>
                </div>
                
                {(matchingStats as any).superMatch.film.description && (
                  <div className="mt-6">
                    <p className="text-gray-200 text-sm md:text-base leading-relaxed">{(matchingStats as any).superMatch.film.description}</p>
                  </div>
                )}
              </div>
            </div>
          </motion.div>
        ) : matchingStats && (matchingStats as any).bestMatch ? (
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            className="mb-8"
          >
            <h2 className="text-2xl font-bold text-pink-400 mb-6 flex items-center">
              <Trophy className="h-6 w-6 mr-2" />
              🎬 Лучший выбор группы
            </h2>
            
            <div className="bg-gradient-to-r from-pink-900 to-pink-800 rounded-2xl p-6 border border-pink-600">
              {/* Постер */}
              <div className="flex justify-center mb-6">
                <img
                  src={(matchingStats as any).bestMatch.film.poster || '/placeholder-poster.jpg'}
                  alt={(matchingStats as any).bestMatch.film.title}
                  className="w-48 md:w-32 h-72 md:h-48 object-cover rounded-xl shadow-lg"
                  onError={(e) => {
                    const target = e.target as HTMLImageElement;
                    target.src = '/placeholder-poster.jpg';
                  }}
                />
              </div>
              
              {/* Информация о фильме */}
              <div className="text-center md:text-left">
                <h3 className="text-xl md:text-2xl font-bold text-white mb-2">{(matchingStats as any).bestMatch.film.title}</h3>
                <p className="text-pink-200 text-base md:text-lg mb-4">{(matchingStats as any).bestMatch.film.year}</p>
                
                <div className="flex items-center justify-center md:justify-start gap-4 mb-4">
                  <div className="flex items-center gap-2 text-pink-400">
                    <Heart className="h-5 w-5 fill-current" />
                    <span className="font-semibold">{(matchingStats as any).bestMatch.likes} лайков</span>
                  </div>
                  <div className="flex items-center gap-2 text-gray-400">
                    <X className="h-5 w-5" />
                    <span>{(matchingStats as any).bestMatch.dislikes} дизлайков</span>
                  </div>
                </div>
                
                <div className="bg-pink-700 bg-opacity-50 rounded-lg p-3 mb-6">
                  <p className="text-pink-200 text-sm">
                    <strong>{(matchingStats as any).bestMatch.likes} из {matchingStats.totalParticipants} участников выбрали этот фильм</strong>
                  </p>
                </div>
                
                {(matchingStats as any).bestMatch.film.description && (
                  <div className="mt-6">
                    <p className="text-gray-300 text-sm md:text-base leading-relaxed">{(matchingStats as any).bestMatch.film.description}</p>
                  </div>
                )}
              </div>
            </div>
          </motion.div>
        ) : hasPerfectMatch ? (
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            className="mb-8"
          >
            <h2 className="text-2xl font-bold text-green-400 mb-6 flex items-center">
              <Trophy className="h-6 w-6 mr-2" />
              🎉 Идеальные совпадения!
            </h2>
            
            <div className="space-y-6">
              {matchingStats.matches.map((match, index) => (
                <div key={match.film.id} className="bg-gradient-to-r from-green-900 to-green-800 rounded-2xl p-6 border border-green-600">
                  {/* Постер фильма */}
                  <div className="flex justify-center mb-6">
                    <img
                      src={match.film.poster || '/placeholder-poster.jpg'}
                      alt={match.film.title}
                      className="w-48 md:w-32 h-72 md:h-48 object-cover rounded-xl shadow-lg"
                      onError={(e) => {
                        const target = e.target as HTMLImageElement;
                        target.src = '/placeholder-poster.jpg';
                      }}
                    />
                  </div>
                  
                  {/* Информация о фильме */}
                  <div className="text-center md:text-left">
                    <h3 className="text-xl md:text-2xl font-bold text-white mb-2">{match.film.title}</h3>
                    <p className="text-green-200 text-base md:text-lg mb-4">{match.film.year}</p>
                    
                    <div className="flex items-center justify-center md:justify-start gap-4 mb-4">
                      <div className="flex items-center gap-2 text-green-400">
                        <Heart className="h-5 w-5 fill-current" />
                        <span className="font-semibold">{match.likes} лайков</span>
                      </div>
                      <div className="flex items-center gap-2 text-gray-400">
                        <X className="h-5 w-5" />
                        <span>{match.dislikes} дизлайков</span>
                      </div>
                    </div>
                    
                    <div className="bg-green-700 bg-opacity-50 rounded-lg p-3 mb-6">
                      <p className="text-green-200 text-sm">
                        <strong>
                          {match.participants.length === 1 
                            ? 'Вы выбрали этот фильм!' 
                            : `Все участники (${match.participants.length}) выбрали этот фильм!`}
                        </strong>
                      </p>
                    </div>
                    
                    {match.film.description && (
                      <div className="mt-6">
                        <p className="text-gray-300 text-sm md:text-base leading-relaxed">{match.film.description}</p>
                      </div>
                    )}
                  </div>
                </div>
              ))}
            </div>
          </motion.div>
        ) : hasPartialMatch ? (
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            className="mb-8"
          >
            <h2 className="text-2xl font-bold text-yellow-400 mb-6 flex items-center">
              <Trophy className="h-6 w-6 mr-2" />
              🤝 Частичные совпадения
            </h2>
            
            <div className="space-y-4">
              {matchingStats.partialMatches.map((match, index) => (
                <div key={match.film.id} className="bg-gradient-to-r from-yellow-900 to-yellow-800 rounded-2xl p-6 border border-yellow-600">
                  <div className="flex items-start gap-6">
                    <img
                      src={match.film.poster || '/placeholder-poster.jpg'}
                      alt={match.film.title}
                      className="w-24 h-36 object-cover rounded-xl shadow-lg"
                      onError={(e) => {
                        const target = e.target as HTMLImageElement;
                        target.src = '/placeholder-poster.jpg';
                      }}
                    />
                    
                    <div className="flex-1">
                      <h3 className="text-xl font-bold text-white mb-2">{match.film.title}</h3>
                      <p className="text-yellow-200 mb-2">{match.film.year}</p>
                      
                      <div className="flex items-center gap-4 mb-3">
                        <div className="flex items-center gap-2 text-yellow-400">
                          <Heart className="h-4 w-4 fill-current" />
                          <span className="font-semibold">{match.likes} лайков</span>
                        </div>
                        <div className="flex items-center gap-2 text-gray-400">
                          <X className="h-4 w-4" />
                          <span>{match.dislikes} дизлайков</span>
                        </div>
                      </div>
                      
                      <div className="bg-yellow-700 bg-opacity-50 rounded-lg p-3">
                        <p className="text-yellow-200 text-sm">
                          <strong>{Math.round(match.matchPercentage)}%</strong> участников выбрали этот фильм
                        </p>
                      </div>
                    </div>
                  </div>
                </div>
              ))}
            </div>
          </motion.div>
        ) : (
          <motion.div
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            className="text-center py-12"
          >
            <AlertCircle className="h-16 w-16 text-gray-500 mx-auto mb-4" />
            <h2 className="text-2xl font-bold text-white mb-4">Совпадений не найдено</h2>
            <p className="text-gray-400 mb-6">
              {matchingStats.totalParticipants === 1
                ? 'Вы не выбрали ни одного фильма, который вам понравился.'
                : 'К сожалению, не удалось найти фильм, который понравился бы всем участникам.'}
            </p>
            <p className="text-gray-500 text-sm">
              Попробуйте добавить больше фильмов или начать новое голосование.
            </p>
          </motion.div>
        )}

        {/* Кнопки действий */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.2 }}
          className="flex justify-center"
        >
          {group && getParticipantName() === (group.createdBy || '') && (
            <Button
              onClick={handleNewVoting}
              className="bg-pink-600 hover:bg-pink-700 text-white px-8 py-3"
            >
              <RotateCcw className="h-5 w-5 mr-2" />
              Начать новое голосование
            </Button>
          )}
        </motion.div>
      </div>
    </div>
  );
}
