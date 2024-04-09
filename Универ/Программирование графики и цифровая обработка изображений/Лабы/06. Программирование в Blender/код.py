import bpy
import random

def create_primitive(position):              
    primitives = ['CUBE', 'UV SPHERE', 'CYLINDER', 'CONE']
    random_primitive = random.choice(primitives)
    
    if random_primitive == 'CUBE':
        bpy.ops.mesh.primitive_cube_add(size = 1, location = position)
    elif random_primitive == 'UV SPHERE':
        bpy.ops.mesh.primitive_uv_sphere_add(radius = 0.5, location = position)
    elif random_primitive == 'CYLINDER':
        bpy.ops.mesh.primitive_cylinder_add(radius = 0.5, depth = 1, location = position)
    elif random_primitive == 'CONE':
        bpy.ops.mesh.primitive_cone_add(radius1 = 0.5, depth = 1, location = position)    

rows = 20                                   # Количество рядов
row_primitives = 5                          # Количество примитивов в одном ряду
height = 1.0                                # Высота ряда
distance = 1.0                              # Pасстояние
start_position = (0, 0, 0)

for row in range(rows):
    new_position = (start_position[0], start_position[1], start_position[2] + row * height)

    for i in range(row_primitives):
        for j in range(row_primitives):
            x = new_position[0] + i * distance
            y = new_position[1] + j * distance
            finish_position = (x, y, new_position[2])
            create_primitive(finish_position)