'use client';

import React from 'react';
import { motion } from 'framer-motion';
import { Users } from 'lucide-react';

interface WaitingForOthersProps {
  completedCount: number;
  totalCount: number;
}

export default function WaitingForOthers({ completedCount, totalCount }: WaitingForOthersProps) {
  const progress = totalCount > 0 ? (completedCount / totalCount) * 100 : 0;

  // Анимация пульсации для иконок
  const pulseVariants = {
    animate: {
      scale: [1, 1.2, 1],
      opacity: [0.7, 1, 0.7],
    },
    transition: {
      duration: 2,
      repeat: Infinity,
      ease: "easeInOut"
    }
  };

  // Анимация для счетчика
  const countVariants = {
    initial: { scale: 0 },
    animate: { scale: 1 },
    transition: { type: "spring", stiffness: 200, damping: 15 }
  };

  return (
    <div className="min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 flex items-center justify-center px-4">
      <div className="max-w-md w-full text-center">
        {/* Главная иконка с пульсацией */}
        <motion.div
          className="flex justify-center mb-8"
          variants={pulseVariants}
          animate="animate"
        >
          <Users className="h-24 w-24 text-pink-500" />
        </motion.div>

        {/* Заголовок */}
        <motion.h1
          initial={{ opacity: 0, y: -20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.2 }}
          className="text-3xl font-bold text-white mb-4"
        >
          Отличная работа! 🎉
        </motion.h1>

        {/* Сообщение */}
        <motion.p
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.3 }}
          className="text-gray-300 text-lg mb-8"
        >
          Вы завершили голосование! Ожидаем других участников...
        </motion.p>

        {/* Прогресс */}
        <motion.div
          initial={{ opacity: 0, y: 20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.4 }}
          className="mb-8"
        >
          <div className="flex items-center justify-center gap-4 mb-4">
            <motion.div
              key={completedCount}
              variants={countVariants}
              initial="initial"
              animate="animate"
              className="text-4xl font-bold text-pink-400"
            >
              {completedCount}
            </motion.div>
            <span className="text-2xl text-gray-400">из</span>
            <span className="text-4xl font-bold text-gray-400">{totalCount}</span>
          </div>
          
          {/* Прогресс-бар */}
          <div className="w-full bg-gray-700 rounded-full h-3 overflow-hidden">
            <motion.div
              className="h-full bg-gradient-to-r from-pink-500 via-purple-500 to-pink-500"
              initial={{ width: 0 }}
              animate={{ width: `${progress}%` }}
              transition={{ duration: 0.5, ease: "easeOut" }}
            />
          </div>
        </motion.div>

        {/* Анимированные точки */}
        <motion.div
          initial={{ opacity: 0 }}
          animate={{ opacity: 1 }}
          transition={{ delay: 0.5 }}
          className="flex justify-center gap-2"
        >
          {[0, 1, 2].map((i) => (
            <motion.div
              key={i}
              className="w-3 h-3 bg-pink-500 rounded-full"
              animate={{
                y: [0, -10, 0],
                opacity: [0.5, 1, 0.5],
              }}
              transition={{
                duration: 1.5,
                repeat: Infinity,
                delay: i * 0.2,
                ease: "easeInOut",
              }}
            />
          ))}
        </motion.div>

        {/* Сообщение о следующем шаге */}
        <motion.p
          initial={{ opacity: 0 }}
          animate={{ opacity: 1 }}
          transition={{ delay: 0.6 }}
          className="text-gray-400 text-sm mt-8"
        >
          Как только все участники завершат голосование, вы автоматически увидите результаты!
        </motion.p>
      </div>
    </div>
  );
}

