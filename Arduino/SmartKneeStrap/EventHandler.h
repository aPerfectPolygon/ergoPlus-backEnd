#ifndef ESPTEST_EVENTHANDLER_H
#define ESPTEST_EVENTHANDLER_H

#include "utils.h"
#include "TcpSocket.h"

class EventHandler {
    /*
     * call `add()` to add events to class queue and call `read()` to retrieve them
     *      adding events to queue requires event id (index of `events`)
     *      each event can have separate timeout
     *          if the same event is triggered between last trigger and `event_timeout` ms after that will be ignored
     *
     * maximum events that can be stored is determined by `max_events`
     *      if it overflows it will automatically flush the queue
     *
     * call `flush()` to flush the queue
     * call `set_startup_time()` to set startup time of the module
     *      this time will be used when reading the queue
     *
     */
private:
    static const int events_count = 2;
    const String events[events_count] = {"0", "1"};  // lor, rol
    const int events_timeout[events_count] = {1000, 1000};

    static const int max_events = 500;
    int current_event = 0;
    unsigned long event_times[max_events];
    int event_logs[max_events];
    unsigned long events_last_triggerred[events_count] = {0, 0};
    unsigned long startup_time = 0;
public:
    String add(int event, bool force = false);
    String read();
    void flush();
    void set_startup_time(unsigned long t);
};

#endif //ESPTEST_EVENTHANDLER_H
