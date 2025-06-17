#include   "../include/Logger.hpp" // Подключаем заголовочный файл класса
#include <iomanip>     // Для форматирования времени
#include <ctime>       // Для работы со временем

// Конструктор: открывает файл лога для записи
Logger::Logger(const std::string& filename) {
    // Открываем файл в режиме добавления (app), чтобы не стирать предыдущие записи
    logfile.open(filename, std::ios::app);
    
    // Проверяем, успешно ли открылся файл
    if (!logfile.is_open()) {
        // Если не удалось открыть файл, выводим ошибку в консоль
        std::cerr << "ОШИБКА: Не удалось открыть файл лога: " << filename << std::endl;
    } else {
        // Записываем сообщение о запуске логгера
        log(INFO, "Логгер успешно инициализирован");
    }
}

// Деструктор: закрывает файл лога
Logger::~Logger() {
    if (logfile.is_open()) {
        // Записываем сообщение о завершении работы
        log(INFO, "Логгер завершает работу");
        
        // Закрываем файл
        logfile.close();
    }
}

// Запись сообщения в лог
void Logger::log(Level level, const std::string& message) {
    // Если файл не открыт, ничего не делаем
    if (!logfile.is_open()) return;

    // Получаем текущее время
    std::time_t now = std::time(nullptr);          // Текущее время в секундах с эпохи
    std::tm* now_tm = std::localtime(&now);        // Преобразуем в структуру времени
    
    // Форматируем время для записи: [ГГГГ-ММ-ДД ЧЧ:ММ:СС]
    logfile << "[" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << "] ";
    
    // Записываем уровень важности в виде строки
    logfile << "[" << levelToString(level) << "] ";
    
    // Записываем само сообщение
    logfile << message << std::endl;  // std::endl добавляет перенос строки и сбрасывает буфер
    
    // Для ошибок также выводим сообщение в консоль
    if (level == ERROR) {
        std::cerr << "ОШИБКА: " << message << std::endl;
    }
}

// Преобразование уровня логирования в строку
std::string Logger::levelToString(Level level) {
    switch(level) {
        case INFO: return "INFO";        // Информационное сообщение
        case WARNING: return "WARNING";  // Предупреждение
        case ERROR: return "ERROR";      // Ошибка
        default: return "UNKNOWN";       // Неизвестный уровень (на всякий случай)
    }
}