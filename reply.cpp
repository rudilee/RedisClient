#include "reply.h"

using namespace Redis;

Reply::Reply(Reply::Types type) : m_type(type)
{
    ;
}

Reply::Types Reply::type()
{
    return m_type;
}

QVariant Reply::value()
{
    return QVariant();
}
