#include"server.hpp"
#include"app.hpp"
#include<QNetworkReply>
#include<QJsonDocument>
Server::Server(App* parent){
    this->parent = parent;
    setLastRequest(QString("clear"), GET);
    while(!serverReplied);
}

Server::~Server(){
    delete lastReply;
    delete lastRequest;
}

QNetworkReply* Server::getLastReplay(){
    return lastReply;
}

QNetworkRequest* Server::getLastRequest(){
    return lastRequest;
}

App* Server::getParent(){
    return parent;
}

void Server::setLastReplay(QNetworkReply *set){
    if(lastReply)
        delete lastReply;
    lastReply = set;
}

bool Server::setLastRequest(QString command, MessageType msgType){
    if(serverReplied){
        serverReplied = false;
        if(lastRequest)
            delete lastRequest;
        lastRequest = new QNetworkRequest();
        lastRequest->setUrl(QUrl(URL + command));
        switch(msgType){
        case GET:
            setLastReplay(get(*lastRequest));
            break;
        default:
            serverReplied = true;
            return true;
        }
        lastReply->waitForReadyRead(3000);

        while(!lastReply->isFinished()){

            qApp->processEvents();
        }
        qDebug() << lastReply->error();
        qDebug() << lastReply->readAll();

        serverReplied = true;

        return true;
    }

    else
        return false;
}

bool Server::setLastRequest(QString command, MessageType msgType, QJsonDocument &body){
    if(serverReplied){
        serverReplied = false;
        if(lastRequest)
            delete lastRequest;
        lastRequest = new QNetworkRequest();
        lastRequest->setUrl(QUrl(URL + command));
        switch(msgType){
        case POST:
            lastRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            setLastReplay(post(*lastRequest, body.toJson()));
            break;
        default:
            serverReplied = true;
            return true;
        }
        lastReply->waitForReadyRead(3000);

        while(!lastReply->isFinished()){

            qApp->processEvents();
        }
        qDebug() << lastReply->error();
        qDebug() << lastReply->readAll();

        serverReplied = true;

        return true;
    }

    else
        return false;
}

bool Server::isServerReplied(){
    return serverReplied;
}
