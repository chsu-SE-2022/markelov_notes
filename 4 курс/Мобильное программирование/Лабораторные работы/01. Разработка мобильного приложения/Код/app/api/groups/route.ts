import { NextRequest, NextResponse } from 'next/server';
import { createGroup, getGroup } from '@/lib/groups';

// POST /api/groups - создание новой группы
export async function POST(request: NextRequest) {
  try {
    const body = await request.json();
    const { creatorName } = body;

    const result = createGroup(creatorName);
    
    if (!result.success) {
      return NextResponse.json(
        { error: result.error },
        { status: 400 }
      );
    }

    return NextResponse.json({
      success: true,
      group: {
        id: result.group!.id,
        code: result.group!.code,
        participants: result.group!.participants,
        createdAt: result.group!.createdAt,
      },
    });
  } catch (error) {
    console.error('Ошибка создания группы:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}

// GET /api/groups?code=ABC123 - получение информации о группе
export async function GET(request: NextRequest) {
  try {
    const { searchParams } = new URL(request.url);
    const code = searchParams.get('code');

    if (!code) {
      return NextResponse.json(
        { error: 'Код группы обязателен' },
        { status: 400 }
      );
    }

    const group = getGroup(code);
    
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    return NextResponse.json({
      success: true,
      data: {
        id: group.id,
        code: group.code,
        participants: group.participants,
        films: group.films,
        createdAt: group.createdAt,
        isActive: group.isActive,
      },
    });
  } catch (error) {
    console.error('Ошибка получения группы:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}
