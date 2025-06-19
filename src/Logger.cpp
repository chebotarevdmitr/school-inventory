#include "../include/Logger.hpp" // Подключаем заголовочный файл класса
#include <iomanip>     // Для форматирования времени
#include <ctime>       // Для работы со времени
#include <stdexcept>   // Для обработки исключений

// Конструктор: открывает файл лога для записи
Logger::Logger(const std::string& filename, Level minLevel)
    : minLogLevel(minLevel) {
    try {
        // Открываем файл в режиме добавления (app), чтобы не стирать предыдущие записи
        logfile.open(filename, std::ios::app);

        // Проверяем, успешно ли открылся файл
        if (!logfile.is_open()) {
            throw std::runtime_error("Не удалось открыть файл лога: " + filename);
        }

        // Записываем сообщение о запуске логгера
        log(INFO, "Логгер успешно инициализирован");
    } catch (const std::exception& e) {
        // Если произошла ошибка, выводим её в консоль
        std::cerr << "ОШИБКА ИНИЦИАЛИЗАЦИИ ЛОГГЕРА: " << e.what() << std::endl;
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
    // Если уровень сообщения ниже минимального, игнорируем его
    if (level < minLogLevel) {
        return;
    }

    // Блокируем мьютекс для безопасной записи в многопоточной среде
    std::lock_guard<std::mutex> lock(logMutex);

    // Получаем текущее время
    std::time_t now = std::time(nullptr);          // Текущее время в секундах с эпохи
    std::tm* now_tm = std::localtime(&now);        // Преобразуем в структуру времени
    
    // Форматируем время для записи: [ГГГГ-ММ-ДД ЧЧ:ММ:СС]
    std::ostringstream timestamp;
    timestamp << "[" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << "] ";

    // Формируем строку лога
    std::string logMessage = timestamp.str() + "[" + levelToString(level) + "] " + message;

    // Записываем лог в файл
    if (logfile.is_open()) {
        logfile << logMessage << std::endl;  // std::endl добавляет перенос строки и сбрасывает буфер
    }

    // Также выводим лог в консоль, если это ошибка или предупреждение
    if (level == ERROR || level == WARNING) {
        std::cerr << logMessage << std::endl;
    }
}

// Преобразование уровня логирования в строку
std::string Logger::levelToString(Level level) const {
    switch (level) {
        case INFO: return "INFO";        // Информационное сообщение
        case WARNING: return "WARNING";  // Предупреждение
        case ERROR: return "ERROR";      // Ошибка
        default: return "UNKNOWN";       // Неизвестный уровень (на всякий случай)
    }
}