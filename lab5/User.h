#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include <iostream>
#include "Logs.h"
#include "Account.h"
#include "Note.h"
#include "Goal.h"

using namespace std;

class User {
private:
    int id;                 // ���������� ������������� ������������
    string name;            // ��� ������������
    string email;           // ����� ����������� �����
    string password;        // ������
    int is_admin;           // ���� �������������� (0 - ������� ������������, 1 - �������������)
    Logs logs;
    vector<Account> accounts;
    vector<Note> notes;
    vector<Goal> goals;

    // ����������� ���� ��� �������� ���������� ��������� �������������
    static int userCount;

public:
    User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};
    User(string name, string email, string password, int is_admin, Logs logs);
    User(const User& other); // ����������� �����
    User& operator=(const User& other); // �������� ������������
    friend bool operator==(const User& lhs, const User& rhs); // ���������� ��������� ���������

    void add_account(Account account);
    void displayAccounts() const;
    void add_note(Note note);
    void displayNotes() const;
    void add_goal(Goal goal);
    void displayGoals() const;
    void print_user() const;

    Account* getAccount(int index); // ������� ����� ���������
    Account& getAccountRef(int index); // ������� ����� ������

    void friend_add_account(Account&);

    // ����������� ����� ��� ��������� ���������� ��������� �������������
    static int getUserCount();

    // �������������� ������ ��� ������ � std::string
    string getFullNameWithId() const;
    bool containsName(const string& substring) const;
};

#endif // USER_H