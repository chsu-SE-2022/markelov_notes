'use client';

import React, { useState } from 'react';
import { motion } from 'framer-motion';
import { Button } from '@/components/ui/button';
import { Plus, Star, Clock, Globe, RotateCcw } from 'lucide-react';
import { KinopoiskFilm } from '@/services/kinopoisk';
import { filmUtils } from '@/services/kinopoisk';

interface FilmCardProps {
  film: KinopoiskFilm;
  onAdd?: (film: KinopoiskFilm) => void;
  showAddButton?: boolean;
  className?: string;
}

export default function FilmCard({ 
  film, 
  onAdd, 
  showAddButton = true, 
  className = '' 
}: FilmCardProps) {
  const [isFlipped, setIsFlipped] = useState(false);

  const handleAdd = () => {
    if (onAdd) {
      onAdd(film);
    }
  };

  const handleFlip = () => {
    setIsFlipped(!isFlipped);
  };

  return (
    <motion.div
      initial={{ opacity: 0, y: 20 }}
      animate={{ opacity: 1, y: 0 }}
      transition={{ duration: 0.3 }}
      className={`bg-gray-800 rounded-xl overflow-hidden shadow-lg hover:shadow-xl transition-shadow ${className}`}
    >
      {/* Контейнер для переворота */}
      <div className="relative aspect-[2/3] bg-gray-700 perspective-1000">
        <motion.div
          className="relative w-full h-full preserve-3d"
          animate={{ rotateY: isFlipped ? 180 : 0 }}
          transition={{ duration: 0.6, ease: "easeInOut" }}
        >
          {/* Передняя сторона - постер */}
          <div className="absolute inset-0 w-full h-full backface-hidden">
            <div 
              className="relative w-full h-full cursor-pointer group"
              onClick={handleFlip}
            >
              <img
                src={filmUtils.getPosterUrl(film)}
                alt={film.nameRu}
                className="w-full h-full object-cover transition-transform group-hover:scale-105"
                onError={(e) => {
                  const target = e.target as HTMLImageElement;
                  target.src = '/placeholder-poster.jpg';
                }}
              />
              
              {/* Рейтинг */}
              {film.ratingKinopoisk && (
                <div className="absolute top-2 right-2 bg-black bg-opacity-70 text-white px-2 py-1 rounded-lg flex items-center gap-1 text-sm">
                  <Star className="h-3 w-3 fill-yellow-400 text-yellow-400" />
                  {filmUtils.formatRating(film.ratingKinopoisk)}
                </div>
              )}

              {/* Индикатор переворота */}
              <div className="absolute bottom-2 left-2 bg-black bg-opacity-70 text-white px-2 py-1 rounded-lg text-xs opacity-0 group-hover:opacity-100 transition-opacity">
                <RotateCcw className="h-3 w-3 inline mr-1" />
                Нажмите для описания
              </div>
            </div>
          </div>

          {/* Задняя сторона - описание */}
          <div 
            className="absolute inset-0 w-full h-full backface-hidden rotate-y-180 bg-gradient-to-br from-gray-800 to-gray-900 p-4 flex flex-col justify-between cursor-pointer group"
            onClick={handleFlip}
          >
            <div className="flex-1 overflow-y-auto">
              <h3 className="font-bold text-white text-lg mb-2 line-clamp-2">
                {film.nameRu}
              </h3>
              
              {film.nameEn && film.nameEn !== film.nameRu && (
                <p className="text-gray-400 text-sm mb-3 line-clamp-1">
                  {film.nameEn}
                </p>
              )}

              {/* Описание */}
              <div className="mb-4">
                <h4 className="text-white text-sm font-semibold mb-2">Описание:</h4>
                <p className="text-gray-300 text-sm leading-relaxed">
                  {film.description || 'Описание не доступно'}
                </p>
              </div>

              {/* Дополнительная информация */}
              <div className="space-y-2 text-sm">
                <div className="flex items-center gap-2 text-gray-400">
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
            </div>

            {/* Подсказка для возврата */}
            <div className="flex justify-center mt-4">
              <div className="bg-black bg-opacity-50 text-white px-3 py-2 rounded-lg text-sm opacity-0 group-hover:opacity-100 transition-opacity">
                <RotateCcw className="h-4 w-4 inline mr-2" />
                Кликните для возврата к постеру
              </div>
            </div>
          </div>
        </motion.div>
      </div>

      {/* Кнопка добавления (всегда видима) */}
      {showAddButton && onAdd && (
        <div className="p-4">
          <Button
            onClick={handleAdd}
            className="w-full bg-pink-600 hover:bg-pink-700 text-white"
          >
            <Plus className="h-4 w-4 mr-2" />
            Добавить в группу
          </Button>
        </div>
      )}
    </motion.div>
  );
}
