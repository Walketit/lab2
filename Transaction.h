#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Account.h"

class Transaction {
private:
    int id;                 // ���������� ������������� ����������
    Account* account;
    int type;               // ���� ���� ���������� (0 - ���������� �� ����, 1 - ������ �� �����)
    string name;         // ��� ����������
    double amount;          // ����� ����������
public:
    Transaction() : id(0), account(), type(0), name(""), amount(0.0) {};
    Transaction(int id, Account* account);
    void set_transaction(int id, Account* account);
    void change_value(string name, int type, int value);
};

#endif // TRANSACTION_H