#include "../include/metaobject.h"

namespace Qux {

QMetaMethod findMethodByName(const QObject* object, const QString& name, QMetaMethod::MethodType type)
{
    auto metaObject = object->metaObject();
    for(auto i = 0; i < metaObject->methodCount(); i++) {
        auto method = metaObject->method(i);
        auto str = QString::fromLatin1(method.methodSignature());
        if (method.methodType() == type &&
                QString::fromLatin1(method.methodSignature()).indexOf(name + "(") == 0) {
            return method;
        }
    }
    return QMetaMethod();
}

QMetaMethod findSignalByName(const QObject* object, const QString& name)
{
    return findMethodByName(object, name, QMetaMethod::Signal);
}

QMetaMethod findSlotByName(const QObject* object, const QString& name)
{
    return findMethodByName(object, name, QMetaMethod::Slot);
}

}