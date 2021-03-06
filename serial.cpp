#include "serial.h"

//_____Konstruktor_____//
Serial::Serial()
{
    setBaudRate(QSerialPort::Baud9600);
    setDataBits(QSerialPort::Data8);

    //___Timer pro indikaci chyby připojení portu___//
    serialTimer = new QTimer;
    serialTimer->setSingleShot(false);
    serialTimer->setInterval(1100);
    connect(serialTimer, SIGNAL(timeout()), this, SLOT(serialError()));

    if(autoConnectEnabled)
    {
        serialTimer->start();
    }
}

//_____Destruktor_____//
Serial::~Serial()
{
    if(serialConnected){
        this->close();
    }
    serialTimer->stop();
    delete serialTimer;
}

//_____Připojení portu_____//
bool Serial::connectPort(QString portName){
    if(serialConnected){
        close();
    }

    setPortName (portName);

    if(open(QIODevice::ReadWrite))
    {
        serialTimer->start();
        serialConnected = true;
        status = PORT_CONNECTING;
        writePaket(CON_PAKET, 0);
    }
    else{
        //___Výpis chybové zprávy___//
        QString errorMessage;

        switch (this->error()){
        case 1:
            errorMessage = "DeviceNotFound";
            break;
        case 2:
            errorMessage = "PermissionError";
            break;
        case 3:
            errorMessage = "OpenError";
            break;
        case 13:
            errorMessage = "NotOpenError";
            break;
        case 4:
            errorMessage = "ParityError";
            break;
        case 5:
            errorMessage = "FramingError";
            break;
        case 6:
        errorMessage = "BreakConditionError";
            break;
        case 7:
            errorMessage = "WriteError";
            break;
        case 8:
            errorMessage = "ReadError";
            break;
        case 9:
            errorMessage = "ResourceError";
            break;
        case 10:
            errorMessage = "UnsupportedOperationError";
            break;
        case 12:
            errorMessage = "TimeoutError";
            break;
        case 11:
            errorMessage = "UnknownError";
            break;
        default:
            errorMessage = "NoError";
            break;
        }
        QMessageBox::warning(nullptr, tr("Zahoreni"), tr("Nepodařilo se otevřít COM port\n %1").arg(errorMessage), QMessageBox::Cancel);
        serialConnected = false;
        status = PORT_DISCONNECTED;
        serialTimer->stop();
    }

    emit statusChanged(this);
    return serialConnected;
}

void Serial::closePort()
{
    if(this->serialConnected)
    {
        serialTimer->stop();
        this->serialConnected = false;
        this->status = PORT_DISCONNECTED;
        emit statusChanged(this);
        this->close();
    }
}

//_____Chyba připojení portu (přípravek se neozývá)_____//
void Serial::serialError()
{
    if (autoConnectEnabled)
    {
        if(serialConnected)
        {
            status = PORT_UNACTIVE;
            emit connectionLost();
        }
        else
            status = PORT_DISCONNECTED;
        QList<QSerialPortInfo>unconnectedPorts = QSerialPortInfo::availablePorts();
        if(unconnectedPorts.count())
        {
            //___Vytvoření seznamu jmen portů___//
            foreach(QSerialPortInfo portInfo, unconnectedPorts)
            {
                if(portInfo.vendorIdentifier() == 1155 && portInfo.productIdentifier() == 22336)
                {
                    connectPort(portInfo.portName());
                }
            }
        }
    }
    else
    {
        status = PORT_UNACTIVE;
        serialTimer->stop();
        emit connectionLost();
    } 

    emit statusChanged(this);
}

portState Serial::getStatus()
{
    return this->status;
}

//___Čtení příchozích dat___//
void Serial::readData()
{
    if(status != PORT_OK)
    {
        status = PORT_OK;
        emit statusChanged(this);
    }

    serialTimer->start();

    char inChar;

    //___Načti všechny příchozí znaky do bufferu___//
    while(read(&inChar, 1) == 1)
    {
        buffer.enqueue(inChar);
    }

    //___Hledání paketu___//
    for (int i = 0; i < buffer.length()-MINIMUM_PAKET_SIZE; i++)
    {
        if(buffer.at(i) == '>' && buffer.at(i+1) == '>')    //Počátek paketu
        {
            for (int y = i; y < buffer.length()-2; y++)
            {
                if(buffer.at(y) == '<' && buffer.at(y+1) == '<' && buffer.at(y+2) == '\n')    //Konec paketu
                {
                    //___Přepis do struktury paket___//
                    Paket* inPaket = (Paket*)malloc(sizeof(Paket));
                    inPaket->type = buffer.at(i+2);
                    inPaket->CA_value = buffer.at(y-1);
                    inPaket->dataLength = y-i-4;    
                    char* data = (char*)malloc((inPaket->dataLength)*sizeof(char));
                    for (int x = 0; x < inPaket->dataLength; x++)
                    {
                        data[x] = buffer.at(x+i+3);
                    }
                    //memcpy(data, &buffer.at(i+3), inPaket->dataLength);
                    inPaket->data = data;

                    //QTextStream out(stdout);
                    //___Vymazání přijatého paketu z bufferu___//
                    for (int x = 0; x < y+2; x++)
                    {
                        buffer.dequeue();
                    }
                    
                    emit paketFound(inPaket);
                }
            }
            
        }
    }
}

//_____Poslání paketu___//
int Serial::writePaket(outPaketType paketType, int sourcePointer = 0)
{
    char paket[8] = {'>', '>', paketType, sourcePointer, paketType+sourcePointer, '<', '<', '\n'};
    return this->write(paket, 8);
}

//_____Label_____//
void portLabel::setState(Serial* port)
{
    switch (port->getStatus())
    {
    case PORT_OK:  
        this->setText("COM: PŘIPOJENO");
        this->setStyleSheet("QLabel { color: white; background: green; font-size: 16px;}");
        break;
    
    case PORT_UNACTIVE:
        this->setText("COM: NEAKTIVNÍ");
        this->setStyleSheet("QLabel { color: white; background: red; font-size: 16px;}");
        break;

    case PORT_CONNECTING:
        this->setText("COM: Připojování");
        this->setStyleSheet("QLabel { color: white; background: orange; font-size: 16px;}");
        break;

    default:
        this->setText("COM: ODPOJENO");
        this->setStyleSheet("QLabel { color: white; background: red; font-size: 16px;}");
        break;
    }
}
