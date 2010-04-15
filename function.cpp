#include "function.h"
#include <QtGui>

function::function(QWidget *parent):
        QWidget(parent)
{
    lastNum=0;
    relation.addItem(tr("min"));
    relation.addItem(tr("max"));
    connect(&relation,SIGNAL(currentIndexChanged(QString)),this,SLOT(relationChanged(QString)));
    mainLayout=new QHBoxLayout(this);
    lblZ=new QLabel(tr("z = "));
    mainLayout->addWidget(lblZ);
    set();
}
function::~function(){
    delete num[0];
    delete lblX[0];
    for(int i=1;i<nNum;i++){
        delete num[i];
        delete lblX[i];
        delete lblPlus[i-1];
    }
    delete mainLayout;
}
void function::setData(double *f, QString d)
{
    for(int i=0;i<nNum;i++)
    {
        num[i]->setText(QString::number(f[i]));
    }
    tRelation=d;
}

void function::set(int _nNum, QString _r){
    setNum(_nNum);
    setRel(_r);
}

QString function::getRel()
{
    return tRelation;
}
int function::getNum()
{
    return nNum;
}
void function::setNum(int _nNum)
{
    if(_nNum<1)
        return;
    nNum=_nNum;
    updateVectors();
}
void function::relationChanged(QString s)
{
    tRelation=s;
}
double* function::getF()
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
void function::setRel(QString s)
{
    tRelation=s;
    relation.setCurrentIndex(relation.findText(tRelation));
}

void function::updateVectors()
{
    if(nNum==lastNum)
        return;
    if(nNum>lastNum)
    {
        mainLayout->removeWidget(&relation);
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

    lastNum=nNum;
}
