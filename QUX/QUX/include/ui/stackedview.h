#ifndef QUX_FLUX_STACKEDVIEW_H
#define QUX_FLUX_STACKEDVIEW_H

#include "../model/abstractlistmodel.h"
#include "../model/keymodel.h"
#include "../defineproperty.h"
#include "../functiontype.h"

#include <QWidget>

namespace Qux{
namespace UI {

class StackedView : public QWidget
{
	Q_OBJECT

	PROPERTY(const Model::AbstractListModel*, model, setModel)
	PROPERTY_NOCOMP(UnaryOp<Model::ModelItem>::Ret<QWidget*>::Type, widgetCreator, setWidgetCreator)

	PROPERTY_NOCOMP(BinaryPredicate<Model::ModelItem>::Type, compareModelItem, setCompareModelItem)
	
	PROPERTY_NOCOMP(QString, select, setSelect)
	
public:
	StackedView(QWidget* parent = nullptr);
	
};

}
}


#endif //QUX_FLUX_STACKEDVIEW_H