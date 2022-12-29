/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QFrame *frame;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *nameText;
    QLabel *label_4;
    QLineEdit *wheelText;
    QPushButton *addProfile;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QComboBox *combo;
    QPushButton *deleteProfile;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *diaTextDisplay;
    QLabel *label_7;
    QLabel *nameTextDisplay;
    QLabel *label_8;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(399, 379);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 29));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        frame = new QFrame(Dialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 40, 381, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayoutWidget_2 = new QWidget(frame);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(9, 9, 361, 172));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFrameShape(QFrame::Box);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_3);

        nameText = new QLineEdit(verticalLayoutWidget_2);
        nameText->setObjectName(QString::fromUtf8("nameText"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameText);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_4);

        wheelText = new QLineEdit(verticalLayoutWidget_2);
        wheelText->setObjectName(QString::fromUtf8("wheelText"));

        formLayout->setWidget(1, QFormLayout::FieldRole, wheelText);


        verticalLayout_2->addLayout(formLayout);

        addProfile = new QPushButton(verticalLayoutWidget_2);
        addProfile->setObjectName(QString::fromUtf8("addProfile"));

        verticalLayout_2->addWidget(addProfile);

        horizontalLayoutWidget = new QWidget(Dialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 230, 381, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_6->setFont(font1);

        horizontalLayout->addWidget(label_6);

        combo = new QComboBox(horizontalLayoutWidget);
        combo->setObjectName(QString::fromUtf8("combo"));
        combo->setEditable(false);

        horizontalLayout->addWidget(combo);

        deleteProfile = new QPushButton(horizontalLayoutWidget);
        deleteProfile->setObjectName(QString::fromUtf8("deleteProfile"));

        horizontalLayout->addWidget(deleteProfile);

        gridLayoutWidget = new QWidget(Dialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 290, 381, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        diaTextDisplay = new QLabel(gridLayoutWidget);
        diaTextDisplay->setObjectName(QString::fromUtf8("diaTextDisplay"));
        diaTextDisplay->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(diaTextDisplay, 1, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font2;
        font2.setBold(true);
        font2.setUnderline(true);
        font2.setWeight(75);
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        nameTextDisplay = new QLabel(gridLayoutWidget);
        nameTextDisplay->setObjectName(QString::fromUtf8("nameTextDisplay"));
        nameTextDisplay->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(nameTextDisplay, 1, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 0, 1, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Vehicle Profiles", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Add Profiles", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Name :", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "Wheel Dia (mm):", nullptr));
        addProfile->setText(QCoreApplication::translate("Dialog", "Add to Profiles", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "Select Profile:", nullptr));
        deleteProfile->setText(QCoreApplication::translate("Dialog", "Delete", nullptr));
        diaTextDisplay->setText(QCoreApplication::translate("Dialog", "Dia", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog", "Name:", nullptr));
        nameTextDisplay->setText(QCoreApplication::translate("Dialog", "Name", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog", "Wheel Dia (mm)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
