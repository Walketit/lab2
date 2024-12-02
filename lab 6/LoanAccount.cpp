#include "LoanAccount.h"
#include <iostream>
#include <iomanip>

LoanAccount::LoanAccount(string acc_name, double initial_balance, string acc_currency, double loanAmount, double interestRate, double monthlyPayment)
    : Account(acc_name, initial_balance, acc_currency) {
    this->loanAmount = loanAmount;
    this->interestRate = interestRate;
    this->monthlyPayment = monthlyPayment;
}

void LoanAccount::makePayment(double amount) {
    if (amount > 0 && balance >= amount) {
        loanAmount -= amount;
        balance -= amount;
        std::cout << "������ � �������:" << amount << " ������ �������. ���������� ����� ��� ���������: " << loanAmount << std::endl;
    }
    else {
        std::cout << "������� �������� �����." << std::endl;
    }
}

void LoanAccount::displayDetails() const
{
    Account::displayDetails(); // ����� ������ �������� ������
    cout << "����� �����������: " << loanAmount << endl;
    cout << "���������� ������: " << interestRate << "%" << endl;
    cout << "�������� �����: " << monthlyPayment << endl;
}

// ��� ������ ������ �������� ������
void LoanAccount::print_account_without_base(){
    cout << "�������� �����: " << name << endl; 
    cout << "������: " << fixed << setprecision(2) << balance << " " << currency << endl;
    cout << "Loan Amount: " << loanAmount << endl;
    cout << "Interest Rate: " << interestRate << "%" << endl;
    cout << "Monthly Payment: " << monthlyPayment << endl;
}

void LoanAccount::calculationOfInterest()
{
    this->loanAmount += (loanAmount * interestRate) / 365;
}

double LoanAccount::getLoanAmount() const {
    return loanAmount;
}

double LoanAccount::getInterestRate() const {
    return interestRate;
}

double LoanAccount::getMonthlyPayment() const {
    return monthlyPayment;
}

void LoanAccount::setLoanAmount(double loanAmount) {
    this->loanAmount = loanAmount;
}

void LoanAccount::setInterestRate(double interestRate) {
    this->interestRate = interestRate;
}

void LoanAccount::setMonthlyPayment(double monthlyPayment) {
    this->monthlyPayment = monthlyPayment;
}

LoanAccount& LoanAccount::operator=(const Account& other) {
    if (this == &other) {
        return *this;
    }
    Account::operator=(other); // ����� ��������� ������������ �������� ������
    return *this;
}