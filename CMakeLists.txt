cmake_minimum_required(VERSION 3.10)
project(SchoolInventory)

# Настройка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск библиотеки SQLite3
find_package(SQLite3 REQUIRED)

# Включаем папку с заголовочными файлами
include_directories(include)

# Список исходных файлов
set(SOURCES
    src/main.cpp
    src/database.cpp
    src/Logger.cpp
    src/Equipment.cpp
)

# Создание исполняемого файла
add_executable(SchoolInventory ${SOURCES})

# Подключение библиотеки SQLite3
target_link_libraries(SchoolInventory PRIVATE SQLite::SQLite3)

# Копирование данных в билд-директорию
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)
add_custom_command(TARGET SchoolInventory POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data
    ${CMAKE_BINARY_DIR}/data
)

# Опция для тестов (будем добавлять позже)
option(ENABLE_TESTS "Enable tests" OFF)
if(ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()