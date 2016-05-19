#include "test_qt.h"
#include <QtWidgets/QApplication>

#include "qt_windows.h"

#include "base/at_exit.h"
#include "base/command_line.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    base::CommandLine::Init(0, NULL);
    base::AtExitManager exit_manager;

    test_qt w;
    w.show();
    return a.exec();
}
