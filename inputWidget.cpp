//                                                                          //
//    This file is part of MMethod.                                         //
//                                                                          //
//    MMethod is free software: you can redistribute it and/or modify       //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    MMethod is distributed in the hope that it will be useful,            //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
//                                                                          //
//    You should have received a copy of the GNU General Public License     //
//    along with MMethod.  If not, see <http://www.gnu.org/licenses/>.      //
//                                                                          //

#include "inputWidget.h"
#include "equation.h"
#include <QApplication>

inputWidget::inputWidget(QWidget *parent):
        QWidget(parent)
{
    nArgs=2;
    nEq=1;
    mainLayout=new QVBoxLayout;
    topLayout=new QHBoxLayout;
    optLayout=new QVBoxLayout;
    optLayout->addWidget(new QLabel(tr("Кількість обмежень:")),1,Qt::AlignBottom);
    optLayout->addWidget(&boxEq,1);
    optLayout->addWidget(new QLabel(tr("Кількість аргументів:")),1,Qt::AlignBottom);
    optLayout->addWidget(&boxArgs);

    boxEq.setMinimum(1);
    boxEq.setValue(nEq);
    boxEq.setMaximum(50);

    boxArgs.setMinimum(2);
    boxArgs.setValue(nArgs);
    boxArgs.setMaximum(50);

    lastNEq=0;

    connect(&boxEq,SIGNAL(valueChanged(int)),this,SLOT(eqChanged(int)));
    connect(&boxArgs,SIGNAL(valueChanged(int)),this,SLOT(argsChanged(int)));

    func.setRel("max");
    topLayout->addWidget(new QLabel(tr("Функція:")));
    topLayout->addWidget(&func,1);
    topLayout->addLayout(optLayout);
    mainLayout->addLayout(topLayout);
    setLayout(mainLayout);

    set();
}
void inputWidget::setData(double**a, QStringList *r, double *b, double *f, QString d)
{
    for(int i=0;i<nEq;i++)
    {
        eq[i]->setData(a[i],(*r)[i],b[i]);
    }
    func.setData(f,d);
}

inputWidget::~inputWidget()
{
    for(int i=0;i<nEq;i++)
        delete eq[i];
    delete optLayout;
    delete topLayout;
    delete mainLayout;
}
QString inputWidget::getMM()
{
    return func.getRel();
}

QStringList* inputWidget::getRel()
{
    QStringList* s=new QStringList;
    for(int i=0;i<nEq;i++)
        s->append(eq[i]->getRel());
    return s;
}
int inputWidget::getNArgs()
{
    return nArgs;
}
int inputWidget::getNEq()
{
    return nEq;
}

double** inputWidget::getA()
{
    double **t=new double*[nEq];
    for(int i=0;i<nEq;i++){
        t[i]=eq[i]->getLeft();
        if(t[i]==NULL)
            return NULL;
    }
    return t;
}
double* inputWidget::getB()
{
    double* t=new double[nEq];
    double** a=new double*;
    for(int i=0;i<nEq;i++){
        *a=eq[i]->getRight();
        if(*a==NULL)
            return NULL;
        t[i]=**a;
    }
    return t;
}
double* inputWidget::getF()
{
    double *t=func.getF();
    if(t==NULL)
        return NULL;
    return t;
}

void inputWidget::eqChanged(int n)
{
    setEq(n);
    emit nEqChanged(QSize(0,0));
}
void inputWidget::argsChanged(int n)
{
    setArgs(n);
    emit nEqChanged(QSize(0,0));
}

void inputWidget::set(int _nEq, int _nArgs)
{
    boxEq.setValue(_nEq);
    boxArgs.setValue(_nArgs);
}
void inputWidget::setEq(int e)
{
    if(e<0)
        e=1;
    nEq=e;
    updateVector();
}
void inputWidget::setArgs(int a)
{
    if(a<1)
        a=2;
    nArgs=a;
    for(int i=0;i<nEq;i++)
        eq[i]->setNum(nArgs);
    func.setNum(nArgs);
}

void inputWidget::updateVector()
{
    if(lastNEq==nEq)
        return;
    if(lastNEq<nEq){
        eq.resize(nEq);
        for(int i=lastNEq;i<nEq;i++)
        {
            eq[i]=new Equation;
            eq[i]->set(nArgs,"=");
            mainLayout->addWidget(eq[i]);
        }
    }
    else
    {
        for(int i=lastNEq-1;i>=nEq;i--)
        {
            mainLayout->removeWidget(eq[i]);
            delete eq[i];
        }
        eq.resize(nEq);
    }
    lastNEq=nEq;
}
