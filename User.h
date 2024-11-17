#ifndef USER_H
#define USER_H

#include <vector>
#include "Logs.h"
#include "Account.h"
#include "Note.h"
#include "Goal.h"

class User {
private:
    int id;                 // Уникальный идентификатор пользователя
    string name;         // Имя пользователя
    string email;        // Адрес электронной почты
    string password;     // Пароль
    int is_admin;           // Флаг администратора (0 - обычный пользователь, 1 - администратор)
    Logs logs;
    vector<Account> accounts;
    vector<Note> notes;
    vector<Goal> goals;
public:
    User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};
    User(int id, string name, string email, string password, int is_admin, Logs logs);
    void add_account(Account account);
    void displayAccounts() const;
    void add_note(Note note);
    void displayNotes() const;
    void add_goal(Goal goal);
    void displayGoals() const;
    void print_user();
    Account* getAccount(int index);
};

#endif // USER_H