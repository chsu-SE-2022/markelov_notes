import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
import statsmodels.api as sm

# Чтение данных из xlsx файла
df = pd.read_excel('KP3.xlsx')

# Предполагаем, что последний столбец - целевая переменная
X = df.iloc[:, :-1].values  # Все столбцы, кроме последнего (признаки)
y = df.iloc[:, -1].values   # Последний столбец (целевая переменная)

# Получаем названия столбцов признаков
columns = df.columns[:-1]

# Создание модели линейной регрессии (sklearn)
model = LinearRegression()

# Обучение модели
model.fit(X, y)

# Коэффициенты линейной регрессии
coefficients = model.coef_
intercept = model.intercept_

# Прогнозирование на тех же данных
y_pred = model.predict(X)

# Вычисление R^2 (коэффициент детерминации)
r2 = r2_score(y, y_pred)

# Вычисление MSE (среднеквадратичная ошибка)
mse = mean_squared_error(y, y_pred)

# Форматированный вывод с названием столбца и коэффициентом
print("Коэффициенты:")
for col, coef in zip(columns, coefficients):
    print(f"{col} = {coef:.6f}")
print(f"\nСвободный член (перехват): {intercept:.6f}")
print(f"\nКоэффициент детерминации R^2: {r2:.6f}")
print(f"\nСреднеквадратичная ошибка MSE: {mse:.6f}")

# Используем statsmodels для расчета p-value
# Добавляем константу (свободный член)
X_with_intercept = sm.add_constant(X)

# Строим модель с использованием statsmodels
stats_model = sm.OLS(y, X_with_intercept).fit()

# Выводим сводную таблицу результатов с большим количеством знаков после запятой
print("\nРезультаты регрессии (statsmodels):")
print(stats_model.summary2(xname=["const"] + list(columns)).tables[1].to_string(float_format='%.20f'))

# Визуализация результатов
plt.figure(figsize=(10, 6))

# График истинных значений vs предсказанных значений
plt.scatter(y, y_pred, color='blue', label='Предсказания vs Истинные значения')

# Линия y = x для отображения идеального соответствия
plt.plot([y.min(), y.max()], [y.min(), y.max()], color='red', linestyle='--', label='Идеальное соответствие')

plt.xlabel('Истинные значения')
plt.ylabel('Предсказанные значения')
plt.title('Истинные значения vs Предсказанные значения')
plt.legend()
plt.show()
