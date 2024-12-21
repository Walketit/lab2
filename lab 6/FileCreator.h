#ifndef FILECREATOR_H
#define FILECREATOR_H

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class FileCreator {
public:
    virtual ~FileCreator() {} // ����������� ����������

    // ����� ����������� ������� ��� ���������� ������ � ����
    virtual void saveToFile(const string& filename) const = 0;

    // ����� ����������� ������� ��� �������� ������ �� �����
    virtual void loadFromFile(const string& filename) = 0;
};

#endif // FILECREATOR_H