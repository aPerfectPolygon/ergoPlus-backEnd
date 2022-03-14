#include "TcpClient.h"

TcpClient::TcpClient(IPAddress _ip, int _port) {
    ip = _ip;
    port = _port;
};

bool TcpClient::is_connected() {
    return client.connected();
}

void TcpClient::send(const String &s) {
    if (is_connected())
        _send(client, s);
}

void TcpClient::send_json(const String &type, const String &data) {
    if (is_connected())
        _send_json(client, type, data);
}

String TcpClient::receive() {
    if (is_connected())
        return _receive(client);
    else
        return "";
}

void TcpClient::log(const String &s, const String &tag) {
    if (is_connected())
        _log(client, s, tag);
    else
        print(tag + " ClientNotConnected " + s);
}

//void TcpClient::message_handler(const String &message){
//    _send("RECEIVED");
//}

void TcpClient::handler() {
    if (!is_connected()) {
        if (!check_time.check())
            return;

        print("connecting to server ...");
        client.connect(ip, port);
        if (is_connected())
            print("connected");
        return;
    }

    while (client.available()) {
        message_handler(receive());
    }
}
