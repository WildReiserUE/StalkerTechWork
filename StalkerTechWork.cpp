#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// структура для известных строгих данных
struct RecordLine
{
    std::string str1;
    std::string str2;
    int num;
};

enum SortType : uint8_t
{
    MIN,
    family,
    name,
    tefone
};

// Компаратор: сортировка по фамилии
bool compareByFamily(const RecordLine& a, const RecordLine& b)
{
    return a.str2 < b.str2;
}

// Компаратор: сортировка по имени
bool compareByName(const RecordLine& a, const RecordLine& b)
{
    return a.str1 < b.str1;
}

// Компаратор: сортировка по телефону от меньше к больше
bool compareByNum(const RecordLine& a, const RecordLine& b)
{
    return a.num < b.num;
}

int main()
{
    setlocale(LC_ALL, "Ru");
    // путь и имя входного файла
    // Windows
    std::ifstream inputFile("InputFile.txt");
    // Linux
    // std::ifstream inputFile("/media/wildreiser/NetacSSD/Projects/StalkerTechWork/InputFile.txt");


    if (!inputFile.is_open())
    {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 2;
    }

    std::string line;
    std::vector<RecordLine> data;

    std::string part1, part2, number;
    while (std::getline(inputFile, part1, ' ') && std::getline(inputFile, part2, ':') && std::getline(inputFile, number))
    {
        // Пытаемся считать два string и один int
        data.push_back({part1, part2, stoi(number)});
    }

    // освобождаем файл от чтения
    inputFile.close();
    // известны 3 варианта сортировок
    int s = 0;
    SortType ST;
    std::cout << "Для сортировки по именам введите – 1, по фамилиям введите - 2, по телефонам введите - 3 \n" ;
    std::cin >> s;
    ST = SortType(s);
    // Сортируем по нужному полю
    switch (ST)
    {
        case family:
            std::sort(data.begin(), data.end(), compareByFamily);
            for (const auto& record : data)
            {
                // Вывод после сортировки
                std::cout << record.str1 << " " << record.str2 << ": " << record.num << "\n";
            }
            break;
        case name:
            std::sort(data.begin(), data.end(), compareByName);
            for (const auto& record : data)
            {
                // Вывод после сортировки
                std::cout << record.str2 << " " << record.str1 << ": " << record.num << "\n";
            }
            break;
        case tefone:
            std::sort(data.begin(), data.end(), compareByNum);
            for (const auto& record : data)
            {
                // Вывод после сортировки
                std::cout << record.num << ": " << record.str1 << " " << record.str2 << "\n";
            }
            break;
    }
    return 0;
}