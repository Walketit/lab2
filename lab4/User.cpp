#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <fstream>

User::User(int id, string name, string email, string password, int is_admin, Logs logs) {
    this->logs = logs;
    this->id = id;
    this->is_admin = is_admin;
    this->name = name;
    this->email = email;
    this->password = password;

    string filename = "profile";
    filename += to_string(id);
    ofstream file(filename + ".txt");
    if (!file.is_open()) {
        printf("������ �������� �����!");
        exit(1);
    }
    file << "���: " << name << " (" << id << ")" << endl;
    file << "�����: " << email << endl;
    file << "������: " << password << endl;
    if (is_admin == 1) {
        file << "������: �����" << endl;
    }
    else {
        file << "������: ����" << endl;
    }
    file.close();

    logs.logfile_create(id);
    logs.logfile_update(id, "������� ������");
}

void User::add_account(Account account) {
    account.setId(id + 100000);
    string filename = "account";
    filename += to_string(id);
    ofstream file(name + ".txt");
    if (!file.is_open()) {
        printf("������ �������� �����!");
        exit(1);
    }
    file << "����: " << account.getName() << " (" << account.getId() << ")" << endl;
    file << "��������: " << name << " (" << id << ")" << endl;
    file << "������: " << account.getBalance() << " " << account.getCurrency() << endl;
    file.close();

    string logname = "C��� ������: ";
    logname += account.getName();
    logs.logfile_update(id, logname);

    accounts.push_back(account);
}

void User::displayAccounts() const {
    cout << "����� " << name << ":" << endl;
    for (const auto& account : accounts) {
        cout << "����: " << account.getName() << endl;
        cout << "������: " << account.getBalance() << " " << account.getCurrency() << endl;
    }
}

void User::add_note(Note note) {
    ofstream file(note.getTitle() + ".txt");
    if (!file.is_open()) {
        printf("������ �������� �����!");
        exit(1);
    }

    file << note.getDescription();
    file.close();
    logs.logfile_update(id, "������� �������");

    notes.push_back(note);
}

void User::displayNotes() const {
    cout << "������� " << name << ":" << endl;
    for (const auto& note : notes) {
        cout << "�������: " << note.getTitle() << ", ���������: " << note.getCategory() << endl;
        cout << note.getDescription() << endl;
    }
}

void User::add_goal(Goal goal) {
    string n = "������� ����: " + goal.getTitle();
    logs.logfile_update(id, n);
    goals.push_back(goal);
}

void User::displayGoals() const {
    cout << "���� " << name << ":" << endl;
    for (const auto& goal : goals) {
        cout << "����: " << goal.getTitle() << ", ������� �����: " << goal.getCurrentBalance()
            << ", ������� �����: " << goal.getTargetAmount() << endl;
    }
}

void User::print_user() {
    cout << "������������ #" << id << ":" << endl;
    cout << "���: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "������: " << (is_admin ? "�������������" : "����") << endl;
}

Account* User::getAccount(int index) {
    if (index >= 0 && index < accounts.size()) {
        return &accounts[index];
    }
    return nullptr;
}