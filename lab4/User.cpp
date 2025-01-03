#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <fstream>

User::User(int id, string name, string email, string password, int is_admin, Logs logs) {
    this->logs = logs;
    this->id = id;
    this->is_admin = is_admin;
    this->name = name;
    this->email = email;
    this->password = password;

    string filename = "profile";
    filename += to_string(id);
    ofstream file(filename + ".txt");
    if (!file.is_open()) {
        printf("Ошибка создания файла!");
        exit(1);
    }
    file << "Имя: " << name << " (" << id << ")" << endl;
    file << "Почта: " << email << endl;
    file << "Пароль: " << password << endl;
    if (is_admin == 1) {
        file << "Статус: Админ" << endl;
    }
    else {
        file << "Статус: Юзер" << endl;
    }
    file.close();

    logs.logfile_create(id);
    logs.logfile_update(id, "Профиль создан");
}

void User::add_account(Account account) {
    account.setId(id + 100000);
    string filename = "account";
    filename += to_string(id);
    ofstream file(name + ".txt");
    if (!file.is_open()) {
        printf("Ошибка создания файла!");
        exit(1);
    }
    file << "Счёт: " << account.getName() << " (" << account.getId() << ")" << endl;
    file << "Владелец: " << name << " (" << id << ")" << endl;
    file << "Баланс: " << account.getBalance() << " " << account.getCurrency() << endl;
    file.close();

    string logname = "Cчёт создан: ";
    logname += account.getName();
    logs.logfile_update(id, logname);

    accounts.push_back(account);
}

void User::displayAccounts() const {
    cout << "Счета " << name << ":" << endl;
    for (const auto& account : accounts) {
        cout << "Счёт: " << account.getName() << endl;
        cout << "Баланс: " << account.getBalance() << " " << account.getCurrency() << endl;
    }
}

void User::add_note(Note note) {
    ofstream file(note.getTitle() + ".txt");
    if (!file.is_open()) {
        printf("Ошибка создания файла!");
        exit(1);
    }

    file << note.getDescription();
    file.close();
    logs.logfile_update(id, "Создана заметка");

    notes.push_back(note);
}

void User::displayNotes() const {
    cout << "Записки " << name << ":" << endl;
    for (const auto& note : notes) {
        cout << "Записка: " << note.getTitle() << ", Категория: " << note.getCategory() << endl;
        cout << note.getDescription() << endl;
    }
}

void User::add_goal(Goal goal) {
    string n = "Создана цель: " + goal.getTitle();
    logs.logfile_update(id, n);
    goals.push_back(goal);
}

void User::displayGoals() const {
    cout << "Цели " << name << ":" << endl;
    for (const auto& goal : goals) {
        cout << "Цель: " << goal.getTitle() << ", Текущая сумма: " << goal.getCurrentBalance()
            << ", Целевая сумма: " << goal.getTargetAmount() << endl;
    }
}

void User::print_user() {
    cout << "Пользователь #" << id << ":" << endl;
    cout << "Имя: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Статус: " << (is_admin ? "Администратор" : "Юзер") << endl;
}

Account* User::getAccount(int index) {
    if (index >= 0 && index < accounts.size()) {
        return &accounts[index];
    }
    return nullptr;
}