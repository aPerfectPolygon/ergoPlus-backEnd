#ifndef ESPTEST_TIMEDDIGITALOUTPUT_H
#define ESPTEST_TIMEDDIGITALOUTPUT_H

#include "utils.h"

class TimedDigitalOutput {
private:
    int return_after;
    unsigned long int changed_at = 0;
    int pin;
    bool stable_state;
public:
    explicit TimedDigitalOutput(int _pin, bool _state, int _return_after);

    void change_stable_state(bool state);

    void change();

    void handle();
};

#endif //ESPTEST_TIMEDDIGITALOUTPUT_H
