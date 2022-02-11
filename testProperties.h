#ifndef __TEST_PROPERTIES__
#define __TEST_PROPERTIES__

#include <QString>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QFileDialog>>

class testProperties
{
private:
    QString path;
    QString serialNumber;
    QString worker;
    int pointer;
    
    QString getSerialNumber();
    QString getPath(QString);
    QString getWorker(QString);
    int getPointer(int);

public:
    testProperties(){};
    testProperties(QString inSerialNumber, QString inPath, QString inWorker, int inPointer)
        : serialNumber{inSerialNumber}, path{inPath}, worker{inWorker}, pointer{inPointer} {};
    //~testProperties();

    bool init(int supplyCount, QString workersPath, QString defaultPath);
    QString retPath(){return path;};
    QString retSerialNumber(){return serialNumber;};
    QString retWorker(){return worker;};
    int retPointer(){return pointer;};

    //void setSerialNumber(QString newNumber){serialNumber = newNumber;};
    //void setPath(QString newPath){path = newPath;};
    //void setWorker(QString newWorker){worker = newWorker;};
    //void setPointer(int newPointer){pointer = newPointer;};
};

/*testProperties::~testProperties()
{
}*/

#endif