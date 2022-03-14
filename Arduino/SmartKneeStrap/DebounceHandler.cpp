#include "DebounceHandler.h"

DebounceHandler::DebounceHandler() {
    for (int & pin : pins)
        pin = -1;
}

void DebounceHandler::add(int pin, bool state) {
    if (_curr_pos >= max_concurrent)
        return;

    pins[_curr_pos] = pin;
    states[_curr_pos] = state;
    times[_curr_pos] = millis();
    _curr_pos += 1;
}

void DebounceHandler::handle() {
    if (_curr_pos == 0)
        return;

    unsigned long now = millis();

    for (int i=0; i<_curr_pos; i++){
        if (pins[i] < 0)
            continue;

        if (now - times[i] >= debounce){
            if ((digitalRead(pins[i]) == 1) == states[i])
                callback(pins[i], states[i], false);
            else
                callback(pins[i], states[i], true);

            pins[i] = -1;
            times[i] = 0;
            states[i] = false;
        }
    }

    // go backwards and update _curr_pos
    for (int i=_curr_pos-1; i>=0; i--){
        if (pins[i] == -1)
            _curr_pos = i;
        else
            break;
    }

}

//void DebounceHandler::callback(int pin, bool state, bool fake) {
//    if (fake)
//        return;
//    print("OK");
//}