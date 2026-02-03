import { NextRequest, NextResponse } from 'next/server';
import { kinopoiskService } from '@/services/kinopoisk';

// GET /api/films/details/[id] - получение деталей фильма
export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id } = await params;
    const kinopoiskId = parseInt(id);

    if (isNaN(kinopoiskId) || kinopoiskId <= 0) {
      return NextResponse.json(
        { error: 'Неверный ID фильма' },
        { status: 400 }
      );
    }

    const filmDetails = await kinopoiskService.getFilmDetails(kinopoiskId);

    return NextResponse.json({
      success: true,
      data: filmDetails,
    });
  } catch (error) {
    console.error('Ошибка получения деталей фильма:', error);
    
    // Если ошибка связана с API ключом
    if (error instanceof Error && error.message.includes('API ключ')) {
      return NextResponse.json(
        { error: 'API ключ Кинопоиска не настроен. Обратитесь к администратору.' },
        { status: 503 }
      );
    }

    // Если фильм не найден
    if (error instanceof Error && error.message.includes('404')) {
      return NextResponse.json(
        { error: 'Фильм не найден' },
        { status: 404 }
      );
    }

    return NextResponse.json(
      { error: 'Произошла ошибка при получении информации о фильме' },
      { status: 500 }
    );
  }
}