#include <iostream>
#include "../include/database.hpp"
#include "../include/Logger.hpp"

int main() {
    Logger logger("school_inventory.log");
    Database db("data/school.db", logger);

    try {
        if (!db.initialize()) {
            std::cerr << "Ошибка инициализации базы данных!" << std::endl;
            return 1;
        }

        while (true) {
            std::cout << "=== Учет материальной базы школы ===\n";
            std::cout << "1. Добавить оборудование\n";
            std::cout << "2. Поиск оборудования\n";
            std::cout << "3. Обновить данные об оборудовании\n";
            std::cout << "4. Удалить оборудование\n";
            std::cout << "5. Выход\n";
            std::cout << "Выберите действие: ";

            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Очистка буфера

            switch (choice) {
                case 1: {
                    std::string name, inventory_number, room, responsible;
                    int quantity;

                    std::cout << "Введите название оборудования: ";
                    std::getline(std::cin, name);

                    std::cout << "Введите количество: ";
                    std::cin >> quantity;
                    std::cin.ignore();

                    std::cout << "Введите инвентарный номер: ";
                    std::getline(std::cin, inventory_number);

                    std::cout << "Введите номер кабинета: ";
                    std::getline(std::cin, room);

                    std::cout << "Введите ФИО материально ответственного лица: ";
                    std::getline(std::cin, responsible);

                    if (db.addEquipment(name, quantity, inventory_number, room, responsible)) {
                        std::cout << "Оборудование успешно добавлено!\n";
                    } else {
                        std::cerr << "Ошибка при добавлении оборудования.\n";
                    }
                    break;
                }
                case 2: {
                    std::string query;
                    std::cout << "Введите запрос для поиска: ";
                    std::getline(std::cin, query);

                    auto results = db.searchEquipment(query);
                    if (results.empty()) {
                        std::cout << "Оборудование не найдено.\n";
                    } else {
                        std::cout << "Результаты поиска:\n";
                        for (const auto& row : results) {
                            std::cout << "Наименование: " << row[0] << ", Количество: " << row[1]
                                      << ", Инвентарный номер: " << row[2] << ", Кабинет: " << row[3]
                                      << ", Ответственное лицо: " << row[4] << "\n";
                        }
                    }
                    break;
                }
                case 3: {
                    std::string inventory_number, new_room, new_responsible;
                    int new_quantity;

                    std::cout << "Введите инвентарный номер оборудования: ";
                    std::getline(std::cin, inventory_number);

                    std::cout << "Введите новое количество: ";
                    std::cin >> new_quantity;
                    std::cin.ignore();

                    std::cout << "Введите новый номер кабинета: ";
                    std::getline(std::cin, new_room);

                    std::cout << "Введите нового ответственного: ";
                    std::getline(std::cin, new_responsible);

                    if (db.updateEquipment(inventory_number, new_quantity, new_room, new_responsible)) {
                        std::cout << "Данные успешно обновлены!\n";
                    } else {
                        std::cerr << "Ошибка при обновлении данных.\n";
                    }
                    break;
                }
                case 4: {
                    std::string inventory_number;
                    std::cout << "Введите инвентарный номер оборудования для удаления: ";
                    std::getline(std::cin, inventory_number);

                    if (db.removeEquipment(inventory_number)) {
                        std::cout << "Оборудование успешно удалено!\n";
                    } else {
                        std::cerr << "Ошибка при удалении оборудования.\n";
                    }
                    break;
                }
                case 5: {
                    std::cout << "Выход из программы...\n";
                    return 0;
                }
                default: {
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}