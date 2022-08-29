#include "database.h"

Database::Database()
{
    //Create connection to database
    int rc;
    QString appDirPath = QCoreApplication::applicationDirPath().section('/', 0, -2).append("/.src/zahorovani.db");
    dbPath = appDirPath.toLocal8Bit();
    rc = sqlite3_open(dbPath.data(), &db);
    if(rc)
    {
        QMessageBox::warning(
            nullptr,    //parent
            "Zahořování zdrojů",    //title
            QString("Nepodařilo se připojit k databázi %1").arg(dbPath), //text
            QMessageBox::Ok //button
            );
        return;
    }
    sqlite3_close(db);
}

Database::~Database()
{
    sqlite3_close(db);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    //Funkce je volána při použití příkazu SELECT
    int i;
    QString retMsg;
    for(i = 0; i<argc; i++) {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        retMsg.append("%1 = %2\n").arg(azColName[i]).arg(argv[i] ? argv[i] : "NULL");
    }
    //printf("\n");
    QMessageBox::warning(
        nullptr,    //parent
        "Zahořování zdrojů",    //title
        retMsg, //text
        QMessageBox::Ok //button
    );
    return 0;
}

int Database::writeRow(float* values, unsigned char testType, unsigned char testNum)
{
    //Create connection to database
    int rc;
    rc = sqlite3_open(dbPath.data(), &db);
    if(rc)
    {
        return -1;
    }

    //Write into database
    char* zErrMsg = 0;
    char values_str[100] = {0};
    sprintf(values_str, "%d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f);",
        supplyID, values[0], values[1], values[2], values[3], values[4], values[5], values[6]);

    char sql[200] = {"INSERT INTO Hodnoty (" \
                "ID_zdroje, " \
                "'5Vkon', " \
                "'5V', "
                "'12V', " \
                "'15V', " \
                "U_bat, " \
                "'24V', " \
                "'24V_O2') " \
                "VALUES (" };
    strcat(sql, values_str);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    sqlite3_close(db);

    if(rc != SQLITE_OK)
    {
        QMessageBox::warning(
            nullptr,    //parent
            "Zahořování zdrojů",    //title
            QString("Nepodařilo se zapsat do databáze (%1)").arg(zErrMsg), //text
            QMessageBox::Ok //button
            );
        return -1;
    }

    return 0;
}


int Database::writeNewSupply(QString serialNumber, QString worker, QString date)
{
    //Create connection to database
    int rc;
    rc = sqlite3_open(dbPath.data(), &db);
    if(rc)
    {
        return -1;
    }

    this->serialNumber = serialNumber;
    this->worker = worker;
    this->date = date;

    //write to database
    char* zErrMsg = 0;
    char sql[100] = {0};
    sprintf(sql, "INSERT INTO Zdroje (" \
                "seriove_cislo, "\
                "pracovnik," \
                "datum) VALUES ( "\
                "'%s', "\
                "'%s', "\
                "'%s');",
                serialNumber.toUtf8().data(), worker.toUtf8().data(), date.toUtf8().data());
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK)
    {
        QMessageBox::warning(
            nullptr,    //parent
            "Zahořování zdrojů",    //title
            QString("Nepodařilo se zapsat do databáze (%1)").arg(zErrMsg), //text
            QMessageBox::Ok //button
            );
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return -1;
    }

    supplyID = sqlite3_last_insert_rowid(db);
    sqlite3_close(db);

    return 0;
}

int Database::writeResult(bool result)
{
    //Create connection to database
    int rc;
    rc = sqlite3_open(dbPath.data(), &db);
    if(rc)
    {
        return -1;
    }

    this->result = result;

    //write to database
    char* zErrMsg = 0;
    char sql[100] = {0};
    sprintf(sql, "UPDATE Zdroje SET vysledek = %i WHERE ID=%i;",
                result, supplyID);
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    sqlite3_close(db);

    if(rc != SQLITE_OK)
    {
        return -1;
    }

    return 0;

}
