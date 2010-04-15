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

#include <QtGui>
#define m_basisColor QColor(165,241,250,255)
#define m_rColor QColor(Qt::green)
class STable
{
public:
                    STable(int _nEq,int _nArgs);
                    ~STable(void);

    void            calcSums(double*);  //вираховує суми
    QPoint*         findR();            //пошук розв'язувального елемента
    QTableWidget*   getTable();         //створює і поверта вказівник на таблицю

    QPoint*         p;                  //розв'язувальний елемент
    double**        A;                  //матриця А
    double*         B;                  //вектор В
    double*         C;                  //вектор Cb
    int*            basis;              //вектор базисів
    double*         sum1;               //вектор сум без М
    double*         sum2;               //вектор сум з М
    double          sumB1;              //сума В без М
    double          sumB2;              //сума В з М
private:
    bool            fp;                 //чи знайдений розв'язувальний елемент
    QStack<int>*    checkSum(double*);  //пошук найменших, повертає стек з номерами, якщо найменших декілька
    int             nEq;                //кількість рівнянь
    int             nArgs;              //кількість аргументів
};
