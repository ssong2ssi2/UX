#ifndef TESTMODEL_H
#define TESTMODEL_H

#include "Qux/include/model/listmodel.h"
#include "Qux/include/model/filteredlistmodel.h"
#include "Qux/include/model/sortedlistmodel.h"
#include "Qux/include/model/proxylistmodel.h"
#include "Qux/include/model/keymodel.h"
#include "Qux/include/model/convertedkeymodel.h"
#include "Qux/include/model/filteredkeymodel.h"
#include "Qux/include/model/keymodeladapterlistmodel.h"
#include "Qux/include/model/keymodelreferencelistmodel.h"
#include "Qux/include/model/keymodelbind.h"
#include "Qux/include/utility.h"

using namespace Qux::Model;

#include <QtTest/QtTest>

namespace TestModel {

class TestModel : public QObject
{
    Q_OBJECT

private slots:
    void testListModel_data()
    {
        QTest::addColumn<QList<ModelItem>>("source");
        QTest::addColumn<QList<ModelItem>>("result");

        auto source = Qux::toList<ModelItem>(0, 1, 2, 3, 4),
             result = source;

        QTest::newRow("0") << source << result;
    }

    void testListModel()
    {
        QFETCH(QList<ModelItem>, source);

        ListModel listModel;
        listModel.append(source);

        QTEST(listModel.list(), "result");
    }

    void testFilteredListModel_data()
    {
        QTest::addColumn<QList<ModelItem>>("source");
        QTest::addColumn<QList<ModelItem>>("result");

        auto source = Qux::toList<ModelItem>(0, 1, 2, 3, 4),
             result = Qux::toList<ModelItem>(0, 2, 4);

        QTest::newRow("0") << source << result;
    }

    void testFilteredListModel()
    {
        QFETCH(QList<ModelItem>, source);

        ListModel listModel;
        FilteredListModel filteredListModel(&listModel);
        filteredListModel.setFilter([] (const ModelItem& a) {
            return a.toInt() % 2 == 0;
        });

        listModel.append(source);

        QTEST(filteredListModel.list(), "result");
    }

    void testSortedListModel_data()
    {
        QTest::addColumn<QList<ModelItem>>("source");
        QTest::addColumn<QList<ModelItem>>("result");

        auto source = Qux::toList<ModelItem>(5, 6, 7, 8, 0, 1, 2, 3, 4),
             result = Qux::toList<ModelItem>(8, 7, 6, 5, 4, 3, 2, 1, 0);

        QTest::newRow("0") << source << result;
    }

    void testSortedListModel()
    {
        QFETCH(QList<ModelItem>, source);

        ListModel listModel;
        SortedListModel sortedListModel(&listModel);
        sortedListModel.setComparer([] (const ModelItem& a, const ModelItem& b) {
            return a > b;
        });

        listModel.append(source);

        QTEST(sortedListModel.list(), "result");
    }

    void testProxyListModel_data()
    {
        QTest::addColumn<QList<ModelItem>>("source");
        QTest::addColumn<QList<ModelItem>>("result");

        auto source = Qux::toList<ModelItem>(5, 6, 7, 8, 0, 1, 2, 3, 4),
             result = Qux::toList<ModelItem>(8, 6, 4, 2, 0);

        QTest::newRow("0") << source << result;
    }

    void testProxyListModel()
    {
        QFETCH(QList<ModelItem>, result);

        ListModel listModel;
        ProxyListModel proxyListModel(&listModel);
        proxyListModel.setFilter([] (const ModelItem& a) {
            return a.toInt() % 2 == 0;
        });
        proxyListModel.setComparer([] (const ModelItem& a, const ModelItem& b) {
            return a > b;
        });

        listModel.append(result);

        QTEST(proxyListModel.list(), "result");
    }

    void testKeyModel_data()
    {
        QTest::addColumn<QMap<ModelItem, ModelItem>>("source");
        QTest::addColumn<QMap<ModelItem, ModelItem>>("result");

        auto source = Qux::toMap<ModelItem, ModelItem>("a", 0, "b", 1, "c", 2),
             result = source;

        QTest::newRow("0") << source << result;
    }

    void testKeyModel()
    {
        typedef QMap<ModelItem, ModelItem> Source;
        QFETCH(Source, source);

        KeyModel keyModel;

        for (auto iter = source.cbegin(); iter != source.cend(); iter++) {
            keyModel.insert(iter.key(), iter.value());
        }

        QTEST(keyModel.map(), "result");
    }

    void testConvertedKeyModel_data()
    {
        QTest::addColumn<QMap<ModelItem, ModelItem>>("source");
        QTest::addColumn<QMap<ModelItem, ModelItem>>("result");

        auto source = Qux::toMap<ModelItem, ModelItem>("a", 0, "b", 1, "c", 2),
             result = Qux::toMap<ModelItem, ModelItem>("a", 0, "b", 2, "c", 4);

        QTest::newRow("0") << source << result;
    }

    void testConvertedKeyModel()
    {
        typedef QMap<ModelItem, ModelItem> Source;
        QFETCH(Source, source);

        KeyModel keyModel;
        ConvertedKeyModel convertedKeyModel(&keyModel);
        convertedKeyModel.setConverter([] (const ModelItem& a) {
            return a.toInt() * 2;
        });

        for (auto iter = source.cbegin(); iter != source.cend(); iter++) {
            keyModel.insert(iter.key(), iter.value());
        }

        QTEST(convertedKeyModel.map(), "result");
    }

    void testFilteredKeyModel_data()
    {
        QTest::addColumn<QMap<ModelItem, ModelItem>>("source");
        QTest::addColumn<QMap<ModelItem, ModelItem>>("result");

        auto source = Qux::toMap<ModelItem, ModelItem>("a", 0, "b", 1, "c", 2, "d", 3),
             result = Qux::toMap<ModelItem, ModelItem>("a", 0, "c", 2);

        QTest::newRow("0") << source << result;
    }

    void testFilteredKeyModel()
    {
        typedef QMap<ModelItem, ModelItem> Source;
        QFETCH(Source, source);

        KeyModel keyModel;
        FilteredKeyModel filteredKeyModel(&keyModel);
        filteredKeyModel.setFilter([] (const ModelItem& a) {
            return a.toInt() % 2 == 0;
        });

        for (auto iter = source.cbegin(); iter != source.cend(); iter++) {
            keyModel.insert(iter.key(), iter.value());
        }

        QTEST(filteredKeyModel.map(), "result");
    }

    void testKeyModelAdapterListModel_data()
    {
        QTest::addColumn<QMap<ModelItem, ModelItem>>("source");
        QTest::addColumn<QList<ModelItem>>("result");

        auto source = Qux::toMap<ModelItem, ModelItem>("a", 0, "b", 1, "c", 2);
        auto result = source.values();

        QTest::newRow("0") << source << result;
    }

    void testKeyModelAdapterListModel()
    {
        typedef QMap<ModelItem, ModelItem> Source;
        QFETCH(Source, source);

        KeyModel keyModel;

        for (auto iter = source.cbegin(); iter != source.cend(); iter++) {
            keyModel.insert(iter.key(), iter.value());
        }

        KeyModelAdapterListModel listModel(&keyModel);
        auto list = listModel.list();
        std::sort(list.begin(), list.end());

        QFETCH(QList<ModelItem>, result);
        std::sort(result.begin(), result.end());

        QCOMPARE(list, result);
    }

    void testKeyModelReferenceListModel_data()
    {
        QTest::addColumn<QMap<ModelItem, ModelItem>>("source");
        QTest::addColumn<QList<ModelItem>>("result");

        auto source = Qux::toMap<ModelItem, ModelItem>("a", 0, "b", 1, "c", 2);
        auto result = Qux::convertList<ModelItem>(Qux::toList(0, 2, 1));

        QTest::newRow("0") << source << result;
    }

    void testKeyModelReferenceListModel()
    {
        typedef QMap<ModelItem, ModelItem> Source;
        QFETCH(Source, source);

        KeyModel keyModel;

        for (auto iter = source.cbegin(); iter != source.cend(); iter++) {
            keyModel.insert(iter.key(), iter.value());
        }

        KeyModelReferenceListModel listModel(&keyModel);
        listModel.append("a");
        listModel.append("c");
        listModel.append("b");

        QTEST(listModel.list(), "result");
    }

    void testKeyModelBind()
    {
        KeyModel keyModel;
        QObject context;

        auto success = false;
        bind(&keyModel, "test key", &context, [&success] (const ModelItem& value) {
            if (value == "test value") success = true;
        });

        keyModel.insert("test key", "test value");

        QVERIFY(success);
    }

};

}

#endif