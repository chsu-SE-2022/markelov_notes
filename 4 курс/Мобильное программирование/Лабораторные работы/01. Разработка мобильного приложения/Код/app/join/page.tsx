'use client';

import React, { useState } from "react";
import { motion } from "framer-motion";
import { Button } from "@/components/ui/button";
import { ArrowLeft } from "lucide-react";
import NicknameInput from "@/components/NicknameInput";

export default function JoinPage() {
  const [code, setCode] = useState("");
  const [isLoading, setIsLoading] = useState(false);
  const [showNicknameInput, setShowNicknameInput] = useState(false);
  const [participantNickname, setParticipantNickname] = useState("");

  const handleNicknameSubmit = (newNickname: string) => {
    setParticipantNickname(newNickname);
    setShowNicknameInput(false);
    // После ввода никнейма присоединяемся к группе
    joinGroup(newNickname);
  };

  const joinGroup = async (nickname: string) => {
    setIsLoading(true);
    
    try {
      const response = await fetch('/api/groups-firebase/join', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          code: code.toUpperCase(),
          participantName: nickname,
        }),
      });

      const data = await response.json();

      if (data.success) {
        // Перенаправляем на страницу группы с никнеймом в URL
        window.location.href = `/group/${data.data.code}?nickname=${encodeURIComponent(nickname)}`;
      } else {
        alert(`Ошибка присоединения: ${data.error}`);
      }
    } catch (error) {
      console.error('Ошибка присоединения к группе:', error);
      alert('Произошла ошибка при присоединении к группе');
    } finally {
      setIsLoading(false);
    }
  };

  const handleJoin = () => {
    if (!code.trim()) return;
    setShowNicknameInput(true);
  };

  if (showNicknameInput) {
    return (
      <NicknameInput
        onNicknameSubmit={handleNicknameSubmit}
        onBack={() => setShowNicknameInput(false)}
        title="Введите ваш никнейм"
        subtitle="Выберите имя, под которым вас будут видеть в группе"
      />
    );
  }

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
            onClick={() => window.history.back()}
            className="mr-4 text-gray-400 hover:text-white"
          >
            <ArrowLeft className="h-5 w-5" />
          </Button>
          <h1 className="text-2xl font-bold">Присоединиться к группе</h1>
        </div>

        {/* Form */}
        <motion.div
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.2, duration: 0.6 }}
          className="space-y-6"
        >
          <div>
            <label htmlFor="code" className="block text-sm font-medium text-gray-300 mb-2">
              Код группы
            </label>
            <input
              id="code"
              type="text"
              value={code}
              onChange={(e) => setCode(e.target.value.toUpperCase())}
              placeholder="Введите 5-значный код"
              maxLength={5}
              className="w-full px-4 py-3 bg-gray-800 border border-gray-700 rounded-xl text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-pink-500 focus:border-transparent text-center text-lg tracking-widest"
            />
            <p className="text-xs text-gray-400 mt-2 text-center">
              Код состоит из 5 символов (буквы и цифры)
            </p>
          </div>

          <Button
            onClick={handleJoin}
            disabled={code.length !== 5 || isLoading}
            className="w-full py-4 text-lg bg-pink-600 hover:bg-pink-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-xl shadow-lg transition"
          >
            {isLoading ? "Подключение..." : "Присоединиться"}
          </Button>
        </motion.div>

        {/* Info */}
        <motion.div
          initial={{ opacity: 0 }}
          animate={{ opacity: 1 }}
          transition={{ delay: 0.4, duration: 0.6 }}
          className="mt-8 text-center"
        >
          <p className="text-sm text-gray-400">
            Получите код от создателя группы
          </p>
        </motion.div>
      </motion.div>
    </div>
  );
}
