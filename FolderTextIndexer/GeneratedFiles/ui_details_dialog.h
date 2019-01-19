/********************************************************************************
** Form generated from reading UI file 'details_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETAILS_DIALOG_H
#define UI_DETAILS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_details_dialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title_label;
    QLineEdit *file_path_line_edit;
    QTreeWidget *tree_widget;
    QPushButton *open_file_button;

    void setupUi(QDialog *details_dialog)
    {
        if (details_dialog->objectName().isEmpty())
            details_dialog->setObjectName(QString::fromUtf8("details_dialog"));
        details_dialog->resize(600, 500);
        verticalLayout = new QVBoxLayout(details_dialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        title_label = new QLabel(details_dialog);
        title_label->setObjectName(QString::fromUtf8("title_label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(16);
        title_label->setFont(font);
        title_label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title_label);

        file_path_line_edit = new QLineEdit(details_dialog);
        file_path_line_edit->setObjectName(QString::fromUtf8("file_path_line_edit"));

        verticalLayout->addWidget(file_path_line_edit);

        tree_widget = new QTreeWidget(details_dialog);
        tree_widget->setObjectName(QString::fromUtf8("tree_widget"));
        tree_widget->header()->setStretchLastSection(false);

        verticalLayout->addWidget(tree_widget);

        open_file_button = new QPushButton(details_dialog);
        open_file_button->setObjectName(QString::fromUtf8("open_file_button"));

        verticalLayout->addWidget(open_file_button);


        retranslateUi(details_dialog);

        QMetaObject::connectSlotsByName(details_dialog);
    } // setupUi

    void retranslateUi(QDialog *details_dialog)
    {
        details_dialog->setWindowTitle(QApplication::translate("details_dialog", "Lookup Details", nullptr));
        title_label->setText(QApplication::translate("details_dialog", "Lookup Details", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = tree_widget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("details_dialog", "Line Text", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("details_dialog", "Line No", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("details_dialog", "Matches", nullptr));
        open_file_button->setText(QApplication::translate("details_dialog", "Open File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class details_dialog: public Ui_details_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETAILS_DIALOG_H
