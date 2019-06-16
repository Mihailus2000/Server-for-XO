#ifndef MYSERVER_H
#define MYSERVER_H

#include "game.h"
#include "myclient.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

    enum whosTurn{
        FIRST,
        SECOND
    };

class myserver : QTcpServer
{
    Q_OBJECT
public:
    explicit myserver();
    ~myserver();
signals:
public slots:
    void startServer();
    void incomingConnection(int socketDescriptor); // Обработчик входящего подключения

    //void readyRead(); // Обработчик входящий данных
    //void stateChanged(QAbstractSocket::SocketState stat); // обработчик изменения состояния вещающего сокета
private:                                                      // (он нам важен, дабы у нас всегда был кто-то,
    whosTurn turn;
    Game* game;                                                      // кто будет вещать)
    QTcpServer *server; // указатель на сервер
    //QList<MyClient *> sockets; // получатели данных
    //QTcpSocket *socket; // вещатель
//    QByteArray Data;
    QList<MyClient*> Clients;
private slots:
    void startCircleOfGame();

//    QJsonDocument doc;
//    QJsonParseError docError;
};

#endif // MYSERVER_H
