#include "database.h"

Database::Database()
{
    //Create connection to database
    int rc;
    rc = sqlite3_open("zahorovani.db", &db);
    if(rc)
    {
        QMessageBox::warning(
            nullptr,    //parent
            "Zahořování zdrojů",    //title
            "Nepodařilo se připojit k databázi", //text
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

}

int Database::writeRow(float* values, unsigned char testType, unsigned char testNum)
{
    //Create connection to database
    int rc;
    rc = sqlite3_open("zahorovani.db", &db);
    if(rc)
    {
        return -1;
    }

    //Write into database
    char* zErrMsg = 0;
    char values_str[40] = {0};
    sprintf(values_str, "%d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f);",\
        supplyID, values[0], values[1], values[2], values[3], values[4], values[5], values[6], values[7]);

    char* sql = "INSERT INTO Hodnoty (" \
                "ID_zdroje, " \
                "5V_KON, " \
                "5V, "
                "12V, " \
                "15V, " \
                "U_bat, " \
                "24V, " \
                "24V_O2) " \
                "VALUES (" \
                ;
    strcat(sql, values_str);
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    sqlite3_close(db);

    if(rc != SQLITE_OK)
    {
        return -1;
    }

    return 0;
}


int Database::writeNewSupply(QString serialNumber, QString worker, QString date)
{
    //Create connection to database
    int rc;
    rc = sqlite3_open("zahorovani.db", &db);
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
                "pracovnik", \
                "datum) VALUES ("\
                "%s, "\
                "%s, "\
                "%s);",
                serialNumber, worker, date);
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    sqlite3_close(db);

    if(rc != SQLITE_OK)
    {
        return -1;
    }

    return 0;
}

int Database::writeResult(bool result)
{
    //Create connection to database
    int rc;
    rc = sqlite3_open("zahorovani.db", &db);
    if(rc)
    {
        return -1;
    }

    this->result = result;

    //write to database
    char* zErrMsg = 0;
    char sql[100] = {0};
    sprintf(sql, "INSERT INTO Zdroje (" \
                "vysledek) VALUES ("\
                "%i);",
                result);
    
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    sqlite3_close(db);

    if(rc != SQLITE_OK)
    {
        return -1;
    }

    return 0;

}