-- Создание таблицы Equipment
CREATE TABLE IF NOT EXISTS Equipment (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,              -- Наименование оборудования
    quantity INTEGER NOT NULL,       -- Количество
    inventory_number TEXT UNIQUE,    -- Инвентарный номер (уникальный)
    room TEXT NOT NULL,              -- Кабинет/помещение
    responsible TEXT NOT NULL        -- МОЛ (Материально ответственное лицо)
);

-- Создание таблицы Classrooms
CREATE TABLE IF NOT EXISTS Classrooms (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    room_number TEXT NOT NULL UNIQUE, -- Номер кабинета (уникальный)
    building TEXT NOT NULL,           -- Корпус (А, Б1, Б2)
    floor INTEGER NOT NULL,           -- Этаж
    purpose TEXT,                     -- Назначение (история, математика и т.д.)
    responsible TEXT                  -- Ответственный за кабинет
);

-- Заполнение таблицы Classrooms начальными данными
INSERT INTO Classrooms (room_number, building, floor, purpose) VALUES 
('1', 'A', 1, 'История'),
('2', 'A', 1, 'Русский язык'),
('3', 'A', 1, 'Русский язык'),
('4', 'A', 1, 'История'),
('6', 'A', 1, 'Русский язык'),
('7', 'A', 1, 'Военная подготовка'),
('8', 'A', 1, 'Английский язык'),
('9', 'A', 1, 'Завхоз'),
('10', 'A', 2, 'Английский язык'),
('11', 'A', 2, 'История'),
('12', 'A', 2, 'Русский язык'),
('13', 'A', 2, 'Химия'),
('14', 'A', 2, 'Математика'),
('15', 'A', 2, 'Математика'),
('16', 'A', 2, 'Русский язык'),
('17', 'A', 2, 'Воспитатели'),
('18', 'A', 3, 'Психолог'),
('19', 'A', 3, 'Информатика'),
('20', 'A', 3, 'Физика'),
('21', 'A', 3, 'Английский язык'),
('22', 'A', 3, 'Химия'),
('24', 'A', 3, 'Английский язык'),
('25', 'A', 3, 'Биология'),
('26', 'A', 3, 'Информатика'),
('27', 'A', 3, 'Бухгалтерия');