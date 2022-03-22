#include "utils.h"

void print(const String &s) {
    if (DEBUG) Serial.println(s);
}

CheckTime::CheckTime(unsigned long _last_check, int _check_interval) {
    last_check = _last_check;
    check_interval = _check_interval;
}

bool CheckTime::check(unsigned long now, bool auto_now) {
    if (first_time){
        first_time = false;
        last_check = now;
        return true;
    }
    if (auto_now)
        now = millis();
    if (now - last_check < check_interval)
        return false;
    last_check = now;
    return true;
}