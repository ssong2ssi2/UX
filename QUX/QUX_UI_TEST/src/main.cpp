#include "QUX_UI_TEST.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QUX_UI_TEST w;
    w.show();
    return a.exec();
}
