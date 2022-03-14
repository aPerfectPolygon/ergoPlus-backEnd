#include "TcpServer.h"

TcpServer::TcpServer(int port) {
    server = WiFiServer(port);
};

void TcpServer::scan_and_add() {
    WiFiClient client = server.available();
    if (client && client.connected()) {
        for (int i = 0; i < max_clients; i++) {
            if (!clients[i].connected()) {
                clients[i] = client;
                log(i, "Connected", "ACTION ");
                clients_initialization[i] = true;
                return;
            }
        }
        _log(client, "Can not connect", "ACTION ");
        client.stop();
    }
}

void TcpServer::remove(int index) {
    log(index, "Disconnected", "ACTION ");
    clients[index].stop();
    clients[index] = WiFiClient();
    clients_initialization[index] = false;
}

void TcpServer::send(int index, const String &s) {
    _send(clients[index], s);
}

void TcpServer::send_json(int index, const String &type, const String &data) {
    _send_json(clients[index], type, data);
}

String TcpServer::receive(int index) {
    return _receive(clients[index]);
}

void TcpServer::log(int index, const String &s, const String &tag) {
    _log(clients[index], s, tag);
}

void TcpServer::broadcast(const String &s) {
    for (auto &client: clients)
        if (client.connected())
            _send(client, s);
}

void TcpServer::broadcast_json(const String &type, const String &data) {
    for (auto &client: clients)
        if (client.connected())
            _send_json(client, type, data);

}

//void TcpServer::message_handler(int index, const String &message){
//    _send(clients[index], "RECEIVED");
//}

void TcpServer::handler() {
    // check tcp server status
    if (server.status() == 0) {
        print("RESTARTING TCP SERVER ...");
        server.stop();
        server.begin();
    }

    // scan for new clients
    scan_and_add();

    // handle connected clients
    for (int i = 0; i < max_clients; i++) {
        if (!clients_initialization[i]) continue;
        if (!clients[i].connected()) {
            remove(i);
            continue;
        }
        while (clients[i].available()) {
            message_handler(i, receive(i));
        }
    }
}
