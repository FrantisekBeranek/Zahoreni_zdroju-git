#ifndef SERIAL_H
#define SERIAL_H

#define MINIMUM_PAKET_SIZE 8

#include "global_macros.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QString>
#include <QMessageBox>
#include <QQueue>
#include <QTextStream>

typedef struct{
	//char startSequence[9];
	char type;
	char* data;
	char dataLength;
	char CA_value;	//control addiction
	//char endSequence[9];
}Paket;

typedef enum{
	DATA_PAKET = 1,
	DATA_BAT_PAKET,
	TEST_NUM_PAKET,
	TEST_PHASE_PAKET,
	ACK_PAKET,
	REFRESH_PAKET
}inPaketType;

typedef enum{
	START_PAKET = 's',
	CANCEL_PAKET = 'c',
	PAUSE_PAKET = 'p',
	CALIB_PAKET = 'k',
	CON_PAKET = 'a',
	MANUAL_PAKET = 'm'	//není implementováno v MCU a nepoužívá se
}outPaketType;

class Serial : public QSerialPort
{
    Q_OBJECT

    QQueue<char> buffer;
    QList<QString> ports;
    bool commandChar = false;

public:
    Serial();
    ~Serial();
    bool serialConnected = false;
    QList<QString> getComs();
    bool connectPort(QString portName);
    Paket* readData();
	int writePaket(outPaketType, int);

public slots:
    void next(){write(QByteArray(1, 'n'));};
    void back(){write(QByteArray(1, 'b'));};
    
signals:
};

#endif // SERIAL_H
