#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>

using namespace std;

class Note {
private:
    string title;        // Заголовок заметки
    string content;      // Содержание заметки
    string category;           // Категория заметки (например, 1 - покупки, 2 - вклады, 3 - финансовые идеи, и т.д.)
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
};

#endif // NOTE_H