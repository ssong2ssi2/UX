#include "itemwidget.h"
#include <QFrame>
#include <QLabel>



#include "component/containerlayout.h"
#include "component/vlayout.h"
#include "component/hlayout.h"

#include "Qux/include/bind.h"
using Qux::bind;

#define ACCESSOR(name) [] (auto a) { return a.name; }
#define ACCESSOR_OP(op, name) [=] (auto a) { return op a.name; }



ItemWidget::ItemWidget(Item data, QWidget *parent /*= nullptr*/)
	: QWidget(parent)
	, m_data(data)
	, m_selected(false)
{

	setAttribute(Qt::WA_TranslucentBackground);
	

	auto baseLayout = new ContainerLayout(this);
	baseLayout->setContentsMargins(0, 6, 0, 0);


	{
		// <background
		auto backgroundFrame = new QFrame;
		baseLayout->addWidget(backgroundFrame);

		bind<bool>(REF(this, selected), BOUND(backgroundFrame, styleSheet), [=](bool select) {
			return select == true ?
				"background-color: rgba(255, 255, 255, 25%); "
				: "background-color: #ffffff;";
		});

	}   // background>


	auto mainLayout = new HLayout;
	mainLayout->setContentsMargins(4, 4, 4, 4);
	baseLayout->addLayout(mainLayout);


	{
		auto selectFrame = new QFrame;
		selectFrame->setObjectName("selectFrame");
		selectFrame->setCursor(Qt::PointingHandCursor);

		

	}


	mainLayout->addStretch(1);		
	{ // <  main
		// 이름 라벨 
		auto nameLabel = new QLabel;
		nameLabel->setFixedWidth(120);
		nameLabel->setAlignment(Qt::AlignLeft);
		nameLabel->setStyleSheet("padding-bottom: 1px; background-color: transparent; color: #333333; font: bold normal 14px;");
		mainLayout->addWidget(nameLabel);
		mainLayout->addSpacing(13); 
		
		// model의 Title 정보 
		bind<Item>(REF(this, data), BOUND(nameLabel, text), ACCESSOR(title));
		
		// 숫자 라벨 
		auto numberLabel = new QLabel;
		numberLabel->setAlignment(Qt::AlignHCenter);
		numberLabel->setStyleSheet("padding-bottom: 1px; background-color: transparent; color: #333333; font: bold normal 14px;");
		mainLayout->addWidget(numberLabel);

		// model의 Number 정보 
		bind<Item>(REF(this, data), BOUND(numberLabel, text), ACCESSOR(calc));

	} // main>

	
	mainLayout->addStretch(1);
}


