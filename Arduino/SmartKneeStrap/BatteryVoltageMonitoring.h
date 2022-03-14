#ifndef ESPTEST_BATTERYVOLTAGEMONITORING_H
#define ESPTEST_BATTERYVOLTAGEMONITORING_H

#include "utils.h"

class BatteryVoltageMonitoring{
private:
    unsigned long last_check = 0;
    const int check_interval = 60; // seconds
public:
    int value = -1;
    explicit BatteryVoltageMonitoring();

    bool check();
};

#endif //ESPTEST_BATTERYVOLTAGEMONITORING_H
