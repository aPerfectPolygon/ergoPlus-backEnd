#ifndef ESPTEST_TCPCLIENT_H
#define ESPTEST_TCPCLIENT_H

#include "TcpSocket.h"

class TcpClient : public TcpSocket {
private:
    IPAddress ip;
    int port;
    unsigned long last_check = 0;
    const int check_interval = 1; // seconds
public:
    WiFiClient client;

    explicit TcpClient(IPAddress _ip, int _port);

    bool is_connected();

    void send(const String &s);

    void send_json(const String &type, const String &data);

    String receive();

    void log(const String &s, const String &tag);

    void message_handler(const String &message);

    void handler();
};


#endif //ESPTEST_TCPCLIENT_H
