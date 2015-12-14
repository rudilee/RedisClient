#ifndef REPLY_H
#define REPLY_H

#include <QVariant>

namespace Redis {
    class Reply
    {
    public:
        enum Types {
            SimpleStrings,
            Errors,
            Integers,
            BulkStrings,
            Arrays
        };

        Reply(Types type);

        Reply::Types type();
        QVariant value();

    private:
        Reply::Types m_type;
    };
}

#endif // REPLY_H
