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
