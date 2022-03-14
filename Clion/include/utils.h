#ifndef ESPTEST_UTILS_H
#define ESPTEST_UTILS_H

#include <ESP8266WiFi.h>

#define DEBUG true

void print(const String &s);

class CheckTime {
private:
    unsigned long last_check;
    int check_interval;
public:
    explicit CheckTime(unsigned long _last_check, int _check_interval);

    bool check(unsigned long now = 0);
};

#endif //ESPTEST_UTILS_H
