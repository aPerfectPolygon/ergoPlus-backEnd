#ifndef SMARTKNEESTRAP_ANALOGTHRESHOLDDETECTOR_H
#define SMARTKNEESTRAP_ANALOGTHRESHOLDDETECTOR_H

#include "utils.h"

class AnalogThresholdDetector{
    /*
     * call `callback` when `pin` crosses `thresh` value upwards
     *
     * check `pin` status every `check_time.check_interval` ms
     *      if `check()` is called repeatedly it will bypass until `check_time.check_interval` ms has passed
     */
private:
    int curr_state = 0;
    CheckTime check_time = CheckTime(0, 100);
public:
    int thresh;
    int pin;

    explicit AnalogThresholdDetector(int _pin, int _thresh);

    void callback();

    void check();
};

#endif //SMARTKNEESTRAP_ANALOGTHRESHOLDDETECTOR_H
