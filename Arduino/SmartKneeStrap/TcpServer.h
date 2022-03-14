#ifndef ESPTEST_TCPSERVER_H
#define ESPTEST_TCPSERVER_H

#include "TcpSocket.h"

class TcpServer : public TcpSocket {
private:
    static const int max_clients = 3;
    bool clients_initialization[max_clients] = {false, false, false};
    WiFiClient clients[max_clients] = {WiFiClient(), WiFiClient(), WiFiClient()};
public:
    WiFiServer server = WiFiServer(0);

    explicit TcpServer(int port);

    void broadcast(const String &s);

    void broadcast_json(const String &type, const String &data);

    void send(int index, const String &s);

    void send_json(int index, const String &type, const String &data);

    String receive(int index);

    void message_handler(int index, const String &message);

    void log(int index, const String &s, const String &tag);

    void scan_and_add();

    void remove(int index);

    void handler();
};


#endif //ESPTEST_TCPSERVER_H
