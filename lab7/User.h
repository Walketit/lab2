#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include <iostream>
#include "Logs.h"
#include "Account.h"
#include "Note.h"
#include "Goal.h"

using namespace std;

class User {
private:
    int id;                 // Уникальный идентификатор пользователя
    string name;            // Имя пользователя
    string email;           // Адрес электронной почты
    string password;        // Пароль
    int is_admin;           // Флаг администратора (0 - обычный пользователь, 1 - администратор)
    Logs logs;
    vector<Account> accounts;
    vector<Note> notes;
    vector<Goal> goals;

    // Статическое поле для хранения количества созданных пользователей
    static int userCount;

public:
    User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};
    User(string name, string email, string password, int is_admin, Logs logs);
    User(const User& other); // Конструктор копии
    User& operator=(const User& other); // Оператор присваивания
    friend bool operator==(const User& lhs, const User& rhs); // Перегрузка оператора сравнения

    void add_account(Account account);
    void displayAccounts() const;
    void add_note(Note note);
    void displayNotes() const;
    void add_goal(Goal goal);
    void displayGoals() const;
    void print_user() const;

    Account* getAccount(int index); // Возврат через указатель
    Account& getAccountRef(int index); // Возврат через ссылку

    void friend_add_account(Account&);

    // Статический метод для получения количества созданных пользователей
    static int getUserCount();

    // Дополнительные методы для работы с std::string
    string getFullNameWithId() const;
    bool containsName(const string& substring) const;
};

#endif // USER_H