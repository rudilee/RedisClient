#include <QDebug>

#include "redisclient.h"

RedisClient::RedisClient(QObject *parent) : QObject(parent),
    subscribing(false)
{
    initConnectionHandler();
}

void RedisClient::connectToServer(QString hostName, quint16 port)
{
    connection.connectToHost(hostName, port);
}

void RedisClient::sendCommand(Command *command)
{
    if (subscribing)
        return;

    subscribing = command->getCommandName() == "SUBSCRIBE";

    sentCommands.enqueue(command);

    sendRequest(command->getArguments());
}

void RedisClient::pipelining(QList<Command *> commands)
{
    QVariantList request;

    foreach (Command *command, commands) {
        sentCommands.enqueue(command);

        request.append(command->getArguments());
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

void RedisClient::sendRequest(QVariantList lines)
{
    if (connection.state() == QTcpSocket::ConnectedState && !lines.isEmpty()) {
        connection.write(QString("*%1\r\n").arg(QString::number(lines.count())).toUtf8());

        foreach (QVariant line, lines) {
            QString bulkString = line.toString();

            connection.write(QString("$%1\r\n").arg(QString::number(bulkString.length())).toUtf8());
            connection.write(QString("%1\r\n").arg(bulkString).toUtf8());
        }

        connection.flush();
    }
}

void RedisClient::handleConnectionError(QAbstractSocket::SocketError socketError)
{
    ;
}

void RedisClient::parseReply()
{
    Reply::Types type;
    QVariant value;

    bool isArray = false;
    int arrayLength = 0;
    QVariantList array;

    while (connection.canReadLine()) {
        QByteArray line = connection.readLine(),
                   firstByte = line.left(1);

        if (firstByte == "*") { // Array
            isArray = true;
            arrayLength = line.trimmed().toInt();

            continue;
        } else if (firstByte == "+") { // Simple String
            type = Reply::SimpleString;
            value = QString(line.trimmed());
        } else if (firstByte == "-") { // Error
            type = Reply::Error;
            value = QString(line.trimmed());
        } else if (firstByte == ":") { // Integer
            type = Reply::Integer;
            value = line.trimmed().toInt();
        } else if (firstByte == "$") { // Bulk String
            type = Reply::BulkString;

            continue;
        } else if (type == Reply::BulkString) {
            value = QString(line.trimmed());
        }

        if (isArray)
            array << value;
    }

    if (isArray) {
        type = Reply::Array;
        value = array;
    }

    if (!sentCommands.isEmpty())
        sentCommands.dequeue()->replyReceived(Reply(type, value));
    else if (subscribing)
        messageReceived(array[1].toString(), array[2]);
}
