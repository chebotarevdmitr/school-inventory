#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP

#include <string> // Для работы со строками
#include <vector> // Для хранения данных
#include "../include/Logger.hpp" // Подключаем логгер
#include "../include/database.hpp" // Подключаем класс Database

/**
 * @brief Класс Equipment представляет оборудование школы.
 * 
 * Этот класс содержит данные об оборудовании и предоставляет методы
 * для добавления, поиска и отображения информации об оборудовании.
 */
class Equipment {
public:
    /**
     * @brief Конструктор класса Equipment.
     * 
     * Инициализирует объект оборудования.
     * 
     * @param db Ссылка на объект базы данных.
     * @param logger Ссылка на объект логгера.
     */
    Equipment(Database& db, Logger& logger);

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
    bool add(const std::string& name, int quantity,
             const std::string& inventory_number,
             const std::string& room,
             const std::string& responsible);

    /**
     * @brief Ищет оборудование по заданному условию.
     * 
     * @param query Условие поиска (например, "room = '101'").
     * @return Вектор объектов, представляющих найденное оборудование.
     */
    std::vector<std::vector<std::string>> search(const std::string& query);

    /**
     * @brief Удаляет оборудование из базы данных.
     * 
     * @param inventory_number Инвентарный номер оборудования.
     * @return true, если оборудование удалено успешно, иначе false.
     */
    bool remove(const std::string& inventory_number);

    /**
     * @brief Обновляет данные об оборудовании.
     * 
     * @param inventory_number Инвентарный номер оборудования.
     * @param new_quantity Новое количество единиц оборудования.
     * @param new_room Новый номер кабинета.
     * @param new_responsible Новое ФИО материально ответственного лица.
     * @return true, если данные обновлены успешно, иначе false.
     */
    bool update(const std::string& inventory_number, int new_quantity,
                const std::string& new_room,
                const std::string& new_responsible);

private:
    Database& db;      // Ссылка на объект базы данных
    Logger& logger;    // Ссылка на объект логгера
};

#endif // EQUIPMENT_HPP