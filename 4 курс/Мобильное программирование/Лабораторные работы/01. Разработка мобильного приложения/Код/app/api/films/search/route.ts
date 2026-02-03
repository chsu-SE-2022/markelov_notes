import { NextRequest, NextResponse } from 'next/server';
import { kinopoiskService } from '@/services/kinopoisk';

// GET /api/films/search?q=query&page=1 - поиск фильмов
export async function GET(request: NextRequest) {
  try {
    const { searchParams } = new URL(request.url);
    const query = searchParams.get('q');
    const page = parseInt(searchParams.get('page') || '1');

    if (!query || query.trim().length === 0) {
      return NextResponse.json(
        { error: 'Поисковый запрос обязателен' },
        { status: 400 }
      );
    }

    if (query.trim().length < 2) {
      return NextResponse.json(
        { error: 'Поисковый запрос должен содержать минимум 2 символа' },
        { status: 400 }
      );
    }

    const results = await kinopoiskService.searchFilms(query.trim(), page);
    
    // Загружаем детали для первых 5 фильмов параллельно
    const filmsWithDetails = await Promise.allSettled(
      results.items.slice(0, 5).map(async (film) => {
        try {
          const details = await kinopoiskService.getFilmDetails(film.kinopoiskId);
          return { ...film, ...details };
        } catch {
          // Если не удалось загрузить детали, возвращаем исходный фильм
          return film;
        }
      })
    );

    // Объединяем результаты
    const enrichedItems = filmsWithDetails.map((result, index) => {
      if (result.status === 'fulfilled') {
        return result.value;
      } else {
        // Если детали не загрузились, используем исходный фильм
        return results.items[index];
      }
    });

    // Добавляем остальные фильмы без деталей
    const remainingItems = results.items.slice(5);

    return NextResponse.json({
      success: true,
      data: {
        ...results,
        items: [...enrichedItems, ...remainingItems]
      },
    });
  } catch (error) {
    console.error('Ошибка поиска фильмов:', error);
    
    // Если ошибка связана с API ключом
    if (error instanceof Error && error.message.includes('API ключ')) {
      return NextResponse.json(
        { error: 'API ключ Кинопоиска не настроен. Обратитесь к администратору.' },
        { status: 503 }
      );
    }

    return NextResponse.json(
      { error: 'Произошла ошибка при поиске фильмов' },
      { status: 500 }
    );
  }
}
