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

#include "widget.h"
#include <float.h>
#include <math.h>

Widget::Widget(QWidget *parent) : QWidget (parent)
{
    mainLayout=new QVBoxLayout(this);
    m_input=new inputWidget;
    m_help=new QWebView;
    m_help->load(QUrl("help/help.html"));

    QHBoxLayout* v=new QHBoxLayout;
    QPushButton* p1=new QPushButton(tr("Почати розрахунки"));
    QPushButton* pF=new QPushButton(tr("Завантажити з файлу"));
    p2=new QPushButton(tr("Показати поля вводу"));
    p2->setCheckable(true);
    p2->setChecked(true);
    QPushButton* p3=new QPushButton(tr("Очистити результати"));
    QPushButton* pH=new QPushButton(tr("Допомога"));
    p1->setMinimumWidth(160);
    p2->setMinimumWidth(200);
    p3->setMinimumWidth(200);
    v->addWidget(p1);
    v->addWidget(pF);
    v->addWidget(p2);
    v->addWidget(p3);
    v->addWidget(pH);
    m_buttonGroupBox=new QGroupBox;
    m_buttonGroupBox->setLayout(v);
    connect(p1,SIGNAL(clicked()),this,SLOT(getDatasFromForm()));
    connect(p2,SIGNAL(clicked(bool)),this,SLOT(showHideInput(bool)));
    connect(p3,SIGNAL(clicked()),this,SLOT(deleteData()));
    connect(pF,SIGNAL(clicked()),this,SLOT(getDatasFromFile()));
    connect(pH,SIGNAL(clicked()),this,SLOT(showHelp()));
    connect(m_input,SIGNAL(nEqChanged(QSize)),this,SLOT(myResize(QSize)));

#ifdef WITH_EFFECTS
    QCheckBox* ch=new QCheckBox(tr("Увімкнути ефекти"));
    ch->setChecked(true);
    connect(ch,SIGNAL(clicked(bool)),this,SLOT(changeEffects(bool)));
    //v->addWidget(ch);
    m_enableEffects=true;
    m_ani=new QPropertyAnimation(this,"size");
#endif

    mainLayout->addWidget(m_buttonGroupBox,0,Qt::AlignTop);

    QVBoxLayout* m_inputL=new QVBoxLayout;
    m_inputL->addWidget(m_input);
    m_inputGB=new QGroupBox;
    m_inputGB->setLayout(m_inputL);
    mainLayout->addWidget(m_inputGB,0,Qt::AlignTop);
    mainLayout->addStretch(1);

    f=NULL;

    tablesScrollArea=NULL;
    tablesGroupBox=NULL;
    tablesLayout=NULL;

    m_isTables=false;
    m_isData=false;
}
void Widget::showHelp()
{
    m_help->resize(QApplication::desktop()->width()/2,QApplication::desktop()->height()-100);
    m_help->move(QApplication::desktop()->width()/2,0);
    m_help->show();
}

void Widget::myResize(int w, int h)
{
    myResize(QSize(w,h));
}
void Widget::myResize(QSize s)
{
#ifdef WITH_EFFECTS
    if(!m_enableEffects)
    {
        this->resize(s);
        return;
    }
    m_ani->stop();
    m_ani->setDuration(500);
    m_ani->setEasingCurve(QEasingCurve::InCubic);
    m_ani->setEndValue(s);
    m_ani->start();
#else
    resize(s);
#endif
}
void Widget::changeEffects(bool b)
{
    m_enableEffects=b;
}
void Widget::showHideInput(bool state)
{
    m_inputGB->setShown(state);
    if(!m_isTables)
        myResize(0,0);
}
Widget::~Widget()
{
    deleteData();
    delete mainLayout;
}
void Widget::deleteData()
{
    if(m_isData)
    {
        simplex.clear();
        if(f!=NULL)
            delete [] f;
        while(!tables.isEmpty())
        {
            QTableWidget* t=tables.dequeue();
            tablesLayout->removeWidget(t);
            delete t;
        }
        m_isTables=false;
        mainLayout->removeWidget(tablesScrollArea);
        if(tablesScrollArea!=NULL)
            delete tablesScrollArea;
        myResize(0,0);
    }
    m_isData=false;
    if(mainLayout->itemAt(2)==0)
        mainLayout->addStretch(1);
}
void Widget::getDatasFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Вибрати файл з даними..."),"","");
    QFile fin(fileName);
    fin.open(QFile::ReadOnly);
    bool check=true;
    nEq=QString(fin.readLine(10)).toInt(&check,10);
    if(!check)
    {
        displayFileError();
        return;
    }
    nArgs=QString(fin.readLine(10)).toInt(&check,10);
    if(!check)
    {
        displayFileError();
        return;
    }
    QStringList list=QString(fin.readLine(100)).split(" ",QString::SkipEmptyParts);
    double* tempF=new double[nArgs];
    for(int i=0;i<nArgs;i++)
    {
        tempF[i]=list[i].toDouble();
    }

    direction=list.last();
    if(direction.indexOf(tr("max"))!=-1)
    {
        direction=tr("max");
    }
    else if(direction.indexOf(tr("min"))!=-1)
    {
        direction=tr("min");
    }
    else
    {
        displayFileError();
        return;
    }

    double** tempA=new double*[nEq];
    double* tempB=new double[nEq];
    rel=new QStringList;
    for(int i=0;i<nEq;i++)
    {
        tempA[i]=new double[nArgs];
        QStringList list=QString(fin.readLine(100)).split(" ",QString::SkipEmptyParts);
        if(list.size()!=nArgs+2)
        {
            displayFileError();
            return;
        }
        for(int j=0;j<nArgs;j++)
        {
            tempA[i][j]=list[j].toDouble(&check);
            if(!check)
            {
                displayFileError();
                return;
            }
        }
        rel->append(list[nArgs]);
        tempB[i]=list.last().toDouble(&check);
        if(!check)
        {
            displayFileError();
            return;
        }
    }
    fin.close();
    m_input->set(nEq,nArgs);
    m_input->setData(tempA,rel,tempB,tempF,direction);

    //чистка
    for(int i=0;i<nEq;i++)
    {
        delete [] tempA[i];
    }
    delete [] tempA;
    delete [] tempB;
    delete [] tempF;
}
void Widget::displayFileError()
{
    QMessageBox::critical(NULL,tr(""),tr("Помилка читання файлу.\nМожливо неправильний формат данних."),QMessageBox::Ok);
}

void Widget::getDatasFromForm(){
    //отримуємо дані та перевіряємо
    double** tempA;
    double* tempB;
    double* tempF;

    if((tempA=m_input->getA())==NULL ||
       (tempB=m_input->getB())==NULL ||
       (tempF=m_input->getF())==NULL )
    {
        QMessageBox::critical(NULL,ERR_TITLE,TYPE_ERR_MSG,QMessageBox::Ok);
        return;
    }
    nEq=m_input->getNEq();
    nArgs=m_input->getNArgs();
    rel=m_input->getRel();
    direction=m_input->getMM();
    mainProcedure(tempA,tempB,tempF);
}
void Widget::mainProcedure(double** tempA, double* tempB, double* tempF)
{
    //перевірка нетут, або взагалі непотрібна
//    if(!(nEq<nArgs))
//    {
//        QMessageBox::critical(NULL,tr(""),tr("Невірні дані\nКількість невідомих повинна бути строго більше кількості рівнянь."),QMessageBox::Ok);
//        return;
//    }
    //перевіряємо обмеження
    for(int i=0;i<nEq;i++)
    {
        if(tempB[i]<0)
        {
            QMessageBox::critical(NULL,tr(""),tr("Невірні дані\nПеревірте вектор В."),QMessageBox::Ok);
            return;
        }
    }
    if(direction==tr("min"))
    {
        for(int i=0;i<nArgs;i++)
            tempF[i]=-tempF[i];
    }
    //чистимо минулі данні
    deleteData();

    //відправляємо дані на аналіз та створення першої симплекс таблиці
    genFirstSTable(tempA,tempF,tempB,rel);
    //запускаємо обчислення
    m_result=calc();
    showHideInput(false);
    fillTables();
    p2->setChecked(false);
}
void Widget::fillTables()
{
    mainLayout->removeItem(mainLayout->itemAt(2));
    m_isTables=true;
    tablesScrollArea=new QScrollArea;
    tablesGroupBox=new QGroupBox;
    tablesLayout=new QVBoxLayout;
    QString _f("z = ");
    QString restr;
    for(int i=0;i<nArgs+2*nEq;i++)
    {
        QString t;
        if(f[i]==-DBL_MAX)
            t=tr(" - M");
        else
        {
            if(i!=0)
            {
                if(f[i]<0)
                    t=tr(" - ");
                else
                    t=tr(" + ");
            }
            t+=QString::number(abs(f[i]));
        }
        t+=tr("x%1").arg(QString::number(i+1));
        restr+=tr("x%1, ").arg(QString::number(i+1));
        _f+=t;
    }
    _f+=tr("  -> ")+direction;
    restr.resize(restr.size()-2);
    restr+=tr(" >= 0");
    tablesLayout->addWidget(new QLabel(_f));
    tablesLayout->addWidget(new QLabel(restr));
    for(int i=0;i<simplex.count();i++)
    {
        tables.enqueue(simplex[i]->getTable());
        if(i!=0)
        {
            QPoint* r=simplex[i-1]->findR();
            if(r!=NULL)
            {
                tablesLayout->addWidget(new QLabel(tr("Найменша сума у %1 стовпцю, найменше відношення у %2 рядку.").arg(QString::number(r->y()+1),QString::number(r->x()+1))));
                tablesLayout->addWidget(new QLabel(tr("Вибраний розв'язувальний елемент: A[%1,%2] = %3").arg(QString::number(r->x()+1),QString::number(r->y()+1),QString::number(simplex[i-1]->A[r->x()][r->y()]))));
                tablesLayout->addWidget(new QLabel(tr("Перераховуємо таблицю: ")));
            }
            delete r;
        }
        tablesLayout->addWidget(tables.last());
    }
    switch(m_result)
    {
        case RESULT_SUCCESS:
            tablesLayout->addWidget(new QLabel(tr("Відповідь:")));
            for(int i=0;i<nEq;i++)
            {
                tablesLayout->addWidget(new QLabel(tr("x%1 = %2").arg(QString::number(simplex.last()->basis[i]+1),QString::number(simplex.last()->B[i]))));
            }
            tablesLayout->addWidget(new QLabel(tr("z = %1").arg(QString::number(simplex.last()->sumB1))));
            break;
        case RESULT_CYCLE:
            QMessageBox::critical(NULL,tr(""),tr("Зациклення."),QMessageBox::Ok);
            tablesLayout->addWidget(new QLabel(tr("Зациклювання.")));
            break;
        case RESULT_NO:
            QMessageBox::information(NULL,tr(""),tr("Розв'язок М-задачі знайдено, вихідна задача розв'язку немає."),QMessageBox::Ok);
            tablesLayout->addWidget(new QLabel(tr("Вихідна задача розв'язку немає.")));
            break;
        case RESULT_INF:
            QMessageBox::information(NULL,tr(""),tr("Цільова функція необмежена."),QMessageBox::Ok);
            tablesLayout->addWidget(new QLabel(tr("Цільова функція необмежена.")));
            break;
    }

    tablesGroupBox->setLayout(tablesLayout);
    tablesScrollArea->setWidget(tablesGroupBox);
    tablesScrollArea->setWidgetResizable(true);
    tablesScrollArea->setMinimumWidth(tables.last()->minimumWidth()+80);

    mainLayout->addWidget(tablesScrollArea,2);
    move(pos().x(),0);
    myResize(size().width(),QApplication::desktop()->height()-100);
    m_isTables=true;
}
double Widget::abs(double x)
{
    return (x<0)?-x:x;
}

int Widget::calc()
{
    while(true)
    {
        //створюємо простір для ще одного кроку
        simplex.append(new STable(nEq,nArgs));

        STable* curr=simplex.last();
        STable* prev=simplex[simplex.count()-2];

        QPoint* r=prev->findR();
        if(r==NULL)
        {
            delete simplex.last();
            simplex.resize(simplex.count()-1);
            for(int i=0;i<nEq;i++)
                if(simplex.last()->basis[i]>=nArgs)
                    if(simplex.last()->C[i]!=0)
                        return RESULT_NO;
            return RESULT_SUCCESS;
        }
        if(prev->A[r->x()][r->y()]<0)
        {
            simplex.pop_back();
            return RESULT_INF;
        }
        //обновляєм базис
        for(int i=0;i<nEq;i++)
            curr->basis[i]=prev->basis[i];
        curr->basis[r->x()]=r->y();
        //готово

        //перевіряємо зациклювання
        for(int i=0;i<simplex.count()-1;i++)
        {
            bool c=true;
            for(int j=0;j<nEq;j++)
            {
                if(curr->basis[j]!=simplex[i]->basis[j])
                {
                    c=false;
                    break;
                }
            }
            if(c)
            {
                simplex.pop_back();
                return RESULT_CYCLE;
            }
        }

        //обновляєм С
        for(int i=0;i<nEq;i++)
            curr->C[i]=f[curr->basis[i]];
        //готово

        //перерахомуємо А
        for(int i=0;i<nEq;i++)
        {
            for(int j=0;j<nArgs+2*nEq;j++)
            {
                if(i!=r->x())
                {

                    curr->A[i][j]=(prev->A[i][j]*prev->A[r->x()][r->y()]-prev->A[r->x()][j]*prev->A[i][r->y()])/prev->A[r->x()][r->y()];
                }
                else
                {
                    curr->A[i][j]=prev->A[i][j]/prev->A[r->x()][r->y()];
                }
            }
            if(i!=r->x())
            {
                curr->B[i]=(prev->B[i]*prev->A[r->x()][r->y()]-prev->B[r->x()]*prev->A[i][r->y()])/prev->A[r->x()][r->y()];
            }
            else
            {
                curr->B[i]=prev->B[i]/prev->A[r->x()][r->y()];
            }
        }
        //готово

        //війна з надмірною точністю, переписуємо базисні вектори
        for(int i=0;i<nEq;i++)
        {
            for(int j=0;j<nEq;j++)
            {
                curr->A[j][curr->basis[i]]=0;
            }
            curr->A[i][curr->basis[i]]=1;
        }

        //рахуємо суми
        curr->calcSums(f);
    }
}
void Widget::genFirstSTable(double** _t, double* _f,double* _b, QStringList *r)
{
    m_isData=true;
    simplex.resize(1);
    simplex[0]=new STable(nEq,nArgs);

    f=new double[nArgs+2*nEq];
    //копіюємо основну частину матриць в нову
    for(int i=0;i<nEq;i++)
    {
        for(int j=0;j<nArgs;j++)
            simplex[0]->A[i][j]=_t[i][j];
        simplex[0]->B[i]=_b[i];
    }
    for(int i=0;i<nArgs;i++)
        f[i]=_f[i];

    //розставляємо додаткові змінні для створення рівностей
    for(int i=0;i<nEq;i++)
    {
        for(int j=0;j<nEq;j++)
            simplex[0]->A[j][nArgs+i]=0;
        f[nArgs+i]=0;
        if((*r)[i]=="<=")
            simplex[0]->A[i][nArgs+i]=1;
        else if((*r)[i]==">=")
            simplex[0]->A[i][nArgs+i]=-1;
        else
            simplex[0]->A[i][nArgs+i]=0;
    }
    //додаємо N еМок, які будуть уведені в базис, заповнюємо базис, вектор С
    for(int i=0;i<nEq;i++)
    {
        for(int j=0;j<nEq;j++)
            simplex[0]->A[j][nArgs+nEq+i]=0;
        simplex[0]->A[i][nArgs+nEq+i]=1;
        f[nArgs+nEq+i]=-DBL_MAX ;
        simplex[0]->basis[i]=nArgs+nEq+i;
        simplex[0]->C[i]=f[simplex[0]->basis[i]];
    }

    simplex[0]->calcSums(f);

    //чистка
    for(int i=0;i<nEq;i++)
        delete [] _t[i];
    delete [] _t;
    delete [] _f;
    delete [] _b;
    //кінець чистки
}
