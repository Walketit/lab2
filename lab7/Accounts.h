#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <vector>
#include <algorithm>
#include <memory>
#include "Account.h"

using namespace std;

class Accounts {
private:
	vector<unique_ptr<Account>> Accounts;

public:
	// ���������� �������� � ���������
	void addAccount(unique_ptr<Account> account);

	// ���������� ���������
	void sortAccounts();

	// ����� �������� �� ��������
	void findByName(const string& name);

	// ����� ���� ���������
	void displayAccounts();
};

#endif // ACCOUNTS_H