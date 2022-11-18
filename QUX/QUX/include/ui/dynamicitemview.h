#ifndef QUX_UI_DYNAMICITEMVIEW_H
#define QUX_UI_DYNAMICITEMVIEW_H

#include "../model/abstractlistmodel.h"
#include "../defineproperty.h"
#include "../functiontype.h"

#include <QWidget>

namespace Qux {
namespace UI {

class DynamicItemView : public QWidget
{
	Q_OBJECT

	PROPERTY(const Model::AbstractListModel*, model, setModel)
	PROPERTY(int, widgetWidth, setWidgetWidth)
	PROPERTY_NOCOMP(UnaryOp<Model::ModelItem>::Ret<QWidget*>::Type, widgetCreator, setWidgetCreator)
	PROPERTY(QRect, visibleArea, setVisibleArea)

public:
	DynamicItemView(QWidget* parent = nullptr);

};
}
}


#endif // QUX_UI_DYNAMICITEMVIEW_H