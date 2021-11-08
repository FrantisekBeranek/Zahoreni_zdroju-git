#ifndef SERIAL_H
#define SERIAL_H

#include "global_macros.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QString>
#include <QMessageBox>
#include <QQueue>

class Serial : public QSerialPort
{
    Q_OBJECT

    QList<QString> ports;
    char inChar;
    QString buffer;
    bool commandChar = false;

public:
    Serial();
    ~Serial();
    bool serialConnected = false;
    QQueue<char> command;
    QList<QString> getComs();
    bool connectPort(QString portName);
    QString readData();

public slots:
    void next(){write(QByteArray(1, 'n'));};
    void back(){write(QByteArray(1, 'b'));};
    
signals:
    void commandComplete();
};

#endif // SERIAL_H
