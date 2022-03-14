#include "utils.h"
#include "TcpServer.h"
#include "TcpClient.h"
#include "WifiHandler.h"
#include "EventHandler.h"
#include "DebounceHandler.h"
#include "TimedDigitalOutput.h"
#include "BatteryVoltageMonitoring.h"

#define interruptPin 4
#define vibratorPin 5
#define is_master true

TcpServer tcp_server(8888);
TcpClient tcp_client(IPAddress(192, 168, 1, 35), 8888);
WifiHandler wifi_handler(is_master);
EventHandler event_handler;
DebounceHandler debounce_handler;
TimedDigitalOutput vibrator(vibratorPin, false, 500);
BatteryVoltageMonitoring battery_voltage;
int slave_battery_voltage = 0;

void trigger_event(int event, bool vibrate = true) {
    if (vibrate) {
        vibrator.change();
    }
    if (is_master)
        tcp_server.broadcast_json("event", event_handler.add(event));
    else
        tcp_client.send("event" + String(event));
}

void TcpServer::message_handler(int index, const String &message) {
    if (message.startsWith("time")) {  // time1645801386000
        event_handler.set_startup_time(message.substring(4).toInt() - int(millis() / 1000));
    } else if (message.startsWith("voltage")) {  // voltage70
        slave_battery_voltage = int(message.substring(7).toInt());
    } else if (message == "readAndFlush") {
        tcp_server._send_json(clients[index], "logs", event_handler.read());
        event_handler.flush();
    } else if (message == "read") {
        tcp_server._send_json(clients[index], "logs", event_handler.read());
    } else if (message == "flush") {
        event_handler.flush();
    } else if (message == "readVoltage") {
        tcp_server._send_json(
                clients[index],
                "voltage", "[" + String(battery_voltage.value) + ", " + String(slave_battery_voltage) + "]"
        );
    } else if (message.startsWith("event")) {  // event0
        trigger_event(int(message.substring(5).toInt()), false);
    }
}

void TcpClient::message_handler(const String &message) {
}

void DebounceHandler::callback(int pin, bool state, bool fake) {
    if (fake or pin != interruptPin)
        return;

    if (!state) {
        if (is_master)
            trigger_event(0);
        else
            trigger_event(1);
    }
}

IRAM_ATTR void input_changed() {
    debounce_handler.add(interruptPin, false);
}

void setup() {
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), input_changed, FALLING);
    Serial.begin(115200);
    Serial.println();
    wifi_handler.connect();
    pinMode(A0, INPUT);
}

void loop() {
    wifi_handler.check(tcp_server.server, tcp_client.client);
    debounce_handler.handle();
    vibrator.handle();
    if (battery_voltage.check() && !is_master)
        tcp_client.send("voltage" + String(battery_voltage.value));

    if (is_master)
        tcp_server.handler();
    else
        tcp_client.handler();
}
