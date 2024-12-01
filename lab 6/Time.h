#ifndef TIME_H
#define TIME_H

class Time {
private:
    char hour[3];         // Переменная для часа
    char min[3];          // Переменная для минуты
    char sec[3];          // Переменная для секунды
    char day[3];          // Переменная для дня
    char month[3];        // Переменная для месяца
    char year[5];         // Переменная для года
    char full_date[22];   // Переменная для полной даты
public:
    void current_time();
    void print_current_time();
    const char* get_full_date();
    void parse_date(const char* date_str, Time* time);
};

#endif // TIME_H