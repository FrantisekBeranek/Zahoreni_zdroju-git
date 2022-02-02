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
#include "toolMenu.h"
#include "menuBar.h"
#include "global_macros.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Serial* port;
    File* file;

    //___Bool proměnné___//
    appStatus status;

    //___Popis fáze testu___//
    unsigned char commandLetter;
    unsigned char commandNum;
    
    unsigned char lastNum = 0;

    //___Počty chyb___//
    unsigned int errorCount = 0;
    unsigned int warningCount = 0;

    //___Timery___//
    QTimer* timer;
    QTimer* endTimer;
    QTimer* startTimer;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QTimer* statusBarTimer;

    void managePaket(Paket* paket);
    void testNumManage(char num);
    void testPhaseManage(char phase);
    void dataManage(char* data, char dataLength);
    void dataBatManage(char* data, char dataLength);



public slots:
    void startManage();
    void stopManage();
    void limitsManage();
    void calibManage(/*QAction**/);
    void connectPort(QAction* action)
    {
        port->connectPort(action->text());
        /*if(port->connectPort(action->text()))
            this->ui->statusbar->showMessage(action->text());*/
    };
    void disconnectPort()
    {
        port->closePort();
        //this->ui->statusbar->showMessage("Odpojeno");
    };
    void read();
    void calibrationFailure();
    void endCalibration();
    void endMeasure();
    void startError();
    void statusBarTiming(){statusBarTimer->start();};
    void portStatusChanged(Serial*);

signals:
    void statusChanged(appStatus);

};
#endif // MAINWINDOW_H
