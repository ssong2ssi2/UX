#include "itemdbmiddelware.h"
#include "action.h"

ItemDBMiddelware::ItemDBMiddelware(QObject *parent)
	: Qux::Flux::Middleware(parent)
{}

void ItemDBMiddelware::reduce(const Qux::Flux::Action& action)
{
	switch (action["type"].value<ActionType>()) {

	}
}
