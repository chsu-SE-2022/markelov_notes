import timeit

# ДОСТУП

def list_access(list1, num):
    print(list1[num])

def dict_access(dict1, key):
    print(dict1.get(key, "unknown"))

# ДОБАВЛЕНИЕ

def list_add(list1, num, element):
    list1.insert(num, element)
    
def dict_add(dict1, key, element):
    dict1[key] = element

# УДАЛЕНИЕ

def list_delete(list1, num):
    list1.pop(num)

def dict_delete(dict1, key):
    del dict1[key]

# ОБЪЕДИНЕНИЕ

def list_merge(list1, list2):
    return list1 + list2

def dict_merge(dict1, dict2):
    return dict1 | dict2

# ПЕРЕСЕЧЕНИЕ

def list_intersection(list1, list2):
    print(set(list1) & set(list2))

# Для словаря такой операции нет

# РАЗНИЦА

def list_difference(list1, list2):
    print(set(list1) - set(list2))

# Для словаря такой операции нет

# СРАВНЕНИЕ

def list_comparison(list1, list2):
    print(list1 == list2)

def dict_comparison(dict1, dict2):
    print(dict1 == dict2)

# ПОИСК

def list_search(list1, num):
    try:
        print("Элемент находится на", list1.index(num), "позиции")
    except ValueError:
        print("Элемент не найден")

def dict_search(dict1, element):
    current = element in dict1
    if current: print("Элемент найден")
    else: print("Элемент не найден")

# СОРТИРОВКА

def list_sort(list3):
    list3.sort()

def dict_sort(dict1):
    print(sorted(dict1.keys()))

# Загрузка данных из файлов
def load():
    list1 = []
    list2 = []
    list3 = []

    dict1 = {}
    dict2 = {}

    # Чтение первого списка из файла
    with open('list1.txt', 'r') as f:
        list1 = [line.strip() for line in f]

    # Чтение второго списка из файла
    with open('list2.txt', 'r') as f:
        list2 = [line.strip() for line in f]

    # Чтение третьего списка из файла
    with open('list3.txt', 'r') as f:
        list3 = [line.strip() for line in f]

    # Чтение первого словаря из файла
    with open('dict1.txt', 'r') as f:
        for line in f:
            key, value = line.strip().split(': ')
            dict1[key] = value

    # Чтение второго словаря из файла
    with open('dict2.txt', 'r') as f:
        for line in f:
            key, value = line.strip().split(': ')
            dict2[key] = value

    return list1, list2, list3, dict1, dict2

# Сохранение в файл
def save(filename, list_data, dict_data):
    with open(filename, 'w') as f:
        f.write("Список:\n")
        for item in list_data:
            f.write(str(item) + "\n")
        f.write("\nСловарь:\n")
        for key, value in dict_data.items():
            f.write(f"{key}: {value}\n")

def main():
    list1, list2, list3, dict1, dict2 = load()
    print("Список 1:", list1)
    print("Словарь 1:", dict1)
    print("Список 2:", list2)
    print("Словарь 2:", dict2)
    print("Список 3:", list3)

    print("\nДоступ к элементам:")
    print(f"Доступ к списку выполнен за {timeit.timeit(lambda: list_access(list1, 0), number = 1) * 1000:.3f} миллисекунд")
    print(f"Доступ к словарю выполнен за {timeit.timeit(lambda: dict_access(dict1, "age"), number = 1) * 1000:.3f} миллисекунд")

    print("\nДобавление элементов:") 
    print(f"Добавление элемента в список выполнено за {timeit.timeit(lambda: list_add(list1, 3, "Cherepovets"), number = 1) * 1000:.3f} миллисекунд")
    print(list1[3])
    print(f"Добавление элемента в словарь выполнено за {timeit.timeit(lambda: dict_add(dict1, "city", "Moscow"), number = 1) * 1000:.3f} миллисекунд")
    print(dict1.get("city", "unknown"))

    print("\nУдаление элементов:")
    print(f"Удаление элемента из списка выполнено за {timeit.timeit(lambda: list_delete(list1, 4), number = 1) * 1000:.3f} миллисекунд")
    print(list1)
    print(f"Удаление элемента из словаря выполнено за {timeit.timeit(lambda: dict_delete(dict1, "birthdate"), number = 1) * 1000:.3f} миллисекунд")
    print(dict1.get("birthdate", "unknown"))

    print("\nОбъединение структур:")
    print(f"Объединение списков выполнено за {timeit.timeit(lambda: list_merge(list1, list2), number = 1) * 1000:.3f} миллисекунд")
    list1 = list_merge(list1, list2)
    print(list1)
    print(f"Объединение словарей выполнено за {timeit.timeit(lambda: dict_merge(dict1, dict2), number = 1) * 1000:.3f} миллисекунд")
    dict1 = dict_merge(dict1, dict2)
    print(dict1)

    print("\nПересечение структур:")
    print(f"Пересечение списков найдено за {timeit.timeit(lambda: list_intersection(list1, list2), number = 1) * 1000:.3f} миллисекунд")
    print("Для словаря операции пересечения нет")

    print("\nРазница структур:")
    print(f"Разница списков найдена за {timeit.timeit(lambda: list_difference(list1, list2), number = 1) * 1000:.3f} миллисекунд")
    print("Для словаря операции разницы нет")

    print("\nСравнение структур:")
    print(f"Сравнение разных списков выполнено за {timeit.timeit(lambda: list_comparison(list1, list2), number = 1) * 1000:.3f} миллисекунд")
    list2 = list1
    print(f"Сравнение одинаковых списков выполнено за {timeit.timeit(lambda: list_comparison(list1, list2), number = 1) * 1000:.3f} миллисекунд")
    print(f"Сравнение разных словарей выполнено за {timeit.timeit(lambda: dict_comparison(dict1, dict2), number = 1) * 1000:.3f} миллисекунд")
    dict2 = dict1
    print(f"Сравнение одинаковых словарей выполнено за {timeit.timeit(lambda: dict_comparison(dict1, dict2), number = 1) * 1000:.3f} миллисекунд")

    print("\nПоиск элементов:")
    print(f"Поиск существующего элемента в списке выполнен за {timeit.timeit(lambda: list_search(list1, 25), number = 1) * 1000:.3f} миллисекунд")
    print(f"Поиск несуществующего элемента в списке выполнен за {timeit.timeit(lambda: list_search(list1, 30), number = 1) * 1000:.3f} миллисекунд")
    print(f"Поиск существующего элемента в словаре выполнен за {timeit.timeit(lambda: dict_search(dict1, "age"), number = 1) * 1000:.3f} миллисекунд")
    print(f"Поиск несуществующего элемента в словаре выполнен за {timeit.timeit(lambda: dict_search(dict1, "birthdate"), number = 1) * 1000:.3f} миллисекунд")

    print("\nСортировка элементов:")
    print(f"Сортировка списка выполнена за {timeit.timeit(lambda: list_sort(list3), number = 1) * 1000:.3f} миллисекунд")
    print(list3)
    print(f"Сортировка словаря выполнена за {timeit.timeit(lambda: dict_sort(dict1), number = 1) * 1000:.3f} миллисекунд")
    print(dict1)

    save('data.txt', list1, dict1)

if __name__ == "__main__":
    main()