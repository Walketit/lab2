#define _CRT_SECURE_NO_WARNINGS
#include "Note.h"

Note::Note(string title, string content, string category) {
    this->title = title;
    this->content = content;
    this->category = category;
}

void Note::print_note() {
    cout << "�������: " << title << endl;
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
        cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
        return;
    }
    file << "Note\n";
    file << "Title: " << title << "\n";
    file << "Content: " << content << "\n";
    file << "Category: " << category << "\n";
    file.close();
    cout << "������� ������� ��������� � TXT ����: " << filename << endl;
}

void Note::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������ ��� �������� ����� ��� ������: " << filename << endl;
        return;
    }
    string line;
    getline(file, line); // ���������� ������ ������ "Note"
    getline(file, line);
    title = line.substr(7); // ������� "Title: "
    getline(file, line);
    content = line.substr(9); // ������� "Content: "
    getline(file, line);
    category = line.substr(10); // ������� "Category: "
    file.close();
    cout << "������� ������� ��������� �� TXT �����: " << filename << endl;
}
