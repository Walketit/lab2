#define _CRT_SECURE_NO_WARNINGS
#include "Logs.h"
#include <fstream>
#include <cstdio>
#include <cstring>

void Logs::logfile_create(int id) {
    name = "logs" + to_string(id);
    ofstream file(name + ".txt");
    if (!file.is_open()) {
        printf("Ошибка создания файла!");
        exit(1);
    }
    file.close();
}

void Logs::logfile_update(int id, string name) {
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

void Logs::read_logs(int id) {
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

Time Logs::get_time() {
    return time;
}