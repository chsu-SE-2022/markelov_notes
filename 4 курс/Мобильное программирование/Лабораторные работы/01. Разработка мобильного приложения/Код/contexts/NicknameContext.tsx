'use client';

import React, { createContext, useContext, useState, useEffect } from 'react';

interface NicknameContextType {
  nickname: string | null;
  setNickname: (nickname: string) => void;
  clearNickname: () => void;
}

const NicknameContext = createContext<NicknameContextType | undefined>(undefined);

export function NicknameProvider({ children }: { children: React.ReactNode }) {
  const [nickname, setNicknameState] = useState<string | null>(null);

  // Загружаем никнейм из localStorage при инициализации
  useEffect(() => {
    if (typeof window !== 'undefined') {
      const stored = localStorage.getItem('flickpick-nickname');
      if (stored) {
        setNicknameState(stored);
      }
    }
  }, []);

  const setNickname = (newNickname: string) => {
    setNicknameState(newNickname);
    if (typeof window !== 'undefined') {
      localStorage.setItem('flickpick-nickname', newNickname);
    }
  };

  const clearNickname = () => {
    setNicknameState(null);
    if (typeof window !== 'undefined') {
      localStorage.removeItem('flickpick-nickname');
    }
  };

  return (
    <NicknameContext.Provider value={{ nickname, setNickname, clearNickname }}>
      {children}
    </NicknameContext.Provider>
  );
}

export function useNickname() {
  const context = useContext(NicknameContext);
  if (context === undefined) {
    throw new Error('useNickname must be used within a NicknameProvider');
  }
  return context;
}
