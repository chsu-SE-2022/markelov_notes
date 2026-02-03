import { NextRequest, NextResponse } from 'next/server';
import { joinGroup } from '@/lib/groups';

// POST /api/groups/join - присоединение к группе
export async function POST(request: NextRequest) {
  try {
    const body = await request.json();
    const { code, participantName } = body;

    const result = joinGroup(code, participantName);
    
    if (!result.success) {
      return NextResponse.json(
        { error: result.error },
        { status: result.error === 'Группа с таким кодом не найдена' ? 404 : 400 }
      );
    }

    return NextResponse.json({
      success: true,
      message: 'Успешно присоединились к группе',
      group: {
        id: result.group!.id,
        code: result.group!.code,
        participants: result.group!.participants,
        films: result.group!.films,
        createdAt: result.group!.createdAt,
        isActive: result.group!.isActive,
      },
    });
  } catch (error) {
    console.error('Ошибка присоединения к группе:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}
