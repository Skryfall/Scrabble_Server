//
// Created by kevin on 16/03/19.
//

#include "Server.h"
#include "Tail.h"
#include "../Logic/Data/Holder.h"
#include "../Logic/Data/GameData.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <QtCore/QJsonDocument>

using namespace std;

 //! Method that initializes the server
 //! \return an integer to know if an error happens
int Server::run() {

    Tail* tail = Tail::getInstance();
    GameData* gameData = GameData::getInstance();

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr *) &hint, sizeof(hint));
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);


    while (true) {
        // Wait for a connection
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        int clientSocket = accept(listening, (sockaddr *) &client, &clientSize);

        char host[NI_MAXHOST];      // Client's remote name

        char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on

        memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
        memset(service, 0, NI_MAXSERV);

        if (getnameinfo((sockaddr *) &client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
            cout << host << " conectado al puerto " << service << endl;
        } else {
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            cout << host << " conectado al puerto " << ntohs(client.sin_port) << endl;
        }

        // While loop: accept and echo message back to client
        char buf[4096];

        memset(buf, 0, 4096);

        // Wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);

        if (bytesReceived == -1) {
            cerr << "Error recibiendo datos" << endl;
            break;
        }
        if (bytesReceived == 0) {
            cout << "El cliente se desconecto " << endl;
            break;
        }

        string jsonHolder = string(buf, 0, bytesReceived);
        QJsonDocument doc2 = QJsonDocument::fromJson(QByteArray(jsonHolder.c_str()));
        QJsonObject json = doc2.object();
        Holder* holder = Holder::read(json);

        if (!tail->searchName(holder->getPlayerName())) {
            tail->addToTail(holder->getPlayerName());
        }

        QJsonObject json2;

        if (gameData->getRoomCode() == 0){
            holder = gameData->beginGame(holder);
            holder->write(json2);
            QJsonDocument doc(json2);
            QByteArray ba = doc.toJson();
            QString qstr = QString(ba);
            string str = qstr.toStdString();
            send(clientSocket, str.c_str(), str.size() + 1, 0);
            // Close the socket
            close(clientSocket);
        }else if (holder->getCodeToEnter() == gameData->getRoomCode() && gameData->getNumberOfPlayers() < gameData->getMaxNumberOfPlayers() && !tail->searchLastJoined(holder->getPlayerName())){
            holder = gameData->beginGame(holder);
            holder->write(json2);
            QJsonDocument doc(json2);
            QByteArray ba = doc.toJson();
            QString qstr = QString(ba);
            string str = qstr.toStdString();
            send(clientSocket, str.c_str(), str.size() + 1, 0);
            // Close the socket
            close(clientSocket);
        }else if (holder->getCodeToEnter() == gameData->getRoomCode() && tail->searchCurrentPlayers(holder->getPlayerName()) && gameData->getNumberOfPlayers() == gameData->getMaxNumberOfPlayers() && holder->getTurn() && tail->checkAllUpdated()){
            holder = gameData->processPlay(holder);
            tail->searchPlayer(holder->getPlayerName())->setUpdated(true);
            holder->write(json2);
            QJsonDocument doc(json2);
            QByteArray ba = doc.toJson();
            QString qstr = QString(ba);
            string str = qstr.toStdString();
            send(clientSocket, str.c_str(), str.size() + 1, 0);
            tail->changeTurns();
            // Close the socket
            close(clientSocket);
        }else if (!holder->getTurn() && holder->getCodeToEnter() == gameData->getRoomCode() && tail->checkAllUpdated() && gameData->getNumberOfPlayers() == gameData->getMaxNumberOfPlayers()){
            if (tail->searchCurrentPlayerTurn() == 1 && tail->numberOfPlayer(holder->getPlayerName())){
                tail->setAllOutdated();
                holder->setTurn(true);
            }if (tail->searchCurrentPlayerTurn() == 2 && tail->numberOfPlayer(holder->getPlayerName())){
                tail->setAllOutdated();
                holder->setTurn(true);
            }if (tail->searchCurrentPlayerTurn() == 3 && tail->numberOfPlayer(holder->getPlayerName())){
                tail->setAllOutdated();
                holder->setTurn(true);
            }if (tail->searchCurrentPlayerTurn() == 4 && tail->numberOfPlayer(holder->getPlayerName())){
                tail->setAllOutdated();
                holder->setTurn(true);
            }
            holder->write(json2);
            QJsonDocument doc(json2);
            QByteArray ba = doc.toJson();
            QString qstr = QString(ba);
            string str = qstr.toStdString();
            send(clientSocket, str.c_str(), str.size() + 1, 0);
            // Close the socket
            close(clientSocket);
        }else if (gameData->getNumberOfPlayers() == gameData->getMaxNumberOfPlayers() && !holder->getTurn() && holder->getCodeToEnter() == gameData->getRoomCode() && !tail->searchPlayer(holder->getPlayerName())->getUpdated()){
            holder->lastPlayList = LastPlayList::getInstance();
            tail->searchPlayer(holder->getPlayerName())->setUpdated(true);
            holder->write(json2);
            QJsonDocument doc(json2);
            QByteArray ba = doc.toJson();
            QString qstr = QString(ba);
            string str = qstr.toStdString();
            send(clientSocket, str.c_str(), str.size() + 1, 0);
            // Close the socket
            close(clientSocket);
        }else{
            holder->lastPlayList = nullptr;
            holder->write(json2);
            QJsonDocument doc(json2);
            QByteArray ba = doc.toJson();
            QString qstr = QString(ba);
            string str = qstr.toStdString();
            send(clientSocket, str.c_str(), str.size() + 1, 0);
            // Close the socket
            close(clientSocket);
        }
    }
}
