#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"

Account::Account(string acc_name, double initial_balance, string acc_currency) {
    create_account(acc_name, acc_currency, initial_balance);
}

void Account::create_account(string acc_name, string acc_currency, double initial_balance) {
    name = acc_name;
    balance = initial_balance;
    currency = acc_currency;
}

void Account::print_account() {
    cout << "Название счета: " << name << endl;
    cout << "Баланс: " << fixed << setprecision(2) << balance << " " << currency << endl;
}

void Account::deposit(double amount) {
    balance += amount;
}

void Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
    }
    else {
        cout << "Insufficient funds!" << endl;
    }
}

void Account::setBalance(double balance) { this->balance = balance; }
void Account::setName(const string& name) { this->name = name; }
void Account::setCurrency(const string& currency) { this->currency = currency; }
void Account::setId(int id) { this->id = id; }

double Account::getBalance() const { return balance; }
string Account::getName() const { return name; }
string Account::getCurrency() const { return currency; }
int Account::getId() const { return id; }