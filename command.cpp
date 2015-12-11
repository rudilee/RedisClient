#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{
    ;
}

QByteArray Command::bulkStrings()
{
    return QByteArray();
}

Command *Command::DEL(QStringList keys)
{
    return new Command;
}

Command *Command::EXPIRE(QString key, int seconds)
{
    return new Command;
}

Command *Command::LPUSH(QString key, QStringList values)
{
    return new Command;
}

Command *Command::RPOP(QString key)
{
    return new Command;
}

Command *Command::SUBSCRIBE(QStringList channels)
{
    return new Command;
}
