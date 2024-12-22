#ifndef LOGS_H
#define LOGS_H

#include <string>
#include "Time.h"

using namespace std;

class Logs {
private:
    string name;         // Название операции
    Time time;            // Дата операции
public:
    Logs() : name(""), time() {};
    void logfile_create(int id);
    void logfile_update(int id, string name);
    void read_logs(int id);
    Time get_time();
};

#endif // LOGS_H