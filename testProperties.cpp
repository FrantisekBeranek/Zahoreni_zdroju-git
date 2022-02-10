#include "testProperties.h"

QString testProperties::getSerialNumber()
{
    bool Ok;

    QString serialNumber = QInputDialog::getText(nullptr, "Sériové číslo",
            "Zadejte sériové číslo testovaného zdroje", QLineEdit::Normal, 
            "Zde zapište sériové číslo", &Ok);  //Zadání sériového čísla zdroje
    if (!Ok)    return nullptr; //Při neúspěchu ukonči

    return serialNumber;
}

QString testProperties::getPath(QString defaultPath, QString defaultName)
{
    QString dateStr = QDateTime::currentDateTime().toString("_dd_MM_yy");   //Získání data v daném formátu

    //___Nastavení názvu souboru___//
    QString fileName;// = serialNumber;
    fileName.append(dateStr);

    //___Získání absolutní adresy nového souboru___//
    QFile file;
    file.setFileName(defaultPath);
    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        QString filePath = file.readLine();
        fileName = QFileDialog::getSaveFileName(nullptr,
            "Vytvořit soubor", filePath.append(defaultName),
            "PDF File (*.pdf);;All Files (*)");
    }
    else{
        fileName = QFileDialog::getSaveFileName(nullptr,
            "Vytvořit soubor", "",
            "PDF File (*.pdf);;All Files (*)");
    }

    return fileName;
}

QString testProperties::getWorker(QString workersPath)
{
    QFile* workerFile = new QFile;
    workerFile->setFileName(workersPath);
    workerFile->open(QIODevice::ReadOnly);
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
    unsigned char num;
    if(supplyCount)
    {
        QStringList zdroje;

        for (int i = 0; i < supplyCount; i++)
        {
            zdroje << QString::number(i+1);
        }
        bool Ok;
        QString supplyPointer = QInputDialog::getItem(nullptr, "Číslo zdroje",
            "Zadejte číslo zdroje k testu", zdroje, 
            0, false, &Ok);
        num = supplyPointer.toInt() - 1;
        if(!Ok)
            return;
    }
    else
    {
        QMessageBox::warning (nullptr, "Zahořování zdrojů",
            "Není znám počet připojitelných zdrojů.");
        return;
    }
}