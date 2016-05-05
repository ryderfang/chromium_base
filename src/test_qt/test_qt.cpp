#include "test_qt.h"

#include "base/bind.h"

#include "qboxlayout.h"
#include "qmessagebox.h"

#include <vector>
#include <string>

test_qt::test_qt(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);
    
    progress_.resize(3);
    start_btn_.resize(3);
    pause_btn_.resize(3);
    delete_btn_.resize(3);

    for (int i = 0; i < 3; ++i) {
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->setAlignment(Qt::AlignTop);
        progress_[i] = new QProgressBar(this);
        progress_[i]->setFixedSize(200, 10);
        progress_[i]->setValue(0);
        start_btn_[i] = new QPushButton(this);
        start_btn_[i]->setText(tr("Start!"));
        pause_btn_[i] = new QPushButton(this);
        pause_btn_[i]->setText(tr("Pause!"));
        delete_btn_[i] = new QPushButton(this);
        delete_btn_[i]->setText(tr("Delete!"));

        hLayout->addWidget(progress_[i], 0, Qt::AlignLeft);
        hLayout->addWidget(start_btn_[i], 0, Qt::AlignLeft);
        hLayout->addWidget(pause_btn_[i], 0, Qt::AlignLeft);
        hLayout->addWidget(delete_btn_[i], 0, Qt::AlignLeft);
        layout->addLayout(hLayout);
    }

    start_all_ = new QPushButton(this);
    start_all_->setText(tr("Start All!"));
    pause_all_ = new QPushButton(this);
    pause_all_->setText(tr("Pause All!"));
    layout->addWidget(start_all_, 0, Qt::AlignLeft);
    layout->addWidget(pause_all_, 0, Qt::AlignLeft);

    connect(start_btn_[0], SIGNAL(clicked()), this, SLOT(sltStart0()));
    connect(pause_btn_[0], SIGNAL(clicked()), this, SLOT(sltPause0()));
    connect(delete_btn_[0], SIGNAL(clicked()), this, SLOT(sltDelete0()));

    connect(start_btn_[1], SIGNAL(clicked()), this, SLOT(sltStart1()));
    connect(pause_btn_[1], SIGNAL(clicked()), this, SLOT(sltPause1()));
    connect(delete_btn_[1], SIGNAL(clicked()), this, SLOT(sltDelete1()));

    connect(start_btn_[2], SIGNAL(clicked()), this, SLOT(sltStart2()));
    connect(pause_btn_[2], SIGNAL(clicked()), this, SLOT(sltPause2()));
    connect(delete_btn_[2], SIGNAL(clicked()), this, SLOT(sltDelete2()));

    connect(start_all_, SIGNAL(clicked()), this, SLOT(sltStartAll()));
    connect(pause_all_, SIGNAL(clicked()), this, SLOT(sltPauseAll()));

    work_loop_ = new WorkLoop();
    work_loop_->Init();

    connect(work_loop_.get(), SIGNAL(update_progress(int)), this, SLOT(sltUpdateProgress(int)));
}

test_qt::~test_qt() {
    work_loop_->Stop();
    //if (!task_manager_) return;
    //base::Thread* thread = task_manager_;
    //task_manager_ = nullptr;
    //delete thread;
}

void test_qt::sltStart0() {
    work_loop_->Start("file1");
}

void test_qt::sltPause0() {
    work_loop_->Pause("file1");
}

void test_qt::sltDelete0() {

}

void test_qt::sltUpdateProgress(int pos) {
    progress_[0]->setValue(pos);
}

void test_qt::sltStart1() {
    
}

void test_qt::sltPause1() {

}

void test_qt::sltDelete1() {

}

void test_qt::sltStart2() {
    
}

void test_qt::sltPause2() {

}

void test_qt::sltDelete2() {

}

void test_qt::sltStartAll() {
    sltStart0();
    sltStart1();
    sltStart2();
}

void test_qt::sltPauseAll() {
    sltPause0();
    sltPause1();
    sltPause2();
}
