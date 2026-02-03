import networkx as nx
import matplotlib.pyplot as plt
import copy


def find_euler_cycle(a):
    stack = [0]  # Начало с стартовой вершины
    cycle = []  # Массив для хранения Эйлерова цикла

    while stack:
        v = stack[-1]
        found = False
        for u in range(len(a[v])):
            if a[v][u] > 0:  # Если есть непосещённое ребро
                stack.append(u)  # Добавление вершины в стек
                a[v][u] -= 1  # Ребро помечается как посещённое
                a[u][v] -= 1
                found = True
                break
        if not found:  # Если из текущей вершины нет исходящих рёбер
            cycle.insert(0, stack.pop() + 1)  # Вершина добавляется в массив удаляется из стека

    return cycle  # Цикл возвращается


def draw_graph(a):
    g = nx.Graph()
    n = len(a)

    # Добавляем все вершины, начиная с 1
    g.add_nodes_from(range(1, n+1))

    # Создаем пустой граф для рёбер
    edge_graph = nx.Graph()

    # Заполняем пустой граф рёбрами
    for i in range(n):
        for j in range(i+1, n):
            if a[i][j] != 0:
                edge_graph.add_edge(i+1, j+1, weight=a[i][j])

    # Располагаем все вершины близко друг к другу
    pos = nx.circular_layout(g)

    # Рисуем вершины
    nx.draw(g, pos, with_labels=True, node_color='lightblue', edge_color='gray', node_size=500, font_size=10)

    # Рисуем рёбра
    for edge in edge_graph.edges(data=True):
        nx.draw_networkx_edges(g, pos, edgelist=[edge], width=edge[2]['weight'])

    # Рисуем подписи на рёбрах
    labels = nx.get_edge_attributes(edge_graph, 'weight')
    nx.draw_networkx_edge_labels(g, pos, edge_labels=labels, label_pos=0.7)

    plt.show()


def main():
    try:
        with open("input2.txt", "r") as f:
            n = int(f.readline().strip())  # количество островов

            try:
                if n > 30:
                    raise ValueError

            except ValueError:
                print("Число N больше 30")
                return 1

            a = [[0] * n for _ in range(n)]  # создание матрицы смежности
            copy_a = [[0] * n for _ in range(n)]

            try:
                for line in f:  # запись в матрицу смежности
                    u, v = map(int, line.split())
                    if u > n or v > n:
                        raise ValueError
                    a[u - 1][v - 1] += 1
                    a[v - 1][u - 1] += 1

            except ValueError:
                print("Номер одной из вершин больше числа N")
                return 1

            copy_a = copy.deepcopy(a)

    except FileNotFoundError:
        print("Ошибка открытия файла!")
        return 1

    for row in a:  # вывод матрицы смежности
        print(' '.join(map(str, row)))

    connected = True  # проверка на связность
    euler = True  # проверка на Эйлеров цикл
    if connected:
        for i in range(n):
            degree = sum(a[i])
            if degree == 0:
                connected = False
                euler = False
                break
            if degree % 2 != 0:
                euler = False
                break
    else:
        euler = False

    if connected:
        print("Граф связный")
    else:
        print("Граф несвязный")

    if euler:
        print("Граф содержит Эйлеров цикл")
        cycle = find_euler_cycle(a)
        print("Эйлеров цикл:", cycle)
    else:
        print("Граф не содержит Эйлеров цикл")

    draw_graph(copy_a)  # отображение графа


if __name__ == "__main__":
    main()
