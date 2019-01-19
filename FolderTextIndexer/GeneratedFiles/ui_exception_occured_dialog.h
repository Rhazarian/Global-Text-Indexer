/********************************************************************************
** Form generated from reading UI file 'exception_occured_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXCEPTION_OCCURED_DIALOG_H
#define UI_EXCEPTION_OCCURED_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_exception_occured_dialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title_label;
    QTextBrowser *message_text_browser;
    QPushButton *ok_button;

    void setupUi(QDialog *exception_occured_dialog)
    {
        if (exception_occured_dialog->objectName().isEmpty())
            exception_occured_dialog->setObjectName(QString::fromUtf8("exception_occured_dialog"));
        exception_occured_dialog->resize(300, 150);
        verticalLayout = new QVBoxLayout(exception_occured_dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title_label = new QLabel(exception_occured_dialog);
        title_label->setObjectName(QString::fromUtf8("title_label"));
        title_label->setStyleSheet(QString::fromUtf8("font: 75 16pt \"Times New Roman\";"));
        title_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title_label);

        message_text_browser = new QTextBrowser(exception_occured_dialog);
        message_text_browser->setObjectName(QString::fromUtf8("message_text_browser"));
        message_text_browser->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(message_text_browser);

        ok_button = new QPushButton(exception_occured_dialog);
        ok_button->setObjectName(QString::fromUtf8("ok_button"));

        verticalLayout->addWidget(ok_button);


        retranslateUi(exception_occured_dialog);

        QMetaObject::connectSlotsByName(exception_occured_dialog);
    } // setupUi

    void retranslateUi(QDialog *exception_occured_dialog)
    {
        exception_occured_dialog->setWindowTitle(QApplication::translate("exception_occured_dialog", "Error", nullptr));
        title_label->setText(QApplication::translate("exception_occured_dialog", "Title", nullptr));
        message_text_browser->setHtml(QApplication::translate("exception_occured_dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Message</p></body></html>", nullptr));
        ok_button->setText(QApplication::translate("exception_occured_dialog", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class exception_occured_dialog: public Ui_exception_occured_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXCEPTION_OCCURED_DIALOG_H
