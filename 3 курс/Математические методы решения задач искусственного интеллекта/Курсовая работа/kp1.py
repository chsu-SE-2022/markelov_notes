import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler  # Импортируем StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

# Загрузка данных
data = pd.read_excel('KP1.xlsx')

# Разделение данных на независимые и зависимые переменные
X = data.drop('Category', axis=1)  # Независимые переменные
y = data['Category']  # Зависимая переменная

# Нормализация данных
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)  # Применяем нормализацию

# Разделение на тренировочную и тестовую выборки
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.3, random_state=42)

# Перебор возможных значений K с кросс-валидацией
k_range = range(1, 31)
k_scores = []

for k in k_range:
    knn = KNeighborsClassifier(n_neighbors=k)
    scores = cross_val_score(knn, X_train, y_train, cv=5, scoring='accuracy')  # 5-fold cross-validation
    k_scores.append(scores.mean())

# Определяем наилучшее значение K
best_k = k_range[k_scores.index(max(k_scores))]
print(f"Оптимальное значение K: {best_k}")

# Создание и обучение модели KNN с оптимальным K
knn = KNeighborsClassifier(n_neighbors=best_k)
knn.fit(X_train, y_train)

# Прогнозирование на тестовых данных
y_pred = knn.predict(X_test)

# Оценка точности модели
accuracy = accuracy_score(y_test, y_pred)
print(f"Точность модели: {accuracy:.4f}")

# Отчет по классификации
print("Матрица ошибок:")
print(confusion_matrix(y_test, y_pred))

print("Отчет по классификации:")
print(classification_report(y_test, y_pred))

# Матрица ошибок
cm = confusion_matrix(y_test, y_pred)

# Визуализация матрицы ошибок как тепловой карты
plt.figure(figsize=(6, 6))
sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
plt.xlabel('Предсказанный класс')
plt.ylabel('Истинный класс')
plt.title('Матрица ошибок')
plt.show()

# График частоты значений UnitPrice для разных классов
plt.figure(figsize=(10, 6))

# Используем seaborn для построения графиков частоты (гистограмм или KDE) для каждой категории
sns.histplot(data=data, x='UnitPrice', hue='Category', multiple='stack', kde=True)

plt.title('Частота значений UnitPrice по категориям')
plt.xlabel('UnitPrice')
plt.ylabel('Частота')
plt.show()
