import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score

# Устанавливаем максимальное количество отображаемых столбцов
pd.set_option('display.max_columns', None)

# Загрузка данных
data = pd.read_excel('KP2.xlsx')

# Убираем пробелы из имен столбцов
data.columns = data.columns.str.strip()

# Переменные
numerical_columns = ['Quantity', 'UnitPrice', 'TotalDiscount', 'SalesChannel', 'ReturnStatus', 
                     'Low', 'Medium', 'High', 'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 
                     'Aug', 'Sep', 'Oct', 'Nov', 'Dec', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 
                     'Sun', 'Apparel', 'Electronics', 'Accessories', 'Stationery', 'Furniture']

# Создаем набор данных с числовыми признаками
X = data[numerical_columns]

# Нормализация данных
scaler = StandardScaler()
X_normalized = scaler.fit_transform(X)

# Выбор оптимального числа кластеров с помощью силуэтного коэффициента
silhouette_scores = []
cluster_range = range(2, 10)
for n_clusters in cluster_range:
    kmeans = KMeans(n_clusters=n_clusters, random_state=42)
    labels = kmeans.fit_predict(X_normalized)
    sil_score = silhouette_score(X_normalized, labels)
    silhouette_scores.append(sil_score)

# Построение столбчатой гистограммы силуэтного коэффициента
plt.bar(cluster_range, silhouette_scores, color='skyblue')
plt.xlabel('Количество кластеров')
plt.ylabel('Силуэтный коэффициент')
plt.title('Оптимальное число кластеров')
plt.show()

# Применение K-Means с оптимальным числом кластеров
optimal_clusters = cluster_range[silhouette_scores.index(max(silhouette_scores))]

# Применение K-Means с оптимальным числом кластеров
kmeans = KMeans(n_clusters=optimal_clusters, random_state=42)
data['Cluster'] = kmeans.fit_predict(X_normalized)

# Анализ кластеров
print(f"\nКоличество точек в каждом кластере:\n{data['Cluster'].value_counts()}")

# Средние значения по числовым признакам для каждого кластера
cluster_means = data.groupby('Cluster')[numerical_columns].mean()
print(f"\nСредние значения числовых признаков для каждого кластера:\n{cluster_means}")

# Расчет силуэтного коэффициента
sil_score = silhouette_score(X_normalized, data['Cluster'])
print(f"\nСилуэтный коэффициент: {sil_score}")

# Вычисление корреляции между признаками
correlation_matrix = X.corr()

# Настройка графика тепловой карты
plt.figure(figsize=(12, 8))
sns.heatmap(correlation_matrix, annot=True, cmap='coolwarm', fmt='.2f', linewidths=0.5, square=True)

# Отображаем тепловую карту
plt.title('Тепловая карта корреляции между признаками')
plt.show()

# Визуализация кластеров с использованием PCA
from sklearn.decomposition import PCA

pca = PCA(n_components=2)
X_pca = pca.fit_transform(X_normalized)

plt.figure(figsize=(10, 6))
plt.scatter(X_pca[:, 0], X_pca[:, 1], c=data['Cluster'], cmap='viridis', label='Точки')
plt.title('PCA: Распределение кластеров в 2D')
plt.xlabel('PC1')
plt.ylabel('PC2')
plt.legend()
plt.show()

# Визуализация кластеров с использованием t-SNE
from sklearn.manifold import TSNE

tsne = TSNE(n_components=2, random_state=42)
X_tsne = tsne.fit_transform(X_normalized)

plt.figure(figsize=(10, 6))
plt.scatter(X_tsne[:, 0], X_tsne[:, 1], c=data['Cluster'], cmap='viridis', label='Точки')
plt.title('t-SNE: Распределение кластеров в 2D')
plt.xlabel('t-SNE 1')
plt.ylabel('t-SNE 2')
plt.legend()
plt.show()
