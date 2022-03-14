#include "TimedDigitalOutput.h"

TimedDigitalOutput::TimedDigitalOutput(int _pin, bool _state, int _return_after) {
    pin = _pin;
    stable_state = _state;
    return_after = _return_after;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, stable_state);
}

void TimedDigitalOutput::change_stable_state(bool state) {
    stable_state = state;
    digitalWrite(pin, stable_state);
}

void TimedDigitalOutput::change() {
    digitalWrite(pin, !stable_state);
    changed_at = millis();
}

void TimedDigitalOutput::handle() {
    if (changed_at == 0)
        return;

    if (millis() - changed_at > return_after) {
        digitalWrite(pin, stable_state);
        changed_at=0;
    }
}
