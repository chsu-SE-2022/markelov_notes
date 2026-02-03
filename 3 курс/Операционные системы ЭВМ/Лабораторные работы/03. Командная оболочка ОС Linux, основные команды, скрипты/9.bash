#!/bin/bash

# Если путь не передан, используем текущий каталог
directory="${1:-.}"

# Проверка, существует ли каталог
if [ ! -d "$directory" ]; then
    echo "Указанный путь не является каталогом."
    exit 1
fi

# Инициализация счетчиков
txt_count=0
exec_count=0
dir_count=0
other_count=0

# Проходим по всем файлам в каталоге
for file in "$directory"/*; do
    if [ -f "$file" ]; then
        # Проверяем, текстовый ли это файл
        if [[ "$file" == *.txt ]]; then
            ((txt_count++))
        # Проверяем, является ли файл исполняемым
        elif [ -x "$file" ]; then
            ((exec_count++))
        else
            ((other_count++))
        fi
    elif [ -d "$file" ]; then
        ((dir_count++))
    fi
done

# Выводим сводку
echo "Количество текстовых файлов (.txt): $txt_count"
echo "Количество исполняемых файлов (с атрибутом 'x'): $exec_count"
echo "Количество каталогов: $dir_count"
echo "Количество других файлов: $other_count"
