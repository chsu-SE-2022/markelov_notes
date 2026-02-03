import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report

# Чтение данных из Excel файла
file_path = 'Data2.xlsx'  # Укажите путь к вашему файлу
data = pd.read_excel(file_path)

# Преобразуем данные в формат numpy для работы с sklearn
X = data[['Возраст', 'Длительность работы', 'Пол', 'Должность', 'Значимые ценности', 'Образование', 'Средняя з/п, мес., тыс. руб']].values
y = data['Готовность остаться'].values  # Зависимая переменная

# Разделение данных на обучающую и тестовую выборки
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Создание модели KNN (k=3 для примера)
knn = KNeighborsClassifier(n_neighbors=3)

# Обучение модели
knn.fit(X_train, y_train)

# Оценка модели
y_pred = knn.predict(X_test)

# Вывод отчета о классификации
print(classification_report(y_test, y_pred))
