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
