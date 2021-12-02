#include "serial.h"

//_____Konstruktor_____//
Serial::Serial()
{
    setBaudRate(QSerialPort::Baud9600);
    setDataBits(QSerialPort::Data8);
}

//_____Destruktor_____//
Serial::~Serial()
{
    if(serialConnected){
        this->close();
    }
}

//_____Připojení portu_____//
bool Serial::connectPort(QString portName){
    if(serialConnected){
        close();
    }

    setPortName (portName);

    if(open(QIODevice::ReadWrite))
        serialConnected = true;
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
        QMessageBox::warning(nullptr, tr("Simulace cidel"), tr("Nepodařilo se otevřít COM port\n %1").arg(errorMessage), QMessageBox::Cancel);
        serialConnected = false;
    }

    return serialConnected;
}

//_____Získání dostupných vstupů___//
QList<QString> Serial::getComs()
{
    QList<QString> ports;
    ports.clear();  //Mazání dříve nalezených portů
    QList<QSerialPortInfo>unconnectedPorts = QSerialPortInfo::availablePorts();
    
    //___Vytvoření seznamu jmen portů___//
    foreach(QSerialPortInfo portInfo, unconnectedPorts){
        ports.push_back(portInfo.portName());
    }

    return ports;
}

//___Čtení příchozích dat___//
Paket* Serial::readData()
{
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
                    /*for (int x = 0; x < inPaket->dataLength; x++)
                    {
                        data[x] = buffer.at(x+i+3);
                    }*/
                    memcpy(data, &buffer.at(i+3), inPaket->dataLength);
                    inPaket->data = data;

                    QTextStream out(stdout);
                    //___Vymazání přijatého paketu z bufferu___//
                    for (int x = 0; x < y+2; x++)
                    {
                        char tmp = buffer.dequeue();
                    }
                    
                    return inPaket;
                }
            }
            
        }
    }

    return nullptr;
}

//_____Poslání paketu___//
int Serial::writePaket(outPaketType paketType, int sourcePointer = 0)
{
    char paket[8] = {'>', '>', paketType, sourcePointer, paketType+sourcePointer, '<', '<', '\n'};
    return this->write(paket, 8);
}