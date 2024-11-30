#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <fstream>

class User;
// ������������� ������������ ����
int User::userCount = 0;

User::User(string name, string email, string password, int is_admin, Logs logs) {
    this->logs = logs;
    this->id = userCount;
    userCount++;
    this->is_admin = is_admin;
    this->name = name;
    this->email = email;
    this->password = password;

    string filename = "profile";
    filename += to_string(id);

    try {
        if (name.empty()) {
            throw invalid_argument("��� �������� �� ����� ���� ������!");
        }
        ofstream file(filename + ".txt");
        if (!file.is_open()) {
            throw runtime_error("������ �������� �����!");
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
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;

    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
        throw;
    }
}

User::User(const User& other) {
    id = other.id;
    name = other.name;
    email = other.email;
    password = other.password;
    is_admin = other.is_admin;
    logs = other.logs;
    accounts = other.accounts;
    notes = other.notes;
    goals = other.goals;
}

User& User::operator=(const User& other) {
    if (this == &other) {
        return *this;
    }
    id = other.id;
    name = other.name;
    email = other.email;
    password = other.password;
    is_admin = other.is_admin;
    logs = other.logs;
    accounts = other.accounts;
    notes = other.notes;
    goals = other.goals;
    return *this;
}

bool operator==(const User& lhs, const User& rhs)
{
    return lhs.name == rhs.name;
}

void User::add_account(Account account)
{
    if (account.getName().empty()) {
        throw invalid_argument("��� ����� �� ����� ���� ������!");
    }
    try {
        account.setId(id + 100000);
        string filename = "account";
        filename += to_string(id);
        ofstream file(name + ".txt");
        if (!file.is_open()) {
            throw runtime_error("������! �������� ��� �����!");
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
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
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

void User::print_user() const {
    cout << "������������ #" << id << ":" << endl;
    cout << "���: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "������: " << (is_admin ? "�������������" : "����") << endl;
}

Account* User::getAccount(int id) {
    if (id >= 0 && id < accounts.size()) {
        return &accounts[id];
    }
    return nullptr;
}

Account& User::getAccountRef(int id) {
    if (id >= 0 && id < accounts.size()) {
        return accounts[id];
    }
    throw out_of_range("������������ id");
}

void User::friend_add_account(Account& account)
{
    try {
        if (account.getName().empty()) {
            throw invalid_argument("��� ����� �� ����� ���� ������!");
        }
        account.id = this->id + 100000;
        string filename = "account";
        filename += to_string(id);
        ofstream file(account.name + ".txt");
        if (!file.is_open()) {
            throw runtime_error("������ �������� �����!");
        }
        file << "����: " << account.name << " (" << account.id << ")" << endl;
        file << "��������: " << name << " (" << id << ")" << endl;
        file << "������: " << account.balance << " " << account.currency << endl;
        file.close();

        string logname = "C��� ������: ";
        logname += account.name;
        logs.logfile_update(id, logname);

        accounts.push_back(account);
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
}

int User::getUserCount()
{
    return userCount;
}

// ������������ + �������������� � ������
string User::getFullNameWithId() const
{
    return name + " (" + to_string(id) + ")";
}

// ����� ���������
bool User::containsName(const string& substring) const
{
    return name.find(substring) != string::npos;
}


