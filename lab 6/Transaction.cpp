#define _CRT_SECURE_NO_WARNINGS
#include "Transaction.h"

Transaction::Transaction(int id, Account* account) {
    set_transaction(id, account);
}

void Transaction::set_transaction(int id, Account* account) {
    this->id = id;
    this->account = account;
    type = 0;
    name = "";
    amount = 0.0;
}

void Transaction::change_value(string name, int type, int value) {
    this->name = name;
    this->type = type;
    this->amount = value;

    if (type == 0) {
        account->deposit(amount);
        cout << "Пополнение на " << amount << ", на счёт " << account->getName() << endl;
    }
    else if (type == 1) {
        account->withdraw(amount);
        cout << "Списание " << amount << " ,со счёта " << account->getName() << endl;
    }
    return;
}