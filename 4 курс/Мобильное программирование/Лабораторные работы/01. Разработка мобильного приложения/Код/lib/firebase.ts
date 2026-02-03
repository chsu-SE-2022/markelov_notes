import { initializeApp } from 'firebase/app';
import { getFirestore } from 'firebase/firestore';

// Конфигурация Firebase (в реальном проекте эти данные должны быть в .env)
const firebaseConfig = {
    apiKey: "AIzaSyCU_u9jfTn6XHwnDshftOy7zB7--Q9JaL8",
    authDomain: "flickpick-5f4ab.firebaseapp.com",
    projectId: "flickpick-5f4ab",
    storageBucket: "flickpick-5f4ab.firebasestorage.app",
    messagingSenderId: "564529143651",
    appId: "1:564529143651:web:449588b431681880493d56",
    measurementId: "G-NZXQS3GRPR"
  };

// Инициализация Firebase
const app = initializeApp(firebaseConfig);

// Инициализация Firestore
export const db = getFirestore(app);

export default app;
