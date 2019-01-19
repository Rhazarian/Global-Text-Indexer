/********************************************************************************
** Form generated from reading UI file 'add_directory_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_DIRECTORY_DIALOG_H
#define UI_ADD_DIRECTORY_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_add_directory_dialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *chooseDirectoryButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *add_directory_dialog)
    {
        if (add_directory_dialog->objectName().isEmpty())
            add_directory_dialog->setObjectName(QString::fromUtf8("add_directory_dialog"));
        add_directory_dialog->setWindowModality(Qt::NonModal);
        add_directory_dialog->resize(425, 139);
        verticalLayout = new QVBoxLayout(add_directory_dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(add_directory_dialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        chooseDirectoryButton = new QPushButton(add_directory_dialog);
        chooseDirectoryButton->setObjectName(QString::fromUtf8("chooseDirectoryButton"));

        horizontalLayout->addWidget(chooseDirectoryButton);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(add_directory_dialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(add_directory_dialog);

        QMetaObject::connectSlotsByName(add_directory_dialog);
    } // setupUi

    void retranslateUi(QDialog *add_directory_dialog)
    {
        add_directory_dialog->setWindowTitle(QApplication::translate("add_directory_dialog", "Add Directory", nullptr));
        chooseDirectoryButton->setText(QApplication::translate("add_directory_dialog", "Choose Dir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_directory_dialog: public Ui_add_directory_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_DIRECTORY_DIALOG_H
