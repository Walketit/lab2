#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"
#include <iostream>
using namespace std;

class SavingsAccount : public Account {
private:
    double interestRate;  // ���������� ������
    int savingsFrequency; // ������� ���������� ��������� (��������, ��� � �����)

public:
    // ������������
    SavingsAccount() : Account(), interestRate(0.0), savingsFrequency(1) {};

    // ����������� � �����������, ���������� ����������� �������� ������
    SavingsAccount(string acc_name, double initial_balance, string acc_currency, double interestRate, int savingsFrequency)
        : Account(acc_name, initial_balance, acc_currency), // ����� ������������ �������� ������
        interestRate(interestRate), savingsFrequency(savingsFrequency) {
        
    }

    // ������
    void applyInterest();

    // ���������� ������ �������� ������ � ������� �������� ������
    void displayDetails() const override;

    // ���������� ������ �������� ������ ��� ������ �������� ������
    void displayDetailsWithoutBase() const;

    // ������� � �������
    double getInterestRate() const;
    void setInterestRate(double rate);

    int getCompoundingFrequency() const;
    void setCompoundingFrequency(int frequency);
};

#endif // SAVINGSACCOUNT_H