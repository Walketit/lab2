#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"
#include <iostream>
using namespace std;

class SavingsAccount : public Account {
private:
    double interestRate;  // Процентная ставка
    int savingsFrequency; // Частота начисления процентов (например, раз в месяц)

public:
    // Конструкторы
    SavingsAccount() : Account(), interestRate(0.0), savingsFrequency(1) {};

    // Конструктор с параметрами, вызывающий конструктор базового класса
    SavingsAccount(string acc_name, double initial_balance, string acc_currency, double interestRate, int savingsFrequency)
        : Account(acc_name, initial_balance, acc_currency), // Вызов конструктора базового класса
        interestRate(interestRate), savingsFrequency(savingsFrequency) {
        
    }

    // Методы
    void applyInterest();

    // Перегрузка метода базового класса с вызовом базового метода
    void displayDetails() const override;

    // Перегрузка метода базового класса без вызова базового метода
    void displayDetailsWithoutBase() const;

    // Геттеры и сеттеры
    double getInterestRate() const;
    void setInterestRate(double rate);

    int getCompoundingFrequency() const;
    void setCompoundingFrequency(int frequency);
};

#endif // SAVINGSACCOUNT_H