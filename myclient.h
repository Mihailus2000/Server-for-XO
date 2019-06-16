#ifndef MYCLIENT_H
#define MYCLIENT_H


#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>


class MyClient : public QObject
{
    Q_OBJECT

public:
    explicit MyClient(int socketDescriptor,QTcpSocket* socket,QObject *parent = nullptr);
    QTcpSocket* getSocket();

signals:

public slots:
    void sockDisk();
    void sockReady();

private:
    QTcpSocket* _sok; //сокет пользователя
    int sok_desck;
    QByteArray Data;
    QJsonDocument doc;
    QJsonParseError docError;

signals:
    void startGame();
};

#endif // MYCLIENT_H
