'use client';

import React, { useState } from "react";
import { motion } from "framer-motion";
import { Button } from "@/components/ui/button";
import { ArrowLeft, Copy, Check } from "lucide-react";
import NicknameInput from "@/components/NicknameInput";

export default function CreatePage() {
  const [groupCode, setGroupCode] = useState("");
  const [isLoading, setIsLoading] = useState(false);
  const [copied, setCopied] = useState(false);
  const [showNicknameInput, setShowNicknameInput] = useState(false);
  const [creatorNickname, setCreatorNickname] = useState("");

  const handleNicknameSubmit = (newNickname: string) => {
    setCreatorNickname(newNickname);
    setShowNicknameInput(false);
    // После ввода никнейма создаем группу
    createGroup(newNickname);
  };


  const createGroup = async (nickname: string) => {
    setIsLoading(true);
    
    try {
      const response = await fetch('/api/groups-firebase', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          creatorName: nickname,
        }),
      });

      const data = await response.json();

      if (data.success) {
        setGroupCode(data.data.code);
        setIsLoading(false);
        // Показываем экран с кодом группы - не перенаправляем автоматически
      } else {
        alert(`Ошибка создания группы: ${data.error}`);
      }
    } catch (error) {
      console.error('Ошибка создания группы:', error);
      alert('Произошла ошибка при создании группы');
    } finally {
      setIsLoading(false);
    }
  };

  const handleCreateGroup = () => {
    setShowNicknameInput(true);
  };

  const handleCopyCode = async () => {
    if (groupCode) {
      await navigator.clipboard.writeText(groupCode);
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    }
  };

  if (showNicknameInput) {
    return (
      <NicknameInput
        onNicknameSubmit={handleNicknameSubmit}
        onBack={() => window.history.back()}
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
          <h1 className="text-2xl font-bold">Создать группу</h1>
        </div>

        <motion.div
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ delay: 0.2, duration: 0.6 }}
          className="space-y-6"
        >
          {!groupCode ? (
            <div className="text-center space-y-4">
              <div className="w-16 h-16 bg-indigo-600 rounded-full flex items-center justify-center mx-auto">
                <span className="text-2xl">🎬</span>
              </div>
              <h2 className="text-xl font-semibold">Создать новую группу</h2>
              <p className="text-gray-400 text-sm">
                Создайте группу и пригласите друзей для выбора фильма
              </p>
              <Button
                onClick={handleCreateGroup}
                disabled={isLoading}
                className="w-full py-4 text-lg bg-indigo-600 hover:bg-indigo-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-xl shadow-lg transition"
              >
                {isLoading ? "Создание..." : "Создать группу"}
              </Button>
            </div>
          ) : (
            <div className="text-center space-y-6">
              <div className="w-16 h-16 bg-green-600 rounded-full flex items-center justify-center mx-auto">
                <Check className="h-8 w-8" />
              </div>
              <h2 className="text-xl font-semibold">Группа создана!</h2>
              <p className="text-gray-400 text-sm">
                Поделитесь кодом с друзьями, чтобы они могли присоединиться
              </p>
              
              {/* Code Display */}
              <div className="bg-gray-800 border border-gray-700 rounded-xl p-6">
                <p className="text-sm text-gray-400 mb-2">Код группы</p>
                <div className="flex items-center justify-center space-x-3">
                  <span className="text-3xl font-bold tracking-widest text-white">
                    {groupCode}
                  </span>
                  <Button
                    size="icon"
                    onClick={handleCopyCode}
                    className="bg-gray-700 hover:bg-gray-600"
                  >
                    {copied ? (
                      <Check className="h-4 w-4" />
                    ) : (
                      <Copy className="h-4 w-4" />
                    )}
                  </Button>
                </div>
              </div>

              <div className="space-y-3">
                <Button
                  onClick={() => window.location.href = `/group/${groupCode}?nickname=${encodeURIComponent(creatorNickname)}`}
                  className="w-full py-4 text-lg bg-pink-600 hover:bg-pink-700 rounded-xl shadow-lg transition"
                >
                  Перейти к группе
                </Button>
                <Button
                  variant="outline"
                  onClick={() => setGroupCode("")}
                  className="w-full py-3 text-gray-300 border-gray-600 hover:bg-gray-800 rounded-xl"
                >
                  Создать новую группу
                </Button>
              </div>
            </div>
          )}
        </motion.div>
      </motion.div>
    </div>
  );
}
