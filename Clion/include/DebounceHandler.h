#ifndef ESPTEST_DEBOUNCEHANDLER_H
#define ESPTEST_DEBOUNCEHANDLER_H
#include "utils.h"

class DebounceHandler{
    /*
     * when an event occurs (for example a button press or an analog value crossing a threshold)
     * call `add()` to track these events
     * the class then calls `callback()` after `debounce` ms indicating if the `state` you
     * previously added was fake(debounce) or it was ok(the state really changed)
     * call `handle()` periodically to keep track of these events
     *
     * ** -1 is neutral value for pins **
     */
private:
    static const int debounce = 50;
    static const int max_concurrent = 100;
    int _curr_pos = 0;
    int pins[max_concurrent]{};
    unsigned long int times[max_concurrent]{};
    int states[max_concurrent]{};
    bool is_analog[max_concurrent]{};
public:
    explicit DebounceHandler();

    void add(int pin, int state, bool pin_is_analog=false);

    static void callback(int pin, int state, bool fake);

    void handle();
};

#endif //ESPTEST_DEBOUNCEHANDLER_H
