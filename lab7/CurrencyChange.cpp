#define _CRT_SECURE_NO_WARNINGS
#include "CurrencyChange.h"

CurrencyChange::CurrencyChange(string request) {
    set_�urrency_�hange(request);
}

void CurrencyChange::set_�urrency_�hange(string request) {
    ifstream file("CurrencyRate.txt");
    if (!file.is_open()) {
        printf("������ �������� ����� CurrencyRate.txt");
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        // �������� ������ ����� (���)
        if (getline(ss, token, ',')) {
            if (request == token) {
                code = token;

                // �������� ������ ����� (������)
                if (getline(ss, token, ',')) {
                    rate = stod(token);
                }

                // �������� ������ ����� (���)
                if (getline(ss, token, '\n')) {
                    name = token;
                }

                file.close();
                return;
            }
        }
        printf("��������� �������� ���� �� ������.");
        exit(1);
    }
}

void CurrencyChange::change(float amount) {
    cout << "����� " << name << endl;
    cout << fixed << setprecision(3) << amount << " = " << amount * rate << endl;
    return;
}