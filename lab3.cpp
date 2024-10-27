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
	Time() {
		current_time();
	}
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
	const char* getFullDate() const {
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
	std::string name;         // Название операции
	Time date;            // Дата операции
public:
	Logs() : name(""), date() {};

	// Функция для создания логфайла
	void logfile_create(int id) {
		name = "logs" + std::to_string(id);
		std::ofstream file(name + ".txt");
		if (!file.is_open()) {
			printf("Ошибка создания файла!");
			exit(1);
		}
		file.close();
	}
	// Функция для внесения лога в логфайл
	void logfile_update(int id, std::string name) {
		std::string mes = name;
		mes += date.getFullDate();

		name = "logs" + std::to_string(id);
		std::ofstream file(name + ".txt", std::ios::app);
		if (!file.is_open()) {
			printf("Ошибка создания файла!");
			exit(1);
		}

		file << mes;
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

				date.parse_date(date_str, &date);

				// Выводим данные
				printf("Название операции: %s\n", operation);
				printf("Дата: %s\n", date.getFullDate());
				printf("-----------------------------\n");
			}
		}

		fclose(file);
	}



};

class User {
private:
	int id;                 // Уникальный идентификатор пользователя
	std::string name;         // Имя пользователя
	std::string email;        // Адрес электронной почты
	std::string password;     // Пароль
	int is_admin;           // Флаг администратора (0 - обычный пользователь, 1 - администратор)
	Logs logs;

public:
	// Конструктор
	User() : id(0), name(""), email(""), password(""), is_admin(0), logs() {};

	User(int id, std::string name, std::string email, std::string password, int is_admin, Logs logs) {
		create_user(id, name, email, password, is_admin, logs);
	};
	// Функция для создания пользователя
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
			printf("Ошибка создания файла!");
			exit(1);
		}
		file << "Имя: " << name << " (" << id << ")" << std::endl;
		file << "Почта: " << email << std::endl;
		file << "Пароль: " << password << std::endl;
		if (is_admin == 1) {
			file << "Статус: Админ" << std::endl;
		}
		else {
			file << "Статус: Юзер" << std::endl;
		}
		file.close();

		logs.logfile_create(id);
		logs.logfile_update(id, "Профиль создан");
	}

	int get_user_id() {
		return id;
	};

	Logs get_logs() {
		return logs;
	}

	// Функция для вывода информации о пользователе
	void print_user() {
		std::cout << "Пользователь #" << id << ":" << std::endl;
		std::cout << "Имя: " << name << std::endl;
		std::cout << "Email: " << email << std::endl;
		std::cout << "Статус: " << (is_admin ? "Администратор" : "Юзер") << std::endl;
	}

	~User() {
	}
};

class Account {
private:
	int id;                 // Уникальный идентификатор счета
	std::string name;         // Название счета
	std::string currency;       // Валюта счета (например, "USD", "EUR", "RUB")
	double balance;         // Текущий баланс счета
	User user;
public:
	Account() : id(0), name(""), currency(""), balance(0.0), user() {};

	Account(std::string acc_name, double initial_balance, std::string acc_currency, User user) {
		create_account(acc_name, acc_currency, initial_balance, user);
	}
	// Функция для создания нового счета пользователя
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
			printf("Ошибка создания файла!");
			exit(1);
		}
		file << "Счёт: " << name << " (" << id << ")" << std::endl;
		file << "Владелец: " << name << " (" << id << ")" << std::endl;
		file << "Баланс: " << balance << " " << currency << std::endl;
		file.close();

		std::string logname = "Cчёт создан: ";
		logname += name;
		user.get_logs().logfile_update(user.get_user_id(), logname);

	}

	// Функция для отображения счета по его идентификатору (в дальнейшем данные будут считываться из базы данных)
	void print_account() {
		std::cout << "Название счета: " << name << std::endl;
		std::cout << "Баланс: " << std::fixed << std::setprecision(2) << balance << " " << currency << std::endl;

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
	int id;                 // Уникальный идентификатор транзакции
	Account* account;
	int type;               // Флаг типа транзакции (0 - зачисление на счет, 1 - снятие со счета)
	std::string name;         // Имя транзакции
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
	void change_value(std::string name, int type, int value) {
		account->set_value(type, value);
		if (type == 0) {
			account->get_user().get_logs().logfile_update(account->get_user().get_user_id(), "Зачисление: " + std::to_string(value) + "(" + name + ")");
		}

		if (type == 1) {
			account->get_user().get_logs().logfile_update(account->get_user().get_user_id(), "Списание: " + std::to_string(value) + "(" + name + ")");
		}
		return;

	}

};

class CurrencyChange {
private:
	std::string code;           // Код обмена (например, "USDRUB")
	std::string name;          // Полное название обмена (например, "доллар к рублю")
	float rate;             // Курс валюты по отношению к базовой валют
public:
	CurrencyChange() : code(""), name(""), rate(0) {};

	CurrencyChange(std::string request) {
		setCurrencyChange(request);
	}

	// Функция для установки обменного курса
	void setCurrencyChange(std::string request) {

		std::ifstream file("CurrencyRate.txt");
		if (!file.is_open()) {
			printf("Ошибка открытия файла CurrencyRate.txt");
			exit(1);
		}

		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string token;

			// Получаем первый токен (код)
			if (std::getline(ss, token, ',')) {
				if (request == token) {
					code = token;

					// Получаем второй токен (ставка)
					if (std::getline(ss, token, ',')) {
						rate = std::stod(token);
					}

					// Получаем третий токен (имя)
					if (std::getline(ss, token, '\n')) {
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
		std::cout << "Обмен " << name << std::endl;
		std::cout << std::fixed << std::setprecision(3) << amount << " = " << amount * rate << std::endl;
		return;
	}
};

class Goal {
private:
	std::string name;         // Название цели
	std::string description;  // Описание цели
	float target_amount;    // Целевая сумма
	float current_amount;   // Текущая сумма
	User user;
public:
	Goal() : name(""), description(""), target_amount(0), current_amount(0), user() {};

	Goal(User user, std::string name, float target_amount, float current_ammount, std::string content) {
		create_goal(user, name, target_amount, current_ammount, content);
	}

	// Функция для создания цели
	void create_goal(User user, std::string name, float target_amount, float current_ammount, std::string content) {
		this->name = name;
		this->current_amount = current_ammount;
		this->target_amount = target_amount;
		this->description = content;
		user.get_logs().logfile_update(user.get_user_id(), "Создана цель");

	}

	// Функция вывода цели
	void print_goal() {
		std::cout << "Цель: " << name << std::endl;
		std::cout << std::fixed << std::setprecision(0) << current_amount << "/" << target_amount << std::endl;
		std::cout << "Описание: " << description << std::endl;
	}
};

class Note {
private:
	std::string title;        // Заголовок заметки
	std::string content;      // Содержание заметки
	int category;           // Категория заметки (например, 1 - покупки, 2 - вклады, 3 - финансовые идеи, и т.д.)
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
			printf("Ошибка создания файла!");
			exit(1);
		}

		file << content;
		file.close();
		user.get_logs().logfile_update(user.get_user_id(), "Создана заметка");

	}

	void print_note() {
		std::cout << "Заметка: " << title << std::endl;
		std::cout << content << std::endl;
	}

	~Note() {
		printf("==Работа Деструктора==");
	}
};

//
// Демонстрация работы
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
	Account account2("Основа", 100.0, "EUR", user2);

	account1.print_account();
	account2.print_account();

	Transaction transaction(1, &account1);
	transaction.change_value("Стипендия", 0, 5000);

	transaction.set_transaction(2, &account2);
	transaction.change_value("Оплата за подписку", 1, 5);

	account1.print_account();
	account2.print_account();

	CurrencyChange cur;
	cur.setCurrencyChange("RUBEUR");
	cur.change(1000);

	Goal goal1(user1, "BMW M5", 5000000.0, 0.0, "Хочу машину");
	goal1.print_goal();

	Note note1(user2, "Список продуктов", "Купить молоко,хлеб,колбасу", 1);
	note1.print_note();
}

void logfile_update(int id, std::string name)
{
}

void logfile_create(int id)
{
}