#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <QMessageBox>
#include <QString>
#include <QCoreApplication>

/*

    Třída pro práci s databází

    Databáze má dvě tabulky: Zdroj, Hodnoty

    Tabulka Zdroj obsahuje záznam o testovaném zdroji(ID, sériové číslo,
    Pracovník provádějící test, datum testu, výsledek testu)

    Tabulka Hodnoty obshuje jednotlivé naměřené hodnoty (ID, ID_zdroje,
    5V, 5V_kon...)

*/

class Database
{

    sqlite3* db;
    int supplyID = 0;

    QString worker;
    QString serialNumber;
    bool result;
    QString date;

public:
    Database();
    ~Database();

    int writeRow(float* values, unsigned char testType, unsigned char testNum);
    int writeNewSupply(QString serialNumber, QString worker, QString date);
    int writeResult(bool result);

};