#include "../include/database.hpp"
#include "../include/Logger.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

// Функция для вывода результатов поиска
void printSearchResults(const std::vector<std::vector<std::string>>& results) {
    // ... (прежняя реализация) ...
}

int main() {
    // Создаем логгер
    Logger logger("school_inventory.log");
    logger.log(Logger::INFO, "Программа запущена");
    
    try {
        // Инициализация базы данных с передачей логгера
        Database db("data/school.db", logger);
        
        logger.log(Logger::INFO, "Проверка инициализации БД");
        if (!db.initialize()) {
            logger.log(Logger::ERROR, "Ошибка инициализации БД. Программа остановлена");
            return 1;
        }
        
        int choice;
        logger.log(Logger::INFO, "Главное меню активировано");
        
        while (true) {
            std::cout << "\n=== Учет материальной базы школы ===\n";
            std::cout << "1. Добавить оборудование\n"
                      << "2. Поиск оборудования\n"
                      << "3. Выход\n"
                      << "Выберите действие: ";
            std::cin >> choice;
            std::cin.ignore();  // Очистка буфера
            
            if (choice == 1) {
                logger.log(Logger::INFO, "Пользователь выбрал: Добавить оборудование");
                
                std::string name, inv_num, room, responsible;
                int quantity;
                
                std::cout << "Наименование: ";
                std::getline(std::cin, name);
                
                std::cout << "Количество: ";
                std::cin >> quantity;
                std::cin.ignore();
                
                std::cout << "Инвентарный номер: ";
                std::getline(std::cin, inv_num);
                
                std::cout << "Кабинет/помещение: ";
                std::getline(std::cin, room);
                
                std::cout << "МОЛ (ФИО): ";
                std::getline(std::cin, responsible);
                
                if (db.addEquipment(name, quantity, inv_num, room, responsible)) {
                    std::cout << "Оборудование успешно добавлено!\n";
                    logger.log(Logger::INFO, "Оборудование добавлено: " + name);
                } else {
                    std::cerr << "Ошибка при добавлении оборудования.\n";
                    logger.log(Logger::ERROR, "Ошибка добавления оборудования: " + name);
                }
                
            } else if (choice == 2) {
                logger.log(Logger::INFO, "Пользователь выбрал: Поиск оборудования");
                
                std::string query;
                std::cout << "Введите название или кабинет для поиска: ";
                std::getline(std::cin, query);
                
                logger.log(Logger::INFO, "Поисковый запрос: " + query);
                auto results = db.searchEquipment(query);
                printSearchResults(results);
                
                logger.log(Logger::INFO, "Найдено результатов: " + std::to_string(results.size()));
                
            } else if (choice == 3) {
                logger.log(Logger::INFO, "Пользователь выбрал выход");
                break;
            } else {
                std::cout << "Некорректный выбор. Попробуйте снова.\n";
                logger.log(Logger::WARNING, "Некорректный выбор в меню: " + std::to_string(choice));
            }
        }
        
    } catch (const std::exception& e) {
        logger.log(Logger::ERROR, "Исключение: " + std::string(e.what()));
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }
    
    logger.log(Logger::INFO, "Программа завершена");
    std::cout << "Работа программы завершена.\n";
    return 0;
}