#ifndef ESPTEST_TCPCLIENT_H
#define ESPTEST_TCPCLIENT_H

#include "TcpSocket.h"

class TcpClient : public TcpSocket {
    /*
     * client-side of a TcpSocket which will connect to `ip` on `port`
     * every time a message is received from server `message_handler()` will be called with the message
     *
     * call `handler()` periodically to handle client status
     * call `send()` to send a string to server
     * call `send_json()` to send a JSON string to server
     *
     * SeeAlso: TcpSocket
     */
private:
    IPAddress ip;
    int port;
    CheckTime check_time = CheckTime(0, 1);
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
