#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

void logfile_create(int id);
void logfile_update(int id, std::string name);


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
	Time() {
		current_time();
	}
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
	const char* getFullDate() const {
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
	std::string name;         // �������� ��������
	Time date;            // ���� ��������
public:
	Logs() : name(""), date() {};

	// ������� ��� �������� ��������
	void logfile_create(int id) {
		name = "logs" + std::to_string(id);
		std::ofstream file(name + ".txt");
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}
		file.close();
	}
	// ������� ��� �������� ���� � �������
	void logfile_update(int id, std::string name) {
		std::string mes = name;
		mes += date.getFullDate();

		name = "logs" + std::to_string(id);
		std::ofstream file(name + ".txt", std::ios::app);
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}

		file << mes;
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

				date.parse_date(date_str, &date);

				// ������� ������
				printf("�������� ��������: %s\n", operation);
				printf("����: %s\n", date.getFullDate());
				printf("-----------------------------\n");
			}
		}

		fclose(file);
	}



};

class User {
private:
	int id;                 // ���������� ������������� ������������
	std::string name;         // ��� ������������
	std::string email;        // ����� ����������� �����
	std::string password;     // ������
	int is_admin;           // ���� �������������� (0 - ������� ������������, 1 - �������������)
	Logs logs;

public:
	// �����������
	User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};

	User(int id, std::string name, std::string email, std::string password, int is_admin, Logs logs) {
		create_user(id, name, email, password, is_admin, logs);
	};
	// ������� ��� �������� ������������
	void create_user(int s_id, std::string s_name, std::string s_email, std::string s_password, int s_is_admin, Logs logs) {
		this->logs = logs;
		id = s_id;
		is_admin = s_is_admin;
		name = s_name;
		email = s_email;
		password = s_password;

		std::string filename = "profile";
		filename += std::to_string(id);
		std::ofstream file(filename + ".txt");
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}
		file << "���: " << name << " (" << id << ")" << std::endl;
		file << "�����: " << email << std::endl;
		file << "������: " << password << std::endl;
		if (is_admin == 1) {
			file << "������: �����" << std::endl;
		}
		else {
			file << "������: ����" << std::endl;
		}
		file.close();

		logs.logfile_create(id);
		logs.logfile_update(id, "������� ������");
	}

	int get_user_id() {
		return id;
	};

	Logs get_logs() {
		return logs;
	}

	// ������� ��� ������ ���������� � ������������
	void print_user() {
		std::cout << "������������ #" << id << ":" << std::endl;
		std::cout << "���: " << name << std::endl;
		std::cout << "Email: " << email << std::endl;
		std::cout << "������: " << (is_admin ? "�������������" : "����") << std::endl;
	}

	~User() {
	}
};

class Account {
private:
	int id;                 // ���������� ������������� �����
	std::string name;         // �������� �����
	std::string currency;       // ������ ����� (��������, "USD", "EUR", "RUB")
	double balance;         // ������� ������ �����
	User user;
public:
	Account() : id(0), name(""), currency(""), balance(0.0), user() {};

	Account(std::string acc_name, double initial_balance, std::string acc_currency, User user) {
		create_account(acc_name, acc_currency, initial_balance, user);
	}
	// ������� ��� �������� ������ ����� ������������
	void create_account(std::string acc_name, std::string acc_currency, double initial_balance, User user) {
		this->user = user;
		id = user.get_user_id() + 100000;
		name = acc_name;
		balance = initial_balance;
		currency = acc_currency;

		std::string filename = "account";
		filename += std::to_string(id);
		std::ofstream file(name + ".txt");
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}
		file << "����: " << name << " (" << id << ")" << std::endl;
		file << "��������: " << name << " (" << id << ")" << std::endl;
		file << "������: " << balance << " " << currency << std::endl;
		file.close();

		std::string logname = "C��� ������: ";
		logname += name;
		user.get_logs().logfile_update(user.get_user_id(), logname);

	}

	// ������� ��� ����������� ����� �� ��� �������������� (� ���������� ������ ����� ����������� �� ���� ������)
	void print_account() {
		std::cout << "�������� �����: " << name << std::endl;
		std::cout << "������: " << std::fixed << std::setprecision(2) << balance << " " << currency << std::endl;

	}

	void set_value(int type, double value) {
		if (type == 0) {
			this->balance += value;
			return;
		}
		if (type == 1) {
			this->balance -= value;
			return;
		}
		printf("Error");
		return;
	}

	User get_user() {
		return user;
	}

	~Account() {
	}
};

class Transaction {
private:
	int id;                 // ���������� ������������� ����������
	Account* account;
	int type;               // ���� ���� ���������� (0 - ���������� �� ����, 1 - ������ �� �����)
	std::string name;         // ��� ����������
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
	void change_value(std::string name, int type, int value) {
		account->set_value(type, value);
		if (type == 0) {
			account->get_user().get_logs().logfile_update(account->get_user().get_user_id(), "����������: " + std::to_string(value) + "(" + name + ")");
		}

		if (type == 1) {
			account->get_user().get_logs().logfile_update(account->get_user().get_user_id(), "��������: " + std::to_string(value) + "(" + name + ")");
		}
		return;

	}

};

class CurrencyChange {
private:
	std::string code;           // ��� ������ (��������, "USDRUB")
	std::string name;          // ������ �������� ������ (��������, "������ � �����")
	float rate;             // ���� ������ �� ��������� � ������� �����
public:
	CurrencyChange() : code(""), name(""), rate(0) {};

	CurrencyChange(std::string request) {
		setCurrencyChange(request);
	}

	// ������� ��� ��������� ��������� �����
	void setCurrencyChange(std::string request) {

		std::ifstream file("CurrencyRate.txt");
		if (!file.is_open()) {
			printf("������ �������� ����� CurrencyRate.txt");
			exit(1);
		}

		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string token;

			// �������� ������ ����� (���)
			if (std::getline(ss, token, ',')) {
				if (request == token) {
					code = token;

					// �������� ������ ����� (������)
					if (std::getline(ss, token, ',')) {
						rate = std::stod(token);
					}

					// �������� ������ ����� (���)
					if (std::getline(ss, token, '\n')) {
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
		std::cout << "����� " << name << std::endl;
		std::cout << std::fixed << std::setprecision(3) << amount << " = " << amount * rate << std::endl;
		return;
	}
};

class Goal {
private:
	std::string name;         // �������� ����
	std::string description;  // �������� ����
	float target_amount;    // ������� �����
	float current_amount;   // ������� �����
	User user;
public:
	Goal() : name(""), description(""), target_amount(0), current_amount(0), user() {};

	Goal(User user, std::string name, float target_amount, float current_ammount, std::string content) {
		create_goal(user, name, target_amount, current_ammount, content);
	}

	// ������� ��� �������� ����
	void create_goal(User user, std::string name, float target_amount, float current_ammount, std::string content) {
		this->name = name;
		this->current_amount = current_ammount;
		this->target_amount = target_amount;
		this->description = content;
		user.get_logs().logfile_update(user.get_user_id(), "������� ����");

	}

	// ������� ������ ����
	void print_goal() {
		std::cout << "����: " << name << std::endl;
		std::cout << std::fixed << std::setprecision(0) << current_amount << "/" << target_amount << std::endl;
		std::cout << "��������: " << description << std::endl;
	}
};

class Note {
private:
	std::string title;        // ��������� �������
	std::string content;      // ���������� �������
	int category;           // ��������� ������� (��������, 1 - �������, 2 - ������, 3 - ���������� ����, � �.�.)
	User user;
public:
	Note() : user(), title(""), content(""), category(0) {};

	Note(User user, std::string title, std::string content, int category) {
		create_note(user, title, content, category);
	};

	void create_note(User user, std::string title, std::string content, int category) {
		this->title = title;
		this->content = content;
		this->category = category;

		std::ofstream file(title + ".txt");
		if (!file.is_open()) {
			printf("������ �������� �����!");
			exit(1);
		}

		file << content;
		file.close();
		user.get_logs().logfile_update(user.get_user_id(), "������� �������");

	}

	void print_note() {
		std::cout << "�������: " << title << std::endl;
		std::cout << content << std::endl;
	}

	~Note() {
		printf("==������ �����������==");
	}
};

//
// ������������ ������
//

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Time time;
	time.print_current_time();
	Logs* logs = new Logs();

	User user1(1, "John", "Johnmail@gmail.com", "123", 0, *logs);
	User user2(2, "Leon", "Leonmail@gmail.com", "321", 0, *logs);

	user1.print_user();
	user2.print_user();

	Account account1("main", 0.0, "RUB", user1);
	Account account2("������", 100.0, "EUR", user2);

	account1.print_account();
	account2.print_account();

	Transaction transaction(1, &account1);
	transaction.change_value("���������", 0, 5000);

	transaction.set_transaction(2, &account2);
	transaction.change_value("������ �� ��������", 1, 5);

	account1.print_account();
	account2.print_account();

	CurrencyChange cur;
	cur.setCurrencyChange("RUBEUR");
	cur.change(1000);

	Goal goal1(user1, "BMW M5", 5000000.0, 0.0, "���� ������");
	goal1.print_goal();

	Note note1(user2, "������ ���������", "������ ������,����,�������", 1);
	note1.print_note();
}

void logfile_update(int id, std::string name)
{
}

void logfile_create(int id)
{
}