#ifndef TESTMETAOBJECT_H
#define TESTMETAOBJECT_H

#include "Qux/include/metaobject.h"

#include <QtTest/QtTest>

namespace TestMetaObject {

class SampleObject : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE void method() {}

public slots:
    void slot() {}

signals:
    void signal();

};

class TestMetaObject : public QObject
{
    Q_OBJECT

private slots:
    void testMetaObject()
    {
        SampleObject obj;

        auto method = Qux::findMethodByName(&obj, "method", QMetaMethod::Method);
        QCOMPARE(QString(method.name()), QString("method"));

        auto signal = Qux::findMethodByName(&obj, "signal", QMetaMethod::Signal);
        QCOMPARE(QString(signal.name()), QString("signal"));

        auto slot = Qux::findMethodByName(&obj, "slot", QMetaMethod::Slot);
        QCOMPARE(QString(slot.name()), QString("slot"));
    }

};

}

#endif