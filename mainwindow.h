#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "global_macros.h"
#include <QMainWindow>
#include <QFile>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "serial.h"
#include "File.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Serial* port;
    File* file;

    bool measureInProgress = false;
    bool manualMode = false;
    bool comError = false;
    bool calibInProgress = false;

    unsigned char commandLetter;
    unsigned char commandNum;

    unsigned int errorCount = 0;
    unsigned int warningCount = 0;

    QTimer* timer;
    QTimer* endTimer;
    QTimer* startTimer;

    unsigned char lastNum = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QTimer* statusBarTimer;
    QTimer* serialTimer;


public slots:
    //void powerManage();
    void zahoreniManage(QAction*);
    void toolManage(QAction*);
    void getCOMs();
    void connectPort(QAction*);
    void read();
    void calibrationFailure();
    void endCalibration();
    void readCommand();
    void endMeasure();
    void serialError();
    void startError();
};
#endif // MAINWINDOW_H
