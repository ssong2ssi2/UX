#pragma once

#include <QMetaType>



struct Item {
	int calc;
	QString title;
};
Q_DECLARE_METATYPE(Item)

