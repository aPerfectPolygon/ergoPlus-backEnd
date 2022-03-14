#include "utils.h"
#include "TcpServer.h"
#include "TcpClient.h"
#include "WifiHandler.h"
#include "EventHandler.h"
#include "DebounceHandler.h"
#include "TimedDigitalOutput.h"
#include "BatteryVoltageMonitoring.h"
#include "AnalogThresholdDetector.h"

#define sensorPin 17
#define vibratorPin 14
#define readVoltagePin 5
#define readSensorPin 4
#define is_master true

TcpServer tcp_server(8888);
TcpClient tcp_client(IPAddress(192, 168, 1, 35), 8888);
WifiHandler wifi_handler(is_master);
EventHandler event_handler;
DebounceHandler debounce_handler;
TimedDigitalOutput vibrator(vibratorPin, false, 500);
BatteryVoltageMonitoring battery_voltage(700, 960);
AnalogThresholdDetector sensor(sensorPin, 750);  // max thresh : 1024
int slave_battery_voltage = 0;

bool trigger_event(int event) {
    /*
     * trigger events based on module master/slave
     * Inputs:
     *      event: [0, 1]
     *          event to trigger
     *          it will be sent to event handler and the numbers are index of events there
     */
    if (is_master) {
        // add the event and broadcast the response to all listeners
        String result = event_handler.add(event);
        if (result != "") {
            tcp_server.broadcast_json("event", result);
            return true;
        }
        return false;
    } else {
        // send the triggered event to server and let it handle the rest
        tcp_client.send("event" + String(event));
        return true;
    }

}

void TcpServer::message_handler(int index, const String &message) {
    /*
     * [MASTER]
     * handle received messages from clients
     * Inputs:
     *      index:
     *          id of the client which is sending the message
     *          this id points to `TcpServer.clients`
     *      message:
     *          the actual message received from client
     *          NOTE: messages are terminated with TcpSocket.terminator
     *          messages:
     *              time{timestamp(s)}: to update module time
     *              voltage{percent}: [ONLY SENT BY SLAVE] set slave module battery percent
     *              event{eventId}: [ONLY SENT BY SLAVE] an event is triggered from slave side
     *              read: read events
     *              flush: flush events
     *              readAndFlush: read and flush events
     *              readVoltage: read module voltages
     */
    if (message.startsWith("time")) {
        // time1645801386000
        // get timestamp from message and calculate startup timestamp of startup and set it on event_handler
        event_handler.set_startup_time(message.substring(4).toInt() - int(millis() / 1000));
    } else if (message.startsWith("voltage")) {
        // voltage70
        // slave sets its battery percent
        // later it will be polled by Application
        slave_battery_voltage = int(message.substring(7).toInt());
    } else if (message == "read") {
        tcp_server._send_json(clients[index], "logs", event_handler.read());
    } else if (message == "flush") {
        event_handler.flush();
    } else if (message == "readAndFlush") {
        tcp_server._send_json(clients[index], "logs", event_handler.read());
        event_handler.flush();
    } else if (message == "readVoltage") {
        tcp_server._send_json(
                clients[index],
                "voltage",
                "[" + String(battery_voltage.value) + ", " + String(slave_battery_voltage) + "]"
        );
    } else if (message.startsWith("event")) {
        // event0
        // when event is triggered from slave there is no need for the master to vibrate
        if (trigger_event(int(message.substring(5).toInt()))){
            tcp_server._send(clients[index], "vibrate");
        }
    }
}

void TcpClient::message_handler(const String &message) {
    /*
     * [MASTER]
     * handle received messages from server
     */
    if (message == "vibrate"){
        vibrator.change();
    }
}

void AnalogThresholdDetector::callback() {
    /*
     * this function is called by `AnalogThresholdDetector` every time sensor crosses pre-defined threshold
     */
    debounce_handler.add(sensor.pin, sensor.thresh, true);
}

void DebounceHandler::callback(int pin, int state, bool fake) {
    /*
     * when debounce time of a pre-added event is reached `DebounceHandler` will call this function
     * and tells us if the event was `fake` (the event was just the multiple switches of the sensor or ...)
     * Inputs:
     *      pin: pin number of which the event happened on
     *      state: the state which was event happened in
     *      fake: whether this event was fake or not
     */
    if (fake or pin != sensorPin or state < sensor.thresh)
        return;

    if (is_master) {
        if (trigger_event(0))
            vibrator.change();
    }
    else
        trigger_event(1);
}

void setup() {
    Serial.begin(115200);
    Serial.println("STARTING ....");

    pinMode(readVoltagePin, OUTPUT);
    digitalWrite(readVoltagePin, LOW);
    pinMode(readSensorPin, OUTPUT);
    digitalWrite(readSensorPin, LOW);
    pinMode(sensorPin, INPUT);  // battery and sensor
}

void loop() {
    // call all the related handlers
    wifi_handler.check(tcp_server.server, tcp_client.client);
    debounce_handler.handle();
    vibrator.handle();

    digitalWrite(readVoltagePin, LOW);
    digitalWrite(readSensorPin, HIGH);
    sensor.check();

    digitalWrite(readSensorPin, LOW);
    digitalWrite(readVoltagePin, HIGH);
    if (battery_voltage.check() && !is_master)
        tcp_client.send("voltage" + String(battery_voltage.value));

    if (is_master)
        tcp_server.handler();
    else
        tcp_client.handler();
}