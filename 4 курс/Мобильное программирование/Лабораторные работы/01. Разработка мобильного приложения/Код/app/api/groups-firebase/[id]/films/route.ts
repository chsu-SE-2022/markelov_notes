import { NextRequest, NextResponse } from 'next/server';
import { getGroupByCode, addFilmToGroup, getFilmsByGroup } from '@/lib/database';

// POST /api/groups-firebase/[id]/films - добавление фильма в группу
export async function POST(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id: groupCode } = await params;
    const body = await request.json();
    const { film } = body;

    if (!film) {
      return NextResponse.json(
        { error: 'Фильм не указан' },
        { status: 400 }
      );
    }

    // Получаем группу
    const group = await getGroupByCode(groupCode);
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    // Добавляем фильм в группу
    await addFilmToGroup({
      groupId: group.id,
      kinopoiskId: film.kinopoiskId,
      title: film.nameRu,
      year: film.year,
      poster: film.posterUrl,
      description: film.description,
      rating: film.ratingKinopoisk,
      addedBy: 'Пользователь' // TODO: Получать реальное имя
    });

    // Получаем обновленный список фильмов
    const films = await getFilmsByGroup(group.id);

    return NextResponse.json({
      success: true,
      data: {
        ...group,
        films
      }
    });

  } catch (error) {
    console.error('Ошибка добавления фильма:', error);
    
    // Более детальная обработка ошибок
    if (error instanceof Error) {
      if (error.message.includes('уже добавлен')) {
        return NextResponse.json(
          { error: 'Этот фильм уже добавлен в группу' },
          { status: 400 }
        );
      }
      if (error.message.includes('index')) {
        return NextResponse.json(
          { error: 'Ошибка базы данных: требуется настройка индексов' },
          { status: 500 }
        );
      }
      return NextResponse.json(
        { error: `Ошибка: ${error.message}` },
        { status: 500 }
      );
    }
    
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}
