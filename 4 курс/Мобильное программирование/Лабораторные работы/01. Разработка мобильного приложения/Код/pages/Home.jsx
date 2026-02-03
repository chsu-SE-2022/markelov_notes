'use client';

import React from "react";
import { motion } from "framer-motion";
import { Button } from "@/components/ui/button";

export default function Home() {
  return (
    <div className="flex flex-col items-center justify-center min-h-screen bg-gradient-to-b from-black via-gray-900 to-gray-800 text-white px-4">
      <motion.h1
        initial={{ opacity: 0, y: -20 }}
        animate={{ opacity: 1, y: 0 }}
        transition={{ duration: 0.6 }}
        className="text-4xl font-bold mb-16 text-center"
      >
        🎬 FlickPick
        <span className="block text-lg font-normal mt-2 text-gray-300">
          Выбор фильма без споров
        </span>
      </motion.h1>

      <motion.div
        initial={{ opacity: 0, y: 30 }}
        animate={{ opacity: 1, y: 0 }}
        transition={{ delay: 0.3, duration: 0.6 }}
        className="flex flex-col w-full max-w-xs gap-6"
      >
        <Button
          className="w-full py-6 text-lg bg-pink-600 hover:bg-pink-700 rounded-2xl shadow-lg transition"
          onClick={() => (window.location.href = "/join")}
        >
          🔗 Присоединиться к группе
        </Button>

        <Button
          className="w-full py-6 text-lg bg-indigo-600 hover:bg-indigo-700 rounded-2xl shadow-lg transition"
          onClick={() => (window.location.href = "/create")}
        >
          ✨ Создать новую группу
        </Button>
      </motion.div>
    </div>
  );
}
