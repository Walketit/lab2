#include "SavingsAccount.h"

void SavingsAccount::applyInterest()
{

	double interest = balance * (interestRate / 100) / savingsFrequency;
	balance += interest;
	cout << "��������� ��������: " << fixed << setprecision(2) << interest << " " << currency << endl;

}

void SavingsAccount::displayDetails() const
{
	Account::displayDetails(); // ����� ������ �������� ������
	cout << "���������� ������: " << fixed << setprecision(2) << interestRate << "%\n"
		<< "������� ����������: " << savingsFrequency << " ���(�) � ���" << endl;
}

void SavingsAccount::displayDetailsWithoutBase() const
{
	cout << "����: " << name << endl
		<< "������: " << currency << endl
		<< "������: " << fixed << setprecision(2) << balance << " " << currency << endl;
	cout << "���������� ������: " << fixed << setprecision(2) << interestRate << "%\n"
		<< "������� ����������: " << savingsFrequency << " ���(�) � ���" << endl;
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
