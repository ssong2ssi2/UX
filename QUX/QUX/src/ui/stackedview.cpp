#include "../../include/ui/stackedview.h"

#include "../../include/ui/rcv.h"
#include "../../include/utility.h"

#include <QLayout>
#include <QStackedLayout>

using namespace Qux::Model;

namespace Qux {
namespace UI {
StackedView::StackedView(QWidget* parent)
	: m_model(nullptr)
    , QWidget(parent)
{

    //auto indexMap = createQValue<QMap<ModelItem, int>>(this);       // < modelitem, modelIndex >

	auto layout = new QStackedLayout(this);

	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

    
    auto setupLayout = [=]() {
        if (!m_model || !m_widgetCreator) return;
        {
            // clear layout
            QLayoutItem* item;
            while (item = layout->takeAt(0)) {
                if (item->widget()) item->widget()->deleteLater();
                    delete item;
            }
            
            for (auto iter = m_model->list().cbegin(); iter != m_model->list().cend(); iter++) {
                layout->addWidget(m_widgetCreator(*iter));
            }
        }

    };
    

    connect(this, &StackedView::modelAboutToBeChanged, [this]() {
        if (m_model != nullptr) {
            disconnect(m_model, 0, this, 0);
        }
    });

    connect(this, &StackedView::modelChanged, [=]() {
        connect(m_model, &AbstractListModel::inserted, this, [=](int start, const QList<ModelItem>& list) {
            foreach(auto & value, list) {
                layout->insertWidget(start++, m_widgetCreator(value));
            }
        });

        connect(m_model, &AbstractListModel::removed, this, [=](int start, int end) {
            for (; start <= end; end--) {
                auto item = layout->takeAt(start);
                item->widget()->deleteLater();
                delete item;
            }
        });

        connect(m_model, &AbstractListModel::updated, this, [=](int start, const QList<ModelItem>& list) {
            foreach(auto & value, list) {
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
    
    connect(this, &StackedView::widgetCreatorChanged, setupLayout);
    //auto findIndexMap = [=](auto item) -> std::tuple<int, int> {

    //    int currentIndex = 0;
    //    int modelIndex = -1;

    //    for (auto iter = indexMap->begin(); iter != indexMap->end(); iter++, currentIndex++){
    //        auto key = iter.key();
    //        if (key == item)
    //        {
    //            modelIndex = iter.value();
    //            break;
    //        }
    //    }

    //    return std::tie(modelIndex, currentIndex);
    //};
    //
    connect(this, &StackedView::selectChanged, [this, layout](QString item) {
        if (m_model == nullptr)
            return;

        int index = 0;
        for (int i = 0; i < m_model->list().count(); i++)
        {
            if (m_compareModelItem(m_model->list().at(i), item) == true)
            {
                auto widget = layout->itemAt(i)->widget();
                widget->setProperty("selected", true);
                layout->setCurrentWidget(widget);
                
            }
            else
            {
                auto widget = layout->itemAt(i)->widget();
                widget->setProperty("selected", false);
            }
                
            
        }
    });

    //    auto result = findIndexMap(item);
    //    auto modelIndex = std::get<0>(result);
    //    auto stackedIndex = std::get<1>(result);

    //    if (modelIndex != -1 &&
    //        stackedIndex != -1)
    //    {
    //        layout->setCurrentIndex(stackedIndex);
    //    }
    //    else
    //    {
    //        // find Model 
    //        bool find = false;
    //        int findModelValue = -1;
    //        for (int i = 0; i < m_model->list().count(); i++)
    //        {
    //            if (m_compareModelItem(m_model->list().at(i), item) == true)
    //            {
    //                find = true;
    //                findModelValue = i;
    //                break;
    //            }

    //        }

    //        if (find == true ||
    //            findModelValue != -1)
    //        {
    //            auto layoutIndex = indexMap->size();
    //            auto widget =  m_widgetCreator(m_model->at(findModelValue));
    //            layout->addWidget(widget);
    //            
    //            indexMap->insert(item, findModelValue);
    //        }
    //    }

    //});





}

}
}

