/* eslint-disable @typescript-eslint/no-explicit-any */
let adminApp: any | null = null;
let adminDb: any | null = null;

export function getAdminDb() {
  try {
    if (adminDb) return adminDb;

    // Динамически подключаем firebase-admin, чтобы не требовать зависимость в браузере
    // и не падать, если пакет не установлен
    // eslint-disable-next-line @typescript-eslint/no-var-requires
    const admin = require('firebase-admin');

    if (!admin.apps || admin.apps.length === 0) {
      const projectId = process.env.FIREBASE_PROJECT_ID;
      const clientEmail = process.env.FIREBASE_CLIENT_EMAIL;
      const privateKey = (process.env.FIREBASE_PRIVATE_KEY || '').replace(/\\n/g, '\n');

      if (!projectId || !clientEmail || !privateKey) {
        console.warn('[firebase-admin] Не заданы переменные окружения FIREBASE_PROJECT_ID / FIREBASE_CLIENT_EMAIL / FIREBASE_PRIVATE_KEY');
        return null;
      }

      adminApp = admin.initializeApp({
        credential: admin.credential.cert({
          projectId,
          clientEmail,
          privateKey,
        }),
      });
    } else {
      adminApp = admin.app();
    }

    adminDb = admin.firestore(adminApp);
    return adminDb;
  } catch (e) {
    console.warn('[firebase-admin] Не удалось инициализировать admin SDK:', (e as Error).message);
    return null;
  }
}

export function hasAdminCredentials(): boolean {
  return Boolean(process.env.FIREBASE_PROJECT_ID && process.env.FIREBASE_CLIENT_EMAIL && process.env.FIREBASE_PRIVATE_KEY);
}




