/********************************************************************************
** Form generated from reading UI file 'setWidget.ui'
**
** Created: Fri Nov 21 16:16:19 2014
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETWIDGET_H
#define UI_SETWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetWidget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *mainColorLabel;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *chooseColorButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *fontLabel;
    QFontComboBox *fontComboBox;
    QLabel *label_2;
    QComboBox *sizecomboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *backgroundLabel;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *SetWidget)
    {
        if (SetWidget->objectName().isEmpty())
            SetWidget->setObjectName(QString::fromUtf8("SetWidget"));
        SetWidget->resize(360, 241);
        widget = new QWidget(SetWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(49, 56, 274, 138));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainColorLabel = new QLabel(widget);
        mainColorLabel->setObjectName(QString::fromUtf8("mainColorLabel"));

        horizontalLayout->addWidget(mainColorLabel);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        chooseColorButton = new QPushButton(widget);
        chooseColorButton->setObjectName(QString::fromUtf8("chooseColorButton"));

        horizontalLayout->addWidget(chooseColorButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        fontLabel = new QLabel(widget);
        fontLabel->setObjectName(QString::fromUtf8("fontLabel"));

        horizontalLayout_2->addWidget(fontLabel);

        fontComboBox = new QFontComboBox(widget);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));

        horizontalLayout_2->addWidget(fontComboBox);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        sizecomboBox = new QComboBox(widget);
        sizecomboBox->setObjectName(QString::fromUtf8("sizecomboBox"));

        horizontalLayout_2->addWidget(sizecomboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        backgroundLabel = new QLabel(widget);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));

        horizontalLayout_3->addWidget(backgroundLabel);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_3->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        okButton = new QPushButton(widget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_4->addWidget(okButton);

        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_4->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(SetWidget);

        QMetaObject::connectSlotsByName(SetWidget);
    } // setupUi

    void retranslateUi(QWidget *SetWidget)
    {
        SetWidget->setWindowTitle(QApplication::translate("SetWidget", "Form", 0, QApplication::UnicodeUTF8));
        mainColorLabel->setText(QApplication::translate("SetWidget", "\344\270\273\351\242\230\350\211\262", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SetWidget", "lightblue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "lightgreen", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "gray", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "cyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkCyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkRed", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "magenta", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkMagenta", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkGreen", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkYellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "blue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkBlue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "purple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "orange", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "brown", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "pink", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "darkGray", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "white", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("SetWidget", "\346\255\214\350\257\215\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        chooseColorButton->setText(QApplication::translate("SetWidget", "\351\200\211\346\213\251\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        fontLabel->setText(QApplication::translate("SetWidget", "\345\255\227\344\275\223", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SetWidget", "\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        sizecomboBox->clear();
        sizecomboBox->insertItems(0, QStringList()
         << QApplication::translate("SetWidget", "12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "15", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "16", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "17", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "18", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "19", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "20", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "21", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "22", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "23", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "24", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "25", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "26", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "27", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "28", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "29", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SetWidget", "30", 0, QApplication::UnicodeUTF8)
        );
        backgroundLabel->setText(QApplication::translate("SetWidget", "\350\203\214\346\231\257", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("SetWidget", "\350\207\252\345\212\250\346\222\255\346\224\276\350\203\214\346\231\257", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("SetWidget", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("SetWidget", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SetWidget: public Ui_SetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETWIDGET_H
