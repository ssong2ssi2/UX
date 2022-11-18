#ifndef TESTFLUX_H
#define TESTFLUX_H

#include "Qux/include/flux/actionhelper.h"
#include "Qux/include/flux/middleware.h"
#include "Qux/include/flux/simplemiddleware.h"
#include "Qux/include/flux/store.h"

#include <QtTest/QtTest>

namespace TestFlux {

enum ActionType
{
    Test
};
Q_DECLARE_METATYPE(ActionType)

namespace Action {

ACTION1(test, Test, QString, value)

}

class SampleMiddleware : public Qux::Flux::Middleware
{
    Q_OBJECT

public:
    virtual void reduce(const Qux::Flux::Action& action)
    {
        if (action["type"].value<ActionType>() == Test) {
            value = action["value"].toString();
        }
    }

    QString value;

};

class SampleStore : public Qux::Flux::Store
{
    Q_OBJECT

public:
    virtual void reduce(const Qux::Flux::Action& action)
    {
        if (action["type"].value<ActionType>() == Test) {
            value = action["value"].toString();
        }
    }

    QString value;

};

class TestFlux : public QObject
{
    Q_OBJECT

private slots:
    void testMiddleware()
    {
        SampleMiddleware middleware;

        QString value = "test value";
        Action::test(value);
        QCOMPARE(middleware.value, value);
    }

    void testSimpleMiddleware()
    {
        QString result;
        Qux::Flux::SimpleMiddleware middleware([&result] (const Qux::Flux::Action& action) {
            if (action["type"].value<ActionType>() == Test) {
                result = action["value"].toString();
            }
        });

        QString value = "test value";
        Action::test(value);
        QCOMPARE(result, value);
    }

    void testStore()
    {
        SampleStore store;

        QString value = "test value";
        Action::test(value);
        QCOMPARE(store.value, value);
    }

};

}

#endif