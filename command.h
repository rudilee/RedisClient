#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

#include "reply.h"

namespace Redis {
    class Command : public QObject
    {
        Q_OBJECT

    public:
        explicit Command(QString commandName, QObject *parent = 0);

        void addArgument(QVariant argument);
        void addArgumentStrings(QStringList arguments);

        QString getCommandName();
        QVariantList getArguments();

        // Hashes commands
        static Command *HGET(QString key, QString field);

        // Keys commands
        static Command *GET(QString key);
        static Command *DEL(QStringList keys);
        static Command *EXPIRE(QString key, int seconds);
        static Command *KEYS(QString pattern);

        // Lists commands
        static Command *LPUSH(QString key, QStringList values);
        static Command *RPOP(QString key);

        // Pub/Sub commands
        static Command *SUBSCRIBE(QStringList channels);

    private:
        QString commandName;
        QVariantList arguments;

    signals:
        void replyReceived(Reply reply);
    };
}

#endif // COMMAND_H
