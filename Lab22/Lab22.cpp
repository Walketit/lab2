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

typedef struct {
	int id;                 // Уникальный идентификатор пользователя
	char name[100];         // Имя пользователя
	char email[100];        // Адрес электронной почты
	char password[100];     // Пароль
	int is_admin;           // Флаг администратора (0 - обычный пользователь, 1 - администратор)
} User;

typedef struct {
	int id;                 // Уникальный идентификатор счета
	int user_id;            // Идентификатор пользователя, которому принадлежит счет
	char name[100];         // Название счета
	double balance;         // Текущий баланс счета
	char currency[4];       // Валюта счета (например, "USD", "EUR", "RUB")
} Account;

typedef struct {
	int id;                 // Уникальный идентификатор транзакции
	int user_id;            // Идентификатор пользователя, которому принадлежит данная транзакция
	int type;               // Флаг типа транзакции (0 - зачисление на счет, 1 - снятие со счета)
	char name[100];         // Имя транзакции
	double amount;          // Сумма транзакции
} Transaction;

typedef struct {
	char code[7];           // Код обмена (например, "USDRUB")
	char name[50];          // Полное название обмена (например, "доллар к рублю")
	float rate;             // Курс валюты по отношению к базовой валют
} CurrencyChange;

typedef struct {
	char hour[3];			// Переменная для часа
	char min[3];			// Переменная для минуты
	char sec[3];			// Переменная для секунды
	char day[3];			// Переменная для дня
	char month[3];			// Переменная для месяца
	char year[5];			// Переменная для года
	char full_date[22];     // Переменная для полной даты
} Time;

typedef struct {
	int user_id;            // Идентификатор пользователя, которому принадлежит данная цель
	char name[100];         // Название цели
	float target_amount;    // Целевая сумма
	float current_amount;   // Текущая сумма
	char description[500];  // Описание цели
} Goal;

typedef struct {
	char title[100];        // Заголовок заметки
	char content[500];      // Содержание заметки
	time_t created_at;      // Временная метка создания заметки
	time_t updated_at;      // Временная метка последнего обновления заметки
	int category;           // Категория заметки (например, 1 - покупки, 2 - вклады, 3 - финансовые идеи, и т.д.)
} Note;

typedef struct {
	char name[100];         // Название операции
	Time date;            // Дата операции
} Logs;

//
// Функции
//

// Функция для создания пользователя
User create_user(int id, const char* name, const char* email, const char* password, int is_admin) {
	User user;
	user.id = id;
	strcpy(user.name, name);
	strcpy(user.email, email);
	strcpy(user.password, password);
	user.is_admin = is_admin;

	char filename[40] = "profile";
	char str_id[3];
	sprintf(str_id, "%d", user.id);
	strcat(filename, str_id);
	FILE* file = fopen(strcat(filename, ".txt"), "w");
	fprintf(file, "Имя: %s (%d)\n", user.name, user.id);
	fprintf(file, "Почта: %s\n", user.email);
	fprintf(file, "Пароль: %s\n", user.password);
	if (user.is_admin == 1) {
		fprintf(file, "Статус: Админ\n");
	}
	else fprintf(file, "Статус: Юзер\n");
	fclose(file);

	logfile_create(user.id);
	logfile_update(user.id, "Профиль создан");
	return user;
}

// Функция для создания нового счета пользователя
Account create_account(Account* accounts, User user, const char* name, double balance, const char* currency) {
	Account account;
	account.id = user.id + 100000;
	account.user_id = user.id;
	strcpy(account.name, name);
	account.balance = balance;
	strcpy(account.currency, currency);
	accounts[user.id] = account;

	char filename[40] = "account";
	char str_id[7];
	sprintf(str_id, "%d", account.id);
	strcat(filename, str_id);
	FILE* file = fopen(strcat(filename, ".txt"), "w");
	fprintf(file, "Счёт: %s (%d)\n", account.name, account.id);
	fprintf(file, "Владелец: %s (%d)\n", user.name, user.id);
	fprintf(file, "Баланс: %d %s\n", account.balance, account.currency);
	fclose(file);

	char logname[100] = "Cчёт создан: ";
	strcat(logname, name);
	logfile_update(user.id, logname);
	return account;
}

// Функция для создания новой заметки
// Заметки будут хранится локально на устройстве пользователя
Note create_note(User user, const char* title, const char* content, int category) {
	Note note;
	strcpy(note.title, title);
	strcpy(note.content, content);
	note.category = category;

	FILE* file = fopen(strcat(note.title, ".txt"), "w");
	fputs(content, file);
	fclose(file);

	logfile_update(user.id, "Создана заметка");
	return note;
}

// Функция для создания цели
Goal create_goal(User user, const char* name, float target_amount, float current_ammount, const char* content) {
	Goal goal;
	goal.user_id = user.id;
	strcpy(goal.name, name);
	goal.current_amount = current_ammount;
	goal.target_amount = target_amount;
	strcpy(goal.description, content);

	logfile_update(user.id, "Создана цель");
	return goal;
}

// Функция для получения текущего времени
Time current_time() {
	Time current_time;
	time_t timen;
	struct tm* timeinfo;
	time(&timen);
	timeinfo = localtime(&timen);
	strftime(current_time.day, 3, "%d", timeinfo);
	strftime(current_time.month, 3, "%m", timeinfo);
	strftime(current_time.year, 5, "%Y", timeinfo);
	strftime(current_time.hour, 3, "%H", timeinfo);
	strftime(current_time.min, 3, "%M", timeinfo);
	strftime(current_time.sec, 3, "%S", timeinfo);
	strftime(current_time.full_date, 22, "|%Y-%m-%d %H:%M:%S|", timeinfo);
	return current_time;
}

// Функция для установки обменного курса
CurrencyChange setCurrencyChange(const char* request) {
	CurrencyChange currency;
	FILE* file = fopen("CurrencyRate.txt", "r");
	if (!file) {
		printf("Ошибка открытия файла CurrencyRate.txt");
		exit(1);
	}

	char line[128];
	while (fgets(line, sizeof(line), file)) {
		char code[7];
		float rate;
		char name[50];

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
				strcpy(currency.code, code);
				strcpy(currency.name, name);
				currency.rate = rate;
				fclose(file);
				return currency;
			}
		}
	printf("Выбранный обменный курс не найден.");
	exit(1);
	}

// Функция для парсинга строки даты и времени
void parse_date(const char* date_str, Time* time) {
	sscanf(date_str, "%4s-%2s-%2s %2s:%2s:%2s",
		time->year, time->month, time->day,
		time->hour, time->min, time->sec);
	strcpy(time->full_date, date_str);
}

// Функция для считывания и вывода логов
void read_logs(User user) {
	char filename[50] = "logs";
	char str_id[3];
	sprintf(str_id, "%d", user.id);
	strcat(filename, str_id);
	strcat(filename, ".txt");
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Ошибка открытия файла");
		return;
	}

	char line[256];
	Logs log;
	printf("История операций:\n\n");

	while (fgets(line, sizeof(line), file)) {
		// Удаляем символ новой строки, если он есть
		line[strcspn(line, "\n")] = '\0';

		// Разбиваем строку на две части: название операции и дату
		char* operation = strtok(line, "|");
		char* date_str = strtok(NULL, "|");

		if (operation != NULL && date_str != NULL) {
			strncpy(log.name, operation, sizeof(log.name) - 1);
			log.name[sizeof(log.name) - 1] = '\0'; // Убедимся, что строка завершена нулевым символом

			parse_date(date_str, &log.date);

			// Выводим данные
			printf("Название операции: %s\n", log.name);
			printf("Дата: %s\n", log.date.full_date);
			printf("-----------------------------\n");
		}
	}

	fclose(file);
}

// Функция обмена курса
void change(CurrencyChange currency, float amount) {
	printf("Обмен %s\n", currency.name);
	printf("%.3f = %.3f\n", amount, amount * currency.rate);
	return;
}
// Функция вывода заметки
void print_note(Note note) {
	printf("Заметка: %s\n", note.title);
	printf("%s", note.content);
}
// Функция вывода цели
void print_goal(Goal goal) {
	printf("Цель: %s\n", goal.name);
	printf("%.f/%.f\n", goal.current_amount, goal.target_amount);
	printf("Описание: %s", goal.description);
}

// Функция для вывода информации о пользователе
void print_user(User user) {
	printf("Пользователь #%d:\n", user.id);
	printf("Имя: %s\n", user.name);
	printf("Email: %s\n", user.email);
	printf("Статус: %s\n", user.is_admin ? "Администратор" : "Юзер");
}

// Функция для отображения счета по его идентификатору (в дальнейшем данные будут считываться из базы данных)
void print_account(Account* accounts, User user) {
	size_t n = sizeof(accounts) / sizeof(int);
	for (int i = 0; i < n; i++) {
		if (accounts[i].user_id == user.id) {
			printf("Название счета: %s\n", accounts[i].name);
			printf("Баланс: %.2f %s\n", accounts[i].balance, accounts[i].currency);
			return;
		}
	}
	printf("У вас нет счетов.\n");
}

// Функция для выполнения транзакции
void change_value(Account account,int type, int value) {
	if (type == 0) {
		account.balance += value;
		logfile_update(account.user_id, "Зачисление: " + char(value));
		return;
	}
	if (type == 1) {
		account.balance -= value;
		logfile_update(account.user_id, "Снятие: " + char(value));
		return;
	}
	printf("Error");
	return;
	
}

// Функция вывода текущего времени
void print_current_time() {
	Time currentTime = current_time();
	printf("Сегодня: %s-%s-%s\n", currentTime.day, currentTime.month, currentTime.year);
	printf("Время: %s:%s:%s\n\n", currentTime.hour, currentTime.min, currentTime.sec);
	return;
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
void logfile_update(int id, const char* name) {
	Time currentTime = current_time();
	char mes[150];
	strcpy(mes, name);
	strcat(mes, currentTime.full_date);

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

	//
	// Демонстрация работы
	//

	int main()
	{

		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		// Статические данные
		print_current_time();

		User user1 = create_user(0, "John", "John@mail.ru", "password123", 0);
		print_user(user1);

		Account accounts[100];
		printf("\n");

		Account account1 = create_account(accounts, user1, "Основной", 0.0, "RUB");
		print_account(accounts, user1);

		printf("\n");

		Note note1 = create_note(user1, "Покупки", "Купить молоко, чипсы, колу", 1);
		print_note(note1);

		printf("\n\n");

		Goal goal1 = create_goal(user1, "Покупка видеокарты", 26000, 0, "Новая видеокарта");
		print_goal(goal1);

		printf("\n\n");

		CurrencyChange currency = setCurrencyChange("RUBEUR");
		change(currency, 200);

		printf("\n\n");

		read_logs(user1);

		printf("\n\n\n\n");

		// Динамические данные

		char user_name[20], email[50], password[20];

		char account_name[20], currenc[4];
		float balance;

		char note_name[20], note_content[150];
		int note_type;

		char goal_name[40], goal_content[100];
		int target_amount;

		char cur_code[7];
		float change_amount;

		printf("Введите ваше имя: ");
		scanf("%[^\n]s", &user_name);
		while (getchar() != '\n');
		printf("Введите вашу почту: ");
		scanf("%[^\n]s", &email);
		while (getchar() != '\n');
		printf("Введите ваш пароль: ");
		scanf("%[^\n]s", &password);
		while (getchar() != '\n');

		User user2 = create_user(1, user_name, email, password, 0);
		print_user(user2);

		printf("\n\n");

		printf("Введите название вашего основного кошелька: ");
		scanf("%[^\n]s", &account_name);
		while (getchar() != '\n');
		printf("Введите код валюты(RUB, USD, EUR): ");
		scanf("%[^\n]s", &currenc);
		while (getchar() != '\n');
		printf("Введите баланс кошелька: ");
		scanf("%f", &balance);
		while (getchar() != '\n');

		Account account2 = create_account(accounts, user2, account_name, balance, currenc);
		print_account(accounts, user2);

		printf("\n\n");

		printf("Введите название заметки: ");
		scanf("%[^\n]s", &note_name);
		while (getchar() != '\n');
		printf("Введите описание заметки: ");
		scanf("%[^\n]s", &note_content);
		while (getchar() != '\n');
		printf("Выберите категорию заметки( 1 - покупки, 2 - вклады, 3 - финансовые идеи): ");
		scanf("%d", &note_type);
		while (getchar() != '\n');

		Note note2 = create_note(user2, note_name, note_content, note_type);
		print_note(note2);

		printf("\n\n");

		printf("Введите название цели: ");
		scanf("%[^\n]s", &goal_name);
		while (getchar() != '\n');
		printf("Введите описание цели: ");
		scanf("%[^\n]s", &goal_content);
		while (getchar() != '\n');
		printf("Введите необходимую сумму: ");
		scanf("%d", &target_amount);
		while (getchar() != '\n');

		Goal goal2 = create_goal(user2, goal_name, target_amount, 0.0, goal_content);
		print_goal(goal2);

		printf("\n\n");

		printf("Введите необходимый обменный код(USDRUB, EURRUB, RUBUSD, RUBEUR): ");
		scanf("%[^\n]s", &cur_code);
		while (getchar() != '\n');
		printf("Введите необходимую для вычисления сумму: ");
		scanf("%f", &change_amount);
		while (getchar() != '\n');

		CurrencyChange currency2 = setCurrencyChange(cur_code);
		change(currency2, change_amount);

		printf("\n\n");

		char answer;

		do {
			printf("Хотите просмотреть логи операций? (y/n)");
			scanf(" %c", &answer);
			while (getchar() != '\n');
		} while (answer != 'y' && answer != 'n');

		if (answer == 'y') read_logs(user2);

		do {
			printf("Хотите просмотреть текущее время? (y/n)");
			scanf(" %c", &answer);
			while (getchar() != '\n');
		} while (answer != 'y' && answer != 'n');

		if (answer == 'y') print_current_time();

	}