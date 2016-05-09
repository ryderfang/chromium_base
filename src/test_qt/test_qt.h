#ifndef TEST_QT_H
#define TEST_QT_H

#include <QtWidgets/QWidget>
#include "qpushbutton.h"
#include "qprogressbar.h"

#include "ui_test_qt.h"
#include "work_loop.hpp"

#include <vector>

class test_qt 
    : public QWidget
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

    void sltDelete();

    void sltStartAll();
    void sltPauseAll();

    void sltUpdateProgress(const std::string& name, int pos, int64 speed);

private:
    scoped_refptr<WorkLoop> work_loop_;
    
    Ui::test_qtClass ui;

    std::vector<QProgressBar*> progress_;

    QPushButton* start_all_;

    QPushButton* pause_all_;
};

#endif // TEST_QT_H
