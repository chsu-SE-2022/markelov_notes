import turtle

# Функция для рисования n-угольника
def draw_polygon(shape, size):
    for _ in range(shape):
        turtle.forward(size)
        turtle.right(360/shape)

# Функция для рисования круга
def draw_circle(size):
    turtle.circle(size)

# Функция для рисования звезды
def draw_star(size):
    for _ in range(5):
        turtle.forward(size)
        turtle.right(144)

# Основная программа
def main():
    cont = 'y'
    while cont.lower() == 'y':
        shape = int(input("Выберите фигуру (1 - круг, 2 - звезда, 3 - треугольник, 4 - квадрат, 5/6/7/... - 5/6/7/...-угольник): "))
        size = int(input("Введите размер фигуры: "))
        
        if shape == 1:
            draw_circle(size)
        elif shape == 2:
            draw_star(size)
        elif shape >= 3:
            draw_polygon(shape, size)
        else:
            print("Неизвестная фигура!")
        
        cont = input("Хотите нарисовать еще одну фигуру? (y/n): ")

    turtle.done()

if __name__ == "__main__":
    main()