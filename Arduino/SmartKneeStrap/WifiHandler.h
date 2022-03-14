#ifndef ESPTEST_WIFIHANDLER_H
#define ESPTEST_WIFIHANDLER_H

#include <ESP8266WiFi.h>
#include "utils.h"

class WifiHandler {
private:
    static const int wifi_count = 3;
    const String SSIDs[wifi_count] = {"esp", "__.enz", "Amghezy"};
    const String Passwords[wifi_count] = {"thisIsEsp", "elyasnz12", "ABC987def123"};
    const IPAddress ips[wifi_count][2] = {
            {IPAddress(192, 168, 4, 35),  IPAddress(192, 168, 4, 1)},
            {IPAddress(192, 168, 43, 35), IPAddress(192, 168, 43, 1)},
            {IPAddress(192, 168, 1, 35),  IPAddress(192, 168, 1, 1)}
    };
    unsigned long last_check = 0;
    const int check_interval = 1; // seconds
    bool is_master;
public:
    explicit WifiHandler(bool _is_master);

    int scan();

    void connect();

    void check(WiFiServer server, WiFiClient client);
};

#endif //ESPTEST_WIFIHANDLER_H
