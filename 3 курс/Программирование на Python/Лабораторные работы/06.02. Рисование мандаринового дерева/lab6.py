import turtle
import random

# Настройки начальных параметров черепахи
turtle.speed(0)  # Максимальная скорость рисования
turtle.hideturtle()  # Скрытие черепахи с экрана
turtle.left(90)  # Поворот черепахи вверх
turtle.penup()  # Поднимаем черепаху, чтобы не рисовала
turtle.setposition(0, -200)  # Устанавливаем начальную позицию черепахи
turtle.pendown()  # Опускаем черепаху для рисования
turtle.tracer(0, 0)  # Отключение автоматической анимации для контроля обновлений
turtle.color((51 / 255, 34 / 255, 17 / 255))  # Темно-коричневый цвет веток
turtle.width(20) # Толщина линии

# Построение последовательности
def process_axiom(axiom, iterations):
    sequence = ""  # Итоговая последовательность
    lvl = 0 # Уровень
    for _ in range(iterations):
        for symbol in axiom:
            if symbol == 'L':
                sequence += 'B[<TL][>TL]'
            elif symbol == 'B':
                sequence += 'TB'
            elif symbol == '[':
                sequence += '[' 
                lvl += 1
            elif symbol == ']':
                sequence += ']'
                lvl -= 1
            elif symbol == 'T':
                if random.random() <= 0.1 and lvl > 2:
                    sequence += 'R[^RL]'
                else:
                    sequence += 'T'
            else:
                sequence += symbol
        axiom = sequence
        sequence = ""   
    return axiom

# Рисование веток
def process_drawing(axiom, angle):
    stack = [] # Стек для хранения состояний
    thickness = 20 # Толщина
    length = 10 # Длина
    leaf_positions = [] # Массив для хранения позиций листьев
    for symbol in axiom:
        if symbol == "T":
            if random.random() <= 0.5:
                turtle.forward(length)
        elif symbol == "B":
            if random.random() <= 0.5:
                turtle.forward(length)
        elif symbol == "R":
            if random.random() <= 0.5:
                turtle.forward(length)
                turtle.update()
        elif symbol == "L":
            rand = random.random()
            if rand <= 0.05:
                leaf_positions.append((turtle.pos(), "orange"))
            elif rand <= 0.2:
                leaf_positions.append((turtle.pos(), "lightgreen"))
            elif rand <= 0.4:
                leaf_positions.append((turtle.pos(), "darkgreen"))
            else:
                leaf_positions.append((turtle.pos(), "green"))
        elif symbol == ">":
            turtle.right(angle - random.uniform(-14, 14))
        elif symbol == "<":
            turtle.left(angle - random.uniform(-14, 14))
        elif symbol == "^":
            ang = random.uniform(-30, 30)
            if ang < 0:
                turtle.left(ang - 25)
            else:
                turtle.left(ang + 25)
        elif symbol == "[":
            stack.append((thickness, turtle.position(), turtle.heading()))
            thickness *= 0.75
            turtle.width(thickness)
        elif symbol == "]":
            turtle.penup()
            thickness, pos, heading = stack.pop()
            turtle.setposition(pos)
            turtle.setheading(heading)
            turtle.width(thickness)
            turtle.pendown()

    return leaf_positions

# Рисование листьев и мандаринов
def draw_leaves(leaf_positions):
    block_size = 20 
    for j in range(0, len(leaf_positions), block_size):
        block = leaf_positions[j:j + block_size]
        for pos, color in block:
            turtle.penup()
            turtle.setposition(pos)
            if color == "orange": 
                turtle.dot(17, "black")
                turtle.dot(15, color)
            else:
                turtle.dot(7, "black") 
                turtle.dot(5, color)
        turtle.update()

def main():
    axiom = "TTTTL"
    iterations = 12
    angle = 14
    
    axiom = process_axiom(axiom, iterations)
    leaf_positions = process_drawing(axiom, angle)
    #draw_leaves(leaf_positions)

    turtle.update()
    turtle.mainloop()

if __name__ == "__main__":
    main()
