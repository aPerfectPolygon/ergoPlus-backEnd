#include "TcpSocket.h"

void TcpSocket::_log(WiFiClient client, const String &s, const String &tag) {
    print(tag + " " + client.remoteIP().toString() + " " + s);
}

void TcpSocket::_send_json(const WiFiClient& client, const String &type, String data) {
    if (not(data.startsWith("[") || data.startsWith("{"))) {
        data = "\"" + data + "\"";
    }
    _send(client, R"({"type":")" + type + R"(","data":)" + data + "}");
}

void TcpSocket::_send(WiFiClient client, const String &s) {
    _log(client, s, "SEND   ");
    client.print(s + terminator);
}

String TcpSocket::_receive(WiFiClient client) {
    String res = client.readStringUntil(terminator);
    _log(client, res, "RECEIVE");
    return res;
}
