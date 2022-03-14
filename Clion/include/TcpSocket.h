#ifndef ESPTEST_TCPSOCKET_H
#define ESPTEST_TCPSOCKET_H

#include <ESP8266WiFi.h>
#include "utils.h"

class TcpSocket {
    /*
     * Base class for TcpSockets
     * sending and receiving on TcpSockets are terminated by `terminator`
     * this class has all the low level functions to work with TcpSockets
     */
private:
    const char terminator = '\n';
public:
    static void _log(WiFiClient client, const String &s, const String &tag);

    void _send(WiFiClient client, const String &s);

    void _send_json(const WiFiClient &client, const String &type, String data);

    String _receive(WiFiClient client);
};


#endif //ESPTEST_TCPSOCKET_H
