#include "BatteryVoltageMonitoring.h"

BatteryVoltageMonitoring::BatteryVoltageMonitoring(){
    pinMode(A0, INPUT);
}

bool BatteryVoltageMonitoring::check(){
    if (value >= 0){
        int now = int(millis() / 1000);
        if (now - last_check < check_interval)
            return false;
        last_check = now;
    }
    value = map(analogRead(A0), 0, 1024, 0, 100);
    return true;
}
