#pragma once

#include "Qux/include/flux/store.h"
#include "Qux/include/singleton.h"
#include "Qux/include/defineproperty.h"
#include "QUX/include/model/keymodel.h"

#include "item.h"

class ItemStore : public Qux::Flux::Store
	, public Qux::Singleton<ItemStore>
{
	Q_OBJECT

	PROPERTY_NOCHANGE(Qux::Model::KeyModel*, itemModel)
	PROPERTY_NOCHANGE(int, index)
private:
	friend ItemStore& Singleton<ItemStore>::inst();
	ItemStore();

private slots:
	void reduce(const Qux::Flux::Action& action) override;
};

inline const ItemStore* itemStore() { return &ItemStore::cinst(); }

