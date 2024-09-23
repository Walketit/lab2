#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <iostream>

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
	char code[4];           // Код валюты
	char name[50];          // Полное название валюты 
	float rate;             // Курс валюты по отношению к базовой валют
} Currency;

typedef struct {
	int id;                 // Уникальный идентификатор оповещения
	char title[100];        // Заголовок оповещения
	char message[500];      // Текст оповещения
	time_t timestamp;       // Временная метка создания оповещения
} Notification;

typedef struct {
	int id;                 // Уникальный идентификатор цели
	int user_id;            // Идентификатор пользователя, которому принадлежит данная цель
	char name[100];         // Название цели
	float target_amount;    // Целевая сумма
	float current_amount;   // Текущая сумма
	time_t deadline;        // Срок выполнения цели
	char description[500];  // Описание цели
} Goal;

typedef struct {
	int id;                 // Уникальный идентификатор заметки
	char title[100];        // Заголовок заметки
	char content[500];      // Содержание заметки
	time_t created_at;      // Временная метка создания заметки
	time_t updated_at;      // Временная метка последнего обновления заметки
	int category;           // Категория заметки (например, 1 - покупки, 2 - вклады, 3 - финансовые идеи, и т.д.)
} Note;

typedef struct {
	int id;                 // Уникальный идентификатор операции
	int type;               // Тип операции (например, 1 - транзакция, 2 - создание цели, 3 - выполнение цели, и т.д.)
	char name[100];         // Название операции
	time_t date;            // Дата операции
} Logs;

//
// Функции
//

// Функция для создания пользователя
User create_user(int id, const char* name, const char* email, const char* password, double balance, int is_admin) {
	User user;
	user.id = id;
	strcpy(user.name, name);
	strcpy(user.email, email);
	strcpy(user.password, password);
	user.is_admin = is_admin;
	Account main_account = create_account(user.id, "Основной счет", 0.0, "РУБ");
	return user;
}

// Функция для создания нового счета пользователя
Account create_account(int user_id, const char* name, double balance, const char* currency) {
	Account account;
	account.id = user_id + 100000;
	account.user_id = user_id;
	strcpy(account.name, name);
	account.balance = balance;
	strcpy(account.currency, currency);
	return account;
}

// Функция для вывода информации о пользователе
void print_user(User user) {
	printf("Пользователь #%d:\n", user.id);
	printf("Имя: %s\n", user.name);
	printf("Email: %s\n", user.email);
	printf("Статус: %s\n", user.is_admin ? "Администратор" : "Юзер");
}

// Функция для отображения счета по его идентификатору (в дальнейшем данные будут считываться из базы данных)
void print_account(Account* accounts, int account_count, int account_id) {
	for (int i = 0; i < account_count; i++) {
		if (accounts[i].id == account_id) {
			printf("Название счета: %s\n", accounts[i].name);
			printf("Баланс: %.2f %s\n", accounts[i].balance, accounts[i].currency);
			return;
		}
	}
	printf("Аккаунт с айди %d, не найден.\n", account_id);
}

// Функция для выполнения транзакции
Transaction create_transcation(Account* accounts, int account_id, int account_count, int type, const char* name, double amount) {
	for (int i = 0; i < account_count; i++) {
		if (accounts[i].id == account_id) {
			if (type == 0) {
				// Зачисление на счет
				accounts[i].balance += amount;
				printf("Операция '%s' успешна: +%.2f %s\n", name, amount, accounts[i].currency);
			}
			else if (type == 1) {
				// Снятие со счета
				if (accounts[i].balance >= amount) {
					accounts[i].balance -= amount;
					printf("Операция '%s' успешна: -%.2f %s\n", name, amount, accounts[i].currency);
				}
				else {
					printf("Операция '%s' отменена: Недостаточно средств\n", name);
				}
			}
			else {
				printf("Ошибка.\n");
			}
			return;
		}
		else {
			printf("Ошибка. Такого счета нет.");
		}
	}
}

// Функция для создания новой заметки (в будущем дата и время будут сохранятся при нажатии на кнопку сохранения)
// Записки будут хранится локально на устройстве пользователя
Note create_note(int id, const char* title, const char* content, int category) {
	Note note;
	note.id = id;
	strcpy(note.title, title);
	strcpy(note.content, content);
	note.category = category;
	return note;
}



	//
	// Демонстрация работы
	//

	int main()
	{
		setlocale(LC_ALL, "Rus");

	}