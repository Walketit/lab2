#ifndef LOANACCOUNT_H
#define LOANACCOUNT_H

#include "Account.h"
#include <string>

class LoanAccount : public Account {
private:
    double loanAmount;       // ����� �������
    double interestRate;     // ���������� ������
    double monthlyPayment;   // ����������� ������

public:
    LoanAccount() : Account(), loanAmount(0.0), interestRate(0.0), monthlyPayment(0.0) {};
    LoanAccount(string acc_name, double initial_balance, string acc_currency, double loanAmount, double interestRate, double monthlyPayment);

    void makePayment(double amount); // ������� ������ �� �������.
    void calculationOfInterest(); // ���������� ���������� ���������

    void displayDetails() const override; // ��������������� ����������� �������
    void print_account_without_base(); // ���������� ��� ������ ������ �������� ������


    // �������, �������
    double getLoanAmount() const;
    double getInterestRate() const;
    double getMonthlyPayment() const;

    void setLoanAmount(double loanAmount);
    void setInterestRate(double interestRate);
    void setMonthlyPayment(double monthlyPayment);

    LoanAccount& operator=(const Account& other); // �������� ������������
};

#endif // LOANACCOUNT_H