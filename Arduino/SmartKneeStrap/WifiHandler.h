#ifndef ESPTEST_WIFIHANDLER_H
#define ESPTEST_WIFIHANDLER_H

#include "utils.h"

class WifiHandler {
    /*
     * handle wifi connections of module
     * first ssid-password will be used as module ssid-password
     * when adding a wifi network you must also add a static ip in `ips`
     *
     * call `check()` periodically to handle Wifi status
     */
private:
    static const int wifi_count = 5;
    const String SSIDs[wifi_count] = {"esp", "__.enz", "Amghezy", "Irancell-TD-B5142-0768_1"};
    const String Passwords[wifi_count] = {"thisIsEsp", "elyasnz12", "ABC987def123", "nt7eujv3"};
    const IPAddress ips[wifi_count][2] = {
            {IPAddress(192, 168, 4, 35),  IPAddress(192, 168, 4, 1)},
            {IPAddress(192, 168, 43, 35), IPAddress(192, 168, 43, 1)},
            {IPAddress(192, 168, 1, 35),  IPAddress(192, 168, 1, 1)},
            {IPAddress(192, 168, 1, 35),  IPAddress(192, 168, 1, 1)},
            {IPAddress(192, 168, 214, 35),  IPAddress(192, 168, 214, 1)}
    };
    CheckTime check_time = CheckTime(0, 1);
    bool is_master;
public:
    explicit WifiHandler(bool _is_master);

    int scan();

    void connect();

    void check(WiFiServer server, WiFiClient client);
};

#endif //ESPTEST_WIFIHANDLER_H
