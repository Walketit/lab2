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
    // вызов конструктора базового класса в конструкторе производного класса с параметрами
    LoanAccount loanAccount("Loan Account", 0.0, "USD", 100000.0, 5.0, 500.0);

    // перегрузка метода базового класса в производном классе с вызовом метода базового класса
    loanAccount.displayDetails();
    // перегрузка метода базового класса в производном классе без вызова метода базового класса
    loanAccount.print_account_without_base();

    cout << "Счет базового класса:" << endl;
    baseAccount.print_account();

    cout << "\nСчет производного класса до присваивания:" << endl;
    loanAccount.print_account();

    loanAccount = baseAccount; // Присваивание объекта базового класса объекту производного класса

    cout << "\nСчет производного класса после присваивания:" << endl;
    loanAccount.print_account();

    cout << "\n--- Создание объекта производного класса ---\n";
    // Объект производного класса
    SavingsAccount savingsAccount("Сберегательный счет", 5000.0, "USD", 3.5, 4);
    savingsAccount.print_account(); // Вызов через базовый класс
    savingsAccount.displayDetails(); // Вызов переопределённого метода

    cout << "\n--- Использование указателя на базовый класс для производного объекта ---\n";
    Account* accountPtr = &savingsAccount;
    accountPtr->print_account(); // Вызов виртуальной функции

    cout << "\n--- Присвоение объекта базового класса в указатель на базовый класс ---\n";
    accountPtr = &baseAccount;
    accountPtr->print_account(); // Вызов функции базового класса

    // Если убрать virtual, вызывается метод базового класса даже для производного объекта.
    cout << "\n--- Изменение на невиртуальную функцию ---\n";
    cout << "Если метод `displayDetails` не виртуальный, вывод всегда будет из базового класса:\n\n";

    // Создаем экземпляры классов Note и Goal
    Note note("Покупки", "Купить хлеб, молоко и яйца", "Покупки");
    Goal goal("Накопление на отпуск",  100000.0, 25000.0, "Собрать деньги на поездку в Испанию");

    // Сохраняем данные в файлы
    note.saveToFile("note.txt");
    goal.saveToFile("goal.json");

    // Загружаем данные из файлов
    Note loadedNote;
    Goal loadedGoal;

    loadedNote.loadFromFile("note.txt");
    loadedGoal.loadFromFile("goal.json");


    return 0;
}