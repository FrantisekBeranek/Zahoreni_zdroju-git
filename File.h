#ifndef FILE_H
#define FILE_H

#include "global_macros.h"
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QTimer>
#include <QPrinter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class limits; }
QT_END_NAMESPACE

class limits : public QDialog
{
    Q_OBJECT

public:
    explicit limits(QWidget *parent = 0);
    ~limits();

    Ui::limits *ui;
private:
};

enum errorLogs
{
    DATA_LOSS = 0U,
    UNCOMPLETE_DATA,
    COM_INTERRUPTION,
    COM_RECONNECTION,
    PROTOCOL_AND_LIMITS_OPEN_ERROR,
    PROTOCOL_OPEN_ERROR,
    LIMITS_OPEN_ERROR,
    HEATER_ERROR
};

class File : public QFile
{
    Q_OBJECT

    QString patternPath = "mustr.txt";
    //QString path;
    QDir dir;

    QString serialNumber;
    QString worker;

    QFile* logFile;
    limits* Form;

    QTextDocument*doc;
    QTextCursor* cursor;

    double transfer[7];

public:
    File();
    ~File();

    QString pathPDF;

    bool testResult = true;

    int createFile(QString);   //vytvoří nový soubor a překopíruje do něj šablonu
    std::vector<QString> makeArray(QString, int);
    bool makeValues(unsigned int*, float*);
    bool writeToFile(float*, unsigned char, unsigned char);
    bool limitsCheck();
    bool limitsSetup();
    int makeProtocol();
    void calibration(unsigned int*);
    void writeLog(errorLogs, int);
    void writeLog(errorLogs);
    void removeAll();
    void setSerialNumber(QString serial){serialNumber = serial;};
    void setWorker(QString newWorker){worker = newWorker;};

public slots:
    void saveLimits();
    void showLog();

signals:
    void calibrationOver();
    void calibrationCancelled();

};


#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>


class JSON_handler
{

    QFile confFile;

public:
    JSON_handler();
    bool fileCheck();
    void setFileName(QString);
    void getWorkers(QStringList*);
    void addWorker(QString);
    void saveLimits(limits*);
    void setLimits(limits*);
    bool getLimits(std::vector<double>*, std::vector<double>*);
    QString getDefaultPath();
    void setDefaultPath(QString);
    bool getConstants(double*);
    bool saveConstants(double*);
};


#endif //FILE_H