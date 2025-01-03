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