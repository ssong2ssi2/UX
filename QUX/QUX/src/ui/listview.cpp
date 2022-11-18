#include "../../include/ui/listview.h"
#include "../../include/ui/rcv.h"

#include <QLayout>

using namespace Qux::Model;

namespace Qux {
namespace UI {

ListView::ListView(BOX_TYPE type, QWidget* parent)
    : m_model(nullptr), QWidget(parent)
{
    QBoxLayout* layout = nullptr;
    if (type == BOX_TYPE::VBOX)
        layout = new QVBoxLayout(this);
    else if (type == BOX_TYPE::HBOX)
        layout = new QHBoxLayout(this);
     
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    auto setupLayout = [=] () {
        if (!m_model || !m_widgetCreator) return;

        {
            // clear layout
            QLayoutItem* item;
            while (item = layout->takeAt(0)) {
                if (item->widget()) delete item->widget();
                delete item;
            }
        }

        for (auto iter = m_model->list().cbegin(); iter != m_model->list().cend(); iter++) {
            layout->addWidget(m_widgetCreator(*iter));
        }
        layout->addStretch(1);
    };

    connect(this, &ListView::modelAboutToBeChanged, [this] () {
        if (m_model != nullptr) {
            disconnect(m_model, 0, this, 0);
        }
    });

    connect(this, &ListView::modelChanged, [=] () {
        connect(m_model, &AbstractListModel::inserted, this, [=] (int start, const QList<ModelItem>& list) {
            foreach(auto& value, list) {
                layout->insertWidget(start++, m_widgetCreator(value));
            }
        });

        connect(m_model, &AbstractListModel::removed, this, [=] (int start, int end) {
            for (; start <= end; end--) {
                auto item = layout->takeAt(start);
                item->widget()->deleteLater();
                delete item;
            }
        });

        connect(m_model, &AbstractListModel::updated, this, [=] (int start, const QList<ModelItem>& list) {
            foreach (auto& value, list) {
                auto item = layout->itemAt(start);
                auto widget = item->widget();

                if (widget->property("data").isValid()) {
                    widget->setProperty("data", value);
                }
                else {
                    layout->removeItem(item);
                    item->widget()->deleteLater();
                    delete item;

                    layout->insertWidget(start, m_widgetCreator(value));
                }

                start++;
            }
        });

        setupLayout();
    });

    connect(this, &ListView::widgetCreatorChanged, setupLayout);
}

}
}