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

	User user1(1, "John", "Johnmail@gmail.com", "123", 0, *logs);

	user1.print_user();

	Account account1("main", 0.0, "RUB");
	Account account2("������", 100.0, "EUR");

	user1.add_account(account1);
	user1.add_account(account2);

	user1.displayAccounts();

	cout << '\n' << endl;

	Transaction transaction(1, user1.getAccount(0));
	transaction.change_value("���������", 0, 5000);

	transaction.set_transaction(2, user1.getAccount(1));
	transaction.change_value("������ �� ��������", 1, 5);

	cout << '\n' << endl;

	user1.displayAccounts();

	cout << '\n' << endl;

	CurrencyChange cur;
	cur.set_�urrency_�hange("RUBEUR");
	cur.change(1000);

	cout << '\n' << endl;

	Goal goal1("BMW M5", 5000000.0, 0.0, "���� ������");
	user1.add_goal(goal1);
	user1.displayGoals();

	cout << '\n' << endl;

	Note note1("������ ���������", "������ ������,����,�������", "�������");
	user1.add_note(note1);
	user1.displayNotes();

	cout << "\n";

	logs->read_logs(1);

	// ������ � ������������ �������� �������� ������
	int numUsers = 3;
	User* users = new User[numUsers]{
			User{3, "Layla", "Layla1999@gmail.com", "asd", 0, *logs},
			User{4, "Matt", "MattSmith@gmail.com", "asdzxc", 1, *logs},
			User{5, "���", "Messi@gmail.com", "111111", 0, *logs}
	};

	cout << "\n������������ ������ ��������:\n";
	for (int i = 0; i < numUsers; ++i) {
		users[i].print_user();
		cout << "\n";
	}

	delete[] users;

	// ������ � �������� ������������ �������� ������
	int numGoals = 2;
	Goal** goals = new Goal * [numGoals];
	goals[0] = new Goal("��������", 500000000.0, 0.0, "�����");
	goals[1] = new Goal("Playstation 5", 65000.0, 0.0, "������ �� ���������� �������");

	cout << "\n������ ������������ ��������:\n";
	for (int i = 0; i < numGoals; ++i) {
		goals[i]->print_goal();
		cout << "\n";
	}

	for (int i = 0; i < numGoals; ++i) {
		delete goals[i];
	}
	delete[] goals;


	return 0;
}