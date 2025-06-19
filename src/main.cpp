#include "../include/database.hpp"
#include "../include/Logger.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

// Функция для вывода результатов поиска
void printSearchResults(const std::vector<std::vector<std::string>>& results) {
    if (results.empty()) {
        std::cout << "Ничего не найдено.\n";
        return;
    }

    std::cout << std::setw(20) << "Наименование"
              << std::setw(10) << "Количество"
              << std::setw(20) << "Инвентарный номер"
              << std::setw(15) << "Кабинет"
              << std::setw(20) << "МОЛ" << "\n";
    std::cout << std::string(85, '-') << "\n";

    for (const auto& row : results) {
        std::cout << std::setw(20) << row[0]  // Наименование
                  << std::setw(10) << row[1]  // Количество
                  << std::setw(20) << row[2]  // Инвентарный номер
                  << std::setw(15) << row[3]  // Кабинет
                  << std::setw(20) << row[4]  // МОЛ
                  << "\n";
    }
}

int main() {
    try {
        // Создаем объект логгера
        Logger logger("school_inventory.log");
        logger.log(Logger::INFO, "Программа запущена");

        // Инициализация базы данных
        Database db("data/school.db", logger);

        // Проверяем инициализацию базы данных
        if (!db.initialize()) {
            logger.log(Logger::ERROR, "Ошибка инициализации БД. Программа остановлена");
            return 1;
        }

        int choice;
        while (true) {
            std::cout << "\n=== Учет материальной базы школы ===\n";
            std::cout << "1. Добавить оборудование\n"
                      << "2. Поиск оборудования\n"
                      << "3. Просмотр всех кабинетов\n"
                      << "4. Выход\n"
                      << "Выберите действие: ";
            std::cin >> choice;
            std::cin.ignore(); // Очистка буфера

            if (choice == 1) {
                logger.log(Logger::INFO, "Пользователь выбрал: Добавить оборудование");

                std::string name, inv_num, room, responsible;
                int quantity;

                std::cout << "Наименование: ";
                std::getline(std::cin, name);
                if (name.empty()) {
                    std::cerr << "Ошибка: Наименование не может быть пустым.\n";
                    logger.log(Logger::WARNING, "Попытка добавить оборудование без наименования");
                    continue;
                }

                std::cout << "Количество: ";
                while (!(std::cin >> quantity) || quantity <= 0) {
                    std::cerr << "Ошибка: Введите корректное количество (целое положительное число).\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                std::cin.ignore();

                std::cout << "Инвентарный номер: ";
                std::getline(std::cin, inv_num);
                if (inv_num.empty()) {
                    std::cerr << "Ошибка: Инвентарный номер не может быть пустым.\n";
                    logger.log(Logger::WARNING, "Попытка добавить оборудование без инвентарного номера");
                    continue;
                }

                std::cout << "Кабинет/помещение: ";
                std::getline(std::cin, room);
                if (room.empty()) {
                    std::cerr << "Ошибка: Кабинет не может быть пустым.\n";
                    logger.log(Logger::WARNING, "Попытка добавить оборудование без указания кабинета");
                    continue;
                }

                std::cout << "МОЛ (ФИО): ";
                std::getline(std::cin, responsible);
                if (responsible.empty()) {
                    std::cerr << "Ошибка: ФИО МОЛ не может быть пустым.\n";
                    logger.log(Logger::WARNING, "Попытка добавить оборудование без указания МОЛ");
                    continue;
                }

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

                if (query.empty()) {
                    std::cerr << "Ошибка: Поисковый запрос не может быть пустым.\n";
                    logger.log(Logger::WARNING, "Попытка выполнить пустой поисковый запрос");
                    continue;
                }

                logger.log(Logger::INFO, "Поисковый запрос: " + query);
                auto results = db.searchEquipment(query);
                printSearchResults(results);
                logger.log(Logger::INFO, "Найдено результатов: " + std::to_string(results.size()));

            } else if (choice == 3) {
                logger.log(Logger::INFO, "Пользователь выбрал: Просмотр всех кабинетов");

                std::vector<std::string> rooms = db.getAllRooms();
                if (rooms.empty()) {
                    std::cout << "Кабинеты не найдены.\n";
                    logger.log(Logger::WARNING, "Список кабинетов пуст");
                    continue;
                }

                std::cout << "Список всех кабинетов:\n";
                for (const auto& room : rooms) {
                    std::cout << "- " << room << "\n";
                }
                logger.log(Logger::INFO, "Показано кабинетов: " + std::to_string(rooms.size()));

            } else if (choice == 4) {
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