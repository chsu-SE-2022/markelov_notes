import pandas as pd
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import DBSCAN
from sklearn.metrics import silhouette_score

# Загрузка данных
data = pd.read_excel('Data.xlsx')

# Переменные
categorical_columns = ['Пол', 'Должность', 'Значимые ценности', 'Образование']
numerical_columns = ['Возраст', 'Длительность работы', 'Средняя з/п, мес., тыс. руб']

# Преобразуем все данные в числовой формат и нормализуем
X = data[categorical_columns + numerical_columns]
X_normalized = StandardScaler().fit_transform(X)  # Нормализация данных

# Применение DBSCAN
dbscan = DBSCAN(eps=0.5, min_samples=5)
data['Cluster'] = dbscan.fit_predict(X_normalized)

# Анализ кластеров
sil_score = silhouette_score(X_normalized, data['Cluster'])
print(f"Силуэтный коэффициент: {sil_score}")

# Анализ средних значений по кластерам
print(data.groupby('Cluster').mean())  # Среднее по признакам для каждого кластера

# Смотрим, какие кластеры наиболее склонны остаться
print(data.groupby('Cluster')['Готовность остаться'].value_counts())
