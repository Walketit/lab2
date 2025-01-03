#ifndef CURRENCYCHANGE_H
#define CURRENCYCHANGE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

class CurrencyChange {
private:
    string code;           // ��� ������ (��������, "USDRUB")
    string name;          // ������ �������� ������ (��������, "������ � �����")
    float rate;             // ���� ������ �� ��������� � ������� �����
public:
    CurrencyChange() : code(""), name(""), rate(0) {};
    CurrencyChange(string request);
    void set_�urrency_�hange(string request);
    void change(float amount);
};

#endif // CURRENCYCHANGE_H