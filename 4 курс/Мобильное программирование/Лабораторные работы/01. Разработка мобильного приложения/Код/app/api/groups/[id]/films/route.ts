import { NextRequest, NextResponse } from 'next/server';
import { getGroup, addFilmToGroup } from '@/lib/groups';

// POST /api/groups/[id]/films - добавление фильма в группу
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
    const group = getGroup(groupCode);
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    // Добавляем фильм в группу
    const updatedGroup = addFilmToGroup(groupCode, film);

    return NextResponse.json({
      success: true,
      data: updatedGroup,
      message: 'Фильм успешно добавлен в группу'
    });

  } catch (error) {
    console.error('Ошибка добавления фильма в группу:', error);
    
    return NextResponse.json(
      { error: 'Произошла ошибка при добавлении фильма' },
      { status: 500 }
    );
  }
}

// GET /api/groups/[id]/films - получение фильмов группы
export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id: groupCode } = await params;

    // Получаем группу
    const group = getGroup(groupCode);
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    return NextResponse.json({
      success: true,
      data: {
        films: group.films || []
      }
    });

  } catch (error) {
    console.error('Ошибка получения фильмов группы:', error);
    
    return NextResponse.json(
      { error: 'Произошла ошибка при получении фильмов' },
      { status: 500 }
    );
  }
}
