#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void logfile_create(int id);
void logfile_update(int id, const char* name);

//
// Структуры
//


class Account {
private:
	int id;                 // Уникальный идентификатор счета
	int user_id;            // Идентификатор пользователя, которому принадлежит счет
	char name[100];         // Название счета
	double balance;         // Текущий баланс счета
	char currency[4];       // Валюта счета (например, "USD", "EUR", "RUB")
public:
	Account(int usr_id, const char* acc_name, double initial_balance, const char* acc_currency) {
		create_account(usr_id, acc_name, initial_balance, acc_currency);
		printf("==Работа Конструктора==");
	}
	// Функция для создания нового счета пользователя
	void create_account(int usr_id, const char* acc_name, double initial_balance, const char* acc_currency) {
		user_id = usr_id;
		id = user_id + 100000;
		strncpy(name, acc_name, sizeof(name) - 1);
		name[sizeof(name) - 1] = '\0';  // Убедимся, что строка завершена нулевым символом
		balance = initial_balance;
		strncpy(currency, acc_currency, sizeof(currency) - 1);
		currency[sizeof(currency) - 1] = '\0';  // Убедимся, что строка завершена нулевым символом

		char filename[40] = "account";
		char str_id[7];
		sprintf(str_id, "%d", id);
		strcat(filename, str_id);
		FILE* file = fopen(strcat(filename, ".txt"), "w");
		fprintf(file, "Счёт: %s (%d)\n", name, id);
		fprintf(file, "Владелец: %s (%d)\n", name, id);
		fprintf(file, "Баланс: %fl %s\n", balance, currency);
		fclose(file);

		char logname[100] = "Cчёт создан: ";
		strcat(logname, name);
		logfile_update(user_id, logname);

	}

	// Функция для отображения счета по его идентификатору (в дальнейшем данные будут считываться из базы данных)
	void print_account() {

		printf("Название счета: %s\n", name);
		printf("Баланс: %.2f %s\n", balance, currency);

	}

	void set_value(int type, double value) {
		if (type == 0) {
			balance += value;
			return;
		}
		if (type == 1) {
			balance -= value;
			return;
		}
		printf("Error");
		return;
	}

	int get_user_id() {
		return user_id;
	}

	~Account() {

		printf("==Работа Деструктора==");
	}
};

class User {
private:
	int id;                 // Уникальный идентификатор пользователя
	char name[100];         // Имя пользователя
	char email[100];        // Адрес электронной почты
	char password[100];     // Пароль
	int is_admin;           // Флаг администратора (0 - обычный пользователь, 1 - администратор)

public:
	Account account;
	// Конструктор
	User(int usr_id, const char* usr_name, const char* usr_email, const char* usr_password, int admin_flag,
		double initial_balance, const char* acc_currency)
		: account(usr_id, "Main", initial_balance, acc_currency) {
		create_user(usr_id, usr_name, usr_email, usr_password, admin_flag);
		printf("==Работа Конструктора==");
	}
	// Функция для создания пользователя
	void create_user(int s_id, const char* s_name, const char* s_email, const char* s_password, int s_is_admin) {
		id = s_id;
		is_admin = s_is_admin;
		strcpy(name, s_name);
		strcpy(email, s_email);
		strcpy(password, s_password);

		char filename[40] = "profile";
		char str_id[3];
		sprintf(str_id, "%d", id);
		strcat(filename, str_id);
		FILE* file = fopen(strcat(filename, ".txt"), "w");
		fprintf(file, "Имя: %s (%d)\n", name, id);
		fprintf(file, "Почта: %s\n", email);
		fprintf(file, "Пароль: %s\n", password);
		if (is_admin == 1) {
			fprintf(file, "Статус: Админ\n");
		}
		else fprintf(file, "Статус: Юзер\n");
		fclose(file);

		logfile_create(id);
		logfile_update(id, "Профиль создан");
	}

	int get_user_id() {
		return id;
	};

	// Функция для вывода информации о пользователе
	void print_user() {
		printf("Пользователь #%d:\n", id);
		printf("Имя: %s\n", name);
		printf("Email: %s\n", email);
		printf("Статус: %s\n", is_admin ? "Администратор" : "Юзер");
	}

	~User() {
		printf("==Работа Деструктора==");
	}
};

class Transaction {
private:
	int id;                 // Уникальный идентификатор транзакции
	int user_id;            // Идентификатор пользователя, которому принадлежит данная транзакция
	int type;               // Флаг типа транзакции (0 - зачисление на счет, 1 - снятие со счета)
	char name[100];         // Имя транзакции
	double amount;          // Сумма транзакции
public:
	Transaction() {

	}

	// Функция для выполнения транзакции
	void change_value(Account account, int type, int value) {
		account.set_value(type, value);
		if (type == 0) {
			logfile_update(account.get_user_id(), "Зачисление: " + char(value));
		}

		if (type == 1) {
			logfile_update(account.get_user_id(), "Списание: " + char(value));
		}
		return;

	}

};

class CurrencyChange {
private:
	char code[7];           // Код обмена (например, "USDRUB")
	char name[50];          // Полное название обмена (например, "доллар к рублю")
	float rate;             // Курс валюты по отношению к базовой валют
public:
	CurrencyChange(const char* request) {
		setCurrencyChange(request);
	}

	// Функция для установки обменного курса
	void setCurrencyChange(const char* request) {

		FILE* file = fopen("CurrencyRate.txt", "r");
		if (!file) {
			printf("Ошибка открытия файла CurrencyRate.txt");
			exit(1);
		}

		char line[128];
		while (fgets(line, sizeof(line), file)) {

			char* token = strtok(line, ",");
			if (token) {
				strncpy(code, token, sizeof(code) - 1);
				code[sizeof(code) - 1] = '\0';
			}

			token = strtok(NULL, ",");
			if (token) {
				rate = atof(token);
			}

			token = strtok(NULL, "\n");
			if (token) {
				strncpy(name, token, sizeof(name) - 1);
				name[sizeof(name) - 1] = '\0';
			}

			if (strcmp(code, request) == 0) {
				strcpy(code, code);
				strcpy(name, name);
				rate = rate;
				fclose(file);
			}
			return;
		}
		printf("Выбранный обменный курс не найден.");
		exit(1);
	}
	// Функция обмена курса
	void change(float amount) {
		printf("Обмен %s\n", name);
		printf("%.3f = %.3f\n", amount, amount * rate);
		return;
	}
};

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

class Goal {
private:
	int user_id;            // Идентификатор пользователя, которому принадлежит данная цель
	char name[100];         // Название цели
	float target_amount;    // Целевая сумма
	float current_amount;   // Текущая сумма
	char description[500];  // Описание цели
public:
	Goal(User user, const char* name, float target_amount, float current_ammount, const char* content) {
		create_goal(user, name, target_amount, current_ammount, content);
	}

	// Функция для создания цели
	void create_goal(User user, const char* name, float target_amount, float current_ammount, const char* content) {
		user_id = user.get_user_id();
		strcpy(this->name, name);
		this->current_amount = current_ammount;
		this->target_amount = target_amount;
		strcpy(this->description, content);
		logfile_update(user_id, "Создана цель");

	}

	// Функция вывода цели
	void print_goal() {
		printf("Цель: %s\n", name);
		printf("%.f/%.f\n", current_amount, target_amount);
		printf("Описание: %s", description);
	}
};

class Note {
private:
	char title[100];        // Заголовок заметки
	char content[500];      // Содержание заметки
	time_t created_at;      // Временная метка создания заметки
	time_t updated_at;      // Временная метка последнего обновления заметки
	int category;           // Категория заметки (например, 1 - покупки, 2 - вклады, 3 - финансовые идеи, и т.д.)
public:
	Note(User user, const char* title, const char* content, int category) {
		create_note(user, title, content, category);
	};

	void create_note(User user,const char* title, const char* content, int category) {
		strcpy(this->title, title);
		strcpy(this->content, content);
		this->category = category;

		FILE* file = fopen(strcat(this->title, ".txt"), "w");
		fputs(content, file);
		fclose(file);
		logfile_update(user.get_user_id(), "Создана заметка");

	}

	void print_note() {
		printf("Заметка: %s\n", title);
		printf("%s", content);
	}

	~Note() {
		printf("==Работа Деструктора==");
	}
};

class Logs {
private:
	char name[100];         // Название операции
	Time date;            // Дата операции
public:
	Logs(int id) {

	}
	// Функция для создания логфайла
	void logfile_create(int id) {
		char n[50] = "logs";
		char str_id[3];
		sprintf(str_id, "%d", id);
		strcat(n, str_id);
		strcat(n, ".txt");
		FILE* file = fopen(n, "w");
		fclose(file);
	}
	// Функция для внесения лога в логфайл
	void logfile_update(int id, char* name) {
		Time currentTime;
		char mes[150];
		strcpy(mes, name);
		strcat(mes, currentTime.getFullDate());

		char n[50] = "logs";
		char str_id[2];
		sprintf(str_id, "%d", id);
		strcat(n, str_id);
		strcat(n, ".txt");
		FILE* file = fopen(n, "a");
		if (file != NULL) {
			fputs(mes, file);
			fputs("\n", file);
			fclose(file);
		}
		else printf("Error");
		return;
	}

	// Функция для считывания и вывода логов
	void read_logs(User user) {
		char filename[50] = "logs";
		char str_id[3];
		sprintf(str_id, "%d", user.get_user_id());
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
				strncpy(name, operation, sizeof(name) - 1);
				name[sizeof(name) - 1] = '\0'; // Убедимся, что строка завершена нулевым символом

				date.parse_date(date_str, &date);

				// Выводим данные
				printf("Название операции: %s\n", name);
				printf("Дата: %s\n", date.getFullDate());
				printf("-----------------------------\n");
			}
		}

		fclose(file);
	}



};

//
// Функции
//






//
// Демонстрация работы
//

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int user_amount = 3;
	User** users = new User * [user_amount];
	users[0] = new User(1, "John", "john.doe@example.com", "password123", 0, 0.0, "RUB");
	users[1] = new User(2, "Jane Smith", "jane.smith@example.com", "password456", 1, 220.0, "EUR");
	users[2] = new User(3, "Alice Johnson", "alice.johnson@example.com", "password789", 0, 100.0, "USD");

	for (int i = 0; i < user_amount; i++) {
		users[i]->print_user();
		printf("\n");
		users[i]->account.print_account();
		printf("\n");
	}

	for (int i = 0; i < user_amount; ++i) {
		delete users[i];
	}
	delete[] users;
}

void logfile_update(int id, const char* name)
{
}

void logfile_create(int id)
{
}