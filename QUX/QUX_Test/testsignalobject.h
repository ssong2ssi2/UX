#ifndef TESTSIGNALOBJECT_H
#define TESTSIGNALOBJECT_H

#include "Qux/include/signalobject.h"

#include <QtTest/QtTest>

namespace TestSignalObject {

class TestSignalObject : public QObject
{
    Q_OBJECT

private:
    template <typename T, typename OBJ>
    void testObject(T targetValue)
    {
        OBJ obj;

        bool check = false;
        QObject::connect(&obj, &OBJ::valueChanged, [&check, targetValue] (T value) {
            check = value == targetValue;
        });
        obj.setValue(targetValue);

        QVERIFY(check);
    }

private slots:
    void testBoolObject()
    {
        testObject<bool, Qux::BoolObject>(true);
    }

    void testIntObject()
    {
        testObject<int, Qux::IntObject>(10);
    }

    void testQStringObject()
    {
        testObject<QString, Qux::QStringObject>("test");
    }

};

}

#endif