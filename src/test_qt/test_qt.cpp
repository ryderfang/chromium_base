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
    
    start_btn_ = new QPushButton(this);
    start_btn_->setText(tr("Start!"));
    pause_btn_ = new QPushButton(this);
    pause_btn_->setText(tr("Pause!"));
    continue_btn_ = new QPushButton(this);
    continue_btn_->setText(tr("Stop!"));
    
    layout->addWidget(start_btn_, Qt::AlignLeft);
    layout->addWidget(pause_btn_, Qt::AlignCenter);
    layout->addWidget(continue_btn_, Qt::AlignRight);
    
    connect(start_btn_, SIGNAL(clicked()), this, SLOT(sltStart()));
    connect(pause_btn_, SIGNAL(clicked()), this, SLOT(sltPause()));
    connect(continue_btn_, SIGNAL(clicked()), this, SLOT(sltContinue()));

    work_loop_ = new WorkLoop();
}

test_qt::~test_qt() {
    work_loop_->Stop();

    delete work_loop_;
    work_loop_ = nullptr;
}

void test_qt::sltStart() {
    static std::vector<std::string> file_list {
        "abcdefg",
        "1234567",
        "!@#$%^&"
    };

    for (auto f : file_list) {
        work_loop_->DoWork(f);
    }
}

void test_qt::sltPause() {
    work_loop_->Pause();
}

void test_qt::sltContinue() {
    work_loop_->Continue();
}