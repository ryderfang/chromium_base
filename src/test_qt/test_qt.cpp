#include "test_qt.h"

#include "base/bind.h"

#include "qboxlayout.h"
#include "qmessagebox.h"

#include "base/strings/string_number_conversions.h"
#include "base/logging.h"

#include "third_party/sqlite3/sqlite3.h"

#include <vector>
#include <string>

test_qt::test_qt(QWidget *parent)
    : QWidget(parent) {
    ui.setupUi(this);

    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    progress_.resize(5);
    for (int i = 0; i < 5; ++i) {
        QHBoxLayout* hLayout = new QHBoxLayout();

        std::string t = "file" + base::IntToString(i + 1);
        progress_[i] = new QProgressBar(this);
        progress_[i]->setFixedSize(200, 10);
        progress_[i]->setValue(0);
        progress_[i]->setObjectName(QString::fromStdString(t));
        
        QPushButton* start_btn = new QPushButton(this);
        start_btn->setText(tr("Start!"));
        start_btn->setObjectName(QString::fromStdString(t));

        QPushButton* pause_btn = new QPushButton(this);
        pause_btn->setText(tr("Pause!"));
        pause_btn->setObjectName(QString::fromStdString(t));

        QPushButton* delete_btn = new QPushButton(this);
        delete_btn->setText(tr("Delete!"));
        delete_btn->setObjectName(QString::fromStdString(t));

        hLayout->addWidget(progress_[i], 0, Qt::AlignLeft);
        hLayout->addWidget(start_btn, 0, Qt::AlignLeft);
        hLayout->addWidget(pause_btn, 0, Qt::AlignLeft);
        hLayout->addWidget(delete_btn, 0, Qt::AlignLeft);
        layout->addLayout(hLayout);

        connect(start_btn, SIGNAL(clicked()), this, SLOT(sltStart()));
        connect(pause_btn, SIGNAL(clicked()), this, SLOT(sltPause()));
        connect(delete_btn, SIGNAL(clicked()), this, SLOT(sltDelete()));
    }

    start_all_ = new QPushButton(this);
    start_all_->setText(tr("Start All!"));
    pause_all_ = new QPushButton(this);
    pause_all_->setText(tr("Pause All!"));
    layout->addWidget(start_all_, 0, Qt::AlignLeft);
    layout->addWidget(pause_all_, 0, Qt::AlignLeft);

    connect(start_all_, SIGNAL(clicked()), this, SLOT(sltStartAll()));
    connect(pause_all_, SIGNAL(clicked()), this, SLOT(sltPauseAll()));

    work_loop_ = new WorkLoop();
    work_loop_->Init();

    qRegisterMetaType<int64>("int64");
    qRegisterMetaType<std::string>("std::string");
    connect(work_loop_.get(), SIGNAL(update_progress(const std::string&, int, int64)),
        this, SLOT(sltUpdateProgress(const std::string&, int, int64)));

    logging::LoggingSettings settings;
    settings.logging_dest = logging::LOG_TO_FILE;
    settings.log_file = L"E:\\fuck.log";
    logging::InitLogging(settings);

    LOG(INFO) << "test logging" << "\r\n";

    static bool init = false;
    if (!init) {
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

        init = true;
    }
}

test_qt::~test_qt() {
    work_loop_->Stop();
    //if (!task_manager_) return;
    //base::Thread* thread = task_manager_;
    //task_manager_ = nullptr;
    //delete thread;
}

void test_qt::sltStart() {
    QPushButton *sender = dynamic_cast<QPushButton*>(QObject::sender());
    QString name = sender->objectName();
    work_loop_->Start(name.toStdString());
}

void test_qt::sltPause() {
    QPushButton *sender = dynamic_cast<QPushButton*>(QObject::sender());
    QString name = sender->objectName();
    work_loop_->Pause(name.toStdString());
}

void test_qt::sltDelete() {
    QPushButton *sender = dynamic_cast<QPushButton*>(QObject::sender());
    QString name = sender->objectName();
    work_loop_->Delete(name.toStdString());
}

void test_qt::sltUpdateProgress(const std::string& name, int pos, int64 speed) {
    qDebug() << "||" << pos << " " << speed;
    for (int i = 0; i < 5; ++i) {
        if (progress_[i]->objectName().toStdString() == name) {
            progress_[i]->setValue(pos);
        }
    }
}

void test_qt::sltStartAll() {
    work_loop_->Start("file1");
    work_loop_->Start("file2");
    work_loop_->Start("file3");
    work_loop_->Start("file4");
    work_loop_->Start("file5");
}

void test_qt::sltPauseAll() {
    work_loop_->Pause("file1");
    work_loop_->Pause("file2");
    work_loop_->Pause("file3");
    work_loop_->Pause("file4");
    work_loop_->Pause("file5");
}
