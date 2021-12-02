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
	REFRESH_PAKET
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

//_____Třída pro práci se sériovým portem_____//
class Serial : public QSerialPort
{
    Q_OBJECT

    QQueue<char> buffer;
    bool commandChar = false;

//___Veřejné funkce a proměnné___//
public:
    Serial();
    ~Serial();
    bool serialConnected = false;
    QList<QString> getComs();
    bool connectPort(QString portName);
    Paket* readData();
	int writePaket(outPaketType, int);

//___Veřejné sloty___//
public slots:
    void next(){write(QByteArray(1, 'n'));};
    void back(){write(QByteArray(1, 'b'));};
};

#endif // SERIAL_H
