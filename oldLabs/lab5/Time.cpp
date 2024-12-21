#define _CRT_SECURE_NO_WARNINGS
#include "Time.h"
#include <ctime>
#include <cstdio>
#include <cstring>

void Time::current_time() {
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

void Time::print_current_time() {
    current_time();
    printf("Сегодня: %s-%s-%s\n", day, month, year);
    printf("Время: %s:%s:%s\n\n", hour, min, sec);
}

const char* Time::get_full_date() {
    current_time();
    return full_date;
}

void Time::parse_date(const char* date_str, Time* time) {
    sscanf(date_str, "%4s-%2s-%2s %2s:%2s:%2s",
        time->year, time->month, time->day,
        time->hour, time->min, time->sec);
    strcpy(time->full_date, date_str);
}
