#include "myserver.h"

myserver::myserver(){

}

myserver::~myserver(){}

void myserver::startServer(){
    if(this->listen(QHostAddress::LocalHost,5555)){
        qDebug() << "Listenning!";
    }
    else{
        qDebug() << "No Listening!";

    }
}
void myserver::incomingConnection(int socketDescriptor){
    QTcpSocket* socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    if(Clients.size()>2){
        qDebug() << "Send to client connect status - NO";
        socket->write("{\"type\":\"connect\",\"status\":\"no\"}");
        return;
    }
    else{
        MyClient* client = new MyClient(socketDescriptor,socket,this);
        Clients.append(client);
    }
    //connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));


    qDebug() << socketDescriptor<< " Client connected";

    socket->write("{\"type\":\"connect\",\"status\":\"yes\"}");
    socket->waitForBytesWritten();
    socket->flush();
    qDebug() << "Send to client connect status - YES";
    if(Clients.size()==2){
//        game.newGame();
        game = new Game();
        game->newGame();
        qDebug() << "Send to " << Clients[0]->getSocket()->socketDescriptor() << " " << "{\"type\":\"game\",\"who\":\"X\"}";
        Clients[0]->getSocket()->write("{\"type\":\"game\",\"who\":\"X\"}");
        Clients[0]->getSocket()->flush();
        connect(Clients[0], SIGNAL(startGame()),this,SLOT(startCircleOfGame()));
        qDebug() << "Send to " << Clients[1]->getSocket()->socketDescriptor() << " " << "{\"type\":\"game\",\"who\":\"O\"}";
        Clients[1]->getSocket()->write("{\"type\":\"game\",\"who\":\"O\"}");
        Clients[1]->getSocket()->flush();
        turn = FIRST;
    }

}

void myserver::startCircleOfGame()
{
    if(turn == FIRST){
        Clients[0]->getSocket()->write("{\"type\":\"game\",\"what\":\"turn\"}");

    }
    if(turn == SECOND){
        Clients[1]->getSocket()->write("{\"type\":\"game\",\"what\":\"turn\"}");

    }
}



