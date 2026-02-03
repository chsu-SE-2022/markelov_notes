// Типы для работы с Кинопоиск API
export interface KinopoiskFilm {
  kinopoiskId: number;
  nameRu: string;
  nameEn?: string;
  year: number;
  posterUrl: string;
  posterUrlPreview: string;
  description?: string;
  ratingKinopoisk?: number;
  ratingImdb?: number;
  genres: Array<{ genre: string }>;
  countries: Array<{ country: string }>;
  duration?: number;
}

export interface KinopoiskSearchResponse {
  total: number;
  totalPages: number;
  items: KinopoiskFilm[];
}

export interface KinopoiskFilmDetails extends KinopoiskFilm {
  shortDescription?: string;
  slogan?: string;
  type: string;
  ratingAgeLimits?: string;
  distributors?: string;
  premiere?: {
    world: string;
    russia?: string;
  };
}

// Конфигурация API
const KINOPOISK_API_BASE_URL = 'https://kinopoiskapiunofficial.tech/api/v2.2';
const KINOPOISK_API_KEY = process.env.KINOPOISK_API_KEY || '';

// Сервис для работы с Кинопоиск API
export class KinopoiskService {
  private static instance: KinopoiskService;
  private apiKey: string;

  private constructor() {
    this.apiKey = KINOPOISK_API_KEY;
  }

  public static getInstance(): KinopoiskService {
    if (!KinopoiskService.instance) {
      KinopoiskService.instance = new KinopoiskService();
    }
    return KinopoiskService.instance;
  }

  // Поиск фильмов по названию
  async searchFilms(query: string, page: number = 1): Promise<KinopoiskSearchResponse> {
    if (!this.apiKey) {
      throw new Error('API ключ Кинопоиска не настроен');
    }

    try {
      const response = await fetch(
        `${KINOPOISK_API_BASE_URL}/films?keyword=${encodeURIComponent(query)}&page=${page}`,
        {
          headers: {
            'X-API-KEY': this.apiKey,
            'Content-Type': 'application/json',
          },
        }
      );

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      const data = await response.json();
      return data;
    } catch (error) {
      console.error('Ошибка поиска фильмов:', error);
      throw new Error('Не удалось найти фильмы');
    }
  }

  // Получение детальной информации о фильме
  async getFilmDetails(kinopoiskId: number): Promise<KinopoiskFilmDetails> {
    if (!this.apiKey) {
      throw new Error('API ключ Кинопоиска не настроен');
    }

    try {
      const response = await fetch(
        `${KINOPOISK_API_BASE_URL}/films/${kinopoiskId}`,
        {
          headers: {
            'X-API-KEY': this.apiKey,
            'Content-Type': 'application/json',
          },
        }
      );

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      const data = await response.json();
      return data;
    } catch (error) {
      console.error('Ошибка получения деталей фильма:', error);
      throw new Error('Не удалось получить информацию о фильме');
    }
  }

  // Получение топ фильмов
  async getTopFilms(page: number = 1): Promise<KinopoiskSearchResponse> {
    if (!this.apiKey) {
      throw new Error('API ключ Кинопоиска не настроен');
    }

    try {
      const response = await fetch(
        `${KINOPOISK_API_BASE_URL}/films/top?type=TOP_250_BEST_FILMS&page=${page}`,
        {
          headers: {
            'X-API-KEY': this.apiKey,
            'Content-Type': 'application/json',
          },
        }
      );

      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }

      const data = await response.json();
      return data;
    } catch (error) {
      console.error('Ошибка получения топ фильмов:', error);
      throw new Error('Не удалось получить топ фильмы');
    }
  }

  // Проверка доступности API
  async checkApiAvailability(): Promise<boolean> {
    try {
      await this.getTopFilms(1);
      return true;
    } catch {
      return false;
    }
  }
}

// Экспорт экземпляра сервиса
export const kinopoiskService = KinopoiskService.getInstance();

// Утилиты для работы с данными фильмов
export const filmUtils = {
  // Форматирование рейтинга
  formatRating(rating?: number): string {
    if (!rating) return 'Нет рейтинга';
    return rating.toFixed(1);
  },

  // Форматирование продолжительности
  formatDuration(duration?: number): string {
    if (!duration) return 'Не указано';
    const hours = Math.floor(duration / 60);
    const minutes = duration % 60;
    return `${hours}ч ${minutes}м`;
  },

  // Форматирование жанров
  formatGenres(genres: Array<{ genre: string }>): string {
    return genres.map(g => g.genre).join(', ');
  },

  // Форматирование стран
  formatCountries(countries: Array<{ country: string }>): string {
    return countries.map(c => c.country).join(', ');
  },

  // Получение URL постера с fallback
  getPosterUrl(film: KinopoiskFilm): string {
    return film.posterUrl || film.posterUrlPreview || '/placeholder-poster.jpg';
  },

  // Создание краткого описания
  getShortDescription(film: KinopoiskFilm): string {
    if (film.description) {
      return film.description.length > 150 
        ? film.description.substring(0, 150) + '...'
        : film.description;
    }
    return 'Описание не доступно';
  }
};
