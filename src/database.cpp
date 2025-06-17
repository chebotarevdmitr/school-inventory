#include "../include/Database.hpp"     // Подключаем собственный заголовочный файл
#include <fstream>          // Для работы с файлами
#include <stdexcept>        // Для исключений
#include <cstring>          // Для работы со строками C-style

// Конструктор класса Database
// db_path - путь к файлу базы данных
// logger - ссылка на объект логгера для записи событий
Database::Database(const std::string& db_path, Logger& logger) 
    : db_path(db_path), logger(logger) {
    
    // Записываем в лог попытку открытия БД
    logger.log(Logger::INFO, "Попытка открыть базу данных: " + db_path);
    
    // Пытаемся открыть базу данных SQLite
    if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK) {
        // Если не удалось, формируем сообщение об ошибке
        std::string err = "Не удалось открыть БД: " + std::string(sqlite3_errmsg(db));
        
        // Записываем ошибку в лог
        logger.log(Logger::ERROR, err);
        
        // Генерируем исключение
        throw std::runtime_error(err);
    }
    
    // Успешное открытие БД
    logger.log(Logger::INFO, "База данных успешно открыта");
}

// Деструктор класса Database
Database::~Database() {
    // Закрываем соединение с БД
    sqlite3_close(db);
    
    // Записываем в лог информацию о закрытии соединения
    logger.log(Logger::INFO, "Соединение с БД закрыто");
}

// Метод для выполнения SQL-запроса
// sql - строка с SQL-запросом
// Возвращает true при успешном выполнении, false при ошибке
bool Database::execute(const std::string& sql) {
    // Логируем выполняемый запрос
    logger.log(Logger::INFO, "Выполнение SQL: " + sql);
    
    // Указатель для сообщения об ошибке от SQLite
    char* errMsg = nullptr;
    
    // Выполняем SQL-запрос
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    // Проверяем результат выполнения
    if (result != SQLITE_OK) {
        // Формируем сообщение об ошибке
        std::string err = "Ошибка SQL: " + std::string(errMsg);
        
        // Логируем ошибку
        logger.log(Logger::ERROR, err);
        
        // Освобождаем память, выделенную SQLite под сообщение об ошибке
        sqlite3_free(errMsg);
        
        return false;
    }
    
    // Успешное выполнение запроса
    logger.log(Logger::INFO, "SQL выполнен успешно");
    return true;
}

// Метод для инициализации структуры базы данных
// Создает необходимые таблицы, если они не существуют
bool Database::initialize() {
    // Логируем начало инициализации
    logger.log(Logger::INFO, "Инициализация структуры БД");
    
    // 1. Проверка и создание таблицы Equipment
    if (!tableExists("Equipment")) {
        logger.log(Logger::WARNING, "Таблица Equipment не найдена, создаем...");
        
        // SQL для создания таблицы оборудования
        std::string sql = R"(
            CREATE TABLE Equipment (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,              -- Наименование оборудования
                quantity INTEGER NOT NULL,       -- Количество
                inventory_number TEXT UNIQUE,    -- Инвентарный номер (уникальный)
                room TEXT NOT NULL,              -- Кабинет/помещение
                responsible TEXT NOT NULL        -- МОЛ (Материально ответственное лицо)
            );
        )";
        
        // Пытаемся создать таблицу
        if (!execute(sql)) {
            logger.log(Logger::ERROR, "Ошибка создания таблицы Equipment");
            return false;
        }
    }
    
    // 2. Проверка и создание таблицы Classrooms (кабинеты)
    if (!tableExists("Classrooms")) {
        logger.log(Logger::WARNING, "Таблица Classrooms не найдена, создаем...");
        
        // SQL для создания таблицы кабинетов
        std::string sql = R"(
            CREATE TABLE Classrooms (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                room_number TEXT NOT NULL UNIQUE, -- Номер кабинета (уникальный)
                building TEXT NOT NULL,           -- Корпус (А, Б1, Б2)
                floor INTEGER NOT NULL,           -- Этаж
                purpose TEXT,                    -- Назначение (история, математика и т.д.)
                responsible TEXT                 -- Ответственный за кабинет
            );
        )";
        
        // Пытаемся создать таблицу
        if (!execute(sql)) {
            logger.log(Logger::ERROR, "Ошибка создания таблицы Classrooms");
            return false;
        }
        
        // Дополнительно: заполнение таблицы начальными данными
        logger.log(Logger::INFO, "Заполнение таблицы Classrooms начальными данными");
        
        // SQL для вставки данных о кабинетах
        std::string insertSql = R"(
            INSERT INTO Classrooms (room_number, building, floor, purpose) VALUES 
            ('1', 'A', 1, 'История'),
            ('2', 'A', 1, 'Русский язык'),
            ('3', 'A', 1, 'Русский язык'),
            ('4', 'A', 1, 'История'),
            ('6', 'A', 1, 'Русский язык'),
            ('7', 'A', 1, 'Военная подготовка'),
            ('8', 'A', 1, 'Английский язык'),
            ('9', 'A', 1, 'Завхоз'),
            ('10', 'A', 2, 'Английский язык'),
            ('11', 'A', 2, 'История'),
            ('12', 'A', 2, 'Русский язык'),
            ('13', 'A', 2, 'Химия'),
            ('14', 'A', 2, 'Математика'),
            ('15', 'A', 2, 'Математика'),
            ('16', 'A', 2, 'Русский язык'),
            ('17', 'A', 2, 'Воспитатели'),
            ('18', 'A', 3, 'Психолог'),
            ('19', 'A', 3, 'Информатика'),
            ('20', 'A', 3, 'Физика'),
            ('21', 'A', 3, 'Английский язык'),
            ('22', 'A', 3, 'Химия'),
            ('24', 'A', 3, 'Английский язык'),
            ('25', 'A', 3, 'Биология'),
            ('26', 'A', 3, 'Информатика'),
            ('27', 'A', 3, 'Бухгалтерия');
        )";
        
        if (!execute(insertSql)) {
            logger.log(Logger::ERROR, "Ошибка заполнения таблицы Classrooms");
            return false;
        }
    }
    
    // Успешное завершение инициализации
    logger.log(Logger::INFO, "Структура БД успешно инициализирована");
    return true;
}

// Метод для проверки существования таблицы в БД
// tableName - имя таблицы для проверки
bool Database::tableExists(const std::string& tableName) {
    // Формируем SQL-запрос для проверки существования таблицы
    std::string sql = "SELECT count(*) FROM sqlite_master "
                      "WHERE type='table' AND name='" + tableName + "';";
    
    // Подготавливаем SQL-запрос
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // Ошибка при подготовке запроса
        std::string err = "Ошибка подготовки запроса: " + std::string(sqlite3_errmsg(db));
        logger.log(Logger::ERROR, err);
        return false;
    }
    
    // Выполняем запрос
    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Если есть хотя бы одна строка в результате
        exists = (sqlite3_column_int(stmt, 0) == 1);
    }
    
    // Финализируем запрос
    sqlite3_finalize(stmt);
    
    // Логируем результат проверки
    if (exists) {
        logger.log(Logger::INFO, "Таблица существует: " + tableName);
    } else {
        logger.log(Logger::INFO, "Таблица не найдена: " + tableName);
    }
    
    return exists;
}

// Метод для выполнения SQL-скрипта из файла
// filepath - путь к файлу со скриптом
bool Database::executeScript(const std::string& filepath) {
    // Логируем начало выполнения скрипта
    logger.log(Logger::INFO, "Выполнение SQL-скрипта: " + filepath);
    
    // Открываем файл со скриптом
    std::ifstream file(filepath);
    if (!file.is_open()) {
        // Формируем сообщение об ошибке
        std::string err = "Не удалось открыть SQL-скрипт: " + filepath;
        
        // Логируем ошибку
        logger.log(Logger::ERROR, err);
        return false;
    }
    
    // Считываем содержимое файла в строку
    std::string sql(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
    
    // Закрываем файл
    file.close();
    
    // Выполняем SQL-скрипт
    return execute(sql);
}

// Метод для добавления оборудования в базу данных
bool Database::addEquipment(const std::string& name, int quantity, 
                           const std::string& inventory_number,
                           const std::string& room, 
                           const std::string& responsible) {
    // Формируем SQL-запрос для вставки данных
    std::string sql = "INSERT INTO Equipment (name, quantity, inventory_number, room, responsible) "
                      "VALUES ('" + name + "', " + std::to_string(quantity) + ", '" + 
                      inventory_number + "', '" + room + "', '" + responsible + "');";
    
    // Выполняем запрос и возвращаем результат
    return execute(sql);
}

// Метод для поиска оборудования
std::vector<std::vector<std::string>> Database::searchEquipment(const std::string& query) {
    // Вектор для хранения результатов
    std::vector<std::vector<std::string>> results;
    
    // Формируем SQL-запрос для поиска
    std::string sql = "SELECT name, quantity, inventory_number, room, responsible "
                      "FROM Equipment WHERE name LIKE '%" + query + "%' OR room LIKE '%" + query + "%';";
    
    // Подготавливаем SQL-запрос
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        // Ошибка при подготовке запроса
        std::string err = "Ошибка подготовки запроса: " + std::string(sqlite3_errmsg(db));
        logger.log(Logger::ERROR, err);
        return results;
    }
    
    // Перебираем результаты запроса
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Вектор для хранения строки результата
        std::vector<std::string> row;
        
        // Количество колонок в результате
        int colCount = sqlite3_column_count(stmt);
        
        // Перебираем колонки
        for (int i = 0; i < colCount; i++) {
            // Получаем значение колонки как строку
            const char* colText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            
            // Добавляем значение в строку результата
            if (colText) {
                row.push_back(colText);
            } else {
                row.push_back(""); // Пустая строка для NULL значений
            }
        }
        
        // Добавляем строку в общий результат
        results.push_back(row);
    }
    
    // Финализируем запрос
    sqlite3_finalize(stmt);
    
    // Логируем количество найденных результатов
    logger.log(Logger::INFO, "Найдено записей оборудования: " + std::to_string(results.size()));
    
    return results;
}