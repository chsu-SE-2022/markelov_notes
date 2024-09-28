import math

# Ввод значений a, b, c, d
a = float(input("Введите значение a: "))
b = float(input("Введите значение b: "))
c = float(input("Введите значение c: "))
d = float(input("Введите значение d: "))

print("Пример №1")
# Проверка деления на 0
if c != 0 and d > 0: 
    # Вычисление выражения
    result1 = int(math.exp(a)) | int((b/c)-(d*5)) | int(math.log2(d))
else:
    # Присваиваем бесконечность
    result1 = float('inf')

# Вывод результата
print("e^a or b/c - d*5 or log(2)d = ", result1)

print("Пример №2")
# Проверка деления на 0
if b+c != 0: 
    # Вычисление выражения
    result2 = (a**2-4)/(b+c) - (~int(d))
else:
    # Присваиваем бесконечность
    result2 = float('inf')   

# Вывод результата
print("(a^2-4)/(b+c) - not d =  ", result2)