#pragma once

#include "Qux/include/flux/middleware.h"

class ItemDBMiddelware : public Qux::Flux::Middleware
{
	Q_OBJECT

public:
	ItemDBMiddelware(QObject *parent);

private slots:
	void reduce(const Qux::Flux::Action& action) override;
};
