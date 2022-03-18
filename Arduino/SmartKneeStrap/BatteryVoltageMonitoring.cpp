#include "BatteryVoltageMonitoring.h"

BatteryVoltageMonitoring::BatteryVoltageMonitoring(int _min, int _max){
    max = _max;
    min = _min;
    pinMode(A0, INPUT);
}

bool BatteryVoltageMonitoring::check(){
    if (value == 0 or check_time.check(int(millis() / 1000))) {
        value = map(analogRead(A0), min, max, 0, 100);
        return true;
    }
    return false;
}
