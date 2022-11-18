#include "QUX_UI_TEST.h"

#include <QFrame>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

#include "Qux/include/ui/listview.h"
#include "Itemstore.h"
#include "itemdbmiddelware.h"

// convert key model
#include "Qux/include/model/keymodeladapterlistmodel.h"

// UI Component
#include "component/containerlayout.h"
#include "component/vlayout.h"
#include "component/hlayout.h"

#include "Qux/include/utility/qvalue.h"
#include "Qux/include/ui/rcv.h"

// UI WIdget 
#include "itemwidget.h"

#include "action.h"
using Qux::UI::Receiver;
using Qux::UI::rcv;

using namespace Qux::Model;
using Qux::UI::ListView;

QUX_UI_TEST::QUX_UI_TEST(QWidget *parent)
    : QWidget(parent)
{
    initFluxModel();

    setupUI();
}


/*
* Flux 모델 초기화 
*/

void QUX_UI_TEST::initFluxModel()
{
    
    itemStore();
    new ItemDBMiddelware(this);
}

/*
* UI 초기화 
*/
void QUX_UI_TEST::setupUI()
{
    
    setFixedSize(300, 500);

    auto baseLayout = new ContainerLayout(this);

    {
        // <background
        auto backgroundFrame = new QFrame;
        backgroundFrame->setStyleSheet("background-color: #ffffff; border: 1px solid #ffffff;");
        baseLayout->addWidget(backgroundFrame);


    } // </background>



    {  // <main
              
        auto mainLayout = new VLayout;
        mainLayout->setContentsMargins(3, 3, 3, 3);
        baseLayout->addLayout(mainLayout);
        {// <container

            auto containerFrame = new QFrame;
            containerFrame->setObjectName("containerFrame");
            containerFrame->setStyleSheet("QFrame#containerFrame { background-color: #1A1C23; border: 1px solid #666666; border-radius: 3px;}");
            mainLayout->addWidget(containerFrame);

            auto itemListView = new ListView(ListView::BOX_TYPE::VBOX, containerFrame);


            {   // <listView
                auto containerLayout = new VLayout(containerFrame);
                containerLayout->setContentsMargins(0, 0, 0, 0);

                auto model = new KeyModelAdapterListModel(itemStore()->itemModel(), this);  // Convert List model      
                itemListView->setModel(model);

                // Model 추가시 위젯 생성 
                itemListView->setWidgetCreator([=](ModelItem data) -> QWidget* {
                    auto item = data.value<Item>();
                    return new ItemWidget(item);
                });
                containerLayout->addWidget(itemListView);

                // 마우스 이벤트 처리 
                auto dragStart = Qux::createQValue<int>(this);
                connect(rcv(containerFrame), &Receiver::mousePressed, [=](QMouseEvent* event) {
                    if (event->buttons() != Qt::LeftButton) return;

                    *dragStart = event->localPos().y();

                    foreach(auto child, itemListView->children()) {
                        auto widget = qobject_cast<QWidget*>(child);
                        if (!widget) continue;

                        widget->setProperty("selected", false);
                    }
                });

                connect(rcv(containerFrame), &Receiver::mouseMoved, [=](QMouseEvent* event) {
                    if (event->buttons() != Qt::LeftButton) return;


                    auto dragEnd = event->localPos().toPoint().y();
                    auto s = qMin(*dragStart, dragEnd);
                    auto e = qMax(*dragStart, dragEnd);

                    foreach(auto child, itemListView->children()) {
                        auto widget = qobject_cast<QWidget*>(child);
                        if (!widget) continue;

                        widget->setProperty("selected", widget->geometry().intersects(QRect(QPoint(0, s), QPoint(1, e))));
                    }
                });

            }// listview>
            

            mainLayout->addSpacing(10);

            auto buttonLayout = new HLayout;
            buttonLayout->setContentsMargins(3, 3, 3, 3);
            mainLayout->addLayout(buttonLayout);
            { // <button

                // 추가 버튼
                auto addButton = new QPushButton;
                addButton->setFixedSize(80, 30);
                addButton->setText(tr("Add"));
                buttonLayout->addWidget(addButton);
                buttonLayout->addSpacing(5);

                connect(addButton, &QPushButton::clicked, this, [=]() {
                    Action::addItem("song3", 4);
                    });

                // 업데이트 버튼
                auto updateButton = new QPushButton;
                updateButton->setFixedSize(80, 30);
                updateButton->setText(tr("Update"));
                buttonLayout->addWidget(updateButton);
                buttonLayout->addSpacing(5);

                connect(updateButton, &QPushButton::clicked, this, [=]() {
                    Action::updateItem();
                    });

                // 삭제 버튼
                auto deleteButton = new QPushButton;
                deleteButton->setFixedSize(80, 30);
                deleteButton->setText(tr("Delete"));
                buttonLayout->addWidget(deleteButton);

                connect(deleteButton, &QPushButton::clicked, this, [=]() {
                    foreach(auto child, itemListView->children()) {
                        auto widget = qobject_cast<QWidget*>(child);
                        if (!widget) continue;

                        auto selected = widget->property("selected").toBool();
                        
                        if (selected == true)
                        {
                            auto item = widget->property("data").value<Item>();
                            Action::deleteItem(item.title);
                        }
                    }
                 });


            }


        }// container>


        

        
    } // </main>


    // TEST 
    Action::addItem("song", 3);
    
}