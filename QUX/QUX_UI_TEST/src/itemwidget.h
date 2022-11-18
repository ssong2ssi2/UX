#pragma once

#include <QWidget>
#include "Qux/include/defineproperty.h"

#include "item.h"

class ItemWidget  : public QWidget
{
	Q_OBJECT
	PROPERTY_NOCOMP(Item, data, setData)
	PROPERTY(bool, selected, setSelected)
public:
	ItemWidget(Item data, QWidget* parent = nullptr);
	
};
