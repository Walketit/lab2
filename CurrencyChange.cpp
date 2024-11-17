#define _CRT_SECURE_NO_WARNINGS
#include "CurrencyChange.h"

CurrencyChange::CurrencyChange(string request) {
    set_сurrency_сhange(request);
}

void CurrencyChange::set_сurrency_сhange(string request) {
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

void CurrencyChange::change(float amount) {
    cout << "Обмен " << name << endl;
    cout << fixed << setprecision(3) << amount << " = " << amount * rate << endl;
    return;
}