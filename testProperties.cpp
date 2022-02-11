#include "testProperties.h"

bool testProperties::init(int supplyCount, QString workersPath, QString defaultPath)
{
    if(getPointer(supplyCount) < 0)
    {
        return false;
    }
    if(getSerialNumber() == nullptr)
    {
        return false;
    }
    if(getWorker(workersPath) == nullptr)
    {
        return false;
    }
    if(getPath(defaultPath) == nullptr)
    {
        return false;
    }
    return true;
}

QString testProperties::getSerialNumber()
{
    bool Ok;

    serialNumber = QInputDialog::getText(nullptr, "Sériové číslo",
            "Zadejte sériové číslo testovaného zdroje", QLineEdit::Normal, 
            "Zde zapište sériové číslo", &Ok);  //Zadání sériového čísla zdroje
    if (!Ok)    return nullptr; //Při neúspěchu ukonči

    return serialNumber;
}

QString testProperties::getPath(QString defaultPath)
{
    QString dateStr = QDateTime::currentDateTime().toString("_dd_MM_yy");   //Získání data v daném formátu

    //___Nastavení názvu souboru___//
    QString defaultName = serialNumber + dateStr;

    //___Získání absolutní adresy nového souboru___//
    QFile file;
    file.setFileName(defaultPath);
    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        QString filePath = file.readLine();
        path = QFileDialog::getSaveFileName(nullptr,
            "Vytvořit soubor", filePath.append(defaultName),
            "PDF File (*.pdf);;All Files (*)");
        file.close();
    }
    else{
        path = QFileDialog::getSaveFileName(nullptr,
            "Vytvořit soubor", "",
            "PDF File (*.pdf);;All Files (*)");
    }

    return path;
}

QString testProperties::getWorker(QString workersPath)
{
    QFile* workerFile = new QFile;
    workerFile->setFileName(workersPath);
    if(workerFile->open(QIODevice::ReadOnly) != true) return nullptr;
    QStringList workers;
    QString input;
    
    input = workerFile->readLine(20);
    while (!input.isEmpty())
    {
        workers << input;
        input = workerFile->readLine(20);
    }
    workers << "Jiný pracovník";
    workerFile->close();
   
    bool Ok;
    QString worker = QInputDialog::getItem(nullptr, "Jméno pracovníka",
            "Zadejte své jméno", workers, 
            0, false, &Ok);   //Zadání jména pracovníka
    if (!Ok)    return nullptr; //Při neúspěchu ukonči

    if(worker == "Jiný pracovník")
    {
        workerFile->open(QIODevice::WriteOnly | QIODevice::Append);
        QString newWorker = QInputDialog::getText(nullptr, "Jméno pracovníka",
            "Zadejte své jméno", QLineEdit::Normal, 
            "", &Ok);   //Zadání jména pracovníka
        if (!Ok)    return nullptr; //Při neúspěchu ukonči
        worker = newWorker;
        newWorker.prepend("\n");
        workerFile->write(newWorker.toUtf8());
        workerFile->close();
    }

    delete workerFile;

    return worker;
}

int testProperties::getPointer(int supplyCount)
{
    //___Výběr zdroje k testu___//
    if(supplyCount)
    {
        QStringList zdroje;

        for (unsigned char i = 0; i < supplyCount; i++)
        {
            zdroje << QString::number(i+1);
        }
        bool Ok;
        QString supplyPointer = QInputDialog::getItem(nullptr, "Číslo zdroje",
            "Zadejte číslo zdroje k testu", zdroje, 
            0, false, &Ok);
        if(!Ok)
            return -1;
        pointer = supplyPointer.toInt()-1;
        return pointer;
    }
    else
    {
        QMessageBox::warning (nullptr, "Zahořování zdrojů",
            "Není znám počet připojitelných zdrojů.");
        return -1;
    }
}