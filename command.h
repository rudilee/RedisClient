#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

#include "reply.h"

class Command : public QObject
{
    Q_OBJECT

public:
    explicit Command(QObject *parent = 0);

    QByteArray bulkStrings();

    // Keys commands
    static Command *DEL(QStringList keys);
    static Command *EXPIRE(QString key, int seconds);

    // Lists commands
    static Command *LPUSH(QString key, QStringList values);
    static Command *RPOP(QString key);

    // Pub/Sub commands
    static Command *SUBSCRIBE(QStringList channels);

signals:
    void replyReceived(Reply reply);
};

#endif // COMMAND_H
