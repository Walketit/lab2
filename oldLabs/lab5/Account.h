#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class User;

class Account {
private:
    int id;                 // Уникальный идентификатор счета
    string name;            // Название счета
    string currency;        // Валюта счета (например, "USD", "EUR", "RUB")
    double balance;         // Текущий баланс счета

public:
    Account() : id(0), name(""), currency(""), balance(0.0) {};
    Account(string acc_name, double initial_balance, string acc_currency);
    Account(const Account& other); // Конструктор копии
    Account& operator=(const Account& other); // Оператор присваивания

    void create_account(string acc_name, string acc_currency, double initial_balance);
    void print_account() const;
    void deposit(double amount);
    void withdraw(double amount);
    void setBalance(double balance);
    void setName(const string& name);
    void setCurrency(const string& currency);
    void setId(int id);
    double getBalance() const;
    string getName() const;
    string getCurrency() const;
    int getId() const;

    // Делаем класс User дружественным для данного класса
    friend class User;
};

#endif // ACCOUNT_H