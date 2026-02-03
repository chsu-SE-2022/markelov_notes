'use client';

import React, { useState } from 'react';
import { motion } from 'framer-motion';
import { Button } from '@/components/ui/button';
import { ArrowLeft, User, Sparkles } from 'lucide-react';

interface NicknameInputProps {
  onNicknameSubmit: (nickname: string) => void;
  onBack: () => void;
  title?: string;
  subtitle?: string;
}

export default function NicknameInput({ 
  onNicknameSubmit, 
  onBack, 
  title = "Введите ваш никнейм",
  subtitle = "Выберите имя, под которым вас будут видеть другие участники"
}: NicknameInputProps) {
  const [nickname, setNickname] = useState('');
  const [isSubmitting, setIsSubmitting] = useState(false);

  // Генерируем случайные предложения никнеймов
  const suggestedNicknames = [
    'Кинокритик', 'Фильмолюб', 'Киноман', 'Режиссер', 'Актер',
    'Сценарист', 'Продюсер', 'Оператор', 'Монтажер', 'Звукорежиссер',
    'Костюмер', 'Гример', 'Каскадер', 'Дублер', 'Статист',
    'Критик', 'Обозреватель', 'Блогер', 'Журналист', 'Редактор'
  ];

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!nickname.trim()) return;

    setIsSubmitting(true);
    
    // Небольшая задержка для анимации
    setTimeout(() => {
      onNicknameSubmit(nickname.trim());
      setIsSubmitting(false);
    }, 500);
  };

  const handleSuggestedClick = (suggested: string) => {
    setNickname(suggested);
  };

  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 text-white px-4">
      <motion.div
        initial={{ opacity: 0, y: -20 }}
        animate={{ opacity: 1, y: 0 }}
        transition={{ duration: 0.6 }}
        className="w-full max-w-md"
      >
        {/* Header */}
        <div className="flex items-center mb-8">
          <Button
            variant="ghost"
            size="icon"
            onClick={onBack}
            className="mr-4 text-gray-400 hover:text-white"
          >
            <ArrowLeft className="h-5 w-5" />
          </Button>
          <h1 className="text-2xl font-bold">{title}</h1>
        </div>

        <motion.div
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.2, duration: 0.6 }}
          className="space-y-6"
        >
          {/* Иконка */}
          <div className="w-16 h-16 bg-indigo-600 rounded-full flex items-center justify-center mx-auto">
            <User className="h-8 w-8" />
          </div>

          {/* Описание */}
          <div className="text-center">
            <h2 className="text-xl font-semibold mb-2">Выберите никнейм</h2>
            <p className="text-gray-400 text-sm">{subtitle}</p>
          </div>

          {/* Форма ввода */}
          <form onSubmit={handleSubmit} className="space-y-4">
            <div>
              <label htmlFor="nickname" className="block text-sm font-medium text-gray-300 mb-2">
                Ваш никнейм
              </label>
              <input
                id="nickname"
                type="text"
                value={nickname}
                onChange={(e) => setNickname(e.target.value)}
                placeholder="Введите ваш никнейм"
                maxLength={20}
                className="w-full px-4 py-3 bg-gray-800 border border-gray-700 rounded-xl text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-indigo-500 focus:border-transparent text-center text-lg"
                required
              />
              <p className="text-xs text-gray-400 mt-2 text-center">
                Максимум 20 символов
              </p>
            </div>

            <Button
              type="submit"
              disabled={!nickname.trim() || isSubmitting}
              className="w-full py-4 text-lg bg-indigo-600 hover:bg-indigo-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-xl shadow-lg transition"
            >
              {isSubmitting ? (
                <div className="flex items-center">
                  <div className="animate-spin rounded-full h-5 w-5 border-b-2 border-white mr-2"></div>
                  Подключение...
                </div>
              ) : (
                'Продолжить'
              )}
            </Button>
          </form>

          {/* Предложенные никнеймы */}
          <div className="space-y-3">
            <div className="flex items-center gap-2 text-gray-400 text-sm">
              <Sparkles className="h-4 w-4" />
              <span>Или выберите из предложенных:</span>
            </div>
            <div className="flex flex-wrap gap-2 justify-center">
              {suggestedNicknames.slice(0, 8).map((suggested, index) => (
                <motion.button
                  key={suggested}
                  type="button"
                  onClick={() => handleSuggestedClick(suggested)}
                  whileHover={{ scale: 1.05 }}
                  whileTap={{ scale: 0.95 }}
                  className={`px-3 py-1 rounded-full text-sm transition-colors ${
                    nickname === suggested
                      ? 'bg-indigo-600 text-white'
                      : 'bg-gray-700 text-gray-300 hover:bg-gray-600'
                  }`}
                >
                  {suggested}
                </motion.button>
              ))}
            </div>
          </div>
        </motion.div>
      </motion.div>
    </div>
  );
}
