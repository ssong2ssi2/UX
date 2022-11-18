#ifndef TESTBIND_H
#define TESTBIND_H

#include <QWidget>
#include <QtTest/QtTest>

#include "Qux/include/bind.h"
#include "Qux/include/defineproperty.h"
#include "Qux/include/ui/rcv.h"


namespace TestBind {

class SampleObject : public QObject
{
    Q_OBJECT

    PROPERTY(bool, value, setValue)

public:
    SampleObject() : m_value(false) {}

};

class SampleObject2 : public QObject
{
    Q_OBJECT

    PROPERTY(int, value, setValue)

public:
    SampleObject2() : m_value(-1) {}

};


class TestBind : public QObject
{
    Q_OBJECT

private slots:
    void testBind()
    {
        {
            SampleObject objSrc, objDst;

            Qux::bind<bool>(REF(&objSrc, value), BOUND(&objDst, value), [] (bool value) { return value; });
            objSrc.setValue(true);
            QCOMPARE(objDst.value(), objSrc.value());
        }

        {
            SampleObject objSrc, objDst;

            objSrc.setValue(true);

            Qux::bind<bool>(REF(&objSrc, value), BOUND(&objDst, value), Qux::identity());
            
            QCOMPARE(objDst.value(), objSrc.value());
            
            objSrc.setValue(false);
            
            QCOMPARE(objDst.value(), objSrc.value());
        }





        {
            SampleObject2 objSrc, objDst;
            objSrc.setValue(1);
            

            Qux::bind<int>(REF(&objSrc, value), &objDst, &SampleObject2::setValue, [] (const int& value) {
                return value; 
            });
            objSrc.setValue(10);
            QCOMPARE(objDst.value(), objSrc.value());
        }

        {
            SampleObject objSrc, objDst;

            
            Qux::bind<bool>(REF(&objSrc, value), &objDst, [&objDst] (bool value) {
                objDst.setValue(value); 
            });

            objSrc.setValue(true);

            QCOMPARE(objDst.value(), objSrc.value());
        }
    }

    void testBindWithReceiver()
    {
        auto widget = new QWidget;
        SampleObject obj;

       widget->setProperty("pressed", true);

        Qux::bind<bool>(REF(Qux::UI::rcv(widget), pressed), BOUND(&obj, value), [] (bool value) {
            return value; 
        });
        QTest::mousePress(widget, Qt::LeftButton);
        QCOMPARE(obj.value(), true);
    }

};

}

#endif