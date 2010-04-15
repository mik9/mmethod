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

#include "STable.h"
#include <float.h>

#define COL_W 50
#define ROW_H 25

STable::STable(int _nEq,int _nArgs)
{
    nEq=_nEq;
    nArgs=_nArgs;
    A=new double*[nEq];
    for(int i=0;i<nEq;i++)
        A[i]=new double[nArgs+2*nEq];
    B=new double[nEq];
    basis=new int[nEq];
    C=new double[nEq];
    sum1=new double[nArgs+2*nEq];
    sum2=new double[nArgs+2*nEq];
    fp=false;
    p=NULL;
}
STable::~STable(void)
{
    delete [] B;
    delete [] C;
    delete [] basis;
    delete [] sum1;
    delete [] sum2;
    for(int z=0;z<nEq;z++){
        delete [] A[z];
    }
    delete [] A;
}
void STable::calcSums(double* f)
{
    for(int i=0;i<nArgs+2*nEq;i++)
    {
            sum1[i]=0;
            for(int j=0;j<nEq;j++)
            {
                double AA=A[j][i];
                double CC=(C[j]==-DBL_MAX ) ? 0 : C[j];
                sum1[i]+=AA*CC;
            }
            sum1[i]-=f[i];
    }
    sumB1=0;
    for(int i=0;i<nEq;i++)
    {
            double CC=(C[i]==-DBL_MAX ) ? 0 : C[i];
            sumB1+=B[i]*CC;
    }

    for(int i=0;i<nArgs+2*nEq;i++)
    {
            sum2[i]=0;
            for(int j=0;j<nEq;j++)
            {
                bool b=false;
                for(int z=0;z<nEq;z++)
                    if(basis[z]==i)
                    {
                        b=true;
                        break;
                    }
                if(b)
                    break;
                    double AA=A[j][i];
                    double CC=(C[j]==-DBL_MAX ) ? -1 : 0;
                    sum2[i]+=AA*CC;
            }
    }
    sumB2=0;
    for(int i=0;i<nEq;i++)
    {
            double CC=(C[i]==-DBL_MAX ) ? -1 : 0;
            sumB2+=B[i]*CC;
    }
}
QStack<int>* STable::checkSum(double *s)
{
    QStack<int>* min=new QStack<int>;
    min->push(0);
    for(int i=1;i<nArgs+2*nEq;i++)
    {
        if(s[i]<s[min->last()])
        {
            min->clear();
            min->push(i);
        }
        else if(s[i]==s[min->last()])
        {
            min->push(i);
        }
    }
    if(s[min->last()]<0)
    {
        return min;
    }
    else
    {
        delete min;
        return new QStack<int>;
    }
}
QPoint* STable::findR()
{
    if(!fp)
    {
        fp=true;
        QStack<int>* minSum;
        QStack<int>* minSum1;
        QStack<int>* minSum2;

        if(!(minSum2=checkSum(sum2))->isEmpty()){
            minSum=minSum2;
        }
        else if(!(minSum1=checkSum(sum1))->isEmpty())
        {
            minSum=minSum1;
        }
        else
        {
            return NULL;
        }
        while(!minSum->isEmpty())
        {
            int min=minSum->pop();
            int minEq=0;
            bool check=false;
            if(A[minEq][min]>0)
                check=true;
            for(int i=1;i<nEq;i++)
            {
                if(
                        (
                                (B[i]/A[i][min] < B[minEq]/A[minEq][min])
                                && (A[i][min] > 0)
                        )
                        || (A[minEq][min]<0)
                  )
                {
                    minEq=i;
                    check=true;
                }
            }
            if(check)
            {
                return (p = new QPoint(minEq,min));
            }
        }
    }
    return p;
}
QTableWidget* STable::getTable()
{
    QTableWidget* t=new QTableWidget(nEq+2,nArgs+2*nEq+3);

    QStringList labels;
    labels.append(QObject::tr("Базис"));
    labels.append(QObject::tr("C"));
    labels.append(QObject::tr("B"));
    for(int j=0;j<nArgs+2*nEq;j++){
        labels.append(QObject::tr("A")+QString::number(j+1));
    }
    t->setHorizontalHeaderLabels(labels);

    for(int i=0;i<nEq;i++)
    {
        t->setItem(i,0,new QTableWidgetItem(QString::number(basis[i]+1)));
        QString c=(new QString)->sprintf("%3.3f",C[i]);
        if(C[i]==-DBL_MAX )
            c="-M";
        t->setItem(i,1,new QTableWidgetItem(c));
        t->setItem(i,2,new QTableWidgetItem((new QString)->sprintf("%3.3f",B[i])));
    }
    QPoint *r=findR();
    for(int i=0;i<nEq;i++)
    {
        for(int j=0;j<nArgs+2*nEq;j++){
            QTableWidgetItem* it=new QTableWidgetItem((new QString)->sprintf("%3.3f",A[i][j]));
            t->setItem(i,j+3,it);
        }
    }
    if(r!=NULL)
    {
        t->item(r->x(),r->y()+3)->setBackgroundColor(m_rColor);
    }
    for(int i=0;i<nEq;i++)
    {
        for(int j=0;j<nEq;j++)
        {
            t->item(i,basis[j]+3)->setBackgroundColor(m_basisColor);
        }
    }

    for(int i=0;i<nArgs+2*nEq;i++)
    {
        QString c=(new QString)->sprintf("%3.3f",sum1[i]);
        if(sum1[i]==DBL_MAX )
            c="M";
        t->setItem(nEq  ,i+3,new QTableWidgetItem(c));
        t->setItem(nEq+1,i+3,new QTableWidgetItem((new QString)->sprintf("%3.3f",sum2[i])));
    }
    t->setItem(nEq  ,2,new QTableWidgetItem((new QString)->sprintf("%3.3f",sumB1)));
    t->setItem(nEq+1,2,new QTableWidgetItem((new QString)->sprintf("%3.3f",sumB2)));

    for(int i=1;i<nArgs+2*nEq+3;i++)
        t->setColumnWidth(i,COL_W);
    t->setColumnWidth(0,COL_W*2);
    for(int i=0;i<nEq+2;i++)
        t->setRowHeight(i,ROW_H);

    t->setMinimumWidth(COL_W*t->columnCount()+50);
    t->setMinimumHeight(ROW_H*t->rowCount()+30);

    return t;
}
