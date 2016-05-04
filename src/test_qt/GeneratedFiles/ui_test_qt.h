/********************************************************************************
** Form generated from reading UI file 'test_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_QT_H
#define UI_TEST_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test_qtClass
{
public:

    void setupUi(QWidget *test_qtClass)
    {
        if (test_qtClass->objectName().isEmpty())
            test_qtClass->setObjectName(QStringLiteral("test_qtClass"));
        test_qtClass->resize(600, 400);

        retranslateUi(test_qtClass);

        QMetaObject::connectSlotsByName(test_qtClass);
    } // setupUi

    void retranslateUi(QWidget *test_qtClass)
    {
        test_qtClass->setWindowTitle(QApplication::translate("test_qtClass", "test_qt", 0));
    } // retranslateUi

};

namespace Ui {
    class test_qtClass: public Ui_test_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_QT_H
