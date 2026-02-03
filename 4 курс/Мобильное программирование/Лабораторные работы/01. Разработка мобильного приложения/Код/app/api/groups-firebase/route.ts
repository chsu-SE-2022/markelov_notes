import { NextRequest, NextResponse } from 'next/server';
import { createGroup, getGroupByCode, getFilmsByGroup, cleanupOldGroups } from '@/lib/database';

// POST /api/groups-firebase - создание новой группы
export async function POST(request: NextRequest) {
  try {
    const body = await request.json();
    const { creatorName } = body;

    if (!creatorName || typeof creatorName !== 'string') {
      return NextResponse.json(
        { error: 'Имя создателя группы обязательно' },
        { status: 400 }
      );
    }

    // Генерируем уникальный код группы (уже в верхнем регистре)
    const code = generateGroupCode().toUpperCase().trim();
    
    const groupId = await createGroup({
      code,
      participants: [creatorName],
      isActive: true,
      createdBy: creatorName
    });

    return NextResponse.json({
      success: true,
      data: {
        id: groupId,
        code,
        participants: [creatorName],
        films: [],
        votes: [],
        createdAt: new Date(),
        isActive: true
      }
    });

  } catch (error) {
    console.error('Ошибка создания группы:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}

// GET /api/groups-firebase?code=ABC123 - получение информации о группе
export async function GET(request: NextRequest) {
  try {
    const { searchParams } = new URL(request.url);
    const code = searchParams.get('code');

    // Автоочистка старых групп (выполняется периодически при запросах)
    // В продакшене лучше делать через cron job, но для простоты делаем здесь
    if (Math.random() < 0.1) { // 10% вероятность при каждом запросе
      cleanupOldGroups().catch(err => console.error('Auto-cleanup error:', err));
    }

    if (!code) {
      return NextResponse.json(
        { error: 'Код группы обязателен' },
        { status: 400 }
      );
    }

    // Нормализуем код группы (верхний регистр, без пробелов)
    const normalizedCode = code.toUpperCase().trim();
    const group = await getGroupByCode(normalizedCode);
    
    if (!group) {
      return NextResponse.json(
        { error: 'Группа не найдена' },
        { status: 404 }
      );
    }

    // Загружаем фильмы группы
    const films = await getFilmsByGroup(group.id);

    return NextResponse.json({
      success: true,
      data: {
        ...group,
        films
      }
    });

  } catch (error) {
    console.error('Ошибка получения группы:', error);
    return NextResponse.json(
      { error: 'Внутренняя ошибка сервера' },
      { status: 500 }
    );
  }
}

// Генерация уникального 5-значного кода
function generateGroupCode(): string {
  const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
  let result = '';
  for (let i = 0; i < 5; i++) {
    result += chars.charAt(Math.floor(Math.random() * chars.length));
  }
  return result;
}
