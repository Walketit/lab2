#ifndef FILECREATOR_H
#define FILECREATOR_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class FileCreator {
public:
    virtual ~FileCreator() {} // Виртуальный деструктор

    // Чисто виртуальная функция для сохранения данных в файл
    virtual void saveToFile(const string& filename) const = 0;

    // Чисто виртуальная функция для загрузки данных из файла
    virtual void loadFromFile(const string& filename) = 0;
};

#endif // FILECREATOR_H