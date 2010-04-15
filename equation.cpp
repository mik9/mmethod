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

#include "equation.h"
#include <QtGui>

Equation::Equation(QWidget *parent):
        QWidget(parent)
{
    lastNum=0;
    relation.addItem(tr("="));
    relation.addItem(tr("<="));
    relation.addItem(tr(">="));
    connect(&relation,SIGNAL(currentIndexChanged(QString)),this,SLOT(relationChanged(QString)));
    right.setMinimumWidth(50);
    mainLayout=new QHBoxLayout(this);
    set();
}
Equation::~Equation(){
    delete num[0];
    delete lblX[0];
    for(int i=1;i<nNum;i++){
        delete num[i];
        delete lblX[i];
        delete lblPlus[i-1];
    }
    delete mainLayout;
}
void Equation::setData(double *a, QString r, double b)
{
    if(r==tr("="))
        relation.setCurrentIndex(0);
    else
        if(r==tr("<="))
            relation.setCurrentIndex(1);
    else if(r==tr(">="))
        relation.setCurrentIndex(2);
    for(int i=0;i<nNum;i++)
    {
        num[i]->setText(QString::number(a[i]));
    }
    right.setText(QString::number(b));
}

void Equation::set(int _nNum, QString _r)
{
    setNum(_nNum);
    setRel(_r);
}

QString Equation::getRel()
{
    return tRelation;
}
int Equation::getNum()
{
    return nNum;
}
void Equation::setNum(int _nNum)
{
    if(_nNum<1)
        return;
    nNum=_nNum;
    updateVectors();
}
void Equation::relationChanged(QString s)
{
    tRelation=s;
}
double* Equation::getLeft()
{
    double *n=new double[nNum];
    bool check=true;
    for(int i=0;i<nNum;i++)
    {
        n[i]=num[i]->text().toDouble(&check);
        if(!check)
        {
            delete [] n;
            return NULL;
        }
    }
    return n;
}
double* Equation::getRight()
{
    bool check=true;
    double* r=new double;
    *r=right.text().toDouble(&check);
    return ((check)?r:NULL);
}
void Equation::setRel(QString s)
{
    tRelation=s;
    relation.setCurrentIndex(relation.findText(tRelation));
}

void Equation::updateVectors()
{
    if(nNum==lastNum)
        return;
    if(nNum>lastNum)
    {
        mainLayout->removeWidget(&relation);
        mainLayout->removeWidget(&right);
        lblPlus.resize(nNum-1);
        num.resize(nNum);
        lblX.resize(nNum);
        for(int i=lastNum;i<nNum;i++)
        {
            if(i!=0)
            {
                lblPlus[i-1]=new QLabel(tr("+"));
                mainLayout->addWidget(lblPlus[i-1]);
            }
            num[i]=new QLineEdit;
            num[i]->setMinimumWidth(50);
            mainLayout->addWidget(num[i],Qt::AlignRight);
            lblX[i]=new QLabel(tr("x%1").arg(QString::number(i+1)));
            mainLayout->addWidget(lblX[i]);
        }
    }
    else
    {
        for(int i=lastNum-1;i>=nNum;i--)
        {
            mainLayout->removeWidget(num[i]);
            if(i!=0)
            {
                mainLayout->removeWidget(lblPlus[i-1]);
                delete lblPlus[i-1];
            }
            mainLayout->removeWidget(lblX[i]);
            delete lblX[i];
            delete num[i];
        }
        num.resize(nNum);
    }
    mainLayout->addWidget(&relation);
    mainLayout->addWidget(&right);

    lastNum=nNum;
}
