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
    double balance;         // Текущий баланс пользователя
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
    float rate;             // Курс валюты по отношению к базовой валюте
    char base_currency[4];  // Код базовой валюты 
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



//
// Демонстрация работы
//

int main()
{
    setlocale(LC_ALL, "Rus");
    
}