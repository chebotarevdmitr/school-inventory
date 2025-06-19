#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>   // Для работы с файлами
#include <string>    // Для работы со строками
#include <iostream>  // Для вывода ошибок в консоль
#include <iomanip>   // Для форматирования вывода
#include <ctime>     // Для работы со временем
#include <mutex>     // Для многопоточной безопасности

// Класс Logger предназначен для записи логов в файл и/или консоль
class Logger {
public:
    // Уровни логирования: INFO (информация), WARNING (предупреждение), ERROR (ошибка)
    enum Level { 
        INFO,       // Обычные информационные сообщения
        WARNING,    // Предупреждения о возможных проблемах
        ERROR       // Критические ошибки
    };
    
    // Конструктор: создает или открывает файл лога
    // filename - путь к файлу лога (по умолчанию "inventory.log")
    // minLevel - минимальный уровень логирования (по умолчанию INFO)
    explicit Logger(const std::string& filename = "inventory.log", Level minLevel = INFO);
    
    // Деструктор: гарантирует закрытие файла при уничтожении объекта
    ~Logger();
    
    // Основной метод для записи сообщений в лог
    // level - уровень важности сообщения
    // message - текст сообщения
    void log(Level level, const std::string& message);

private:
    std::ofstream logfile; // Поток для записи в файл
    Level minLogLevel;     // Минимальный уровень логирования
    std::mutex logMutex;   // Мьютекс для многопоточной безопасности

    // Вспомогательная функция для преобразования уровня в строку
    std::string levelToString(Level level) const;
};

#endif // LOGGER_HPP