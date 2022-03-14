#include "EventHandler.h"

String EventHandler::add(int event, bool force) {
    /*
     * add event to queue and return a JSON string of the event
     * `force` will bypass time checking of event
     */
    if (current_event >= max_events)
        // flush if overflow
        flush();

    unsigned long now = millis();
    if (not force and (now - events_last_triggerred[event]) < events_timeout[event])
        return "";

    // add event to queue
    event_times[current_event] = int(now / 1000);
    events_last_triggerred[event] = now;
    event_logs[current_event] = event;
    current_event++;

    // return last event as String
    return "[" +
           String(startup_time + event_times[current_event-1]) + ",\"" + events[event_logs[current_event-1]] +
           "\"]";
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