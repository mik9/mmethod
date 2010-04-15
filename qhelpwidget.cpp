#include "qhelpwidget.h"

QHelpWidget::QHelpWidget(QWidget *parent):QWidget(parent)
{
    QHBoxLayout* l=new QHBoxLayout(this);
    view=new QWebView;
    l->addWidget(view);
    view->load(QUrl("help.html"));
    resize(QApplication::desktop()->width()/2,QApplication::desktop()->height()-100);
}
QHelpWidget::~QHelpWidget()
{
    delete view;
}
