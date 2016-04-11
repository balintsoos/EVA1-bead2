#include "minefieldwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MinefieldWidget w;
    w.show();

    return a.exec();
}
