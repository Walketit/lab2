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
	// Добавление элемента в коллекцию
	void addAccount(unique_ptr<Account> account);

	// Сортировка коллекции
	void sortAccounts();

	// Поиск элемента по названию
	void findByName(const string& name);

	// Вывод всей коллекции
	void displayAccounts();
};

#endif // ACCOUNTS_H