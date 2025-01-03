#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class User;

class Account {
private:
    int id;                 // ���������� ������������� �����
    string name;            // �������� �����
    string currency;        // ������ ����� (��������, "USD", "EUR", "RUB")
    double balance;         // ������� ������ �����

public:
    Account() : id(0), name(""), currency(""), balance(0.0) {};
    Account(string acc_name, double initial_balance, string acc_currency);
    Account(const Account& other); // ����������� �����
    Account& operator=(const Account& other); // �������� ������������

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

    // ������ ����� User ������������� ��� ������� ������
    friend class User;
};

#endif // ACCOUNT_H