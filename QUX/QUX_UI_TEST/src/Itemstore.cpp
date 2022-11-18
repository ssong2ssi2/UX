#include "ItemStore.h"
#include "action.h"
#include "QUX/include/utility/variant.h"

ItemStore::ItemStore()
	: m_itemModel(new Qux::Model::KeyModel(this))
	, m_index(1)
{

}

void ItemStore::reduce(const Qux::Flux::Action& action)
{
	switch (action["type"].value<ActionType>()) {
	case AddItem:
	{
		//auto name = action["name"].toString();
		//auto number = action["number"].toInt();


		auto name = "TEST" + QString::number(m_index);
		auto number = m_index;
		
		Item i{ number, name };

		m_itemModel->insert(name, QVariant::fromValue(i));
		m_index++;
	}
	break;
	case UpdateItem:
	{
		for (auto item : Qux::fromQVariantList<Item>(m_itemModel->map().values())) {
			item.calc += 1;

			m_itemModel->insert(item.title, QVariant::fromValue(item));
		}


		
	}
	break;

	case DeleteItem:
	{
		auto title = action["name"].toString();
		if (m_itemModel->contains(title) == true)
			m_itemModel->remove(title);
	}
	}
}
