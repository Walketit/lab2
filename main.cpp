#include <iostream>
#include <Windows.h>
#include "User.h"
#include "Account.h"
#include "Transaction.h"
#include "CurrencyChange.h"
#include "Goal.h"
#include "Note.h"
#include "Logs.h"
#include "LoanAccount.h"
#include "SavingsAccount.h"

using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logs* logs = new Logs();
	logs->get_time().print_current_time();

    Account baseAccount("Base Account", 1000.0, "USD");
    // ����� ������������ �������� ������ � ������������ ������������ ������ � �����������
    LoanAccount loanAccount("Loan Account", 0.0, "USD", 100000.0, 5.0, 500.0);

    // ���������� ������ �������� ������ � ����������� ������ � ������� ������ �������� ������
    loanAccount.displayDetails();
    // ���������� ������ �������� ������ � ����������� ������ ��� ������ ������ �������� ������
    loanAccount.print_account_without_base();

    cout << "���� �������� ������:" << endl;
    baseAccount.print_account();

    cout << "\n���� ������������ ������ �� ������������:" << endl;
    loanAccount.print_account();

    loanAccount = baseAccount; // ������������ ������� �������� ������ ������� ������������ ������

    cout << "\n���� ������������ ������ ����� ������������:" << endl;
    loanAccount.print_account();

    cout << "\n--- �������� ������� ������������ ������ ---\n";
    // ������ ������������ ������
    SavingsAccount savingsAccount("�������������� ����", 5000.0, "USD", 3.5, 4);
    savingsAccount.print_account(); // ����� ����� ������� �����
    savingsAccount.displayDetails(); // ����� ���������������� ������

    cout << "\n--- ������������� ��������� �� ������� ����� ��� ������������ ������� ---\n";
    Account* accountPtr = &savingsAccount;
    accountPtr->print_account(); // ����� ����������� �������

    cout << "\n--- ���������� ������� �������� ������ � ��������� �� ������� ����� ---\n";
    accountPtr = &baseAccount;
    accountPtr->print_account(); // ����� ������� �������� ������

    // ���� ������ virtual, ���������� ����� �������� ������ ���� ��� ������������ �������.
    cout << "\n--- ��������� �� ������������� ������� ---\n";
    cout << "���� ����� `displayDetails` �� �����������, ����� ������ ����� �� �������� ������:\n\n";

    // ������� ���������� ������� Note � Goal
    Note note("�������", "������ ����, ������ � ����", "�������");
    Goal goal("���������� �� ������",  100000.0, 25000.0, "������� ������ �� ������� � �������");

    // ��������� ������ � �����
    note.saveToFile("note.txt");
    goal.saveToFile("goal.json");

    // ��������� ������ �� ������
    Note loadedNote;
    Goal loadedGoal;

    loadedNote.loadFromFile("note.txt");
    loadedGoal.loadFromFile("goal.json");


    return 0;
}