#ifndef TEST_QT_H
#define TEST_QT_H

#define NOMINMAX

#include <QtWidgets/QWidget>
#include "qpushbutton.h"

#include "ui_test_qt.h"
#include "work_loop.hpp"

class test_qt : public QWidget
{
    Q_OBJECT

public:
    test_qt(QWidget *parent = 0);

    ~test_qt();

private:
    void DoWork();

public slots:
    void sltStart();

    void sltPause();

    void sltContinue();

private:
    WorkLoop* work_loop_;

    Ui::test_qtClass ui;
  
    QPushButton* start_btn_;

    QPushButton* pause_btn_;

    QPushButton* continue_btn_;
};

#endif // TEST_QT_H
