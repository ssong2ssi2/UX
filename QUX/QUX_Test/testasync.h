#ifndef TESTASYNC_H
#define TESTASYNC_H

#include "Qux/include/async/waitforsignal.h"
#include "Qux/include/async/waitforsignal.h"
#include "Qux/include/async/runonmainthread.h"
#include "Qux/include/async/runonnextframe.h"


#include "Qux/include/ui/rcv.h"
#include "Qux/include/bind.h"


#include <QtTest/QtTest>

namespace TestAsync {

    class SampleObject : public QObject
    {
        Q_OBJECT

            PROPERTY(bool, value, setValue)

    public:
        SampleObject() : m_value(false) {}

    };


class TestAsync : public QObject
{
    Q_OBJECT

private slots:
    void testWaitForSignal()
    {
        SampleObject objSrc, objDst;

        Qux::bind<bool>(REF(&objSrc, value), BOUND(&objDst, value), [] (bool value) {
            return value; 
        });

        objSrc.setValue(true);
        QCOMPARE(objDst.value(), objSrc.value());



        bool check = false;

        QThread thread;
        connect(&thread, &QThread::started, [&] () {
            QThread::msleep(50);

            check = true;
            emit testCompleted();
        });

        thread.start();

        Qux::Async::waitForSignal(this, &TestAsync::testCompleted);

        QVERIFY(check);

        thread.exit();
        thread.wait();
    }

    void testRunOnMainThread()
    {
        auto mainThreadId = QThread::currentThreadId();

        QThread thread;

        connect(&thread, &QThread::started, [this, mainThreadId] () {
            Qux::Async::runOnMainThread([=] () {
                QCOMPARE(QThread::currentThreadId(), mainThreadId);
                emit testCompleted();
            });
        });

        thread.start();

        Qux::Async::waitForSignal(this, &TestAsync::testCompleted);

        thread.exit();
        thread.wait();
    }

    void testRunOnNextFrame()
    {
        auto context = new QObject;

        Qux::Async::runOnNextFrame(context, [this] () {
            emit testCompleted();
        });

        Qux::Async::waitForSignal(this, &TestAsync::testCompleted);

        delete context;
    }

signals:
    void testCompleted();

};

}

#endif