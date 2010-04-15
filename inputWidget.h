#ifndef inputWidget_H
#define inputWidget_H

#include <QWidget>
#include <QtGui>
#include "equation.h"
#include "function.h"

class inputWidget : public QWidget
{
    Q_OBJECT
public:
    inputWidget(QWidget *parent=0);
    ~inputWidget();
    void set(int _nEq=1,int _nArgs=2);
    void setEq(int e=1);
    void setArgs(int a=2);
    double** getA();
    double* getB();
    double* getF();
    int getNEq();
    int getNArgs();
    QStringList* getRel();
    QString getMM();
    void setData(double** a,QStringList* r, double *b, double *f, QString d);
private:
    int nEq;
    int nArgs;
    int lastNEq;
    QSpinBox boxEq;
    QSpinBox boxArgs;
    QVector<Equation*> eq;
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QVBoxLayout *optLayout;
    function func;
    void updateVector();
private slots:
    void argsChanged(int);
    void eqChanged(int);
signals:
    void nEqChanged(QSize);
};

#endif // inputWidget_H
