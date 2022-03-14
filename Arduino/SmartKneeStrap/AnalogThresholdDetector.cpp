#include "AnalogThresholdDetector.h"

AnalogThresholdDetector::AnalogThresholdDetector(int _pin, int _thresh) {
    pin = _pin;
    thresh = _thresh;
}

void AnalogThresholdDetector::check() {
    if (!check_time.check())
        return;

    int new_state = analogRead(pin);
    if (curr_state < thresh && new_state >= thresh)
        // threshold crossed upwards
        callback();
    curr_state = new_state;
}