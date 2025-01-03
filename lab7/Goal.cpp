#define _CRT_SECURE_NO_WARNINGS
#include "Goal.h"

Goal::Goal(string name, float target_amount, float current_ammount, string content) {
    this->name = name;
    this->current_amount = current_ammount;
    this->target_amount = target_amount;
    this->description = content;
}

void Goal::print_goal() {
    cout << "Цель: " << name << endl;
    cout << fixed << setprecision(0) << current_amount << "/" << target_amount << endl;
    cout << "Описание: " << description << endl;
}

void Goal::addToBalance(double amount) {
    current_amount += amount;
}

bool Goal::isAchieved() const {
    return current_amount >= target_amount;
}

string Goal::getTitle() const { return name; }
string Goal::getDescription() const { return description; }
double Goal::getCurrentBalance() const { return current_amount; }
double Goal::getTargetAmount() const { return target_amount; }

void Goal::setTitle(const string& title) { this->name = name; }
void Goal::setDescription(const string& description) { this->description = description; }
void Goal::setCurrentBalance(double currentBalance) { this->current_amount = current_amount; }
void Goal::setTargetAmount(double targetAmount) { this->target_amount = target_amount; }

void Goal::saveToFile(const string& filename) const
{
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для записи: " << filename << endl;
        return;
    }
    file << "{\n";
    file << "  \"Goal\": {\n";
    file << "    \"Name\": \"" << name << "\",\n";
    file << "    \"Description\": \"" << description << "\",\n";
    file << "    \"TargetAmount\": " << target_amount << ",\n";
    file << "    \"CurrentAmount\": " << current_amount << "\n";
    file << "  }\n";
    file << "}\n";
    file.close();
    cout << "Цель успешно сохранена в JSON файл: " << filename << endl;
}

void Goal::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла для чтения: " << filename << endl;
        return;
    }
    string line;
    getline(file, line); // Пропускаем первую строку "{"
    getline(file, line); // Пропускаем строку "  \"Goal\": {"
    getline(file, line);
    name = line.substr(line.find(": \"") + 3, line.rfind("\"") - (line.find(": \"") + 3)); // Извлекаем "Name"
    getline(file, line);
    description = line.substr(line.find(": \"") + 3, line.rfind("\"") - (line.find(": \"") + 3)); // Извлекаем "Description"
    getline(file, line);
    target_amount = stod(line.substr(line.find(": ") + 2)); // Извлекаем "TargetAmount"
    getline(file, line);
    current_amount = stod(line.substr(line.find(": ") + 2)); // Извлекаем "CurrentAmount"
    file.close();
    cout << "Цель успешно загружена из JSON файла: " << filename << endl;
}
