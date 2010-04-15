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
