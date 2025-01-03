#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
#include "FileCreator.h"

using namespace std;

class Note : public FileCreator {
private:
    string title;        // ��������� �������
    string content;      // ���������� �������
    string category;           // ��������� ������� (��������, 1 - �������, 2 - ������, 3 - ���������� ����, � �.�.)
public:
    Note() : title(""), content(""), category("") {};
    Note(string title, string content, string category);
    void print_note();
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    void setTitle(const string& title);
    void setDescription(const string& description);
    void setCategory(const string& category);

    void saveToFile(const string& filename) const override;
    void loadFromFile(const string& filename) override;
};

#endif // NOTE_H