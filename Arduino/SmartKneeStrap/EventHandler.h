#ifndef ESPTEST_EVENTHANDLER_H
#define ESPTEST_EVENTHANDLER_H

#include "utils.h"
#include "TcpSocket.h"

class EventHandler {
private:
    static const int max_events = 500;
    int current_event = 0;
    unsigned long event_times[max_events];
    int event_logs[max_events];
    const String events[2] = {"lor", "rol"};
    unsigned long startup_time = 0;
public:
    String add(int event);
    String read();
    void flush();
    void set_startup_time(unsigned long t);
};

#endif //ESPTEST_EVENTHANDLER_H
