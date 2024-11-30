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
    
    // Будет выброшено исключение пустого имени
    cout << endl << "Будет выброшено исключение пустого имени" << endl;
    User user3("", "adadsd@example.com", "23233323", 1, *logs);

	// Добавление счетов
	Account account1("Копилка", 1000.0, "USD");
	Account account2("", 500.0, "USD");
	user1.add_account(account1);
	
    // Дружественная функция
    user2.friend_add_account(account2);

    // Перегрузка оператора сравнения
    cout << endl << "Перегрузка оператора сравнения" << endl;
    if (user1 == user2) {
        cout << "У пользователей одинаковое имя!" << endl;
    }
    else
        cout << "У пользователей разные имена!" << endl;

    // Возврат значения через указатель
    cout << endl << "Возврат значения через указатель" << endl;
    Account* accountPtr = user1.getAccount(0);
    if (accountPtr != nullptr) {
        cout << "Счёт: " << accountPtr->getName() << endl;
        cout << "Баланс счёта: " << accountPtr->getBalance() << endl;
    }
    else {
        cout << "Ошибка!" << endl;
    }

    // Возврат значения через ссылку + (try - catch)
    cout << endl << "Возврат значения через ссылку + (try - catch)" << endl;
    try {
        Account& accRef = user1.getAccountRef(0);
        cout << "Счёт: " << accRef.getName() << endl;
        cout << "Баланс счёта: " << accRef.getBalance() << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    // Конструктор копии и оператор присваивания
    cout << endl << "Конструктор копии (Вызывается описания user4, который имеет такие же данные как user1)" << endl;
    User user4 = user1; // Конструктор копии
    user4.print_user();

    cout << endl << "Оператор присваивания(Вызывается описания user5, который имеет такие же данные как user2)" << endl;
    User user5;
    user5 = user2; // Оператор присваивания
    user5.print_user();

    // Статическая функция показывающая кол-во уникальных пользователей
    cout << "Количество созданных юзеров: " << user1.getUserCount() << endl;

    // Работа с std::string
    cout << endl << "Некоторые методы std::string" << endl;
    cout << user1.getFullNameWithId() << endl;
    cout << user1.containsName("Dima") << endl;

    return 0;
}