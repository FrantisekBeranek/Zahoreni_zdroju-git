#include "serial.h"


Serial::Serial()
{
    setBaudRate(QSerialPort::Baud9600);
    setDataBits(QSerialPort::Data8);
}

Serial::~Serial()
{
    if(serialConnected){
        this->close();
    }
}

bool Serial::connectPort(QString portName){
    if(serialConnected){
        close();
    }
    setPortName (portName);

    if(open(QIODevice::ReadWrite))
        serialConnected = true;
    else{
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

QList<QString> Serial::getComs()
{
    ports.clear();  //Mazání dříve nalezených portů
    QList<QSerialPortInfo>unconnectedPorts = QSerialPortInfo::availablePorts();
    
    foreach(QSerialPortInfo portInfo, unconnectedPorts){
        ports.push_back(portInfo.portName());
    }
    return ports;
}

QString Serial::readData()
{
    QString tmp;

    while(read(&inChar, 1) == 1)
    {
        switch (inChar)
        {
            case '#':
                commandChar = true;
                break;
            
            case '\n':
                if(commandChar == true)
                {
                    commandChar = false;
                    emit commandComplete();
                    break;
                }
                else
                {
                    buffer.append(inChar);
                    tmp = buffer;
                    buffer.clear();
                }
            
            default:
                if(commandChar == true)
                {
                    if(inChar == 126)
                        inChar = 10;
                    command.enqueue(inChar);
                    break;
                }
                else
                {
                    buffer.append(inChar);
                    break;
                }
        }
        
    }
    return tmp;
}
