#include "testProperties.h"

bool testProperties::init(int supplyCount, std::vector<int> allreadySet)
{
    if(getPointer(supplyCount, allreadySet) < 0)
    {
        return false;
    }
    if(getSerialNumber() == nullptr)
    {
        return false;
    }
    if(getWorker() == nullptr)
    {
        return false;
    }
    if(getPath() == nullptr)
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

QString testProperties::getPath()
{
    QString dateStr = QDateTime::currentDateTime().toString("_dd_MM_yy");   //Získání data v daném formátu

    //___Nastavení názvu souboru___//
    QString defaultName = serialNumber + dateStr;

    QString srcDirPath = QCoreApplication::applicationDirPath().section('/', 0).append("/.src/");
    JSON_handler confFile;
    confFile.setFileName(QString("config.json").prepend(srcDirPath));
    QString defaultPath = confFile.getDefaultPath();
    //___Získání absolutní adresy nového souboru___//
    if(defaultPath != nullptr){
        path = QFileDialog::getSaveFileName(nullptr,
            "Vytvořit soubor", defaultPath.append(defaultName),
            "PDF File (*.pdf);;All Files (*)");
    }
    else{
        path = QFileDialog::getSaveFileName(nullptr,
            "Vytvořit soubor", defaultName,
            "PDF File (*.pdf);;All Files (*)");
    }
    confFile.setDefaultPath(path);

    return path;
}

QString testProperties::getWorker()
{
    
    QString srcDirPath = QCoreApplication::applicationDirPath().section('/', 0).append("/.src/");
    JSON_handler confFile;
    confFile.setFileName(QString("config.json").prepend(srcDirPath));
    QStringList workers;
    confFile.getWorkers(&workers);
    workers.push_back("Jiný pracovník");
   
    bool Ok;
    worker = QInputDialog::getItem(nullptr, "Jméno pracovníka",
            "Zadejte své jméno", workers, 
            0, false, &Ok);   //Zadání jména pracovníka
    if (!Ok)    return nullptr; //Při neúspěchu ukonči

    if(worker == "Jiný pracovník")
    {
        QString newWorker = QInputDialog::getText(nullptr, "Jméno pracovníka",
            "Zadejte své jméno", QLineEdit::Normal, 
            "", &Ok);   //Zadání jména pracovníka
        if (!Ok)    return nullptr; //Při neúspěchu ukonči
        confFile.addWorker(newWorker);
        worker = newWorker;
    }

    return worker;
}

int testProperties::getPointer(int supplyCount, std::vector<int> allreadySet)
{
    //___Výběr zdroje k testu___//
    supplyCount = 1;
    if(supplyCount)
    {
        QStringList zdroje;

        for (int i = 0; i < supplyCount; i++)
        {
            bool inQueue = false;
            for (int x = 0; x < allreadySet.size(); x++)
            {
                if(allreadySet.at(x) == i)
                {
                    inQueue = true;
                    break;
                }
            }
            
            if(!inQueue)
                zdroje << QString::number(i+1);
        }

        if(zdroje.isEmpty())
            zdroje << "Dostupné zdroje byly nastaveny";

        bool Ok;
        QString supplyPointer = QInputDialog::getItem(nullptr, "Číslo zdroje",
            "Zadejte číslo zdroje k testu", zdroje, 
            0, false, &Ok);
        if(!Ok)
            return -1;
        if(supplyPointer == "Dostupné zdroje byly nastaveny")
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