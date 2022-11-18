#ifndef TESTQVALUE_H
#define TESTQVALUE_H

#include "Qux/include/utility/qvalue.h"

#include <QtTest/QtTest>
#include <functional>

namespace TestQValue {

class CallOnDestructor
{
public:
    std::function<void ()> callbackOnDestructor;

    ~CallOnDestructor()
    {
        callbackOnDestructor();
    }

};

class TestQValue : public QObject
{
    Q_OBJECT

private slots:
    void testQValue()
    {
        auto obj = new QObject;
        auto qvalue = Qux::createQValue<CallOnDestructor>(obj);

        bool deleted = false;
        qvalue->callbackOnDestructor = [&deleted] () {
            deleted = true;
        };

        delete obj;

        QVERIFY(deleted);
    }

};

}

#endif