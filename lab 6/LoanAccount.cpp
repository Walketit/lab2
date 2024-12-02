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
        std::cout << "Оплата в размере:" << amount << " прошла успешно. Оставшаяся сумма для погашения: " << loanAmount << std::endl;
    }
    else {
        std::cout << "Введена неверная сумма." << std::endl;
    }
}

void LoanAccount::displayDetails() const
{
    Account::displayDetails(); // Вызов метода базового класса
    cout << "Сумма задолжности: " << loanAmount << endl;
    cout << "Процентная ставка: " << interestRate << "%" << endl;
    cout << "Месячная плата: " << monthlyPayment << endl;
}

// Без вызова метода базового класса
void LoanAccount::print_account_without_base(){
    cout << "Название счета: " << name << endl; 
    cout << "Баланс: " << fixed << setprecision(2) << balance << " " << currency << endl;
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
    Account::operator=(other); // Вызов оператора присваивания базового класса
    return *this;
}