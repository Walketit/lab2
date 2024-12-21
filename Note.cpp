#define _CRT_SECURE_NO_WARNINGS
#include "Note.h"

Note::Note(string title, string content, string category) {
    this->title = title;
    this->content = content;
    this->category = category;
}

void Note::print_note() {
    cout << "Заметка: " << title << endl;
    cout << content << endl;
}

string Note::getTitle() const { return title; }
string Note::getDescription() const { return content; }
string Note::getCategory() const { return category; }

void Note::setTitle(const string& title) { this->title = title; }
void Note::setDescription(const string& description) { this->content = description; }
void Note::setCategory(const string& category) { this->category = category; }

void Note::saveToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи: " << filename << endl;
        return;
    }
    file << "Note\n";
    file << "Title: " << title << "\n";
    file << "Content: " << content << "\n";
    file << "Category: " << category << "\n";
    file.close();
    cout << "Заметка успешно сохранена в TXT файл: " << filename << endl;
}

void Note::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
        return;
    }
    string line;
    getline(file, line); // Пропускаем первую строку "Note"
    getline(file, line);
    title = line.substr(7); // Убираем "Title: "
    getline(file, line);
    content = line.substr(9); // Убираем "Content: "
    getline(file, line);
    category = line.substr(10); // Убираем "Category: "
    file.close();
    cout << "Заметка успешно загружена из TXT файла: " << filename << endl;
}
