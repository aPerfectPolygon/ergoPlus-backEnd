#include "EventHandler.h"

String EventHandler::add(int event) {
    if (current_event >= max_events)
        flush();

    event_times[current_event] = int(millis() / 1000);
    event_logs[current_event] = event;
    String output =
            "[" + String(startup_time + event_times[current_event]) + ",\"" + events[event_logs[current_event]] + "\"]";
    current_event++;

    return output;
}

String EventHandler::read() {
    String output = "";
    for (int i = 0; i < current_event; i++) {
        if (output != "")
            output += ",";
        output += ("[" + String(startup_time + event_times[i]) + ",\"" + events[event_logs[i]] + "\"]");
    }
    return "[" + output + "]";
}

void EventHandler::flush() {
    for (int i = 0; i < current_event; i++) {
        event_times[i] = 0;
        event_logs[i] = *"";
    }
    current_event = 0;
}

void EventHandler::set_startup_time(unsigned long t) {
    startup_time = t;
}