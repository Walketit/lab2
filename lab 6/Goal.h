#ifndef GOAL_H
#define GOAL_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Goal {
private:
    string name;         // Название цели
    string description;  // Описание цели
    float target_amount;    // Целевая сумма
    float current_amount;   // Текущая сумма
public:
    Goal() : name(""), description(""), target_amount(0), current_amount(0) {}
    Goal(string name, float target_amount, float current_ammount, string content);
    void print_goal();
    void addToBalance(double amount);
    bool isAchieved() const;
    string getTitle() const;
    string getDescription() const;
    double getCurrentBalance() const;
    double getTargetAmount() const;
    void setTitle(const string& title);
    void setDescription(const string& description);
    void setCurrentBalance(double currentBalance);
    void setTargetAmount(double targetAmount);
};

#endif // GOAL_H