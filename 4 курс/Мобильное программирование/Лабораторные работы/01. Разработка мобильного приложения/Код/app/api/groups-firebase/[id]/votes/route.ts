import { NextRequest, NextResponse } from 'next/server';
import { getGroupByCode, addVotes, getVotesByGroup, deleteVotesByGroup } from '@/lib/database';

// POST /api/groups-firebase/[id]/votes - сохранение голосов
export async function POST(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id: groupCode } = await params;
    const body = await request.json();
    const { votes } = body;

    // Нормализуем код группы (верхний регистр, без пробелов)
    const normalizedCode = groupCode?.toUpperCase().trim();
    
    console.log('Saving votes for group:', {
      original: groupCode,
      normalized: normalizedCode,
      votesCount: votes?.length
    });
    console.log('Votes data:', votes);

    if (!votes || !Array.isArray(votes)) {
      console.error('Invalid votes format:', votes);
      return NextResponse.json(
        { error: 'Неверный формат голосов' },
        { status: 400 }
      );
    }

    if (!normalizedCode) {
      console.error('Group code is missing or invalid');
      return NextResponse.json(
        { error: 'Код группы не указан' },
        { status: 400 }
      );
    }

    // Получаем группу
    const group = await getGroupByCode(normalizedCode);
    if (!group) {
      console.error('Group not found:', normalizedCode);
      // Пробуем найти все группы для отладки
      console.error('Attempting to find group with code:', normalizedCode);
      return NextResponse.json(
        { error: `Группа с кодом "${normalizedCode}" не найдена` },
        { status: 404 }
      );
    }

    console.log('Group found:', group.id, group.code);

    // Валидация голосов
    const validVotes = votes.filter((vote: { filmId: number; vote: string }) => 
      vote.filmId && 
      typeof vote.filmId === 'number' && 
      (vote.vote === 'like' || vote.vote === 'dislike')
    );

    if (validVotes.length === 0) {
      return NextResponse.json(
        { error: 'Нет валидных голосов' },
        { status: 400 }
      );
    }

    // Сохраняем голоса
    await addVotes(validVotes.map(vote => ({
      groupId: group.id,
      filmId: vote.filmId,
      vote: vote.vote,
      participantId: vote.participantId
    })));

    return NextResponse.json({
      success: true,
      message: 'Голоса успешно сохранены'
    });

  } catch (error) {
    console.error('Ошибка сохранения голосов:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}

// GET /api/groups-firebase/[id]/votes - получение голосов
export async function GET(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id: groupCode } = await params;

    const group = await getGroupByCode(groupCode);
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    const votes = await getVotesByGroup(group.id);

    return NextResponse.json({
      success: true,
      data: { votes }
    });

  } catch (error) {
    console.error('Ошибка получения голосов:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}

// DELETE /api/groups-firebase/[id]/votes - удаление всех голосов группы
export async function DELETE(
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

    await deleteVotesByGroup(group.id);

    return NextResponse.json({
      success: true,
      message: 'Все голоса успешно удалены'
    });

  } catch (error) {
    console.error('Ошибка удаления голосов:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}
