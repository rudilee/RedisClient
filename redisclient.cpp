#include "redisclient.h"

RedisClient::RedisClient(QObject *parent) : QObject(parent)
{
    initConnectionHandler();
}

void RedisClient::connectToServer(QString hostName, quint16 port)
{
    connection.connectToHost(hostName, port);
}

void RedisClient::sendCommand(Command *command)
{
    sentCommands.enqueue(command);

    sendRequest(command->bulkStrings());
}

void RedisClient::pipelining(QList<Command *> commands)
{
    QByteArray request;

    foreach (Command *command, commands) {
        sentCommands.enqueue(command);

        request.append(command->bulkStrings());
    }

    sendRequest(request);
}

void RedisClient::initConnectionHandler()
{
    connect(&connection, SIGNAL(connected()), SIGNAL(connected()));
    connect(&connection, SIGNAL(disconnected()), SIGNAL(disconnected()));
    connect(&connection, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(handleConnectionError(QAbstractSocket::SocketError)));
    connect(&connection, SIGNAL(readyRead()), SLOT(parseReply()));
}

void RedisClient::sendRequest(QByteArray request)
{
    if (connection.state() == QTcpSocket::ConnectedState && !request.isEmpty())
        connection.write(request);
}

void RedisClient::handleConnectionError(QAbstractSocket::SocketError socketError)
{
    ;
}

void RedisClient::parseReply()
{
    QByteArray line = connection.readLine(),
               firstByte = line.left(1);

    if (firstByte == "+") { // Simple Strings
        ;
    } else if (firstByte == "-") { // Errors
        ;
    } else if (firstByte == ":") { // Integers
        ;
    } else if (firstByte == "$") { // Bulk Strings
        ;
    } else if (firstByte == "*") { // Arrays
        ;
    }
}
