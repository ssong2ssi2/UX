#include <QtCore/QCoreApplication>

#include <QApplication>

#include "testasync.h"
#include "testbind.h"
#include "testflux.h"
#include "testmetaobject.h"
#include "testmodel.h"
#include "testqvalue.h"
#include "testsignalobject.h"
#include "testui.h"

int main(int argc, char *argv[])
{
    QApplication  a(argc, argv);

    auto test = [](QObject* testObject) {
        QTest::qExec(testObject);
        delete testObject;
    };

    test(new TestAsync::TestAsync);
    test(new TestBind::TestBind);
    test(new TestFlux::TestFlux);
    test(new TestMetaObject::TestMetaObject);
    test(new TestModel::TestModel);
    test(new TestQValue::TestQValue);
    test(new TestSignalObject::TestSignalObject);
    test(new TestUI::TestUI);

    return a.exec();
}
