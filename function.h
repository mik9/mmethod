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

#ifndef FUNCTION_H
#define FUNCTION_H
#include <QWidget>
#include <QtGui>

class function : public QWidget
{
    Q_OBJECT
public:
    function(QWidget *parent = 0);
    ~function();
    QString getRel();
    int getNum();
    void setNum(int _nNum);
    void set(int _nNum=2,QString _r="=");
    void setRel(QString);
    double* getF();
    void setData(double* f,QString d);
private:
    int nNum;
    int lastNum;
    QString tRelation;
    QVector<QLineEdit*> num;
    QVector<QLabel*> lblPlus;
    QVector<QLabel*> lblX;
    QComboBox relation;
    QHBoxLayout *mainLayout;
    QLabel *lblZ;
    void updateVectors();
private slots:
    void relationChanged(QString);
};

#endif // FUNCTION_H
