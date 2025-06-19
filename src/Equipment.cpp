#include "../include/Equipment.hpp" // Подключаем собственный заголовочный файл
#include <iostream>                 // Для вывода ошибок

/**
 * @brief Конструктор класса Equipment.
 * 
 * Инициализирует объект оборудования, связывая его с базой данных и логгером.
 * 
 * @param db Ссылка на объект базы данных.
 * @param logger Ссылка на объект логгера.
 */
Equipment::Equipment(Database& db, Logger& logger)
    : db(db), logger(logger) {
    logger.log(Logger::INFO, "Создан объект Equipment");
}

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
bool Equipment::add(const std::string& name, int quantity,
                    const std::string& inventory_number,
                    const std::string& room,
                    const std::string& responsible) {
    logger.log(Logger::INFO, "Попытка добавить оборудование: " + name);

    if (db.addEquipment(name, quantity, inventory_number, room, responsible)) {
        logger.log(Logger::INFO, "Оборудование успешно добавлено: " + name);
        return true;
    }

    logger.log(Logger::ERROR, "Ошибка добавления оборудования: " + name);
    return false;
}

/**
 * @brief Ищет оборудование по заданному условию.
 * 
 * @param query Условие поиска (например, "room = '101'").
 * @return Вектор объектов, представляющих найденное оборудование.
 */
std::vector<std::vector<std::string>> Equipment::search(const std::string& query) {
    logger.log(Logger::INFO, "Поиск оборудования: " + query);

    auto results = db.searchEquipment(query);
    logger.log(Logger::INFO, "Найдено записей оборудования: " + std::to_string(results.size()));

    return results;
}

/**
 * @brief Удаляет оборудование из базы данных.
 * 
 * @param inventory_number Инвентарный номер оборудования.
 * @return true, если оборудование удалено успешно, иначе false.
 */
bool Equipment::remove(const std::string& inventory_number) {
    logger.log(Logger::INFO, "Попытка удалить оборудование с инвентарным номером: " + inventory_number);

    if (db.removeEquipment(inventory_number)) {
        logger.log(Logger::INFO, "Оборудование успешно удалено: " + inventory_number);
        return true;
    }

    logger.log(Logger::ERROR, "Ошибка удаления оборудования: " + inventory_number);
    return false;
}

/**
 * @brief Обновляет данные об оборудовании.
 * 
 * @param inventory_number Инвентарный номер оборудования.
 * @param new_quantity Новое количество единиц оборудования.
 * @param new_room Новый номер кабинета.
 * @param new_responsible Новое ФИО материально ответственного лица.
 * @return true, если данные обновлены успешно, иначе false.
 */
bool Equipment::update(const std::string& inventory_number, int new_quantity,
                       const std::string& new_room,
                       const std::string& new_responsible) {
    logger.log(Logger::INFO, "Попытка обновить данные оборудования: " + inventory_number);

    if (db.updateEquipment(inventory_number, new_quantity, new_room, new_responsible)) {
        logger.log(Logger::INFO, "Данные оборудования успешно обновлены: " + inventory_number);
        return true;
    }

    logger.log(Logger::ERROR, "Ошибка обновления данных оборудования: " + inventory_number);
    return false;
}