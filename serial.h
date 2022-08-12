#ifndef SERIAL_H
#define SERIAL_H

#define MINIMUM_PAKET_SIZE 8

#include "global_macros.h"
#include "toolMenu.h"
#include <QWidget>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QString>
#include <QMessageBox>
#include <QQueue>
#include <QTextStream>
#include <QTimer>
#include <QLabel>

//_____Struktura paketu_____//
typedef struct{
	//char startSequence[9];
	char type;
	char* data;
	char dataLength;
	char CA_value;	//control addiction
	//char endSequence[9];
}Paket;

//_____Typy vstupních dat_____//
typedef enum{
	DATA_PAKET = 1,
	DATA_BAT_PAKET,
	TEST_NUM_PAKET,
	TEST_PHASE_PAKET,
	ACK_PAKET,
	REFRESH_PAKET,
	HEATER_PAKET,
	CANCEL_FROM_USER_PAKET
}inPaketType;

//_____Typy výstupních dat_____//
typedef enum{
	START_PAKET = 's',
	CANCEL_PAKET = 'c',
	PAUSE_PAKET = 'p',
	CALIB_PAKET = 'k',
	CON_PAKET = 'a',
	MANUAL_PAKET = 'm'	//není implementováno v MCU a nepoužívá se
}outPaketType;

//_____Stav portu_____//
typedef enum{
	PORT_OK = 0U,
	PORT_DISCONNECTED,
    PORT_UNACTIVE,
    PORT_CONNECTING
}portState;

//_____Třída pro práci se sériovým portem_____//
class Serial : public QSerialPort
{
    Q_OBJECT

    QQueue<char> buffer;
    bool commandChar = false;
	bool autoConnectEnabled = true;
	portState status = PORT_DISCONNECTED;
    QTimer* serialTimer;

public:
    Serial();
    ~Serial();
    bool serialConnected = false;
    QList<QString> getComs();
    bool connectPort(QString portName);
	void closePort();
    void readData();
	int writePaket(outPaketType, int);
    portState getStatus();

public slots:
    void next(){write(QByteArray(1, 'n'));};
    void back(){write(QByteArray(1, 'b'));};
	void serialError();
    void setAutoConnect(bool enabled)
    {
        autoConnectEnabled = enabled;
        serialTimer->start();
    };

signals:
	void statusChanged(Serial*);
	void connectionLost();
	void paketFound(Paket*);

};

//_____Label pro zobrazení stavu portu_____//
class portLabel : public QLabel
{
	Q_OBJECT

public:
	portLabel(QWidget *parent=nullptr) : QLabel(parent){};

public slots:
	void setState(Serial*);
};

#endif // SERIAL_H
