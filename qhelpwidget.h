#ifndef QHELPWIDGET_H
#define QHELPWIDGET_H

#include <QtGui>
#include <QtWebKit>

class QHelpWidget : public QWidget
{
public:
    QHelpWidget(QWidget* parent=0);
    ~QHelpWidget();
private:
    QWebView* view;
};

#endif // QHELPWIDGET_H
