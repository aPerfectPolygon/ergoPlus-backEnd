#ifndef ESPTEST_BATTERYVOLTAGEMONITORING_H
#define ESPTEST_BATTERYVOLTAGEMONITORING_H

#include "utils.h"

class BatteryVoltageMonitoring{
    /*
     * read batter voltage from `A0` pin and store it in `value`(percent)
     * battery voltage percentage is calculated by mapping battery voltage value
     * which is in scale of `min` to `max` to a scale of 0 to 100
     */
private:
    int max;
    int min;
    CheckTime check_time = CheckTime(0, 60);
public:
    int value = -1;
    explicit BatteryVoltageMonitoring(int _min, int _max);

    bool check();
};

#endif //ESPTEST_BATTERYVOLTAGEMONITORING_H
