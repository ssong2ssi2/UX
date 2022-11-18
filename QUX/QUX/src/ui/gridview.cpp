#include "../../include/ui/gridview.h"
#include "../../include/ui/rcv.h"

#include <QGridLayout>

using namespace Qux::Model;

namespace Qux {
namespace UI {

GridView::GridView(QWidget* parent)
	: m_model(nullptr), QWidget(parent)
    , m_col(0)
{
	auto layout = new QGridLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(2);
    
    


    auto rowcol = [=](int index) -> std::tuple<int, int> {
        auto row = index / m_col;
        auto col = index % m_col;

        return std::tie(row, col);
    };
	
    auto setupLayout = [=]() {
        if (!m_model || !m_widgetCreator) return;

        {
            // clear layout
            QLayoutItem* item;
            while (item = layout->takeAt(0)) {
                if (item->widget()) delete item->widget();
                delete item;
            }
        }

        int start = 0;
        for (auto iter = m_model->list().cbegin(); iter != m_model->list().cend(); iter++) {
            {
                
                auto result = rowcol(start++);
                auto row = std::get<0>(result);
                auto col = std::get<1>(result);

                layout->addWidget(m_widgetCreator(*iter));

            }
            
        }
        
    };

    connect(this, &GridView::modelAboutToBeChanged, [this]() {
        if (m_model != nullptr) {
            disconnect(m_model, 0, this, 0);
        }
    });

    connect(this, &GridView::modelChanged, [=]() {
        connect(m_model, &AbstractListModel::inserted, this, [=](int start, const QList<ModelItem>& list) {
            foreach(auto & value, list) {

                auto result = rowcol(start);
                auto row = std::get<0>(result);
                auto col = std::get<1>(result);

                layout->addWidget(m_widgetCreator(value), row, col);
            }
            });

        connect(m_model, &AbstractListModel::removed, this, [=](int start, int end) {
            for (; start <= end; end--) {
                //auto item = layout->takeAt(start);
                
                //auto result = rowcol(start);
                //auto row = std::get<0>(result);
                //auto col = std::get<1>(result);

                //auto item = layout->itemAtPosition(row, col);

                //layout->removeItem(item);

                //auto item = layout->takeAt(start);
                //item->widget()->deleteLater();
                //delete item;





                auto item = layout->itemAt(start);
                layout->removeItem(item);
                item->layout()->deleteLater();
                


                //if (item->widget() != nullptr)
                //{
                //    item->widget()->deleteLater();
                //}


                

                
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

                    auto result = rowcol(start);
                    auto row = std::get<0>(result);
                    auto col = std::get<1>(result);

                    layout->addWidget(m_widgetCreator(value), row, col);
                    
                }

                start++;
            }
            });

        setupLayout();
    });

    connect(this, &GridView::widgetCreatorChanged, setupLayout);
    connect(this, &GridView::colChanged, setupLayout);
}

}
}