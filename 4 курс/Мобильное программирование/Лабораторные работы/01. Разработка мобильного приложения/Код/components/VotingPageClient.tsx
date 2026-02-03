'use client';

import React, { useState, useEffect } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { ArrowLeft, Users, AlertCircle } from 'lucide-react';
import { Button } from '@/components/ui/button';
import VotingCard from '@/components/VotingCard';
import { KinopoiskFilm } from '@/services/kinopoisk';
import { Vote } from '@/lib/groups';
import { useGroupSocket } from '@/hooks/useSocket';
import WaitingForOthers from '@/components/WaitingForOthers';

interface VotingPageClientProps {
  groupCode: string;
}


export default function VotingPageClient({ groupCode }: VotingPageClientProps) {
  const [group, setGroup] = useState<{ participants: string[]; films: KinopoiskFilm[] } | null>(null);
  const [films, setFilms] = useState<KinopoiskFilm[]>([]);
  const [currentFilmIndex, setCurrentFilmIndex] = useState(0);
  const [votes, setVotes] = useState<Vote[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);
  const [isVotingComplete, setIsVotingComplete] = useState(false);
  const [votesSaved, setVotesSaved] = useState(false);
  const [completedParticipants, setCompletedParticipants] = useState<string[]>([]);

  // Получаем никнейм из URL или sessionStorage
  const participantName = typeof window !== 'undefined' 
    ? (() => {
        const urlParams = new URLSearchParams(window.location.search);
        const nicknameFromUrl = urlParams.get('nickname');
        
        if (nicknameFromUrl) {
          // Сохраняем никнейм в sessionStorage для последующего использования
          sessionStorage.setItem(`nickname_${groupCode}`, nicknameFromUrl);
          return nicknameFromUrl;
        }
        
        // Пробуем получить из sessionStorage
        const nicknameFromStorage = sessionStorage.getItem(`nickname_${groupCode}`);
        return nicknameFromStorage || 'Участник';
      })()
    : 'Участник';

  // Подключаемся к WebSocket для отслеживания завершения голосования
  const { completeVoting, isConnected, participants, completedParticipants: socketCompletedParticipants } = useGroupSocket(groupCode, participantName);

  // Загрузка данных группы
  useEffect(() => {
    const loadGroupData = async () => {
      try {
        setIsLoading(true);
        // Нормализуем код группы
        const normalizedCode = groupCode?.toUpperCase().trim();
        const response = await fetch(`/api/groups-firebase?code=${encodeURIComponent(normalizedCode)}`);
        const data = await response.json();
        
        if (data.success) {
          setGroup(data.data);
          // Преобразуем Film в KinopoiskFilm для голосования
          const filmsData = data.data.films || [];
          console.log('Загружено фильмов:', filmsData.length, filmsData);
          
          const kinopoiskFilms = filmsData.map((film: { id?: string; kinopoiskId: number; title: string; year: number; poster?: string; description?: string; rating?: number }) => ({
            kinopoiskId: film.kinopoiskId,
            nameRu: film.title,
            nameEn: film.title,
            year: film.year,
            posterUrl: film.poster,
            posterUrlPreview: film.poster,
            description: film.description,
            ratingKinopoisk: film.rating,
            ratingImdb: film.rating,
            genres: [],
            countries: [],
            duration: 0
          }));
          setFilms(kinopoiskFilms);
        } else {
          setError(data.error || 'Группа не найдена');
        }
      } catch (err) {
        setError('Ошибка загрузки группы');
        console.error('Ошибка загрузки группы:', err);
      } finally {
        setIsLoading(false);
      }
    };

    loadGroupData();
  }, [groupCode]);

  // Автоматическое сохранение голосов при завершении
  useEffect(() => {
    if (isVotingComplete && !votesSaved && votes.length > 0) {
      saveVotesAutomatically();
    }
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [isVotingComplete, votesSaved, votes.length]);

  // Обновляем список завершивших из WebSocket
  useEffect(() => {
    if (socketCompletedParticipants.length > 0) {
      // Объединяем с текущим пользователем, если его там нет
      const allCompleted = Array.from(new Set([participantName, ...socketCompletedParticipants]));
      setCompletedParticipants(allCompleted);
    } else if (votesSaved) {
      // Если голоса сохранены, добавляем текущего пользователя
      setCompletedParticipants([participantName]);
    }
  }, [socketCompletedParticipants, votesSaved, participantName]);

  // Автоматическое сохранение голосов
  const saveVotesAutomatically = async () => {
    if (votesSaved) return; // Предотвращаем повторное сохранение
    
    try {
      setVotesSaved(true);
      
      const normalizedGroupCode = groupCode?.toUpperCase().trim() || groupCode;
      
      console.log('Auto-saving votes:', {
        groupCode: normalizedGroupCode,
        participantName,
        votesCount: votes.length
      });

      // Сохраняем голоса через API
      const response = await fetch(`/api/groups-firebase/${normalizedGroupCode}/votes`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({ 
          votes: votes.map(v => ({
            filmId: v.filmId,
            vote: v.vote,
            participantId: participantName
          }))
        }),
      });

      if (!response.ok) {
        const errorData = await response.json().catch(() => ({ error: 'Ошибка сервера' }));
        console.error('HTTP error saving votes:', response.status, errorData);
        setError(errorData.error || 'Ошибка сохранения голосов');
        setVotesSaved(false); // Разрешаем повторную попытку
        return;
      }

      const data = await response.json();
      
      if (data.success) {
        console.log('Votes saved successfully');
        // Отправляем событие о завершении голосования через WebSocket
        if (isConnected && completeVoting) {
          completeVoting();
        }
      } else {
        console.error('Error saving votes:', data.error);
        setError(data.error || 'Ошибка сохранения голосов');
        setVotesSaved(false);
      }
    } catch (err) {
      console.error('Exception saving votes:', err);
      setError('Ошибка сохранения голосов: ' + (err instanceof Error ? err.message : 'Неизвестная ошибка'));
      setVotesSaved(false);
    }
  };

  // Обработка голоса
  const handleVote = (filmId: number, vote: 'like' | 'dislike') => {
    const newVote: Vote = {
      filmId,
      vote,
      timestamp: Date.now(),
      participantId: participantName // Используем никнейм из URL
    };

    setVotes(prev => [...prev, newVote]);
    
    // Переход к следующему фильму
    if (currentFilmIndex < films.length - 1) {
      setCurrentFilmIndex(prev => prev + 1);
    } else {
      // Голосование завершено - автоматически сохраним
      setIsVotingComplete(true);
    }
  };

  // Пропуск фильма (добавляем как dislike)
  const handleSkip = () => {
    if (currentFilmIndex < films.length) {
      const currentFilm = films[currentFilmIndex];
      if (currentFilm) {
        // При пропуске считаем как dislike
        handleVote(currentFilm.kinopoiskId, 'dislike');
      }
    }
  };

  // Возврат к предыдущему фильму
  const handlePrevious = () => {
    if (currentFilmIndex > 0) {
      setCurrentFilmIndex(prev => prev - 1);
    }
  };


  if (isLoading) {
    return (
      <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 flex items-center justify-center">
        <div className="text-center">
          <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-pink-500 mx-auto mb-4"></div>
          <p className="text-white text-lg">Загрузка голосования...</p>
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

  // Показываем ошибку только после завершения загрузки
  if (!isLoading && (!group || films.length === 0)) {
    return (
      <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 flex items-center justify-center">
        <div className="text-center max-w-md mx-auto px-4">
          <Users className="h-16 w-16 text-gray-500 mx-auto mb-4" />
          <h1 className="text-2xl font-bold text-white mb-4">Нет фильмов для голосования</h1>
          <p className="text-gray-300 mb-6">
            {error 
              ? `Ошибка: ${error}` 
              : 'В группе пока нет добавленных фильмов. Попросите участников добавить фильмы.'}
          </p>
          <Button
            onClick={() => {
              const nickname = sessionStorage.getItem(`nickname_${groupCode}`) || participantName;
              window.location.href = `/group/${groupCode}?nickname=${encodeURIComponent(nickname)}`;
            }}
            className="bg-pink-600 hover:bg-pink-700"
          >
            <ArrowLeft className="h-4 w-4 mr-2" />
            Вернуться к группе
          </Button>
        </div>
      </div>
    );
  }

  if (isVotingComplete) {
    // Показываем красивый экран ожидания вместо кнопки сохранения
    return (
      <WaitingForOthers
        completedCount={completedParticipants.length || 1} // Начинаем с 1, так как текущий пользователь завершил
        totalCount={participants.length || group?.participants?.length || 1}
      />
    );
  }

  const currentFilm = films[currentFilmIndex];
  const progress = ((currentFilmIndex + 1) / films.length) * 100;

  return (
    <div 
      className="h-screen overflow-hidden bg-gradient-to-b from-black via-gray-900 to-gray-800 text-white flex flex-col"
      style={{
        overscrollBehavior: 'none',
        WebkitOverscrollBehavior: 'none'
      }}
    >
      {/* Заголовок - фиксированный */}
      <div className="container mx-auto px-4 py-6 flex-shrink-0">
        <div className="flex items-center justify-between mb-6">
          <Button
            onClick={() => {
              const nickname = sessionStorage.getItem(`nickname_${groupCode}`) || participantName;
              window.location.href = `/group/${groupCode}?nickname=${encodeURIComponent(nickname)}`;
            }}
            variant="outline"
            className="text-gray-300 border-gray-600 hover:bg-gray-700"
          >
            <ArrowLeft className="h-4 w-4 mr-2" />
            Назад к группе
          </Button>
          
          <div className="text-center">
            <h1 className="text-2xl font-bold">Голосование</h1>
            <p className="text-gray-400">Группа: {groupCode}</p>
          </div>
          
          <div className="text-right">
            <p className="text-sm text-gray-400">
              {currentFilmIndex + 1} из {films.length}
            </p>
            <p className="text-xs text-gray-500">
              {votes.length} голосов
            </p>
          </div>
        </div>

        {/* Прогресс-бар */}
        <div className="w-full bg-gray-700 rounded-full h-2 mb-4">
          <motion.div
            className="bg-gradient-to-r from-pink-500 to-purple-500 h-2 rounded-full"
            initial={{ width: 0 }}
            animate={{ width: `${progress}%` }}
            transition={{ duration: 0.5 }}
          />
        </div>
      </div>

      {/* Карточка фильма и навигация - скроллируемая область */}
        <div className="flex-1 overflow-y-auto">
          <div className="container mx-auto px-4 py-6">
            <div className="flex justify-center">
              <AnimatePresence mode="wait">
                <motion.div
                  key={currentFilmIndex}
                  initial={{ opacity: 0, scale: 0.8 }}
                  animate={{ opacity: 1, scale: 1 }}
                  exit={{ opacity: 0, scale: 0.8 }}
                  transition={{ duration: 0.3 }}
                >
                  <VotingCard
                    film={currentFilm}
                    onVote={handleVote}
                    onSkip={handleSkip}
                  />
                </motion.div>
              </AnimatePresence>
            </div>

            {/* Навигация */}
            <div className="flex justify-center gap-4 mt-8">
              <Button
                onClick={handlePrevious}
                disabled={currentFilmIndex === 0}
                variant="outline"
                className="text-gray-300 border-gray-600 hover:bg-gray-700 disabled:opacity-50"
              >
                Предыдущий
              </Button>
              
              <div className="text-center">
                <p className="text-sm text-gray-400">
                  Свайпните влево (👎) или вправо (👍)
                </p>
                <p className="text-xs text-gray-500 mt-1">
                  Или используйте кнопки внизу
                </p>
              </div>
            </div>
          </div>
        </div>
    </div>
  );
}
