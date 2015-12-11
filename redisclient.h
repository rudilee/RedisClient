#ifndef REDISCLIENT_H
#define REDISCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QQueue>

#include "command.h"

class RedisClient : public QObject
{
    Q_OBJECT

public:
    explicit RedisClient(QObject *parent = 0);

    void connectToServer(QString hostName, quint16 port = 6379);
    void sendCommand(Command *command);
    void pipelining(QList<Command *> commands);

private:
    QTcpSocket connection;
    QQueue<Command *> sentCommands;

    void initConnectionHandler();
    void sendRequest(QByteArray request);

private slots:
    void handleConnectionError(QAbstractSocket::SocketError socketError);
    void parseReply();

signals:
    void connected();
    void disconnected();
};

#endif // REDISCLIENT_H