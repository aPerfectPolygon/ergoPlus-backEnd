#include "DebounceHandler.h"

DebounceHandler::DebounceHandler() {
    for (int & pin : pins)
        // fill pins with neutral values
        pin = -1;
}

void DebounceHandler::add(int pin, int state, bool pin_is_analog) {
    if (_curr_pos >= max_concurrent)
        // queue is full
        return;

    pins[_curr_pos] = pin;
    states[_curr_pos] = state;
    is_analog[_curr_pos] = pin_is_analog;
    times[_curr_pos] = millis();
    _curr_pos += 1;
}

void DebounceHandler::handle() {
    if (_curr_pos == 0)
        // nothing to check
        return;
    unsigned long now = millis();

    for (int i=0; i<_curr_pos; i++){
        if (pins[i] < 0)
            // is neutral (next values may not be neutral)
            continue;

        if (now - times[i] >= debounce){
            // time to check the pin
            if (is_analog[i])
                callback(pins[i], states[i], analogRead(pins[i]) < states[i]);
            else
                callback(pins[i], states[i], digitalRead(pins[i]) != states[i]);

            // empty the queue
            pins[i] = -1;
            times[i] = 0;
            states[i] = 0;
            is_analog[_curr_pos] = false;
        }
    }

    // go backwards and update _curr_pos
    for (int i=_curr_pos-1; i>=0; i--){
        if (pins[i] == -1)
            // is neutral (next values may be neutral)
            _curr_pos = i;
        else
            // not neutral (next values are definitely not neutral)
            break;
    }
}

//void DebounceHandler::callback(int pin, bool state, bool fake) {
//    if (fake)
//        return;
//    print("OK");
//}