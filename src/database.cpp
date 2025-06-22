#include "../include/database.hpp" // Подключаем собственный заголовочный файл
#include <fstream>                 // Для работы с файлами
#include <stdexcept>               // Для исключений
#include <cstring>                 // Для работы со строками C-style

// Конструктор класса Database
Database::Database(const std::string& db_path, Logger& logger)
    : db(nullptr), db_path(db_path), logger(logger) {
    logger.log(Logger::INFO, "Попытка открыть базу данных: " + db_path);

    if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK) {
        std::string err = "Не удалось открыть БД: " + std::string(sqlite3_errmsg(db));
        logger.log(Logger::ERROR, err);
        throw std::runtime_error(err);
    }

    logger.log(Logger::INFO, "База данных успешно открыта");
}

// Деструктор класса Database
Database::~Database() {
    if (db) {
        sqlite3_close(db);
        logger.log(Logger::INFO, "Соединение с БД закрыто");
    }
}

// Метод для выполнения SQL-запроса
bool Database::execute(const std::string& sql) {
    logger.log(Logger::INFO, "Выполнение SQL: " + sql);

    char* errMsg = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK) {
        std::string err = "Ошибка SQL: " + std::string(errMsg);
        logger.log(Logger::ERROR, err);
        sqlite3_free(errMsg);
        return false;
    }

    logger.log(Logger::INFO, "SQL выполнен успешно");
    return true;
}

// Метод для инициализации структуры базы данных
bool Database::initialize() {
    logger.log(Logger::INFO, "Инициализация структуры БД");

    if (!tableExists("Equipment")) {
        logger.log(Logger::WARNING, "Таблица Equipment не найдена, создаем...");

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

        if (!execute(sql)) {
            logger.log(Logger::ERROR, "Ошибка создания таблицы Equipment");
            return false;
        }
    }

    if (!tableExists("Classrooms")) {
        logger.log(Logger::WARNING, "Таблица Classrooms не найдена, создаем...");

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

        if (!execute(sql)) {
            logger.log(Logger::ERROR, "Ошибка создания таблицы Classrooms");
            return false;
        }

        logger.log(Logger::INFO, "Заполнение таблицы Classrooms начальными данными");

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

    logger.log(Logger::INFO, "Структура БД успешно инициализирована");
    return true;
}

// Метод для проверки существования таблицы
bool Database::tableExists(const std::string& tableName) {
    std::string sql = "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='" + tableName + "';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::string err = "Ошибка подготовки запроса: " + std::string(sqlite3_errmsg(db));
        logger.log(Logger::ERROR, err);
        return false;
    }

    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = (sqlite3_column_int(stmt, 0) == 1);
    }

    sqlite3_finalize(stmt);

    if (exists) {
        logger.log(Logger::INFO, "Таблица существует: " + tableName);
    } else {
        logger.log(Logger::INFO, "Таблица не найдена: " + tableName);
    }

    return exists;
}

// Метод для выполнения SQL-скрипта из файла
bool Database::executeScript(const std::string& filepath) {
    logger.log(Logger::INFO, "Выполнение SQL-скрипта: " + filepath);

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::string err = "Не удалось открыть SQL-скрипт: " + filepath;
        logger.log(Logger::ERROR, err);
        return false;
    }

    std::string sql((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return execute(sql);
}

// Метод для добавления оборудования
bool Database::addEquipment(const std::string& name, int quantity,
                            const std::string& inventory_number,
                            const std::string& room,
                            const std::string& responsible) {
    std::string sql = "INSERT INTO Equipment (name, quantity, inventory_number, room, responsible) "
                      "VALUES ('" + name + "', " + std::to_string(quantity) + ", '" +
                      inventory_number + "', '" + room + "', '" + responsible + "');";

    return execute(sql);
}

// Метод для обновления данных об оборудовании
bool Database::updateEquipment(const std::string& inventory_number, int new_quantity,
                               const std::string& new_room,
                               const std::string& new_responsible) {
    std::string sql = "UPDATE Equipment SET "
                      "quantity = " + std::to_string(new_quantity) + ", "
                      "room = '" + new_room + "', "
                      "responsible = '" + new_responsible + "' "
                      "WHERE inventory_number = '" + inventory_number + "';";

    return execute(sql);
}

// Метод для удаления оборудования
bool Database::removeEquipment(const std::string& inventory_number) {
    std::string sql = "DELETE FROM Equipment WHERE inventory_number = '" + inventory_number + "';";
    return execute(sql);
}

// Метод для поиска оборудования
std::vector<std::vector<std::string>> Database::searchEquipment(const std::string& query) {
    std::vector<std::vector<std::string>> results;

    std::string sql = "SELECT name, quantity, inventory_number, room, responsible "
                      "FROM Equipment WHERE name LIKE '%" + query + "%' OR room LIKE '%" + query + "%';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::string err = "Ошибка подготовки запроса: " + std::string(sqlite3_errmsg(db));
        logger.log(Logger::ERROR, err);
        return results;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::vector<std::string> row;
        int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; ++i) {
            const char* colText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.push_back(colText ? colText : "");
        }

        results.push_back(row);
    }

    sqlite3_finalize(stmt);
    logger.log(Logger::INFO, "Найдено записей оборудования: " + std::to_string(results.size()));
    return results;
}