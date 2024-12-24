#include "SavingsAccount.h"

void SavingsAccount::applyInterest()
{

	double interest = balance * (interestRate / 100) / savingsFrequency;
	balance += interest;
	cout << "Начислены проценты: " << fixed << setprecision(2) << interest << " " << currency << endl;

}

void SavingsAccount::displayDetails() const
{
	Account::displayDetails(); // Вызов метода базового класса
	cout << "Процентная ставка: " << fixed << setprecision(2) << interestRate << "%\n"
		<< "Частота начисления: " << savingsFrequency << " раз(а) в год" << endl;
}

void SavingsAccount::displayDetailsWithoutBase() const
{
	cout << "Счет: " << name << endl
		<< "Валюта: " << currency << endl
		<< "Баланс: " << fixed << setprecision(2) << balance << " " << currency << endl;
	cout << "Процентная ставка: " << fixed << setprecision(2) << interestRate << "%\n"
		<< "Частота начисления: " << savingsFrequency << " раз(а) в год" << endl;
}

double SavingsAccount::getInterestRate() const
{
	 return interestRate; 
}

void SavingsAccount::setInterestRate(double rate)
{
	 interestRate = rate;
}

int SavingsAccount::getCompoundingFrequency() const
{
	return savingsFrequency;
}

void SavingsAccount::setCompoundingFrequency(int frequency)
{
	 savingsFrequency = frequency;
}
