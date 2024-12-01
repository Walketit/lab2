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


using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logs* logs = new Logs();
	logs->get_time().print_current_time();

    Account baseAccount("Base Account", 1000.0, "USD");
    LoanAccount loanAccount("Home Loan", 0.0, "USD", 100000.0, 5.0, 500.0);

    cout << "Base Account Details:" << endl;
    baseAccount.print_account();

    cout << "\nLoan Account Details before assignment:" << endl;
    loanAccount.print_account();

    loanAccount = baseAccount; // Присваивание объекта базового класса объекту производного класса

    cout << "\nLoan Account Details after assignment:" << endl;
    loanAccount.print_account();

    return 0;
}