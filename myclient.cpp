#include "myclient.h"

MyClient::MyClient(int socketDescriptor, QTcpSocket *socket, QObject *parent)
{
    _sok = socket;
    sok_desck = socketDescriptor;
    connect(_sok,SIGNAL(disconnected()),this,SLOT(sockDisk()));
    connect(_sok,SIGNAL(readyRead()),this,SLOT(sockReady()));
}

QTcpSocket* MyClient::getSocket()
{
    return _sok;
}

void MyClient::sockDisk(){
    qDebug() << "Disconnect socket " + QString(_sok->socketDescriptor());
    _sok->deleteLater();

}

void MyClient::sockReady(){
    Data=_sok->readAll();
    qDebug() << "Data: " << Data;
    doc = QJsonDocument::fromJson(Data,&docError);
    //{"type":"text"}
    if (docError.errorString()=="no error occurred"){
       if(doc.object().value("type").toString()=="game" && doc.object().value("sendWho").toString()=="FIRST" && doc.object().value("what").toString()=="chooseReady"){
            qDebug() << "First player as 'X' is ready";
       }
       if(doc.object().value("type").toString()=="game" && doc.object().value("sendWho").toString()=="SECOND" && doc.object().value("what").toString()=="chooseReady"){
            qDebug() << "Second player as 'O' is ready. Game can be started!";
            //_sok->write("{\"type\":\"game\",\"turn\":\"your\"}");
            emit startGame();// emit signal that start game
       }
        ///TODO

    }
}
