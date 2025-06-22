# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SchoolInventory)

# Установка стандарта C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Путь к исходным файлам основной программы
set(SOURCES
    src/main.cpp          # Главный файл программы
    src/database.cpp      # Реализация класса Database
    src/Logger.cpp        # Реализация класса Logger
    src/Equipment.cpp     # Реализация класса Equipment
)

# Путь к заголовочным файлам
set(HEADERS
    include/database.hpp  # Заголовочный файл для Database
    include/Logger.hpp    # Заголовочный файл для Logger
    include/Equipment.hpp # Заголовочный файл для Equipment
)

# Добавление исполняемого файла основной программы
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключение директории с заголовочными файлами
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Поиск библиотеки SQLite3
find_package(SQLite3 REQUIRED)

# Связывание библиотеки SQLite3 с проектом
target_link_libraries(${PROJECT_NAME} PRIVATE sqlite3)

# Настройка флагов компиляции (опционально)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Установка пути для выходного исполняемого файла
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Вывод информации о сборке
message(STATUS "Project '${PROJECT_NAME}' configured successfully.")

# *** Добавление Google Test ***
# Ищем Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Путь к тестовым файлам
set(TEST_SOURCES
    tests/database_test.cpp # Тесты для класса Database
)

# Создаем исполняемый файл для тестов
add_executable(run_tests ${TEST_SOURCES} src/database.cpp src/Logger.cpp src/Equipment.cpp)

# Подключаем заголовочные файлы для тестов
target_include_directories(run_tests PRIVATE include)

# Связываем Google Test, SQLite3 и объектные файлы с тестами
target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main sqlite3)

# Добавляем тесты
add_test(NAME runTests COMMAND run_tests)

# Вывод информации о настройке тестов
message(STATUS "Google Test configured successfully.")