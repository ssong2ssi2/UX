#ifndef TESTUI_H
#define TESTUI_H

#include "Qux/include/ui/rcv.h"

#include <QtTest/QtTest>
#include <QWidget>

namespace TestUI {

class TestUI : public QObject
{
    Q_OBJECT

private slots:
    void testRcv()
    {
        QScopedPointer<QWidget> widget(new QWidget);
        auto receiver = Qux::UI::rcv(widget.data());

        QCOMPARE(receiver, Qux::UI::rcv(widget.data()));
        widget.reset(new QWidget);
        QVERIFY(receiver != Qux::UI::rcv(widget.data()));
    }

    void testReceiver()
    {
        QWidget widget;

        auto success = false;
        connect(Qux::UI::rcv(&widget), &Qux::UI::Receiver::mousePressed, [&success] (QMouseEvent*, bool* consumed) {
            success = true;
        });

        QTest::mousePress(&widget, Qt::LeftButton);
        QVERIFY(success);
    }

};

}

#endif