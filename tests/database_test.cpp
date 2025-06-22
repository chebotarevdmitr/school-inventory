#include "../include/database.hpp"
#include "../include/Logger.hpp"
#include <gtest/gtest.h>

// Тест для проверки создания таблиц
TEST(DatabaseTest, Initialization) {
    Logger logger("test.log");
    Database db(":memory:", logger); // Используем временную БД в памяти

    // Инициализация базы данных
    ASSERT_TRUE(db.initialize());

    // Проверка существования таблиц
    EXPECT_TRUE(db.tableExists("Equipment"));
    EXPECT_TRUE(db.tableExists("Classrooms"));
}

// Тест для проверки добавления оборудования
TEST(DatabaseTest, AddEquipment) {
    Logger logger("test.log");
    Database db(":memory:", logger); // Используем временную БД в памяти

    // Инициализация базы данных
    ASSERT_TRUE(db.initialize());

    // Добавление оборудования
    bool result = db.addEquipment("Стол", 5, "INV-001", "101", "Иванов И.И.");
    ASSERT_TRUE(result);

    // Поиск оборудования
    auto results = db.searchEquipment("Стол");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0][0], "Стол");
    EXPECT_EQ(results[0][1], "5");
    EXPECT_EQ(results[0][2], "INV-001");
    EXPECT_EQ(results[0][3], "101");
    EXPECT_EQ(results[0][4], "Иванов И.И.");
}