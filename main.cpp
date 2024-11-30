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
    
    // ����� ��������� ���������� ������� �����
    cout << endl << "����� ��������� ���������� ������� �����" << endl;
    User user3("", "adadsd@example.com", "23233323", 1, *logs);

	// ���������� ������
	Account account1("�������", 1000.0, "USD");
	Account account2("", 500.0, "USD");
	user1.add_account(account1);
	
    // ������������� �������
    user2.friend_add_account(account2);

    // ���������� ��������� ���������
    cout << endl << "���������� ��������� ���������" << endl;
    if (user1 == user2) {
        cout << "� ������������� ���������� ���!" << endl;
    }
    else
        cout << "� ������������� ������ �����!" << endl;

    // ������� �������� ����� ���������
    cout << endl << "������� �������� ����� ���������" << endl;
    Account* accountPtr = user1.getAccount(0);
    if (accountPtr != nullptr) {
        cout << "����: " << accountPtr->getName() << endl;
        cout << "������ �����: " << accountPtr->getBalance() << endl;
    }
    else {
        cout << "������!" << endl;
    }

    // ������� �������� ����� ������ + (try - catch)
    cout << endl << "������� �������� ����� ������ + (try - catch)" << endl;
    try {
        Account& accRef = user1.getAccountRef(0);
        cout << "����: " << accRef.getName() << endl;
        cout << "������ �����: " << accRef.getBalance() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "������: " << e.what() << endl;
    }

    // ����������� ����� � �������� ������������
    cout << endl << "����������� ����� (���������� �������� user4, ������� ����� ����� �� ������ ��� user1)" << endl;
    User user4 = user1; // ����������� �����
    user4.print_user();

    cout << endl << "�������� ������������(���������� �������� user5, ������� ����� ����� �� ������ ��� user2)" << endl;
    User user5;
    user5 = user2; // �������� ������������
    user5.print_user();

    // ����������� ������� ������������ ���-�� ���������� �������������
    cout << "���������� ��������� ������: " << user1.getUserCount() << endl;

    // ������ � std::string
    cout << endl << "��������� ������ std::string" << endl;
    cout << user1.getFullNameWithId() << endl;
    cout << user1.containsName("Dima") << endl;

    return 0;
}