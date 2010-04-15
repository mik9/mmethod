#include <QtGui>
#include "widget.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    Widget w;
    w.resize(0,0);
    w.show();
    return a.exec();
}
