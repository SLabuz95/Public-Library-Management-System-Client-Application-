#ifndef SERVER_HPP
#define SERVER_HPP
#include<QtNetwork/QNetworkAccessManager>
#include"messagetype.hpp"
#define URL QString("http://192.168.0.101:8080/")
class App;
class QNetworkReply;
class QNetworkReply;
class Server : public QNetworkAccessManager{
public:
    // Konstruktor
    Server(App*);

    // Destruktor
    ~Server();
private:
    // Parent
    App* parent = nullptr;

    // Flaga obsłużenia zgłoszenia
    bool serverReplied = true;

    // Server Reply
    QNetworkReply* lastReply = nullptr;

    // Server Request
    QNetworkRequest* lastRequest = nullptr;
public:
    // Get
    QNetworkReply* getLastReplay();
    QNetworkRequest* getLastRequest();
    App* getParent();
    bool isServerReplied();

    // Set
    void setLastReplay(QNetworkReply*);
    bool setLastRequest(QNetworkRequest*, QString, MessageType, QJsonDocument&);

};

#endif // SERVER_HPP
