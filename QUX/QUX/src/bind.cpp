#include "../include/bind.h"
#include "../include/metaobject.h"
#include "../include/ui/receiver.h"
#include "../include/utility.h"

namespace Qux {

namespace {

class SlotContainer : public QObject
{
    Q_OBJECT

public:
    SlotContainer(std::function<void ()> func, QObject* parent = nullptr)
        : m_func(func), QObject(parent)
    {}

public slots:
    void call()
    {
        m_func();
    }

private:
    std::function<void ()> m_func;

};

}

void bind(const QList<QPair<const QObject*, QString>>& propertyRefs, QObject* context, std::function<void (const QList<QVariant>& properties)> func)
{
    auto slotContainer = new SlotContainer([propertyRefs, func] () {
        func(convertList<QVariant>(propertyRefs, [] (const QPair<const QObject*, QString>& ref) -> QVariant {
            auto sender = ref.first;
            auto prop = sender->property(qPrintable(ref.second));
            if (!prop.isValid() && qobject_cast<const UI::Receiver*>(sender))
            {
                return sender->parent()->property(qPrintable(ref.second));
            }

            return prop;
        }));
    }, context);
    auto slot = findSlotByName(slotContainer, "call");

    foreach (auto ref, propertyRefs) {
        auto sender = ref.first;
        auto signalName = ref.second + "Changed";
        QObject::connect(sender, findSignalByName(sender, signalName), slotContainer, slot);
    }

    slotContainer->call();
}

}

#include "bind.moc"