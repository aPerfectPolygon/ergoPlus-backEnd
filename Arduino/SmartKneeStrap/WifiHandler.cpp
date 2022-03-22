#include "WifiHandler.h"

WifiHandler::WifiHandler(bool _is_master) {
    is_master = _is_master;
}

int WifiHandler::scan() {
    int networks = WiFi.scanNetworks();
    for (int j = 0; j < wifi_count; j++) {
        if (!is_master && j>0)
            break;
        for (int i = 0; i < networks; i++) {
            if (WiFi.SSID(i) == SSIDs[j]) {
                return j;
            }
        }
    }
    return -1;
}

void WifiHandler::connect() {
    if (WiFi.status() != WL_CONNECTED) {
        if (is_master) {
            WiFi.softAPConfig(
                    IPAddress(192,168,4,1),
                    IPAddress(192,168,4,1),
                    IPAddress(255, 255, 255, 0)
            );
            WiFi.mode(WIFI_AP_STA);
            WiFi.softAP(SSIDs[0], Passwords[0]);
        } else {
            WiFi.mode(WIFI_STA);
        }

        int wifi_number = scan();
        if (wifi_number >= 0) {
            WiFi.config(
                    ips[wifi_number][0],
                    ips[wifi_number][1],
                    IPAddress(255, 255, 255, 0)
            );
            WiFi.begin(SSIDs[wifi_number], Passwords[wifi_number]);
            print("Connecting to " + SSIDs[wifi_number] + " ...");
            for (int i = 0; i < 100; i++)
                if (WiFi.status() == WL_CONNECTED)
                    break;
                else
                    delay(100);
            if (WiFi.status() == WL_CONNECTED)
                print("Connected to " + SSIDs[wifi_number]);
            else
                print("could not connect to " + SSIDs[wifi_number]);
        } else {
            print("no WIFI found");
        }
    } else {
        print("already connected");
    }
}

void WifiHandler::check(WiFiServer server, WiFiClient client) {
    if (!check_time.check(int(millis() / 30000),false))
        return;

    if (WiFi.status() != WL_CONNECTED) {
        connect();
        if (WiFi.status() == WL_CONNECTED) {
            if (is_master)
                server.stop();
            else
                client.stop();
        }

    }
}
