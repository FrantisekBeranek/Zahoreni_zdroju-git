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
    LIMITS_OPEN_ERROR
};

class File : public QFile
{
    Q_OBJECT

    QString homePath2 = ".\\src\\";
    QString patternPath = "mustr.txt";
    QString limitsPath = "meze.txt";
    QString defaultPath = "defaultPath.txt";
    QString calibPath = "kalibrace.txt";
    QString path;
    QDir dir;

    QString serialNumber;
    QString worker;

    QFile limitsFile;
    QFile* logFile;
    limits* Form;

    QTextDocument*doc;
    QTextCursor* cursor;

    double transfer[7];

    bool getConstants();

public:
    File();
    ~File();
    
    QString homePath1 = "..\\src\\";

    QString pathPDF;

    bool testResult = true;

    QString getPath();  //dialogovým oknem zjistí adresu a název nového souboru
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
    void showLog();
    void removeAll();

public slots:
    void saveLimits();

signals:
    void calibrationOver();

};


#endif //FILE_H