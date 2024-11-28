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

	// Добавление счетов
	Account account1("Копилка", 1000.0, "USD");
	Account account2("Карманные деньги", 500.0, "USD");
	user1.add_account(account1);
	
    // Дружественная функция
    user2.friend_add_account(account2);

    // Перегрузка оператора сравнения
    if (user1 == user2) {
        cout << "У пользователей одинаковое имя!" << endl;
    }
    else
        cout << "У пользователей разные имена!" << endl;


	// Отображение информации о пользователе
	user1.print_user();
	user1.displayAccounts();
	user1.displayNotes();
	user1.displayGoals();

    // Возврат значения через указатель
    Account* accountPtr = user1.getAccount(0);
    if (accountPtr != nullptr) {
        cout << "Счёт: " << accountPtr->getName() << endl;
        cout << "Баланс счёта: " << accountPtr->getBalance() << endl;
    }
    else {
        cout << "Ошибка!" << endl;
    }

    // Возврат значения через ссылку + (try - catch)
    try {
        Account& accRef = user1.getAccountRef(1);
        cout << "Счёт: " << accRef.getName() << endl;
        cout << "Баланс счёта: " << accRef.getBalance() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    // Конструктор копии и оператор присваивания
    User user3 = user1; // Конструктор копии
    user3.print_user();

    User user4;
    user4 = user2; // Оператор присваивания
    user4.print_user();

    cout << "Количество созданных юзеров: " << user1.getUserCount() << endl;

    return 0;
}