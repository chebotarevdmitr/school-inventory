# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(SchoolInventory)

# Установка стандарта C++ (например, C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Путь к исходным файлам
set(SOURCES
    src/main.cpp
    src/Database.cpp
    src/Logger.cpp
    src/Equipment.cpp
)

# Путь к заголовочным файлам
set(HEADERS
    include/database.hpp
    include/Logger.hpp
    include/Equipment.hpp
)

# Добавление исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключение директории с заголовочными файлами
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Поиск библиотеки SQLite3
find_package(SQLite3 REQUIRED)

# Связывание библиотеки SQLite3 с проектом
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite3::SQLite3)

# Включение каталога для поиска заголовочных файлов SQLite3
if(SQLite3_FOUND)
    message(STATUS "SQLite3 library found: ${SQLite3_LIBRARIES}")
else()
    message(FATAL_ERROR "SQLite3 library not found!")
endif()

# Настройка флагов компиляции (опционально)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Установка пути для выходного исполняемого файла
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Вывод информации о сборке
message(STATUS "Project '${PROJECT_NAME}' configured successfully.")