#ifndef WIDGET_H
#define WIDGET_H

#define WITH_EFFECTS

#include <QWidget>

#include "inputWidget.h"
#include "STable.h"
#include <fstream>
#include <QtGui>
#include <QtWebKit>
#define TYPE_ERR_MSG    tr("Перевірте правильність набору.")
#define ERR_TITLE       tr("Помилка.")
#define CALC_ERR_MSG    tr("Помилка при обрахунках.")
#define RESULT_SUCCESS 0
#define RESULT_CYCLE 1
#define RESULT_NO 2
#define RESULT_INF 3

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    int                 max(int,int);
    void                fillTables();
    int                 calc();
    int                 checkSum(double*);
    void                genFirstSTable(double**,double*,double*,QStringList*);
    void                mainProcedure(double**,double*,double*);
    void                displayFileError();

    bool                m_enableEffects;
    int                 m_result;
    bool                m_isTables;
    bool                m_isData;
    QPropertyAnimation* m_ani;
    inputWidget*        m_input;
    int                 nEq;
    double*             f;
    int                 nArgs;
    QStringList*        rel;
    QString             direction;
    QVector<STable*>    simplex;
    QQueue<QTableWidget*> tables;
    QVBoxLayout*        mainLayout;
    QScrollArea*        tablesScrollArea;
    QGroupBox*          tablesGroupBox;
    QGroupBox*          m_inputGB;
    QVBoxLayout*        tablesLayout;
    QGroupBox*          m_buttonGroupBox;
    QPushButton*        p2;
    QWebView*           m_help;
private slots:
    void                getDatasFromForm();
    void                getDatasFromFile();
    void                showHideInput(bool);
    void                myResize(int w,int h);
    void                myResize(QSize);
    void                deleteData();
    void                changeEffects(bool);
    void                showHelp();
};

#endif // WIDGET_H
