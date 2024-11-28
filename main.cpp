#include <iostream>
#include <Windows.h>
#include "User.h"
#include "Account.h"
#include "Transaction.h"
#include "CurrencyChange.h"
#include "Goal.h"
#include "Note.h"
#include "Logs.h"


using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logs* logs = new Logs();
	logs->get_time().print_current_time();

	User user1("Alex", "Alex@gmail.com", "123321", 1, *logs);
	User user2("Bob", "bob@example.com", "password456", 1, *logs);

	// ���������� ������
	Account account1("�������", 1000.0, "USD");
	Account account2("��������� ������", 500.0, "USD");
	user1.add_account(account1);
	
    // ������������� �������
    user2.friend_add_account(account2);

    // ���������� ��������� ���������
    if (user1 == user2) {
        cout << "� ������������� ���������� ���!" << endl;
    }
    else
        cout << "� ������������� ������ �����!" << endl;


	// ����������� ���������� � ������������
	user1.print_user();
	user1.displayAccounts();
	user1.displayNotes();
	user1.displayGoals();

    // ������� �������� ����� ���������
    Account* accountPtr = user1.getAccount(0);
    if (accountPtr != nullptr) {
        cout << "����: " << accountPtr->getName() << endl;
        cout << "������ �����: " << accountPtr->getBalance() << endl;
    }
    else {
        cout << "������!" << endl;
    }

    // ������� �������� ����� ������ + (try - catch)
    try {
        Account& accRef = user1.getAccountRef(1);
        cout << "����: " << accRef.getName() << endl;
        cout << "������ �����: " << accRef.getBalance() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "������: " << e.what() << endl;
    }

    // ����������� ����� � �������� ������������
    User user3 = user1; // ����������� �����
    user3.print_user();

    User user4;
    user4 = user2; // �������� ������������
    user4.print_user();

    cout << "���������� ��������� ������: " << user1.getUserCount() << endl;

    return 0;
}