#pragma once

#include <QWidget>

#include "../model/abstractlistmodel.h"
#include "../defineproperty.h"
#include "../functiontype.h"

namespace Qux {
namespace UI {

class GridView : public QWidget
{
	Q_OBJECT

	PROPERTY(const Model::AbstractListModel*, model, setModel)
	PROPERTY_NOCOMP(UnaryOp<Model::ModelItem>::Ret<QWidget*>::Type, widgetCreator, setWidgetCreator)
	PROPERTY(int, col, setCol)
	
public:
	GridView(QWidget* parent = nullptr);

};

}
}
