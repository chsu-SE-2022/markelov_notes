@echo off
chcp 65001
setlocal enabledelayedexpansion

:: Проверка на наличие аргумента
if "%1"=="" (
    echo Не задано количество файлов.
    exit /b
)

:: Чтение количества файлов из аргумента
set count=%1

:: Цикл для создания файлов
for /l %%i in (1,1,%count%) do (
    set filename=file_%%i.txt
    echo Создание файла !filename!
    
    :: Заполнение файла строками
    for /l %%j in (1,1,%%i) do (
        echo Строка %%j >> !filename!
    )
)

echo Файлы успешно созданы.
