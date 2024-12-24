#define _CRT_SECURE_NO_WARNINGS
#include "Accounts.h"

void Accounts::addAccount(unique_ptr<Account> account)
{
	Accounts.push_back(move(account));
}

void Accounts::sortAccounts()
{
	sort(Accounts.begin(), Accounts.end(), [](const unique_ptr<Account>& a, const unique_ptr<Account>& b) {
		return a->getBalance() < b->getBalance();
		});
}

void Accounts::findByName(const string& name)
{
	auto it = find_if(Accounts.begin(), Accounts.end(), [&name](const unique_ptr<Account>& account) {
		return account->getName() == name;
		});

	if (it != Accounts.end()) {
		cout << "\n������� ������:" << endl;
		(*it)->displayDetails();
	}
	else {
		cout << "\n������� � ��������� '" << name << "' �� ������." << endl;
	}
}

void Accounts::displayAccounts()
{
	for (const auto& account : Accounts) {
		account->displayDetails();
		cout << "_______________________________________________" << endl;
	}
}


