#ifndef TIME_H
#define TIME_H

class Time {
private:
    char hour[3];         // ���������� ��� ����
    char min[3];          // ���������� ��� ������
    char sec[3];          // ���������� ��� �������
    char day[3];          // ���������� ��� ���
    char month[3];        // ���������� ��� ������
    char year[5];         // ���������� ��� ����
    char full_date[22];   // ���������� ��� ������ ����
public:
    void current_time();
    void print_current_time();
    const char* get_full_date();
    void parse_date(const char* date_str, Time* time);
};

#endif // TIME_H