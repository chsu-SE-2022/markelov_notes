// Типы для работы с группами
export interface Group {
  id: string;
  code: string;
  participants: string[];
  films: Film[];
  votes?: Vote[];
  createdAt: Date;
  isActive: boolean;
  createdBy?: string;
}

export interface Vote {
  filmId: number;
  vote: 'like' | 'dislike';
  timestamp: number;
  participantId: string;
}

export interface Film {
  id: string;
  title: string;
  year: number;
  poster?: string;
  description?: string;
  rating?: number;
  addedBy: string;
  addedAt: Date;
}
