#ifndef QUX_UI_LISTVIEW_H
#define QUX_UI_LISTVIEW_H

#include "../model/abstractlistmodel.h"
#include "../defineproperty.h"
#include "../functiontype.h"

#include <QWidget>

namespace Qux {
namespace UI {

class ListView : public QWidget
{
    Q_OBJECT

    PROPERTY(const Model::AbstractListModel*, model, setModel)
    PROPERTY_NOCOMP(UnaryOp<Model::ModelItem>::Ret<QWidget*>::Type, widgetCreator, setWidgetCreator)
    
public:
    enum BOX_TYPE {
        VBOX,
        HBOX
    };

public:
    ListView(BOX_TYPE type, QWidget* parent = nullptr);

};

}
}

#endif
