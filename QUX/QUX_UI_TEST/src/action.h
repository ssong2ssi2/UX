#pragma once

#include <QMetaType>
#include "Qux/include/flux/actionhelper.h"


enum ActionType
{
	AddItem,				// 메시지 추가 아이템 
	UpdateItem,				// 모든 숫자 + 1
	DeleteItem,
};
Q_DECLARE_METATYPE(ActionType)


namespace Action {
ACTION2(addItem, AddItem, QString, name, int, number)
ACTION0(updateItem, UpdateItem)
ACTION1(deleteItem, DeleteItem, QString, name)
}