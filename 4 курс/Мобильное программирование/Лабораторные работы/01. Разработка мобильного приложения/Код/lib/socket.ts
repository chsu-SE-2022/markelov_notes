/* eslint-disable @typescript-eslint/no-explicit-any */
import { Server as NetServer } from 'http';
import { NextApiResponse } from 'next';
import { Server as SocketIOServer } from 'socket.io';

export type NextApiResponseServerIO = NextApiResponse & {
  socket: {
    server: NetServer & {
      io: SocketIOServer;
    };
  };
};

// Интерфейсы для событий WebSocket
export interface ServerToClientEvents {
  // События группы
  'group:participant-joined': (data: { participant: string; participants: string[] }) => void;
  'group:participant-left': (data: { participant: string; participants: string[] }) => void;
  'group:film-added': (data: { film: any; films: any[] }) => void;
  'group:film-removed': (data: { filmId: string; films: any[] }) => void;
  'group:closed': (data: { message: string }) => void;
  'group:reset': (data: { message: string }) => void;
  'group:creator-changed': (data: { newCreator: string; message: string }) => void;
  
  // События голосования
  'voting:started': (data: { films: any[] }) => void;
  'voting:vote-cast': (data: { participant: string; filmId: number; vote: 'like' | 'dislike' }) => void;
  'voting:completed': (data: { participant: string }) => void;
  'voting:all-completed': (data: { results: any }) => void;
  
  // Уведомления
  'notification:match-found': (data: { film: any; participants: string[] }) => void;
  'notification:error': (data: { message: string }) => void;
}

export interface ClientToServerEvents {
  // Подключение к группе
  'group:join': (data: { groupCode: string; participantName: string }) => void;
  'group:leave': (data: { groupCode: string; participantName: string }) => void;
  'group:reset': (data: { groupCode: string }) => void;
  
  // Управление фильмами
  'film:add': (data: { groupCode: string; film: any }) => void;
  'film:remove': (data: { groupCode: string; filmId: string }) => void;
  
  // Голосование
  'voting:start': (data: { groupCode: string; films: any[] }) => void;
  'voting:vote': (data: { groupCode: string; filmId: number; vote: 'like' | 'dislike' }) => void;
  'voting:skip': (data: { groupCode: string; filmId: number }) => void;
  'voting:completed': (data: { groupCode: string; participantName: string }) => void;
}

export interface InterServerEvents {
  ping: () => void;
}

export interface SocketData {
  groupCode?: string;
  participantName?: string;
}

// Хранилище активных групп и участников
export const activeGroups = new Map<string, Set<string>>();
export const groupSockets = new Map<string, Set<string>>();

// Утилиты для работы с группами
export function addParticipantToGroup(groupCode: string, participantName: string) {
  if (!activeGroups.has(groupCode)) {
    activeGroups.set(groupCode, new Set());
  }
  activeGroups.get(groupCode)!.add(participantName);
}

export function removeParticipantFromGroup(groupCode: string, participantName: string) {
  const group = activeGroups.get(groupCode);
  if (group) {
    group.delete(participantName);
    if (group.size === 0) {
      activeGroups.delete(groupCode);
    }
  }
}

export function getGroupParticipants(groupCode: string): string[] {
  const group = activeGroups.get(groupCode);
  return group ? Array.from(group) : [];
}

export function addSocketToGroup(groupCode: string, socketId: string) {
  if (!groupSockets.has(groupCode)) {
    groupSockets.set(groupCode, new Set());
  }
  groupSockets.get(groupCode)!.add(socketId);
}

export function removeSocketFromGroup(groupCode: string, socketId: string) {
  const sockets = groupSockets.get(groupCode);
  if (sockets) {
    sockets.delete(socketId);
    if (sockets.size === 0) {
      groupSockets.delete(groupCode);
    }
  }
}

export function getGroupSockets(groupCode: string): string[] {
  const sockets = groupSockets.get(groupCode);
  return sockets ? Array.from(sockets) : [];
}
