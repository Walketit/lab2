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
// Классы
//

class Time {
private:
	char hour[3];			// Переменная для часа
	char min[3];			// Переменная для минуты
	char sec[3];			// Переменная для секунды
	char day[3];			// Переменная для дня
	char month[3];			// Переменная для месяца
	char year[5];			// Переменная для года
	char full_date[22];     // Переменная для полной даты
public:
	// Функция для получения текущего времени
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

	// Функция вывода текущего времени
	void print_current_time() {
		current_time();
		printf("Сегодня: %s-%s-%s\n", day, month, year);
		printf("Время: %s:%s:%s\n\n", hour, min, sec);
	}
	const char* get_full_date() {
		current_time();
		return full_date;
	}

	// Функция для парсинга строки даты и времени
	void parse_date(const char* date_str, Time* time) {
		sscanf(date_str, "%4s-%2s-%2s %2s:%2s:%2s",
			time->year, time->month, time->day,
			time->hour, time->min, time->sec);
		strcpy(time->full_date, date_str);
	}
};

class Logs {
private:
	string name;         // Название операции
	Time time;            // Дата операции
public:
	Logs() : name(""), time() {};

	// Функция для создания логфайла
	void logfile_create(int id) {
		name = "logs" + to_string(id);
		ofstream file(name + ".txt");
		if (!file.is_open()) {
			printf("Ошибка создания файла!");
			exit(1);
		}
		file.close();
	}
	// Функция для внесения лога в логфайл
	void logfile_update(int id, string name) {
		time.current_time();
		string mes = name + time.get_full_date();

		name = "logs" + to_string(id);
		ofstream file(name + ".txt", ios::app);
		if (!file.is_open()) {
			printf("Ошибка создания файла!");
			exit(1);
		}

		file << mes << endl;
		file.close();

		return;
	}

	// Функция для считывания и вывода логов
	void read_logs(int id) {
		char filename[50] = "logs";
		char str_id[3];
		sprintf(str_id, "%d", id);
		strcat(filename, str_id);
		strcat(filename, ".txt");
		FILE* file = fopen(filename, "r");
		if (file == NULL) {
			printf("Ошибка открытия файла");
			return;
		}

		char line[256];
		printf("История операций:\n\n");

		while (fgets(line, sizeof(line), file)) {
			// Удаляем символ новой строки, если он есть
			line[strcspn(line, "\n")] = '\0';

			// Разбиваем строку на две части: название операции и дату
			char* operation = strtok(line, "|");
			char* date_str = strtok(NULL, "|");

			if (operation != NULL && date_str != NULL) {

				time.parse_date(date_str, &time);

				// Выводим данные
				printf("Название операции: %s\n", operation);
				printf("Дата: %s\n", time.get_full_date());
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
	int id;                 // Уникальный идентификатор счета
	string name;         // Название счета
	string currency;       // Валюта счета (например, "USD", "EUR", "RUB")
	double balance;         // Текущий баланс счета
public:
	Account() : id(0), name(""), currency(""), balance(0.0) {};

	Account(string acc_name, double initial_balance, string acc_currency) {
		create_account(acc_name, acc_currency, initial_balance);
	}
	// Функция для создания нового счета пользователя
	void create_account(string acc_name, string acc_currency, double initial_balance) {
		name = acc_name;
		balance = initial_balance;
		currency = acc_currency;
	}

	// Функция для отображения счета по его идентификатору (в дальнейшем данные будут считываться из базы данных)
	void print_account() {
		cout << "Название счета: " << name << endl;
		cout << "Баланс: " << fixed << setprecision(2) << balance << " " << currency << endl;

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
	int id;                 // Уникальный идентификатор транзакции
	Account* account;
	int type;               // Флаг типа транзакции (0 - зачисление на счет, 1 - снятие со счета)
	string name;         // Имя транзакции
	double amount;          // Сумма транзакции
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

	// Функция для выполнения транзакции
	void change_value(string name, int type, int value) {
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

};

class CurrencyChange {
private:
	string code;           // Код обмена (например, "USDRUB")
	string name;          // Полное название обмена (например, "доллар к рублю")
	float rate;             // Курс валюты по отношению к базовой валют
public:
	CurrencyChange() : code(""), name(""), rate(0) {};

	CurrencyChange(string request) {
		set_сurrency_сhange(request);
	}

	// Функция для установки обменного курса
	void set_сurrency_сhange(string request) {

		ifstream file("CurrencyRate.txt");
		if (!file.is_open()) {
			printf("Ошибка открытия файла CurrencyRate.txt");
			exit(1);
		}

		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string token;

			// Получаем первый токен (код)
			if (getline(ss, token, ',')) {
				if (request == token) {
					code = token;

					// Получаем второй токен (ставка)
					if (getline(ss, token, ',')) {
						rate = stod(token);
					}

					// Получаем третий токен (имя)
					if (getline(ss, token, '\n')) {
						name = token;
					}

					file.close();
					return;
				}
			}
			printf("Выбранный обменный курс не найден.");
			exit(1);
		}
	}
	// Функция обмена курса
	void change(float amount) {
		cout << "Обмен " << name << endl;
		cout << fixed << setprecision(3) << amount << " = " << amount * rate << endl;
		return;
	}
};

class Goal {
private:
	string name;         // Название цели
	string description;  // Описание цели
	float target_amount;    // Целевая сумма
	float current_amount;   // Текущая сумма
public:
	Goal() : name(""), description(""), target_amount(0), current_amount(0) {}

	Goal(string name, float target_amount, float current_ammount, string content) {
		this->name = name;
		this->current_amount = current_ammount;
		this->target_amount = target_amount;
		this->description = content;
	}

	// Функция вывода цели
	void print_goal() {
		cout << "Цель: " << name << endl;
		cout << fixed << setprecision(0) << current_amount << "/" << target_amount << endl;
		cout << "Описание: " << description << endl;
	}
	// Прибавление к текущей сумме
	void addToBalance(double amount) {
		current_amount += amount;
	}
	// Проверка достижения цели
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
	string title;        // Заголовок заметки
	string content;      // Содержание заметки
	string category;           // Категория заметки (например, 1 - покупки, 2 - вклады, 3 - финансовые идеи, и т.д.)
public:
	Note() : title(""), content(""), category("") {};

	Note(string title, string content, string category) {
		this->title = title;
		this->content = content;
		this->category = category;
	};

	void print_note() {
		cout << "Заметка: " << title << endl;
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
	int id;                 // Уникальный идентификатор пользователя
	string name;         // Имя пользователя
	string email;        // Адрес электронной почты
	string password;     // Пароль
	int is_admin;           // Флаг администратора (0 - обычный пользователь, 1 - администратор)
	Logs logs;
	vector<Account> accounts;
	vector<Note> notes;
	vector<Goal> goals;
public:
	// Конструктор
	User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};
	// Конструктор для создания пользователя
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
			printf("Ошибка создания файла!");
			exit(1);
		}
		file << "Имя: " << name << " (" << id << ")" << endl;
		file << "Почта: " << email << endl;
		file << "Пароль: " << password << endl;
		if (is_admin == 1) {
			file << "Статус: Админ" << endl;
		}
		else {
			file << "Статус: Юзер" << endl;
		}
		file.close();

		logs.logfile_create(id);
		logs.logfile_update(id, "Профиль создан");
	};

	void add_account(Account account) {
		account.setId(id + 100000);
		string filename = "account";
		filename += to_string(id);
		ofstream file(name + ".txt");
		if (!file.is_open()) {
			printf("Ошибка создания файла!");
			exit(1);
		}
		file << "Счёт: " << account.getName() << " (" << account.getId() << ")" << endl;
		file << "Владелец: " << name << " (" << id << ")" << endl;
		file << "Баланс: " << account.getBalance() << " " << account.getCurrency() << endl;
		file.close();

		string logname = "Cчёт создан: ";
		logname += account.getName();
		logs.logfile_update(id, logname);

		accounts.push_back(account);
	}

	void displayAccounts() const {
		cout << "Счета " << name << ":" << endl;
		for (const auto& account : accounts) {
			cout << "Счёт: " << account.getName() << endl;
			cout << "Баланс: " << account.getBalance() << " " << account.getCurrency() << endl;
		}
	}

	void add_note(Note note) {
		ofstream file(note.getTitle() + ".txt");
		if (!file.is_open()) {
			printf("Ошибка создания файла!");
			exit(1);
		}

		file << note.getDescription();
		file.close();
		logs.logfile_update(id, "Создана заметка");

		notes.push_back(note);
	}

	void displayNotes() const {
		cout << "Записки " << name << ":" << endl;
		for (const auto& note : notes) {
			cout << "Записка: " << note.getTitle() << ", Категория: " << note.getCategory() << endl;
			cout << note.getDescription() << endl;
		}
	}

	void add_goal(Goal goal) {
		string n = "Создана цель: " + goal.getTitle();
		logs.logfile_update(id, n);
		goals.push_back(goal);
	}

	void displayGoals() const {
		cout << "Цели " << name << ":" << endl;
		for (const auto& goal : goals) {
			cout << "Цель: " << goal.getTitle() << ", Текущая сумма: " << goal.getCurrentBalance()
				<< ", Целевая сумма: " << goal.getTargetAmount() << endl;
		}
	}

	// Функция для вывода информации о пользователе
	void print_user() {
		cout << "Пользователь #" << id << ":" << endl;
		cout << "Имя: " << name << endl;
		cout << "Email: " << email << endl;
		cout << "Статус: " << (is_admin ? "Администратор" : "Юзер") << endl;
	}

	Account* getAccount(int index) {
		if (index >= 0 && index < accounts.size()) {
			return &accounts[index];
		}
		return nullptr;
	}

};

//
// Демонстрация работы
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
	Account account2("Основа", 100.0, "EUR");

	user1.add_account(account1);
	user1.add_account(account2);

	user1.displayAccounts();

	cout << '\n' << endl;

	Transaction transaction(1, user1.getAccount(0));
	transaction.change_value("Стипендия", 0, 5000);

	transaction.set_transaction(2, user1.getAccount(1));
	transaction.change_value("Оплата за подписку", 1, 5);

	cout << '\n' << endl;

	user1.displayAccounts();

	cout << '\n' << endl;

	CurrencyChange cur;
	cur.set_сurrency_сhange("RUBEUR");
	cur.change(1000);

	cout << '\n' << endl;

	Goal goal1("BMW M5", 5000000.0, 0.0, "Хочу машину");
	user1.add_goal(goal1);
	user1.displayGoals();

	cout << '\n' << endl;

	Note note1("Список продуктов", "Купить молоко,хлеб,колбасу", "Покупки");
	user1.add_note(note1);
	user1.displayNotes();

	cout << "\n";

	logs->read_logs(1);

	// Работа с динамическим массивом объектов класса
	int numUsers = 3;
	User* users = new User[numUsers]{
			User{3, "Layla", "Layla1999@gmail.com", "asd", 0, *logs},
			User{4, "Matt", "MattSmith@gmail.com", "asdzxc", 1, *logs},
			User{5, "Лео", "Messi@gmail.com", "111111", 0, *logs}
	};

	cout << "\nДинамический список объектов:\n";
	for (int i = 0; i < numUsers; ++i) {
		users[i].print_user();
		cout << "\n";
	}

	delete[] users;

	// Работа с массивом динамических объектов класса
	int numGoals = 2;
	Goal** goals = new Goal * [numGoals];
	goals[0] = new Goal("Квартира", 500000000.0, 0.0, "Мечта");
	goals[1] = new Goal("Playstation 5", 65000.0, 0.0, "Купить на новогодних скидках");

	cout << "\nСписок Динамических объектов:\n";
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