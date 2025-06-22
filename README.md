Описание проекта
School Inventory Management System — консольное приложение для учета материальной базы школы. Позволяет управлять записями об оборудовании: добавление, поиск, обновление и удаление данных. Все записи хранятся в базе данных SQLite3.
Основные функции:

📦 Добавление оборудования с указанием названия, количества, инвентарного номера, кабинета и ответственного лица.
🔍 Поиск по названию оборудования или номеру кабинета.
✏️ Обновление данных (количество, кабинет, ответственное лицо).
🚪 Просмотр списка всех кабинетов.
📝 Логирование действий в файл school_inventory.log.

Требования
C++ компилятор с поддержкой стандарта C++17
CMake версии 3.10 или выше
Библиотека SQLite3

Установка зависимостей
Linux (Debian/Ubuntu):

sudo apt-get update
sudo apt-get install build-essential cmake libsqlite3-dev

Windows:

Скачайте CMake
Установите SQLite3
Добавьте пути к библиотекам в системную переменную PATH

Сборка проекта
git clone https://github.com/chtbotarevdmitr/school-inventory.git
cd SchoolInventory
mkdir build
cd build
cmake ..
make

Запуск
./build/bin/SchoolInventory 

Использование
После запуска отображается главное меню:

=== Учет материальной базы школы ===
1. Добавить оборудование
2. Поиск оборудования
3. Просмотр всех кабинетов
4. Выход
Выберите действие:

Добавление оборудования:
Ввод названия, количества, инвентарного номера, номера кабинета и ФИО ответственного лица.
Поиск оборудования:
Поиск по названию или номеру кабинета.
Просмотр кабинетов:
Отображение списка всех кабинетов из базы данных.

Логирование
Все действия записываются в файл school_inventory.log в формате:
[ГГГГ-ММ-ДД ЧЧ:ММ:СС] [ТИП_СООБЩЕНИЯ] Описание события

Пример записей:
[2023-10-01 12:34:56] [INFO] Оборудование успешно добавлено: Стол
[2023-10-01 12:35:10] [WARNING] Попытка добавить оборудование без инвентарного номера

Возможности для расширения
🖥️ Графический интерфейс: Реализация GUI с использованием Qt.
📤 Экспорт данных: Поддержка форматов CSV/Excel.
📊 Автоотчеты: Генерация отчетов о состоянии оборудования.
👥 Сетевое взаимодействие: Многопользовательский доступ через сеть.


Автор
Chebotarev Dmitriy
https://img.shields.io/badge/C++-17-blue https://img.shields.io/badge/SQLite-3-green https://img.shields.io/badge/CMake-3.10+-yellow

┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory]
└─$ ./build/bin/SchoolInventory 
[2025-06-22 21:12:20] [WARNING] Таблица Equipment не найдена, создаем...
[2025-06-22 21:12:20] [WARNING] Таблица Classrooms не найдена, создаем...
=== Учет материальной базы школы ===
1. Добавить оборудование
2. Поиск оборудования
3. Обновить данные об оборудовании
4. Удалить оборудование
5. Выход
Выберите действие: 1
Введите название оборудования: snol
Введите количество: 15
Введите инвентарный номер: 00002
Введите номер кабинета: 15
Введите ФИО материально ответственного лица: dima
Оборудование успешно добавлено!
=== Учет материальной базы школы ===
1. Добавить оборудование
2. Поиск оборудования
3. Обновить данные об оборудовании
4. Удалить оборудование
5. Выход
Выберите действие: 5
Выход из программы...

┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory]
└─$ 
1|snol|15|00002|15|dima
1|1|A|1|История|
2|2|A|1|Русский язык|
3|3|A|1|Русский язык|
4|4|A|1|История|
5|6|A|1|Русский язык|
6|7|A|1|Военная подготовка|
7|8|A|1|Английский язык|
8|9|A|1|Завхоз|
9|10|A|2|Английский язык|
10|11|A|2|История|
11|12|A|2|Русский язык|
12|13|A|2|Химия|
13|14|A|2|Математика|
14|15|A|2|Математика|
15|16|A|2|Русский язык|
16|17|A|2|Воспитатели|
17|18|A|3|Психолог|
18|19|A|3|Информатика|
19|20|A|3|Физика|
20|21|A|3|Английский язык|
21|22|A|3|Химия|
22|24|A|3|Английский язык|
23|25|A|3|Биология|
24|26|A|3|Информатика|
25|27|A|3|Бухгалтерия|
sqlite> .

GooleTest
┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory]
└─$ mkdir -p build
cd build 

┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory/build]
└─$ cmake .. 
-- The C compiler identification is GNU 14.2.0
-- The CXX compiler identification is GNU 14.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found SQLite3: /usr/include (found version "3.46.1")
-- Project 'SchoolInventory' configured successfully.
-- Found GTest: /usr/lib/x86_64-linux-gnu/cmake/GTest/GTestConfig.cmake (found version "1.15.0")
-- Google Test configured successfully.
-- Configuring done (0.7s)
-- Generating done (0.0s)
-- Build files have been written to: /home/dmitriy/Documents/my_basic_course/dz/school_inventory/build

┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory/build]
└─$ make 
[ 10%] Building CXX object CMakeFiles/SchoolInventory.dir/src/main.cpp.o
[ 20%] Building CXX object CMakeFiles/SchoolInventory.dir/src/database.cpp.o
[ 30%] Building CXX object CMakeFiles/SchoolInventory.dir/src/Logger.cpp.o
[ 40%] Building CXX object CMakeFiles/SchoolInventory.dir/src/Equipment.cpp.o
[ 50%] Linking CXX executable bin/SchoolInventory
[ 50%] Built target SchoolInventory
[ 60%] Building CXX object CMakeFiles/run_tests.dir/tests/database_test.cpp.o
[ 70%] Building CXX object CMakeFiles/run_tests.dir/src/database.cpp.o
[ 80%] Building CXX object CMakeFiles/run_tests.dir/src/Logger.cpp.o
[ 90%] Building CXX object CMakeFiles/run_tests.dir/src/Equipment.cpp.o
[100%] Linking CXX executable run_tests
[100%] Built target run_tests

┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory/build]
└─$ ./run_tests 
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from DatabaseTest
[ RUN      ] DatabaseTest.Initialization
[2025-06-22 22:50:14] [WARNING] Таблица Equipment не найдена, создаем...
[2025-06-22 22:50:14] [WARNING] Таблица Classrooms не найдена, создаем...
[       OK ] DatabaseTest.Initialization (1 ms)
[ RUN      ] DatabaseTest.AddEquipment
[2025-06-22 22:50:14] [WARNING] Таблица Equipment не найдена, создаем...
[2025-06-22 22:50:14] [WARNING] Таблица Classrooms не найдена, создаем...
[       OK ] DatabaseTest.AddEquipment (0 ms)
[----------] 2 tests from DatabaseTest (2 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (2 ms total)
[  PASSED  ] 2 tests.

┌──(dmitriy㉿kali)-[~/Documents/my_basic_course/dz/school_inventory/build]