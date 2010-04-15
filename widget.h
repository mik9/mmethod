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
    double              abs(double x);
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
