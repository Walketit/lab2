#define _CRT_SECURE_NO_WARNINGS
#include "Goal.h"

Goal::Goal(string name, float target_amount, float current_ammount, string content) {
    this->name = name;
    this->current_amount = current_ammount;
    this->target_amount = target_amount;
    this->description = content;
}

void Goal::print_goal() {
    cout << "Цель: " << name << endl;
    cout << fixed << setprecision(0) << current_amount << "/" << target_amount << endl;
    cout << "Описание: " << description << endl;
}

void Goal::addToBalance(double amount) {
    current_amount += amount;
}

bool Goal::isAchieved() const {
    return current_amount >= target_amount;
}

string Goal::getTitle() const { return name; }
string Goal::getDescription() const { return description; }
double Goal::getCurrentBalance() const { return current_amount; }
double Goal::getTargetAmount() const { return target_amount; }

void Goal::setTitle(const string& title) { this->name = name; }
void Goal::setDescription(const string& description) { this->description = description; }
void Goal::setCurrentBalance(double currentBalance) { this->current_amount = current_amount; }
void Goal::setTargetAmount(double targetAmount) { this->target_amount = target_amount; }