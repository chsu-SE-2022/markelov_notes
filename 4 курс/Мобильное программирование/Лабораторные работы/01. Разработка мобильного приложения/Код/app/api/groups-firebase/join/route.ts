import { NextRequest, NextResponse } from 'next/server';
import { getGroupByCode, updateGroup } from '@/lib/database';

// POST /api/groups-firebase/join - присоединение к группе
export async function POST(request: NextRequest) {
  try {
    const body = await request.json();
    const { code, participantName } = body;

    if (!code || !participantName) {
      return NextResponse.json(
        { error: 'Код группы и имя участника обязательны' },
        { status: 400 }
      );
    }

    // Получаем группу
    const group = await getGroupByCode(code);
    if (!group) {
      return NextResponse.json(
        { error: 'Группа с таким кодом не найдена' },
        { status: 404 }
      );
    }

    // Проверяем, не является ли участник уже членом группы
    if (group.participants.includes(participantName)) {
      return NextResponse.json(
        { error: 'Вы уже являетесь участником этой группы' },
        { status: 400 }
      );
    }

    // Добавляем участника
    const updatedParticipants = [...group.participants, participantName];
    await updateGroup(group.id, { participants: updatedParticipants });

    return NextResponse.json({
      success: true,
      data: {
        ...group,
        participants: updatedParticipants
      }
    });

  } catch (error) {
    console.error('Ошибка присоединения к группе:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}
