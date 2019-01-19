/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FolderTextIndexerClass
{
public:
    QWidget *central_widget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *left_widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *left_widget_upper_horizontal_layout;
    QLabel *indexed_dirs_label;
    QPushButton *add_dir_button;
    QListWidget *indexed_dirs_list_widget;
    QHBoxLayout *left_widget_lower_horizontal_layout;
    QGroupBox *dir_indexing_progress_group_box;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *queued_dirs_counter_group_box;
    QHBoxLayout *horizontalLayout_3;
    QLCDNumber *queued_dirs_counter_lcd_number;
    QProgressBar *dir_indexing_progress_bar;
    QWidget *right_widget;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lookup_pattern_line_edit;
    QTreeWidget *matched_files_tree_widget;
    QGroupBox *lookup_progress_group_box;
    QHBoxLayout *horizontalLayout;
    QProgressBar *lookup_progress_bar;

    void setupUi(QMainWindow *FolderTextIndexerClass)
    {
        if (FolderTextIndexerClass->objectName().isEmpty())
            FolderTextIndexerClass->setObjectName(QString::fromUtf8("FolderTextIndexerClass"));
        FolderTextIndexerClass->resize(1200, 800);
        central_widget = new QWidget(FolderTextIndexerClass);
        central_widget->setObjectName(QString::fromUtf8("central_widget"));
        verticalLayout = new QVBoxLayout(central_widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(central_widget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        left_widget = new QWidget(splitter);
        left_widget->setObjectName(QString::fromUtf8("left_widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(left_widget->sizePolicy().hasHeightForWidth());
        left_widget->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(left_widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        left_widget_upper_horizontal_layout = new QHBoxLayout();
        left_widget_upper_horizontal_layout->setSpacing(6);
        left_widget_upper_horizontal_layout->setObjectName(QString::fromUtf8("left_widget_upper_horizontal_layout"));
        indexed_dirs_label = new QLabel(left_widget);
        indexed_dirs_label->setObjectName(QString::fromUtf8("indexed_dirs_label"));
        indexed_dirs_label->setStyleSheet(QString::fromUtf8("font: 12pt \"Times New Roman\";"));
        indexed_dirs_label->setScaledContents(false);
        indexed_dirs_label->setWordWrap(false);

        left_widget_upper_horizontal_layout->addWidget(indexed_dirs_label);

        add_dir_button = new QPushButton(left_widget);
        add_dir_button->setObjectName(QString::fromUtf8("add_dir_button"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(add_dir_button->sizePolicy().hasHeightForWidth());
        add_dir_button->setSizePolicy(sizePolicy2);

        left_widget_upper_horizontal_layout->addWidget(add_dir_button);


        verticalLayout_2->addLayout(left_widget_upper_horizontal_layout);

        indexed_dirs_list_widget = new QListWidget(left_widget);
        indexed_dirs_list_widget->setObjectName(QString::fromUtf8("indexed_dirs_list_widget"));

        verticalLayout_2->addWidget(indexed_dirs_list_widget);

        left_widget_lower_horizontal_layout = new QHBoxLayout();
        left_widget_lower_horizontal_layout->setSpacing(6);
        left_widget_lower_horizontal_layout->setObjectName(QString::fromUtf8("left_widget_lower_horizontal_layout"));
        dir_indexing_progress_group_box = new QGroupBox(left_widget);
        dir_indexing_progress_group_box->setObjectName(QString::fromUtf8("dir_indexing_progress_group_box"));
        dir_indexing_progress_group_box->setEnabled(true);
        horizontalLayout_4 = new QHBoxLayout(dir_indexing_progress_group_box);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetDefaultConstraint);
        queued_dirs_counter_group_box = new QGroupBox(dir_indexing_progress_group_box);
        queued_dirs_counter_group_box->setObjectName(QString::fromUtf8("queued_dirs_counter_group_box"));
        horizontalLayout_3 = new QHBoxLayout(queued_dirs_counter_group_box);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        queued_dirs_counter_lcd_number = new QLCDNumber(queued_dirs_counter_group_box);
        queued_dirs_counter_lcd_number->setObjectName(QString::fromUtf8("queued_dirs_counter_lcd_number"));
        queued_dirs_counter_lcd_number->setFrameShape(QFrame::NoFrame);
        queued_dirs_counter_lcd_number->setSmallDecimalPoint(false);
        queued_dirs_counter_lcd_number->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_3->addWidget(queued_dirs_counter_lcd_number);


        horizontalLayout_4->addWidget(queued_dirs_counter_group_box);

        dir_indexing_progress_bar = new QProgressBar(dir_indexing_progress_group_box);
        dir_indexing_progress_bar->setObjectName(QString::fromUtf8("dir_indexing_progress_bar"));
        dir_indexing_progress_bar->setEnabled(true);
        dir_indexing_progress_bar->setValue(0);

        horizontalLayout_4->addWidget(dir_indexing_progress_bar);


        left_widget_lower_horizontal_layout->addWidget(dir_indexing_progress_group_box);


        verticalLayout_2->addLayout(left_widget_lower_horizontal_layout);

        splitter->addWidget(left_widget);
        right_widget = new QWidget(splitter);
        right_widget->setObjectName(QString::fromUtf8("right_widget"));
        sizePolicy1.setHeightForWidth(right_widget->sizePolicy().hasHeightForWidth());
        right_widget->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(right_widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lookup_pattern_line_edit = new QLineEdit(right_widget);
        lookup_pattern_line_edit->setObjectName(QString::fromUtf8("lookup_pattern_line_edit"));

        verticalLayout_3->addWidget(lookup_pattern_line_edit);

        matched_files_tree_widget = new QTreeWidget(right_widget);
        matched_files_tree_widget->setObjectName(QString::fromUtf8("matched_files_tree_widget"));
        matched_files_tree_widget->header()->setStretchLastSection(false);

        verticalLayout_3->addWidget(matched_files_tree_widget);

        lookup_progress_group_box = new QGroupBox(right_widget);
        lookup_progress_group_box->setObjectName(QString::fromUtf8("lookup_progress_group_box"));
        horizontalLayout = new QHBoxLayout(lookup_progress_group_box);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lookup_progress_bar = new QProgressBar(lookup_progress_group_box);
        lookup_progress_bar->setObjectName(QString::fromUtf8("lookup_progress_bar"));
        lookup_progress_bar->setValue(0);

        horizontalLayout->addWidget(lookup_progress_bar);


        verticalLayout_3->addWidget(lookup_progress_group_box);

        splitter->addWidget(right_widget);

        verticalLayout->addWidget(splitter);

        FolderTextIndexerClass->setCentralWidget(central_widget);

        retranslateUi(FolderTextIndexerClass);

        QMetaObject::connectSlotsByName(FolderTextIndexerClass);
    } // setupUi

    void retranslateUi(QMainWindow *FolderTextIndexerClass)
    {
        FolderTextIndexerClass->setWindowTitle(QApplication::translate("FolderTextIndexerClass", "Global Text Indexer", nullptr));
        indexed_dirs_label->setText(QApplication::translate("FolderTextIndexerClass", "Indexed Directories", nullptr));
        add_dir_button->setText(QApplication::translate("FolderTextIndexerClass", "Add Directory", nullptr));
        dir_indexing_progress_group_box->setTitle(QApplication::translate("FolderTextIndexerClass", "Idle...", nullptr));
        queued_dirs_counter_group_box->setTitle(QApplication::translate("FolderTextIndexerClass", "Queued", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = matched_files_tree_widget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("FolderTextIndexerClass", "File", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("FolderTextIndexerClass", "Matches", nullptr));
        lookup_progress_group_box->setTitle(QApplication::translate("FolderTextIndexerClass", "Idle...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FolderTextIndexerClass: public Ui_FolderTextIndexerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
