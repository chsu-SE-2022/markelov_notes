import { NextRequest, NextResponse } from 'next/server';
import { getGroup } from '@/lib/groups';

// POST /api/groups/[id]/votes - сохранение голосов участника
export async function POST(
  request: NextRequest,
  { params }: { params: Promise<{ id: string }> }
) {
  try {
    const { id: groupCode } = await params;
    const body = await request.json();
    const { votes } = body;

    if (!votes || !Array.isArray(votes)) {
      return NextResponse.json(
        { error: 'Неверный формат голосов' },
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

    // Сохраняем голоса (в реальном приложении здесь была бы база данных)
    // Пока что сохраняем в памяти группы
    if (group) {
      // Добавляем голоса к группе (в реальном приложении это было бы в отдельной таблице)
      if (!group.votes) {
        group.votes = [];
      }
      group.votes.push(...validVotes);
    }
    
    console.log(`Сохранены голоса для группы ${groupCode}:`, validVotes);

    return NextResponse.json({
      success: true,
      message: 'Голоса успешно сохранены',
      data: {
        groupCode,
        votesCount: validVotes.length,
        votes: validVotes
      }
    });

  } catch (error) {
    console.error('Ошибка сохранения голосов:', error);
    
    return NextResponse.json(
      { error: 'Произошла ошибка при сохранении голосов' },
      { status: 500 }
    );
  }
}

// GET /api/groups/[id]/votes - получение голосов группы
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

    // Получаем голоса из группы
    const votes = group.votes || [];
    
    return NextResponse.json({
      success: true,
      data: {
        groupCode,
        votes
      }
    });

  } catch (error) {
    console.error('Ошибка получения голосов:', error);
    
    return NextResponse.json(
      { error: 'Произошла ошибка при получении голосов' },
      { status: 500 }
    );
  }
}
