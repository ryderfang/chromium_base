#include "test_qt.h"

#include "base/bind.h"

#include "qboxlayout.h"
#include "qmessagebox.h"

#include "base/strings/string_number_conversions.h"

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
    //work_loop_->Start("file1");
    //for (int i = 0; i < 32; ++i) {
    //    std::string t = "file" + base::IntToString(i);
    //    work_loop_->Start(t);
    //}

    VideoInfo f1("file1");
    for (int i = 0; i < 10; ++i) {
        std::string t = "file1_p" + base::IntToString(i);
        f1.piece.push_back(t);
    }

    VideoInfo f2("file2");
    for (int i = 0; i < 2; ++i) {
        std::string t = "file2_p" + base::IntToString(i);
        f2.piece.push_back(t);
    }

    VideoInfo f3("file3");
    for (int i = 0; i < 14; ++i) {
        std::string t = "file3_p" + base::IntToString(i);
        f3.piece.push_back(t);
    }

    VideoInfo f4("file4");
    for (int i = 0; i < 22; ++i) {
        std::string t = "file4_p" + base::IntToString(i);
        f4.piece.push_back(t);
    }

    VideoInfo f5("file5");
    for (int i = 0; i < 8; ++i) {
        std::string t = "file5_p" + base::IntToString(i);
        f5.piece.push_back(t);
    }

    work_loop_->PushData(f1.file_name, f1);
    work_loop_->PushData(f2.file_name, f2);
    work_loop_->PushData(f3.file_name, f3);
    work_loop_->PushData(f4.file_name, f4);
    work_loop_->PushData(f5.file_name, f5);

    work_loop_->Start(f1.file_name);
    work_loop_->Start(f2.file_name);
    work_loop_->Start(f3.file_name);
    work_loop_->Start(f4.file_name);
    work_loop_->Start(f5.file_name);
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
