#include <iostream> // Для работы с вводом/выводом
#include "../include/database.hpp" // Подключаем класс Database
#include "../include/Logger.hpp"   // Подключаем класс Logger

int main() {
    // Создаем объект логгера для записи событий в файл school_inventory.log
    Logger logger("school_inventory.log");

    // Создаем объект базы данных, указывая путь к файлу БД и передавая ссылку на логгер
    Database db("data/school.db", logger);

    try {
        // Инициализация базы данных (создание таблиц, если они не существуют)
        if (!db.initialize()) {
            std::cerr << "Ошибка инициализации базы данных!" << std::endl;
            return 1; // Завершаем программу с кодом ошибки
        }

        // Основной цикл программы: отображение меню и обработка выбора пользователя
        while (true) {
            // Выводим меню программы
            std::cout << "=== Учет материальной базы школы ===\n";
            std::cout << "1. Добавить оборудование\n";
            std::cout << "2. Поиск оборудования\n";
            std::cout << "3. Обновить данные об оборудовании\n";
            std::cout << "4. Удалить оборудование\n";
            std::cout << "5. Выход\n";
            std::cout << "Выберите действие: ";

            int choice; // Переменная для хранения выбора пользователя
            std::cin >> choice;
            std::cin.ignore(); // Очищаем буфер ввода после чтения числа

            // Обработка выбора пользователя через switch-case
            switch (choice) {
                case 1: { // Добавление нового оборудования
                    std::string name, inventory_number, room, responsible;
                    int quantity;

                    // Ввод данных от пользователя
                    std::cout << "Введите название оборудования: ";
                    std::getline(std::cin, name);

                    std::cout << "Введите количество: ";
                    std::cin >> quantity;
                    std::cin.ignore(); // Очищаем буфер после чтения числа

                    std::cout << "Введите инвентарный номер: ";
                    std::getline(std::cin, inventory_number);

                    std::cout << "Введите номер кабинета: ";
                    std::getline(std::cin, room);

                    std::cout << "Введите ФИО материально ответственного лица: ";
                    std::getline(std::cin, responsible);

                    // Пытаемся добавить оборудование в базу данных
                    if (db.addEquipment(name, quantity, inventory_number, room, responsible)) {
                        std::cout << "Оборудование успешно добавлено!\n";
                    } else {
                        std::cerr << "Ошибка при добавлении оборудования.\n";
                    }
                    break;
                }

                case 2: { // Поиск оборудования
                    std::string query;

                    // Ввод запроса для поиска
                    std::cout << "Введите запрос для поиска: ";
                    std::getline(std::cin, query);

                    // Выполняем поиск оборудования в базе данных
                    auto results = db.searchEquipment(query);
                    if (results.empty()) {
                        std::cout << "Оборудование не найдено.\n";
                    } else {
                        std::cout << "Результаты поиска:\n";
                        for (const auto& row : results) {
                            // Выводим найденные записи
                            std::cout << "Наименование: " << row[0] << ", Количество: " << row[1]
                                      << ", Инвентарный номер: " << row[2] << ", Кабинет: " << row[3]
                                      << ", Ответственное лицо: " << row[4] << "\n";
                        }
                    }
                    break;
                }

                case 3: { // Обновление данных об оборудовании
                    std::string inventory_number, new_room, new_responsible;
                    int new_quantity;

                    // Ввод данных для обновления
                    std::cout << "Введите инвентарный номер оборудования: ";
                    std::getline(std::cin, inventory_number);

                    std::cout << "Введите новое количество: ";
                    std::cin >> new_quantity;
                    std::cin.ignore(); // Очищаем буфер после чтения числа

                    std::cout << "Введите новый номер кабинета: ";
                    std::getline(std::cin, new_room);

                    std::cout << "Введите нового ответственного: ";
                    std::getline(std::cin, new_responsible);

                    // Пытаемся обновить данные в базе данных
                    if (db.updateEquipment(inventory_number, new_quantity, new_room, new_responsible)) {
                        std::cout << "Данные успешно обновлены!\n";
                    } else {
                        std::cerr << "Ошибка при обновлении данных.\n";
                    }
                    break;
                }

                case 4: { // Удаление оборудования
                    std::string inventory_number;

                    // Ввод инвентарного номера для удаления
                    std::cout << "Введите инвентарный номер оборудования для удаления: ";
                    std::getline(std::cin, inventory_number);

                    // Пытаемся удалить оборудование из базы данных
                    if (db.removeEquipment(inventory_number)) {
                        std::cout << "Оборудование успешно удалено!\n";
                    } else {
                        std::cerr << "Ошибка при удалении оборудования.\n";
                    }
                    break;
                }

                case 5: { // Выход из программы
                    std::cout << "Выход из программы...\n";
                    return 0; // Завершаем программу
                }

                default: { // Неверный выбор
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        // Ловим исключения и выводим сообщение об ошибке
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1; // Завершаем программу с кодом ошибки
    }

    return 0; // Успешное завершение программы
}