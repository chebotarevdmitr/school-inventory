#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <sqlite3.h>
#include <string>
#include <vector>
#include "../include/Logger.hpp"  // Подключаем логгер

class Database {
public:
    // Добавляем логгер в конструктор
    Database(const std::string& db_path, Logger& logger);
    ~Database();

    bool execute(const std::string& sql);
    bool initialize();
    bool tableExists(const std::string& tableName);
    bool executeScript(const std::string& filepath);
    
    bool addEquipment(const std::string& name, int quantity, 
                     const std::string& inventory_number,
                     const std::string& room, 
                     const std::string& responsible);
    
    std::vector<std::vector<std::string>> searchEquipment(const std::string& query);

private:
    sqlite3* db;
    std::string db_path;
    Logger& logger;  // Ссылка на логгер
};

#endif // DATABASE_HPP