#ifndef ESPTEST_TCPSERVER_H
#define ESPTEST_TCPSERVER_H

#include "TcpSocket.h"

class TcpServer : public TcpSocket {
    /*
     * server-side of a TcpSocket which will create a TcpServer on `port`
     * specify how many clients by setting `max_clients` and its related variables
     * every time a message is received from client `message_handler()` will be called with the message
     *
     * call `handler()` periodically to handle client status
     * call `broadcast()` to send a message to all connected clients
     * call `broadcast_json()` to send a JSON message to all connected clients
     * call `send()` to send a message to specified clients
     * call `send_json()` to send a JSON message to specified clients
     * call `scan_and_add()` to check if new clients are ready to connect
     *
     * SeeAlso: TcpSocket
     */
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
