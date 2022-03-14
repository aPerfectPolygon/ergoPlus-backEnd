#ifndef ESPTEST_TIMEDDIGITALOUTPUT_H
#define ESPTEST_TIMEDDIGITALOUTPUT_H

#include "utils.h"

class TimedDigitalOutput {
    /*
     * change a DigitalOutput state and go back to last state after `return_after`ms
     *
     * call `handle()` periodically to handle pin times
     * call `change_stable_state()` to change pin default state
     * call `change()` to temporarily revert pin state
     */
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
