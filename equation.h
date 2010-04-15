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

#ifndef EQUATION_H
#define EQUATION_H

#include <QWidget>
#include <QtGui>
class Equation : public QWidget
{
    Q_OBJECT
public:
    Equation(QWidget *parent = 0);
    ~Equation();
    QString getRel();
    int getNum();
    void setNum(int _nNum);
    void set(int _nNum=2,QString _r="=");
    void setRel(QString);
    double* getLeft();
    double* getRight();
    void setData(double* a,QString r,double b);
private:
    int nNum;
    int lastNum;
    QString tRelation;
    QVector<QLineEdit*> num;
    QLineEdit right;
    QVector<QLabel*> lblPlus;
    QVector<QLabel*> lblX;
    QComboBox relation;
    QHBoxLayout *mainLayout;
    void updateVectors();
private slots:
    void relationChanged(QString);
};

#endif // EQUATION_H
