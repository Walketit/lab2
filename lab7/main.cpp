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
#include "Accounts.h"

using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logs* logs = new Logs();
	Accounts AccList;

	// ������ �������
	AccList.addAccount(make_unique<Account>("Basic Account", 500.0, "USD"));
	AccList.addAccount(make_unique<LoanAccount>("Home Loan", 2000.0, "USD", 10000.0, 4.5, 2000.0));
	AccList.addAccount(make_unique<SavingsAccount>("Savings", 1500.0,"RUB", 2.0, 1));

	// ����� ������
	AccList.displayAccounts();
	cout << "\n\n" << endl;

	// ���������� �� �������
	AccList.sortAccounts();

	// ����� ����� ����������
	AccList.displayAccounts();
	cout << "\n\n" << endl;

	// ����� ����� �� ��������

	AccList.findByName("�������� ����");
	AccList.findByName("Basic Account");

    return 0;
}