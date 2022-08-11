/********************************************************************************
** Form generated from reading UI file 'limits.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIMITS_H
#define UI_LIMITS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_limits
{
public:
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *fiveVoltsConMax;
    QDoubleSpinBox *fiveVoltsMax;
    QLabel *label;
    QLabel *short_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QDoubleSpinBox *twelveVoltsMax;
    QDoubleSpinBox *fifteenVoltsMax;
    QDoubleSpinBox *ubatMax;
    QDoubleSpinBox *twentyfourVoltsMax;
    QDoubleSpinBox *ubatMin;
    QDoubleSpinBox *fiveVoltsMin;
    QDoubleSpinBox *fifteenVoltsMin;
    QDoubleSpinBox *twelveVoltsMin;
    QDoubleSpinBox *twentyfourVoltsMin;
    QDoubleSpinBox *fiveVoltsConMin;
    QDoubleSpinBox *ubatMaxShort;
    QDoubleSpinBox *fiveVoltsMaxShort;
    QDoubleSpinBox *fifteenVoltsMaxShort;
    QDoubleSpinBox *twelveVoltsMaxShort;
    QDoubleSpinBox *twentyfourVoltsMaxShort;
    QDoubleSpinBox *fiveVoltsConMaxShort;
    QDoubleSpinBox *ubatMinShort;
    QDoubleSpinBox *fiveVoltsMinShort;
    QDoubleSpinBox *fifteenVoltsMinShort;
    QDoubleSpinBox *twelveVoltsMinShort;
    QDoubleSpinBox *twentyfourVoltsMinShort;
    QDoubleSpinBox *fiveVoltsConMinShort;
    QDoubleSpinBox *oxyMin;
    QDoubleSpinBox *oxyMinShort;
    QDoubleSpinBox *oxyMaxShort;
    QDoubleSpinBox *oxyMax;
    QFrame *line_4;
    QLabel *fiveVoltsCon;
    QLabel *fiveVolts;
    QLabel *twelveVolts;
    QLabel *fifteenVolts;
    QLabel *U_bat;
    QLabel *twentyfourVolts;
    QLabel *twentyfourVolts_oxy;

    void setupUi(QDialog *limits)
    {
        if (limits->objectName().isEmpty())
            limits->setObjectName(QString::fromUtf8("limits"));
        limits->resize(400, 300);
        buttonBox = new QDialogButtonBox(limits);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        fiveVoltsConMax = new QDoubleSpinBox(limits);
        fiveVoltsConMax->setObjectName(QString::fromUtf8("fiveVoltsConMax"));
        fiveVoltsConMax->setGeometry(QRect(80, 50, 62, 22));
        fiveVoltsConMax->setMinimum(4.500000000000000);
        fiveVoltsConMax->setMaximum(6.500000000000000);
        fiveVoltsConMax->setSingleStep(0.100000000000000);
        fiveVoltsConMax->setValue(5.500000000000000);
        fiveVoltsMax = new QDoubleSpinBox(limits);
        fiveVoltsMax->setObjectName(QString::fromUtf8("fiveVoltsMax"));
        fiveVoltsMax->setGeometry(QRect(80, 80, 62, 22));
        fiveVoltsMax->setMinimum(4.500000000000000);
        fiveVoltsMax->setMaximum(6.500000000000000);
        fiveVoltsMax->setSingleStep(0.100000000000000);
        fiveVoltsMax->setValue(5.500000000000000);
        label = new QLabel(limits);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 10, 61, 16));
        short_2 = new QLabel(limits);
        short_2->setObjectName(QString::fromUtf8("short_2"));
        short_2->setGeometry(QRect(290, 10, 55, 16));
        label_3 = new QLabel(limits);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 30, 31, 16));
        label_4 = new QLabel(limits);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 30, 21, 16));
        label_5 = new QLabel(limits);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(260, 30, 31, 16));
        label_6 = new QLabel(limits);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(340, 30, 21, 16));
        line = new QFrame(limits);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(60, 0, 16, 261));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(limits);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 20, 401, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(limits);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(220, 0, 16, 261));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        twelveVoltsMax = new QDoubleSpinBox(limits);
        twelveVoltsMax->setObjectName(QString::fromUtf8("twelveVoltsMax"));
        twelveVoltsMax->setGeometry(QRect(80, 110, 62, 22));
        twelveVoltsMax->setMinimum(11.500000000000000);
        twelveVoltsMax->setMaximum(13.500000000000000);
        twelveVoltsMax->setSingleStep(0.100000000000000);
        twelveVoltsMax->setValue(12.500000000000000);
        fifteenVoltsMax = new QDoubleSpinBox(limits);
        fifteenVoltsMax->setObjectName(QString::fromUtf8("fifteenVoltsMax"));
        fifteenVoltsMax->setGeometry(QRect(80, 140, 62, 22));
        fifteenVoltsMax->setMinimum(14.500000000000000);
        fifteenVoltsMax->setMaximum(16.500000000000000);
        fifteenVoltsMax->setSingleStep(0.100000000000000);
        fifteenVoltsMax->setValue(15.500000000000000);
        ubatMax = new QDoubleSpinBox(limits);
        ubatMax->setObjectName(QString::fromUtf8("ubatMax"));
        ubatMax->setGeometry(QRect(80, 170, 62, 22));
        ubatMax->setSingleStep(0.100000000000000);
        ubatMax->setValue(9.000000000000000);
        twentyfourVoltsMax = new QDoubleSpinBox(limits);
        twentyfourVoltsMax->setObjectName(QString::fromUtf8("twentyfourVoltsMax"));
        twentyfourVoltsMax->setGeometry(QRect(80, 200, 62, 22));
        twentyfourVoltsMax->setMinimum(15.000000000000000);
        twentyfourVoltsMax->setMaximum(30.000000000000000);
        twentyfourVoltsMax->setSingleStep(0.100000000000000);
        twentyfourVoltsMax->setValue(24.500000000000000);
        ubatMin = new QDoubleSpinBox(limits);
        ubatMin->setObjectName(QString::fromUtf8("ubatMin"));
        ubatMin->setGeometry(QRect(160, 170, 62, 22));
        ubatMin->setSingleStep(0.100000000000000);
        ubatMin->setValue(8.000000000000000);
        fiveVoltsMin = new QDoubleSpinBox(limits);
        fiveVoltsMin->setObjectName(QString::fromUtf8("fiveVoltsMin"));
        fiveVoltsMin->setGeometry(QRect(160, 80, 62, 22));
        fiveVoltsMin->setMinimum(3.500000000000000);
        fiveVoltsMin->setMaximum(5.500000000000000);
        fiveVoltsMin->setSingleStep(0.100000000000000);
        fiveVoltsMin->setValue(4.500000000000000);
        fifteenVoltsMin = new QDoubleSpinBox(limits);
        fifteenVoltsMin->setObjectName(QString::fromUtf8("fifteenVoltsMin"));
        fifteenVoltsMin->setGeometry(QRect(160, 140, 62, 22));
        fifteenVoltsMin->setMinimum(13.500000000000000);
        fifteenVoltsMin->setMaximum(15.500000000000000);
        fifteenVoltsMin->setSingleStep(0.100000000000000);
        fifteenVoltsMin->setValue(14.500000000000000);
        twelveVoltsMin = new QDoubleSpinBox(limits);
        twelveVoltsMin->setObjectName(QString::fromUtf8("twelveVoltsMin"));
        twelveVoltsMin->setGeometry(QRect(160, 110, 62, 22));
        twelveVoltsMin->setMinimum(10.500000000000000);
        twelveVoltsMin->setMaximum(12.500000000000000);
        twelveVoltsMin->setSingleStep(0.100000000000000);
        twelveVoltsMin->setValue(11.500000000000000);
        twentyfourVoltsMin = new QDoubleSpinBox(limits);
        twentyfourVoltsMin->setObjectName(QString::fromUtf8("twentyfourVoltsMin"));
        twentyfourVoltsMin->setGeometry(QRect(160, 200, 62, 22));
        twentyfourVoltsMin->setMinimum(15.000000000000000);
        twentyfourVoltsMin->setMaximum(30.000000000000000);
        twentyfourVoltsMin->setSingleStep(0.100000000000000);
        twentyfourVoltsMin->setValue(23.500000000000000);
        fiveVoltsConMin = new QDoubleSpinBox(limits);
        fiveVoltsConMin->setObjectName(QString::fromUtf8("fiveVoltsConMin"));
        fiveVoltsConMin->setGeometry(QRect(160, 50, 62, 22));
        fiveVoltsConMin->setMinimum(3.500000000000000);
        fiveVoltsConMin->setMaximum(5.500000000000000);
        fiveVoltsConMin->setSingleStep(0.100000000000000);
        fiveVoltsConMin->setValue(4.500000000000000);
        ubatMaxShort = new QDoubleSpinBox(limits);
        ubatMaxShort->setObjectName(QString::fromUtf8("ubatMaxShort"));
        ubatMaxShort->setGeometry(QRect(240, 170, 62, 22));
        ubatMaxShort->setSingleStep(0.100000000000000);
        ubatMaxShort->setValue(9.000000000000000);
        fiveVoltsMaxShort = new QDoubleSpinBox(limits);
        fiveVoltsMaxShort->setObjectName(QString::fromUtf8("fiveVoltsMaxShort"));
        fiveVoltsMaxShort->setGeometry(QRect(240, 80, 62, 22));
        fiveVoltsMaxShort->setMinimum(4.500000000000000);
        fiveVoltsMaxShort->setMaximum(6.500000000000000);
        fiveVoltsMaxShort->setSingleStep(0.100000000000000);
        fiveVoltsMaxShort->setValue(5.500000000000000);
        fifteenVoltsMaxShort = new QDoubleSpinBox(limits);
        fifteenVoltsMaxShort->setObjectName(QString::fromUtf8("fifteenVoltsMaxShort"));
        fifteenVoltsMaxShort->setGeometry(QRect(240, 140, 62, 22));
        fifteenVoltsMaxShort->setMinimum(14.500000000000000);
        fifteenVoltsMaxShort->setMaximum(16.500000000000000);
        fifteenVoltsMaxShort->setSingleStep(0.100000000000000);
        fifteenVoltsMaxShort->setValue(15.500000000000000);
        twelveVoltsMaxShort = new QDoubleSpinBox(limits);
        twelveVoltsMaxShort->setObjectName(QString::fromUtf8("twelveVoltsMaxShort"));
        twelveVoltsMaxShort->setGeometry(QRect(240, 110, 62, 22));
        twelveVoltsMaxShort->setMinimum(11.500000000000000);
        twelveVoltsMaxShort->setMaximum(13.500000000000000);
        twelveVoltsMaxShort->setSingleStep(0.100000000000000);
        twelveVoltsMaxShort->setValue(12.500000000000000);
        twentyfourVoltsMaxShort = new QDoubleSpinBox(limits);
        twentyfourVoltsMaxShort->setObjectName(QString::fromUtf8("twentyfourVoltsMaxShort"));
        twentyfourVoltsMaxShort->setGeometry(QRect(240, 200, 62, 22));
        twentyfourVoltsMaxShort->setMinimum(15.000000000000000);
        twentyfourVoltsMaxShort->setMaximum(30.000000000000000);
        twentyfourVoltsMaxShort->setSingleStep(0.100000000000000);
        twentyfourVoltsMaxShort->setValue(24.500000000000000);
        fiveVoltsConMaxShort = new QDoubleSpinBox(limits);
        fiveVoltsConMaxShort->setObjectName(QString::fromUtf8("fiveVoltsConMaxShort"));
        fiveVoltsConMaxShort->setGeometry(QRect(240, 50, 62, 22));
        fiveVoltsConMaxShort->setMinimum(4.500000000000000);
        fiveVoltsConMaxShort->setMaximum(6.500000000000000);
        fiveVoltsConMaxShort->setSingleStep(0.100000000000000);
        fiveVoltsConMaxShort->setValue(5.500000000000000);
        ubatMinShort = new QDoubleSpinBox(limits);
        ubatMinShort->setObjectName(QString::fromUtf8("ubatMinShort"));
        ubatMinShort->setGeometry(QRect(320, 170, 62, 22));
        ubatMinShort->setSingleStep(0.100000000000000);
        ubatMinShort->setValue(8.000000000000000);
        fiveVoltsMinShort = new QDoubleSpinBox(limits);
        fiveVoltsMinShort->setObjectName(QString::fromUtf8("fiveVoltsMinShort"));
        fiveVoltsMinShort->setGeometry(QRect(320, 80, 62, 22));
        fiveVoltsMinShort->setMinimum(3.500000000000000);
        fiveVoltsMinShort->setMaximum(5.500000000000000);
        fiveVoltsMinShort->setSingleStep(0.100000000000000);
        fiveVoltsMinShort->setValue(4.500000000000000);
        fifteenVoltsMinShort = new QDoubleSpinBox(limits);
        fifteenVoltsMinShort->setObjectName(QString::fromUtf8("fifteenVoltsMinShort"));
        fifteenVoltsMinShort->setGeometry(QRect(320, 140, 62, 22));
        fifteenVoltsMinShort->setMinimum(13.500000000000000);
        fifteenVoltsMinShort->setMaximum(15.500000000000000);
        fifteenVoltsMinShort->setSingleStep(0.100000000000000);
        fifteenVoltsMinShort->setValue(14.500000000000000);
        twelveVoltsMinShort = new QDoubleSpinBox(limits);
        twelveVoltsMinShort->setObjectName(QString::fromUtf8("twelveVoltsMinShort"));
        twelveVoltsMinShort->setGeometry(QRect(320, 110, 62, 22));
        twelveVoltsMinShort->setMinimum(10.500000000000000);
        twelveVoltsMinShort->setMaximum(12.500000000000000);
        twelveVoltsMinShort->setSingleStep(0.100000000000000);
        twelveVoltsMinShort->setValue(11.500000000000000);
        twentyfourVoltsMinShort = new QDoubleSpinBox(limits);
        twentyfourVoltsMinShort->setObjectName(QString::fromUtf8("twentyfourVoltsMinShort"));
        twentyfourVoltsMinShort->setGeometry(QRect(320, 200, 62, 22));
        twentyfourVoltsMinShort->setMinimum(15.000000000000000);
        twentyfourVoltsMinShort->setMaximum(30.000000000000000);
        twentyfourVoltsMinShort->setSingleStep(0.100000000000000);
        twentyfourVoltsMinShort->setValue(23.500000000000000);
        fiveVoltsConMinShort = new QDoubleSpinBox(limits);
        fiveVoltsConMinShort->setObjectName(QString::fromUtf8("fiveVoltsConMinShort"));
        fiveVoltsConMinShort->setGeometry(QRect(320, 50, 62, 22));
        fiveVoltsConMinShort->setMinimum(3.500000000000000);
        fiveVoltsConMinShort->setMaximum(5.500000000000000);
        fiveVoltsConMinShort->setSingleStep(0.100000000000000);
        fiveVoltsConMinShort->setValue(4.500000000000000);
        oxyMin = new QDoubleSpinBox(limits);
        oxyMin->setObjectName(QString::fromUtf8("oxyMin"));
        oxyMin->setGeometry(QRect(160, 230, 62, 22));
        oxyMin->setMinimum(15.000000000000000);
        oxyMin->setMaximum(30.000000000000000);
        oxyMin->setSingleStep(0.100000000000000);
        oxyMin->setValue(23.500000000000000);
        oxyMinShort = new QDoubleSpinBox(limits);
        oxyMinShort->setObjectName(QString::fromUtf8("oxyMinShort"));
        oxyMinShort->setGeometry(QRect(320, 230, 62, 22));
        oxyMinShort->setMinimum(15.000000000000000);
        oxyMinShort->setMaximum(30.000000000000000);
        oxyMinShort->setSingleStep(0.100000000000000);
        oxyMinShort->setValue(23.500000000000000);
        oxyMaxShort = new QDoubleSpinBox(limits);
        oxyMaxShort->setObjectName(QString::fromUtf8("oxyMaxShort"));
        oxyMaxShort->setGeometry(QRect(240, 230, 62, 22));
        oxyMaxShort->setMinimum(15.000000000000000);
        oxyMaxShort->setMaximum(30.000000000000000);
        oxyMaxShort->setSingleStep(0.100000000000000);
        oxyMaxShort->setValue(24.500000000000000);
        oxyMax = new QDoubleSpinBox(limits);
        oxyMax->setObjectName(QString::fromUtf8("oxyMax"));
        oxyMax->setGeometry(QRect(80, 230, 62, 22));
        oxyMax->setMinimum(15.000000000000000);
        oxyMax->setMaximum(30.000000000000000);
        oxyMax->setSingleStep(0.100000000000000);
        oxyMax->setValue(24.500000000000000);
        line_4 = new QFrame(limits);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(0, 250, 401, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        fiveVoltsCon = new QLabel(limits);
        fiveVoltsCon->setObjectName(QString::fromUtf8("fiveVoltsCon"));
        fiveVoltsCon->setGeometry(QRect(10, 50, 55, 16));
        fiveVolts = new QLabel(limits);
        fiveVolts->setObjectName(QString::fromUtf8("fiveVolts"));
        fiveVolts->setGeometry(QRect(10, 80, 55, 16));
        twelveVolts = new QLabel(limits);
        twelveVolts->setObjectName(QString::fromUtf8("twelveVolts"));
        twelveVolts->setGeometry(QRect(10, 110, 55, 16));
        fifteenVolts = new QLabel(limits);
        fifteenVolts->setObjectName(QString::fromUtf8("fifteenVolts"));
        fifteenVolts->setGeometry(QRect(10, 140, 55, 16));
        U_bat = new QLabel(limits);
        U_bat->setObjectName(QString::fromUtf8("U_bat"));
        U_bat->setGeometry(QRect(10, 170, 55, 16));
        twentyfourVolts = new QLabel(limits);
        twentyfourVolts->setObjectName(QString::fromUtf8("twentyfourVolts"));
        twentyfourVolts->setGeometry(QRect(10, 200, 55, 16));
        twentyfourVolts_oxy = new QLabel(limits);
        twentyfourVolts_oxy->setObjectName(QString::fromUtf8("twentyfourVolts_oxy"));
        twentyfourVolts_oxy->setGeometry(QRect(10, 230, 55, 16));

        retranslateUi(limits);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, limits, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, limits, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(limits);
    } // setupUi

    void retranslateUi(QDialog *limits)
    {
        limits->setWindowTitle(QCoreApplication::translate("limits", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("limits", "Napr\303\241zdno", nullptr));
        short_2->setText(QCoreApplication::translate("limits", "V z\303\241t\304\233\305\276i", nullptr));
        label_3->setText(QCoreApplication::translate("limits", "Max", nullptr));
        label_4->setText(QCoreApplication::translate("limits", "Min", nullptr));
        label_5->setText(QCoreApplication::translate("limits", "Max", nullptr));
        label_6->setText(QCoreApplication::translate("limits", "Min", nullptr));
        fiveVoltsCon->setText(QCoreApplication::translate("limits", "5V_K", nullptr));
        fiveVolts->setText(QCoreApplication::translate("limits", "5V", nullptr));
        twelveVolts->setText(QCoreApplication::translate("limits", "12V", nullptr));
        fifteenVolts->setText(QCoreApplication::translate("limits", "15V", nullptr));
        U_bat->setText(QCoreApplication::translate("limits", "Ubat", nullptr));
        twentyfourVolts->setText(QCoreApplication::translate("limits", "24V", nullptr));
        twentyfourVolts_oxy->setText(QCoreApplication::translate("limits", "24V_O2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class limits: public Ui_limits {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIMITS_H
