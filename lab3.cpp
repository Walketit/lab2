#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <io.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

void logfile_create(int id);
void logfile_update(int id, string name);


//
// ������
//

class Time {
private:
	char hour[3];			// ���������� ��� ����
	char min[3];			// ���������� ��� ������
	char sec[3];			// ���������� ��� �������
	char day[3];			// ���������� ��� ���
	char month[3];			// ���������� ��� ������
	char year[5];			// ���������� ��� ����
	char full_date[22];     // ���������� ��� ������ ����
public:
	// ������� ��� ��������� �������� �������
	void current_time() {
		time_t timen;
		struct tm* timeinfo;
		time(&timen);
		timeinfo = localtime(&timen);
		strftime(day, 3, "%d", timeinfo);
		strftime(month, 3, "%m", timeinfo);
		strftime(year, 5, "%Y", timeinfo);
		strftime(hour, 3, "%H", timeinfo);
		strftime(min, 3, "%M", timeinfo);
		strftime(sec, 3, "%S", timeinfo);
		strftime(full_date, 22, "|%Y-%m-%d %H:%M:%S|", timeinfo);
	}

	// ������� ������ �������� �������
	void print_current_time() {
		current_time();
		printf("�������: %s-%s-%s\n", day, month, year);
		printf("�����: %s:%s:%s\n\n", hour, min, sec);
	}
	const char* get_full_date() {
		current_time();
		return full_date;
	}

	// ������� ��� �������� ������ ���� � �������
	void parse_date(const char* date_str, Time* time) {
		sscanf(date_str, "%4s-%2s-%2s %2s:%2s:%2s",
			time->year, time->month, time->day,
			time->hour, time->min, time->sec);
		strcpy(time->full_date, date_str);
	}
};

class Logs {
private:
	string name;         // �������� ��������
	Time time;            // ���� ��������
public:
	Logs() : name(""), time() {};

	// ������� ��� �������� ��������
	void logfile_create(int id) {
		name = "logs" + to_string(id);
		ofstream file(name + ".txt");
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}
		file.close();
	}
	// ������� ��� �������� ���� � �������
	void logfile_update(int id, string name) {
		time.current_time();
		string mes = name + time.get_full_date();

		name = "logs" + to_string(id);
		ofstream file(name + ".txt", ios::app);
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}

		file << mes << endl;
		file.close();

		return;
	}

	// ������� ��� ���������� � ������ �����
	void read_logs(int id) {
		char filename[50] = "logs";
		char str_id[3];
		sprintf(str_id, "%d", id);
		strcat(filename, str_id);
		strcat(filename, ".txt");
		FILE* file = fopen(filename, "r");
		if (file == NULL) {
			printf("������ �������� �����");
			return;
		}

		char line[256];
		printf("������� ��������:\n\n");

		while (fgets(line, sizeof(line), file)) {
			// ������� ������ ����� ������, ���� �� ����
			line[strcspn(line, "\n")] = '\0';

			// ��������� ������ �� ��� �����: �������� �������� � ����
			char* operation = strtok(line, "|");
			char* date_str = strtok(NULL, "|");

			if (operation != NULL && date_str != NULL) {

				time.parse_date(date_str, &time);

				// ������� ������
				printf("�������� ��������: %s\n", operation);
				printf("����: %s\n", time.get_full_date());
				printf("-----------------------------\n");
			}
		}

		fclose(file);
	}

	Time get_time() {
		return time;
	}

};

class Account {
private:
	int id;                 // ���������� ������������� �����
	string name;         // �������� �����
	string currency;       // ������ ����� (��������, "USD", "EUR", "RUB")
	double balance;         // ������� ������ �����
public:
	Account() : id(0), name(""), currency(""), balance(0.0) {};

	Account(string acc_name, double initial_balance, string acc_currency) {
		create_account(acc_name, acc_currency, initial_balance);
	}
	// ������� ��� �������� ������ ����� ������������
	void create_account(string acc_name, string acc_currency, double initial_balance) {
		name = acc_name;
		balance = initial_balance;
		currency = acc_currency;
	}

	// ������� ��� ����������� ����� �� ��� �������������� (� ���������� ������ ����� ����������� �� ���� ������)
	void print_account() {
		cout << "�������� �����: " << name << endl;
		cout << "������: " << fixed << setprecision(2) << balance << " " << currency << endl;

	}

	void deposit(double amount) {
		balance += amount;
	}

	void withdraw(double amount) {
		if (balance >= amount) {
			balance -= amount;
		}
		else {
			cout << "Insufficient funds!" << endl;
		}
	}

	void setBalance(double balance) { this->balance = balance; }
	void setName(const string& name) { this->name = name; }
	void setCurrency(const string& currency) { this->currency = currency; }
	void setId(int id) { this->id = id; }


	double getBalance() const { return balance; }
	string getName() const { return name; }
	string getCurrency() const { return currency; }
	int getId() const { return id; }


};

class Transaction {
private:
	int id;                 // ���������� ������������� ����������
	Account* account;
	int type;               // ���� ���� ���������� (0 - ���������� �� ����, 1 - ������ �� �����)
	string name;         // ��� ����������
	double amount;          // ����� ����������
public:
	Transaction() : id(0), account(), type(0), name(""), amount(0.0) {};

	Transaction(int id, Account* account) {
		set_transaction(id, account);
	}

	void set_transaction(int id, Account* account) {
		this->id = id;
		this->account = account;
		type = 0;
		name = "";
		amount = 0.0;
	}

	// ������� ��� ���������� ����������
	void change_value(string name, int type, int value) {
		this->name = name;
		this->type = type;
		this->amount = value;

		if (type == 0) {
			account->deposit(amount);
			cout << "���������� �� " << amount << ", �� ���� " << account->getName() << endl;
		}
		else if (type == 1) {
			account->withdraw(amount);
			cout << "�������� " << amount << " ,�� ����� " << account->getName() << endl;
		}
		return;

	}

};

class CurrencyChange {
private:
	string code;           // ��� ������ (��������, "USDRUB")
	string name;          // ������ �������� ������ (��������, "������ � �����")
	float rate;             // ���� ������ �� ��������� � ������� �����
public:
	CurrencyChange() : code(""), name(""), rate(0) {};

	CurrencyChange(string request) {
		set_�urrency_�hange(request);
	}

	// ������� ��� ��������� ��������� �����
	void set_�urrency_�hange(string request) {

		ifstream file("CurrencyRate.txt");
		if (!file.is_open()) {
			printf("������ �������� ����� CurrencyRate.txt");
			exit(1);
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string token;

			// �������� ������ ����� (���)
			if (getline(ss, token, ',')) {
				if (request == token) {
					code = token;

					// �������� ������ ����� (������)
					if (getline(ss, token, ',')) {
						rate = stod(token);
					}

					// �������� ������ ����� (���)
					if (getline(ss, token, '\n')) {
						name = token;
					}

					file.close();
					return;
				}
			}
			printf("��������� �������� ���� �� ������.");
			exit(1);
		}
	}
	// ������� ������ �����
	void change(float amount) {
		cout << "����� " << name << endl;
		cout << fixed << setprecision(3) << amount << " = " << amount * rate << endl;
		return;
	}
};

class Goal {
private:
	string name;         // �������� ����
	string description;  // �������� ����
	float target_amount;    // ������� �����
	float current_amount;   // ������� �����
public:
	Goal() : name(""), description(""), target_amount(0), current_amount(0) {}

	Goal(string name, float target_amount, float current_ammount, string content) {
		this->name = name;
		this->current_amount = current_ammount;
		this->target_amount = target_amount;
		this->description = content;
	}

	// ������� ������ ����
	void print_goal() {
		cout << "����: " << name << endl;
		cout << fixed << setprecision(0) << current_amount << "/" << target_amount << endl;
		cout << "��������: " << description << endl;
	}
	// ����������� � ������� �����
	void addToBalance(double amount) {
		current_amount += amount;
	}
	// �������� ���������� ����
	bool isAchieved() const {
		return current_amount >= target_amount;
	}

	string getTitle() const { return name; }
	string getDescription() const { return description; }
	double getCurrentBalance() const { return current_amount; }
	double getTargetAmount() const { return target_amount; }

	void setTitle(const string& title) { this->name = name; }
	void setDescription(const string& description) { this->description = description; }
	void setCurrentBalance(double currentBalance) { this->current_amount = current_amount; }
	void setTargetAmount(double targetAmount) { this->target_amount = target_amount; }

};

class Note {
private:
	string title;        // ��������� �������
	string content;      // ���������� �������
	string category;           // ��������� ������� (��������, 1 - �������, 2 - ������, 3 - ���������� ����, � �.�.)
public:
	Note() : title(""), content(""), category("") {};

	Note(string title, string content, string category) {
		this->title = title;
		this->content = content;
		this->category = category;
	};

	void print_note() {
		cout << "�������: " << title << endl;
		cout << content << endl;
	}

	string getTitle() const { return title; }
	string getDescription() const { return content; }
	string getCategory() const { return category; }

	void setTitle(const string& title) { this->title = title; }
	void setDescription(const string& description) { this->content = description; }
	void setCategory(const string& category) { this->category = category; }

};

class User {
private:
	int id;                 // ���������� ������������� ������������
	string name;         // ��� ������������
	string email;        // ����� ����������� �����
	string password;     // ������
	int is_admin;           // ���� �������������� (0 - ������� ������������, 1 - �������������)
	Logs logs;
	vector<Account> accounts;
	vector<Note> notes;
	vector<Goal> goals;
public:
	// �����������
	User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};
	// ����������� ��� �������� ������������
	User(int id, string name, string email, string password, int is_admin, Logs logs) {
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
	};

	void add_account(Account account) {
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

	void displayAccounts() const {
		cout << "����� " << name << ":" << endl;
		for (const auto& account : accounts) {
			cout << "����: " << account.getName() << endl;
			cout << "������: " << account.getBalance() << " " << account.getCurrency() << endl;
		}
	}

	void add_note(Note note) {
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

	void displayNotes() const {
		cout << "������� " << name << ":" << endl;
		for (const auto& note : notes) {
			cout << "�������: " << note.getTitle() << ", ���������: " << note.getCategory() << endl;
			cout << note.getDescription() << endl;
		}
	}

	void add_goal(Goal goal) {
		string n = "������� ����: " + goal.getTitle();
		logs.logfile_update(id, n);
		goals.push_back(goal);
	}

	void displayGoals() const {
		cout << "���� " << name << ":" << endl;
		for (const auto& goal : goals) {
			cout << "����: " << goal.getTitle() << ", ������� �����: " << goal.getCurrentBalance()
				<< ", ������� �����: " << goal.getTargetAmount() << endl;
		}
	}

	// ������� ��� ������ ���������� � ������������
	void print_user() {
		cout << "������������ #" << id << ":" << endl;
		cout << "���: " << name << endl;
		cout << "Email: " << email << endl;
		cout << "������: " << (is_admin ? "�������������" : "����") << endl;
	}

	Account* getAccount(int index) {
		if (index >= 0 && index < accounts.size()) {
			return &accounts[index];
		}
		return nullptr;
	}

};

//
// ������������ ������
//

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Logs* logs = new Logs();
	logs->get_time().print_current_time();

	User user1(1, "John", "Johnmail@gmail.com", "123", 0, *logs);

	user1.print_user();

	Account account1("main", 0.0, "RUB");
	Account account2("������", 100.0, "EUR");

	user1.add_account(account1);
	user1.add_account(account2);

	user1.displayAccounts();

	cout << '\n' << endl;

	Transaction transaction(1, user1.getAccount(0));
	transaction.change_value("���������", 0, 5000);

	transaction.set_transaction(2, user1.getAccount(1));
	transaction.change_value("������ �� ��������", 1, 5);

	cout << '\n' << endl;

	user1.displayAccounts();

	cout << '\n' << endl;

	CurrencyChange cur;
	cur.set_�urrency_�hange("RUBEUR");
	cur.change(1000);

	cout << '\n' << endl;

	Goal goal1("BMW M5", 5000000.0, 0.0, "���� ������");
	user1.add_goal(goal1);
	user1.displayGoals();

	cout << '\n' << endl;

	Note note1("������ ���������", "������ ������,����,�������", "�������");
	user1.add_note(note1);
	user1.displayNotes();

	cout << "\n";

	logs->read_logs(1);

	// ������ � ������������ �������� �������� ������
	int numUsers = 3;
	User* users = new User[numUsers]{
			User{3, "Layla", "Layla1999@gmail.com", "asd", 0, *logs},
			User{4, "Matt", "MattSmith@gmail.com", "asdzxc", 1, *logs},
			User{5, "���", "Messi@gmail.com", "111111", 0, *logs}
	};

	cout << "\n������������ ������ ��������:\n";
	for (int i = 0; i < numUsers; ++i) {
		users[i].print_user();
		cout << "\n";
	}

	delete[] users;

	// ������ � �������� ������������ �������� ������
	int numGoals = 2;
	Goal** goals = new Goal * [numGoals];
	goals[0] = new Goal("��������", 500000000.0, 0.0, "�����");
	goals[1] = new Goal("Playstation 5", 65000.0, 0.0, "������ �� ���������� �������");

	cout << "\n������ ������������ ��������:\n";
	for (int i = 0; i < numGoals; ++i) {
		goals[i]->print_goal();
		cout << "\n";
	}

	for (int i = 0; i < numGoals; ++i) {
		delete goals[i];
	}
	delete[] goals;


	return 0;
}

void logfile_update(int id, string name)
{
}

void logfile_create(int id)
{
}