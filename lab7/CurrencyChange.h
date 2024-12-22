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
    string code;           // Код обмена (например, "USDRUB")
    string name;          // Полное название обмена (например, "доллар к рублю")
    float rate;             // Курс валюты по отношению к базовой валют
public:
    CurrencyChange() : code(""), name(""), rate(0) {};
    CurrencyChange(string request);
    void set_сurrency_сhange(string request);
    void change(float amount);
};

#endif // CURRENCYCHANGE_H