#ifndef ESPTEST_DEBOUNCEHANDLER_H
#define ESPTEST_DEBOUNCEHANDLER_H
#include "utils.h"

class DebounceHandler{
private:
    static const int debounce = 50;
    static const int max_concurrent = 100;
    int _curr_pos = 0;
    int pins[max_concurrent]{};
    unsigned long int times[max_concurrent]{};
    bool states[max_concurrent]{};
public:
    explicit DebounceHandler();

    void add(int pin, bool state);

    static void callback(int pin, bool state, bool fake);

    void handle();
};

#endif //ESPTEST_DEBOUNCEHANDLER_H
