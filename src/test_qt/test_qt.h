#ifndef TEST_QT_H
#define TEST_QT_H

#define NOMINMAX

#include <QtWidgets/QWidget>
#include "qpushbutton.h"
#include "qprogressbar.h"

#include "ui_test_qt.h"
#include "work_loop.hpp"

#include "base/threading/thread.h"

#include <vector>

class test_qt : public QWidget
{
    Q_OBJECT

public:
    test_qt(QWidget *parent = 0);

    ~test_qt();

private:
    void DoWork();

public slots:
    void sltStart0();
    void sltStart1();
    void sltStart2();

    void sltPause0();
    void sltPause1();
    void sltPause2();

    void sltDelete0();
    void sltDelete1();
    void sltDelete2();

    void sltStartAll();
    void sltPauseAll();

private:
    scoped_refptr<WorkLoop> work_loop_;
    
    Ui::test_qtClass ui;

    std::vector<QProgressBar*> progress_;
  
    std::vector<QPushButton*> start_btn_;

    std::vector<QPushButton*> pause_btn_;

    std::vector<QPushButton*> delete_btn_;

    QPushButton* start_all_;

    QPushButton* pause_all_;
};

#endif // TEST_QT_H
