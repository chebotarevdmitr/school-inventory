#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h> // Библиотека SQLite3
#include <string>    // Для работы со строками
#include <vector>    // Для возврата результатов запросов
#include "../include/Logger.hpp" // Подключаем логгер

/**
 * @brief Класс для работы с базой данных SQLite3.
 * 
 * Этот класс предоставляет методы для подключения к базе данных,
 * выполнения SQL-запросов, инициализации таблиц и работы с данными.
 */
class Database {
public:
    /**
     * @brief Конструктор класса.
     * 
     * Открывает соединение с базой данных и инициализирует логгер.
     * 
     * @param db_path Путь к файлу базы данных.
     * @param logger Ссылка на объект логгера для записи событий.
     */
    Database(const std::string& db_path, Logger& logger);

    /**
     * @brief Деструктор класса.
     * 
     * Закрывает соединение с базой данных.
     */
    ~Database();

    /**
     * @brief Выполняет SQL-запрос.
     * 
     * Используется для выполнения запросов, которые не возвращают данные (например, INSERT, UPDATE, DELETE).
     * 
     * @param sql SQL-запрос для выполнения.
     * @return true, если запрос выполнен успешно, иначе false.
     */
    bool execute(const std::string& sql);

    /**
     * @brief Инициализирует базу данных.
     * 
     * Создает необходимые таблицы, если они еще не существуют.
     * 
     * @return true, если инициализация прошла успешно, иначе false.
     */
    bool initialize();

    /**
     * @brief Проверяет существование таблицы.
     * 
     * @param tableName Имя таблицы.
     * @return true, если таблица существует, иначе false.
     */
    bool tableExists(const std::string& tableName);

    /**
     * @brief Выполняет SQL-скрипт из файла.
     * 
     * Читает SQL-скрипт из указанного файла и выполняет его.
     * 
     * @param filepath Путь к файлу со скриптом.
     * @return true, если скрипт выполнен успешно, иначе false.
     */
    bool executeScript(const std::string& filepath);

    /**
     * @brief Добавляет новое оборудование в базу данных.
     * 
     * @param name Наименование оборудования.
     * @param quantity Количество единиц оборудования.
     * @param inventory_number Инвентарный номер.
     * @param room Номер кабинета.
     * @param responsible ФИО материально ответственного лица.
     * @return true, если оборудование добавлено успешно, иначе false.
     */
    bool addEquipment(const std::string& name, int quantity,
                      const std::string& inventory_number,
                      const std::string& room,
                      const std::string& responsible);

    /**
     * @brief Ищет оборудование по заданному условию.
     * 
     * @param query Условие поиска (например, "room = '101'").
     * @return Вектор векторов строк, где каждый внутренний вектор представляет строку результата.
     */
    std::vector<std::vector<std::string>> searchEquipment(const std::string& query);

private:
    sqlite3* db;                  // Указатель на объект базы данных SQLite3
    std::string db_path;          // Путь к файлу базы данных
    Logger& logger;               // Ссылка на объект логгера
};

#endif // DATABASE_HPP