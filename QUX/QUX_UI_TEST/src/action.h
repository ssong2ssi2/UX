#pragma once

#include <QMetaType>
#include "Qux/include/flux/actionhelper.h"


enum ActionType
{
	AddItem,				// �޽��� �߰� ������ 
	UpdateItem,				// ��� ���� + 1
	DeleteItem,
};
Q_DECLARE_METATYPE(ActionType)


namespace Action {
ACTION2(addItem, AddItem, QString, name, int, number)
ACTION0(updateItem, UpdateItem)
ACTION1(deleteItem, DeleteItem, QString, name)
}