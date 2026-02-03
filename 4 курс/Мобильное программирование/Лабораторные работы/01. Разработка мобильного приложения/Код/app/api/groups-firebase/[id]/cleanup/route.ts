import { NextRequest, NextResponse } from 'next/server';
import { getGroupByCode, deleteFilmsByGroup, deleteVotesByGroup } from '@/lib/database';

// POST /api/groups-firebase/[id]/cleanup - удаление фильмов и голосов группы
export async function POST(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id: groupCode } = await params;
    const normalizedCode = groupCode?.toUpperCase().trim();

    if (!normalizedCode) {
      return NextResponse.json(
        { error: 'Код группы не указан' },
        { status: 400 }
      );
    }

    const group = await getGroupByCode(normalizedCode);
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    // Удаляем фильмы и голоса (но не саму группу)
    await deleteFilmsByGroup(group.id);
    await deleteVotesByGroup(group.id);

    return NextResponse.json({
      success: true,
      message: 'Фильмы и голоса успешно удалены'
    });

  } catch (error) {
    console.error('Ошибка очистки данных группы:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}

