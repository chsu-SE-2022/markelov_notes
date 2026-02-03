'use client';

import React, { useState, useRef, useEffect } from 'react';
import { motion, PanInfo } from 'framer-motion';
import { Heart, X, Star, Globe, Clock, Info } from 'lucide-react';
import { KinopoiskFilm } from '@/services/kinopoisk';
import { filmUtils } from '@/services/kinopoisk';

interface VotingCardProps {
  film: KinopoiskFilm;
  onVote: (filmId: number, vote: 'like' | 'dislike') => void;
  onSkip?: () => void;
  className?: string;
}

export default function VotingCard({ 
  film, 
  onVote, 
  onSkip,
  className = '' 
}: VotingCardProps) {
  const [showDescription, setShowDescription] = useState(false);
  const [dragDirection, setDragDirection] = useState<'left' | 'right' | null>(null);
  const descriptionRef = useRef<HTMLDivElement>(null);

  const handleDrag = (event: unknown, info: PanInfo) => {
    const threshold = 50;
    
    if (info.offset.x > threshold) {
      setDragDirection('right');
    } else if (info.offset.x < -threshold) {
      setDragDirection('left');
    } else {
      setDragDirection(null);
    }
  };

  const handleDragEnd = (event: unknown, info: PanInfo) => {
    const threshold = 100;
    
    if (info.offset.x > threshold) {
      onVote(film.kinopoiskId, 'like');
    } else if (info.offset.x < -threshold) {
      onVote(film.kinopoiskId, 'dislike');
    }
    
    setDragDirection(null);
  };

  const handleLike = () => {
    onVote(film.kinopoiskId, 'like');
  };

  const handleDislike = () => {
    onVote(film.kinopoiskId, 'dislike');
  };

  // Прокрутка к описанию на мобильных устройствах
  useEffect(() => {
    if (showDescription && descriptionRef.current) {
      // Проверяем, что это мобильное устройство
      const isMobile = window.innerWidth < 768;
      
      if (isMobile) {
        // Небольшая задержка для завершения анимации появления
        setTimeout(() => {
          descriptionRef.current?.scrollIntoView({
            behavior: 'smooth',
            block: 'start',
          });
        }, 350); // Немного больше, чем длительность анимации (300ms)
      }
    }
  }, [showDescription]);


  return (
    <motion.div
      className={`relative w-full max-w-[280px] md:max-w-sm mx-auto ${className}`}
      drag="x"
      dragConstraints={{ left: 0, right: 0 }}
      dragElastic={0.2}
      onDrag={handleDrag}
      onDragEnd={handleDragEnd}
      animate={{
        x: dragDirection === 'left' ? -20 : dragDirection === 'right' ? 20 : 0,
        rotate: dragDirection === 'left' ? -5 : dragDirection === 'right' ? 5 : 0,
      }}
      transition={{ type: "spring", stiffness: 300, damping: 30 }}
    >
      {/* Карточка фильма */}
      <div className="relative aspect-[2/3] bg-gray-800 rounded-2xl overflow-hidden shadow-2xl max-h-[60vh] md:max-h-none">
        <div className="relative w-full h-full">
          <img
            src={filmUtils.getPosterUrl(film)}
            alt={film.nameRu}
            className="w-full h-full object-cover"
            onError={(e) => {
              const target = e.target as HTMLImageElement;
              target.src = '/placeholder-poster.jpg';
            }}
          />
          
          {/* Рейтинг */}
          {film.ratingKinopoisk && (
            <div className="absolute top-4 right-4 bg-black bg-opacity-70 text-white px-3 py-2 rounded-xl flex items-center gap-2 text-lg font-bold">
              <Star className="h-5 w-5 fill-yellow-400 text-yellow-400" />
              {filmUtils.formatRating(film.ratingKinopoisk)}
            </div>
          )}


          {/* Индикаторы свайпа */}
          <div className="absolute inset-0 pointer-events-none">
            {/* Лайк индикатор */}
            <motion.div
              className="absolute top-1/2 left-8 transform -translate-y-1/2"
              animate={{
                opacity: dragDirection === 'right' ? 1 : 0,
                scale: dragDirection === 'right' ? 1.2 : 1,
              }}
              transition={{ duration: 0.2 }}
            >
              <div className="bg-green-500 text-white px-6 py-3 rounded-2xl text-2xl font-bold flex items-center gap-3 shadow-lg">
                <Heart className="h-8 w-8 fill-white" />
                ЛАЙК!
              </div>
            </motion.div>

            {/* Дизлайк индикатор */}
            <motion.div
              className="absolute top-1/2 right-8 transform -translate-y-1/2"
              animate={{
                opacity: dragDirection === 'left' ? 1 : 0,
                scale: dragDirection === 'left' ? 1.2 : 1,
              }}
              transition={{ duration: 0.2 }}
            >
              <div className="bg-red-500 text-white px-6 py-3 rounded-2xl text-2xl font-bold flex items-center gap-3 shadow-lg">
                <X className="h-8 w-8" />
                ПАСС!
              </div>
            </motion.div>
          </div>
        </div>
      </div>

      {/* Кнопки действий */}
      <div className="flex justify-center gap-6 mt-8">
        <motion.button
          onClick={handleDislike}
          className="w-16 h-16 bg-red-500 hover:bg-red-600 text-white rounded-full flex items-center justify-center shadow-lg transition-colors"
          whileHover={{ scale: 1.1 }}
          whileTap={{ scale: 0.9 }}
        >
          <X className="h-8 w-8" />
        </motion.button>

        <motion.button
          onClick={() => setShowDescription(!showDescription)}
          className="w-16 h-16 bg-gray-500 hover:bg-gray-600 text-white rounded-full flex items-center justify-center shadow-lg transition-colors"
          whileHover={{ scale: 1.1 }}
          whileTap={{ scale: 0.9 }}
          title="Информация о фильме"
        >
          <Info className="h-6 w-6" />
        </motion.button>

        <motion.button
          onClick={handleLike}
          className="w-16 h-16 bg-green-500 hover:bg-green-600 text-white rounded-full flex items-center justify-center shadow-lg transition-colors"
          whileHover={{ scale: 1.1 }}
          whileTap={{ scale: 0.9 }}
        >
          <Heart className="h-8 w-8" />
        </motion.button>
      </div>

      {/* Описание фильма */}
      {showDescription && (
        <motion.div
          ref={descriptionRef}
          initial={{ opacity: 0, height: 0 }}
          animate={{ opacity: 1, height: 'auto' }}
          exit={{ opacity: 0, height: 0 }}
          transition={{ duration: 0.3 }}
          className="mt-4 bg-gray-800 rounded-xl p-4"
        >
          <h3 className="font-bold text-white text-xl mb-2">
            {film.nameRu}
          </h3>
          
          {film.nameEn && film.nameEn !== film.nameRu && (
            <p className="text-gray-400 text-sm mb-3">
              {film.nameEn}
            </p>
          )}

          {/* Описание */}
          <p className="text-gray-200 text-sm md:text-base leading-relaxed mb-4">
            {film.description || 'Описание не доступно'}
          </p>

          {/* Дополнительная информация */}
          <div className="space-y-2 text-sm">
            <div className="flex items-center gap-3 text-gray-400">
              <Globe className="h-4 w-4" />
              <span>{film.year}</span>
              {film.duration && (
                <>
                  <span>•</span>
                  <Clock className="h-4 w-4" />
                  <span>{filmUtils.formatDuration(film.duration)}</span>
                </>
              )}
            </div>
            
            {film.genres && film.genres.length > 0 && (
              <div className="text-gray-400">
                <span className="font-medium">Жанры:</span> {filmUtils.formatGenres(film.genres)}
              </div>
            )}

            {film.countries && film.countries.length > 0 && (
              <div className="text-gray-400">
                <span className="font-medium">Страны:</span> {filmUtils.formatCountries(film.countries)}
              </div>
            )}
          </div>
        </motion.div>
      )}
    </motion.div>
  );
}
