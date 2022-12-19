#include "File.h"
#include "ui_limits.h"

//_____Konstruktor_____//
File::File()
{
    //---Nastavení cesty k souboru meze podle domovského adresáře---//
    QDir srcDirectory = QDir(QCoreApplication::applicationDirPath());
    srcDirectory.cd(".src");
    QString srcDirPath = srcDirectory.path();
    JSON_handler confFile;
    if(!confFile.fileCheck())
    {
        QMessageBox::critical(nullptr, "Chyba souborového systému!",
            QString("Důležité soubory neexistují, nebo byly přesunuty: %1").arg(srcDirPath), QMessageBox::Ok);
            //Pokud se soubory nenajdou, zobrazit confused Travoltu
        // Load animated GIF
        QMovie* movie = new QMovie(QString("200.gif").prepend(srcDirPath));

        // Make sure the GIF was loaded correctly
        if (movie->isValid()) 
        {
            // Play GIF
            QLabel* label = new QLabel(nullptr);
            label->setMovie(movie);
            movie->start();
            label->show();
        }
    }

    logFile = new QFile;
}

//_____Destruktor_____//
File::~File()
{

}

//_____Vytvoření souboru_____//
int File::createFile(QString path)
{
    //----------------PDF--------------------//

    doc = new QTextDocument;
    cursor = new QTextCursor(doc);
    cursor->movePosition(QTextCursor::Start);

    printer = new QPrinter(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
    printer->setPageSize(QPageSize::A4);
    printer->setPageOrientation(QPageLayout::Portrait);
    printer->setPageMargins(QMarginsF(15,15,15,15),QPageLayout::Millimeter);
    printer->setFullPage(false);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat); //you can use native format of system usin QPrinter::NativeFormat

    //___Nastavení fontu pdf___//
    QFont font("Courier", 2);
    font.setFixedPitch(true);
    doc->setDefaultFont(font);
    doc->setPageSize(printer->pageRect(QPrinter::Millimeter).size()); // This is necessary if you want to hide the page number

    //___Přepsání do pdf___//
    protocolText = 
    "+------------------------------------------------------------------------------+\n"
    "|                    Zahoření zdroje - Protokol o zkoušce                      |\n"
    "+------------------------------------------------------------------------------+\n"
    "================================================================================\n"
    "  Dle zkušebního a nastavovacího předpisu 1F395028G pro zdroj SI-610-1, RW-610  \n\n";

    doc->setPlainText(protocolText);
    doc->print(printer);
    
    return 1;
}

//_____Převod z hodnot ADC na napětí_____//
bool File::makeValues(unsigned int* valuesADC, float* valuesFloat)
{
    //___TODO___//
    /*JSON_handler confFile;
    if(!confFile.getConstants(this->transfer)) //Načtení převodních konstant
        return false;
    for (int i = 0; i < MEAS_TYPES_COUNT; i++)
    {
        valuesFloat[i] = valuesADC[i] * transfer[i];
    }*/

    float transferConsts[] = {
        U5VK_TRANSFER_CONSTANT,
        U5V_TRANSFER_CONSTANT,
        U12V_TRANSFER_CONSTANT,
        U15V_TRANSFER_CONSTANT,
        UBAT_TRANSFER_CONSTANT,
        U24V_TRANSFER_CONSTANT,
        U24VO2_TRANSFER_CONSTANT
    };

    int interRef = valuesADC[7];
    double valTmp = 0;
	for(uint8_t i = 0; i < 7; i++)
	{
		valTmp = valuesADC[i]*3.3*CALIB_CONSTANT;
		valTmp /= interRef*4095;
		valTmp *= transferConsts[i];
        valuesFloat[i] = valTmp;
	}
    
    return true;
}

//_____Zápis dat do souboru_____//
bool File::writeToFile(QString path, float* values, unsigned char testType, unsigned char testNum)
{
    static bool bat = false;
    unsigned int retVal = 0;

    QString divLine = "+---------+---------+---------+---------+---------+---------+---------+---------+\n";

    std::vector<double> limits_open, limits_short;

    JSON_handler confFile;

    retVal = 1 | confFile.getLimits(&limits_open, &limits_short) << 1;
        //3 -> vše v pořádku
        //2 -> chyba protokolu
        //1 -> chyba limitsfile
        //0 -> chyba všeho

    if(retVal == 3){
        QString testName;

        if(testNum == 0)
        {
            createFile(path);
            protocolText += QString("Seriove cislo zdroje: %1\n\n").arg(serialNumber);
            protocolText += divLine;
            protocolText += "|         | 5V_KON  | 5V      | 12V     | 15V     | U_bat   | 24V     | 24V_O2  |\n";
        }

        if(testNum < START_MEAS_COUNT) //Start testu
        {
            testName = "start    ";
            bat = false;
        }

        else if(testNum < (START_MEAS_COUNT + MAIN_MEAS_COUNT))   //hlavní test
        {
            if(testNum == START_MEAS_COUNT)   //První měření hlavního testu
            {
                protocolText += divLine;
            }
            testName = QString("Mereni %1").arg(testNum-START_MEAS_COUNT+1).leftJustified(9, ' ');
            bat = false;
        }

        else    //baterie
        {
            if(testNum <= (START_MEAS_COUNT + MAIN_MEAS_COUNT + BAT_START_MEAS_COUNT))
            {
                protocolText += divLine + '\n' + "Baterie\n";
            }
            
            testName = QString("Mereni %1").arg(testNum-(START_MEAS_COUNT + MAIN_MEAS_COUNT + BAT_START_MEAS_COUNT)+1).leftJustified(9, ' ');
            bat = true;
        }

        if(bat)
        {
            divLine = "+---------+---------+\n";
        }

        protocolText += divLine + '|' + testName + '|';

        for(int i = 0; i < MEAS_TYPES_COUNT; i++){

            if(bat)
            {
                i = 4;
            }

            double max, min;
            QString numString;
            numString = QString::number(values[i], 10, 2);
            if(testNum == 0){
                //---První měření, tj. zdroj naprázdno---//
                max = limits_open.at(2*i);
                min = limits_open.at(2*i+1);
            }
            else
            {
                //---Další měření, tj. zdroj v zátěži---//
                max = limits_short.at(2*i);
                min = limits_short.at(2*i+1);
            }
            //---Vyhodnoť a převeď data---//
            if((values[i] < min || values[i] > max) && bat == false){
                //---Změřená hodnota je mimo dané meze---//
                testResult = false;
                numString.append(" -");
            }
            else
            {
                numString.append(" +");
            }
                    
                    
            if(numString.length() > 9){
                //---Zkrať na sedm a přidej ".."---//
                numString.resize(7);
                numString.append("..|");
                protocolText += numString;
            }
            else
            {
                protocolText += numString;
                for (int x = 0; x < 9 - numString.length(); x++)
                {
                    protocolText += ' ';
                }
                protocolText += '|';
            }
            if(bat)
                break;
        }
        protocolText += '\n';

        doc->setPlainText(protocolText);
        doc->print(printer);
        return true;
    }
    else{
        //---Zapiš log o chybě zápisu---//
        errorLogs err;
        switch(retVal)
        {
            case 0:
                err = PROTOCOL_AND_LIMITS_OPEN_ERROR;
                break;
            case 1:
                err = PROTOCOL_OPEN_ERROR;
                break;
            case 2:
                err = LIMITS_OPEN_ERROR;
                break;
        }
        writeLog(path, err);

        return false;
    }
}

//_____Dopíše závěr protokolu a přepíše ho do pdf_____//
int File::makeProtocol()
{
    QString divLine = "+---------+---------+\n";
 
    //___Zapiš výsledek testu___//
    protocolText += divLine + "\n\n" + "Výsledek: ";
    if(testResult)
        protocolText += "+";
    else
        protocolText += "-";
    
    //___Zapiš pracovníka a datum___//
    protocolText += "\nProvedl: " + worker + "    dne: " + QDateTime::currentDateTime().toString("dd.MM.yyyy");

    doc->setPlainText(protocolText);
    doc->print(printer);

    return 1;
}

//====Práce s mezemi====//

//_____Kontrola umístění souboru limits___//
bool File::limitsCheck()
{
    JSON_handler confFile;
    return confFile.fileCheck();
}

//_____Uložení hodnot limit z formuláře do souboru_____//
void File::saveLimits()
{
    JSON_handler confFile;
    confFile.saveLimits(Form);
    disconnect(Form, SIGNAL(accepted()), this, SLOT(saveLimits()));
    delete(Form);
}

//_____Vytvoření formuláře pro nastavení mezních hodnot_____//
bool File::limitsSetup()
{
    //---Vytvořit okno s formulářem pro nastavení---//
    Form = new limits;
    Form->setWindowTitle("Nastavení mezních hodnot");
    //---Výchozí hodnoty nastav dle existujících hodnot---//
    JSON_handler confFile;
    confFile.setLimits(Form);
    //---Po potvrzení zapsat hodnoty do souboru---//
    connect(Form, SIGNAL(accepted()), this, SLOT(saveLimits()));
    //---Spušť formulář---//
    Form->exec();
    return true;
}


//=====Formulář mezí=====//
//_____Konstruktor_____//
limits::limits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::limits)
{
    ui->setupUi(this);
}

//_____Destruktor_____//
limits::~limits()
{
    delete ui;
}

//=====Kalibrace=====//
void File::calibration(unsigned int* values)
{
    QString voltages[7] = {"5V_Kon", "5V", "12V", "15V", "U_bat", "24V", "24V_O2"};
    double voltagesNum[7] = {5, 5, 12, 15, 8, 24, 24};
    bool Ok;

    //___Otevření souboru___//
    JSON_handler confFile;
    if(confFile.fileCheck()){

        double constants[MEAS_TYPES_COUNT];
        for (int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            voltages[i].prepend("Změřte napětí ");
            double refValue = QInputDialog::getDouble(nullptr, "Kalibrace", 
                    voltages[i], voltagesNum[i], voltagesNum[i] - 2, voltagesNum[i] + 2, 1, &Ok);
            if(Ok){
                //Přepočti na konstantu
                constants[i] = refValue/values[i];
            }
            else
            {
                if (QMessageBox::question(nullptr, "Kalibrace", "Opravdu chtete ukončit kalibraci?\nStávající hodnoty budou odstraněny!",
                    QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok){
                        emit calibrationCancelled();
                        return;
                    }
            }
            
        } 
        if(confFile.saveConstants(constants))
            emit calibrationOver();
        else
            QMessageBox::warning(nullptr, "Kalibrace", "Nepodařilo se zapsat hodnoty", QMessageBox::Ok);
    }
}

//====Logování chyb====//

void File::writeLog(QString path, errorLogs error, int argument)
{
    QString logFilePath = path.section('.', 0, 0);
    logFilePath.append("_log.txt");
    logFile->setFileName(logFilePath);

    if(logFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(logFile);
        QString timeStamp = QDateTime::currentDateTime().toString("hh:mm:ss");
        timeStamp.append('\t');
        timeStamp.append(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
        QString message;
        switch (error)
        {
        case DATA_LOSS: //Ztráta dat
            message = QString("!!!Ztráta dat %1!!!").arg(argument);
            break;

        case UNCOMPLETE_DATA: //Neúplný datový řádek
            message = QString("!!!Neúplný datový řetězec %1!!!").arg(argument);
            break;

        default:
            break;
        }
        
        out << timeStamp << "\t" << message << '\n';
        logFile->close();
    }
}

void File::writeLog(QString path, errorLogs error)
{
    QString logFilePath = path.section('.', 0, 0);
    logFilePath.append("_log.txt");
    logFile->setFileName(logFilePath);

    if(logFile->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(logFile);
        QString timeStamp = QDateTime::currentDateTime().toString("hh:mm:ss");
        timeStamp.append(' ');
        timeStamp.append(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
        QString message;
        switch (error)
        {
        case COM_INTERRUPTION: //Přerušení komunikace
            message = "Přerušení spojení";
            break;

        case COM_RECONNECTION: //Obnovení komunikace
            message = "Obnovení spojení";
            break;

        //---Chyby writeToFile---//
        //2 -> chyba protokolu
        //1 -> chyba limitsfile
        //0 -> chyba všeho

        case PROTOCOL_AND_LIMITS_OPEN_ERROR:
            message = "Nepodařilo se otevřít protokol a mezní hodnoty";
            break;

        case PROTOCOL_OPEN_ERROR:
            message = "Nepodařilo se otevřít mezní hodnoty";
            break;

        case LIMITS_OPEN_ERROR:
            message = "Nepodařilo se otevřít protokol";
            break;

        case HEATER_ERROR:
            message = "Chyba spuštění topení";
            break;

        case HEATER_TRIAC_ERROR:
            message = "Chyba vypínání topení";
            break;
        
        default:
            break;
        }

        out << timeStamp << "\t" << message << '\n';
        logFile->close();
    }
}

//_____Zobrazení chyb na konci testu_____//
void File::showLog()
{
    if(logFile->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(nullptr, "Průběh testu", QString::fromUtf8(logFile->readAll()), QMessageBox::Ok);
        logFile->close();
    }
}

//====Odstranění všech souborů testu====//

void File::removeAll()
{
    if(logFile->exists())
    {
        logFile->remove();
        delete logFile;
    }
}

//===Práce s JSON souborem pro configuraci===//
JSON_handler::JSON_handler()
{
    QDir srcDirectory = QDir(QCoreApplication::applicationDirPath());
    srcDirectory.cd(".src");
    QString confFilePath = srcDirectory.absoluteFilePath("config.json");
    confFile.setFileName(confFilePath);
}

void JSON_handler::setFileName(QString fileName)
{
    confFile.setFileName(fileName);
}

bool JSON_handler::fileCheck()
{
    return confFile.exists();
}

void JSON_handler::getWorkers(QStringList* workers)
{
    workers->clear();
    if(confFile.open(QIODevice::ReadOnly))
    {
        QString data = (QString)confFile.readAll();
        confFile.close();
        QJsonDocument confDoc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject confObj = confDoc.object();
        QJsonArray workersArray = confObj.value("workers").toArray();
        for (int i = 0; i < workersArray.size(); i++)
        {
            workers->push_back(workersArray.at(i).toString());
        } 
    }
}

void JSON_handler::addWorker(QString newWorker)
{
    if(confFile.open(QIODevice::ReadWrite))
    {
        QByteArray data = confFile.readAll();
        QJsonDocument confDoc = QJsonDocument::fromJson(data);
        QJsonObject confObj = confDoc.object();
        QJsonArray workersArray = confObj.value("workers").toArray();
        QJsonValue workerValue = QJsonValue(newWorker);
        workersArray.push_back(workerValue);
        confObj.insert("workers", workersArray);
        confDoc.setObject(confObj);
        confFile.resize(0);
        confFile.write(confDoc.toJson());
        confFile.close();
    }
}

void JSON_handler::saveLimits(limits* Form)
{
    if(confFile.open(QIODevice::ReadWrite))
    {
        QByteArray data = confFile.readAll();
        QJsonDocument confDoc = QJsonDocument::fromJson(data);
        QJsonObject confObj = confDoc.object();
        QJsonObject limitsObj = confObj.value("limits").toObject();
        
        QJsonObject twelveVolts = limitsObj.value("12Volts").toObject();
        twelveVolts.insert("maxOpen", Form->ui->twelveVoltsMax->value());
        twelveVolts.insert("minOpen", Form->ui->twelveVoltsMin->value());
        twelveVolts.insert("max", Form->ui->twelveVoltsMaxShort->value());
        twelveVolts.insert("min", Form->ui->twelveVoltsMinShort->value());
        limitsObj.insert("12Volts", twelveVolts);
        
        QJsonObject fifteenVolts = limitsObj.value("15Volts").toObject();
        fifteenVolts.insert("maxOpen", Form->ui->fifteenVoltsMax->value());
        fifteenVolts.insert("minOpen", Form->ui->fifteenVoltsMin->value());
        fifteenVolts.insert("max", Form->ui->fifteenVoltsMaxShort->value());
        fifteenVolts.insert("min", Form->ui->fifteenVoltsMinShort->value());
        limitsObj.insert("15Volts", fifteenVolts);
        
        QJsonObject twentyFourVolts = limitsObj.value("24Volts").toObject();
        twentyFourVolts.insert("maxOpen", Form->ui->twentyfourVoltsMax->value());
        twentyFourVolts.insert("minOpen", Form->ui->twentyfourVoltsMin->value());
        twentyFourVolts.insert("max", Form->ui->twentyfourVoltsMaxShort->value());
        twentyFourVolts.insert("min", Form->ui->twentyfourVoltsMinShort->value());
        limitsObj.insert("24Volts", twentyFourVolts);
        
        QJsonObject twentyFourVolts_oxy = limitsObj.value("24VoltsOxy").toObject();
        twentyFourVolts_oxy.insert("maxOpen", Form->ui->oxyMax->value());
        twentyFourVolts_oxy.insert("minOpen", Form->ui->oxyMin->value());
        twentyFourVolts_oxy.insert("max", Form->ui->oxyMaxShort->value());
        twentyFourVolts_oxy.insert("min", Form->ui->oxyMinShort->value());
        limitsObj.insert("24VoltsOxy", twentyFourVolts_oxy);
        
        QJsonObject kon = limitsObj.value("5VoltKon").toObject();
        kon.insert("maxOpen", Form->ui->fiveVoltsConMax->value());
        kon.insert("minOpen", Form->ui->fiveVoltsConMin->value());
        kon.insert("max", Form->ui->fiveVoltsConMaxShort->value());
        kon.insert("min", Form->ui->fiveVoltsConMinShort->value());
        limitsObj.insert("5VoltKon", kon);
        
        QJsonObject five = limitsObj.value("5Volts").toObject();
        five.insert("maxOpen", Form->ui->fiveVoltsMax->value());
        five.insert("minOpen", Form->ui->fiveVoltsMin->value());
        five.insert("max", Form->ui->fiveVoltsMaxShort->value());
        five.insert("min", Form->ui->fiveVoltsMinShort->value());
        limitsObj.insert("5Volts", five);
        
        QJsonObject batt = limitsObj.value("battery").toObject();
        batt.insert("maxOpen", Form->ui->ubatMax->value());
        batt.insert("minOpen", Form->ui->ubatMin->value());
        batt.insert("max", Form->ui->ubatMaxShort->value());
        batt.insert("min", Form->ui->ubatMinShort->value());
        limitsObj.insert("battery", batt);

        confObj.insert("limits", limitsObj);
        confDoc.setObject(confObj);
        confFile.resize(0);
        confFile.write(confDoc.toJson());
        confFile.close();
    }
    else
    {
        QMessageBox::warning(nullptr, "Nastavení mezí", "Nedošlo k uložení hodnot", QMessageBox::Ok);
    }
}

void JSON_handler::setLimits(limits* Form)
{
    if(confFile.open(QIODevice::ReadOnly))
    {
        QString data = (QString)confFile.readAll();
        confFile.close();
        QJsonDocument confDoc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject confObj = confDoc.object();
        QJsonObject limitsObj = confObj.value("limits").toObject();

        QJsonObject fiveVoltsCon = limitsObj.value("5VoltKon").toObject();
        Form->ui->fiveVoltsConMax->setValue(fiveVoltsCon.value("maxOpen").toDouble());
        Form->ui->fiveVoltsConMin->setValue(fiveVoltsCon.value("minOpen").toDouble());
        Form->ui->fiveVoltsConMaxShort->setValue(fiveVoltsCon.value("max").toDouble());
        Form->ui->fiveVoltsConMinShort->setValue(fiveVoltsCon.value("min").toDouble());
        
        QJsonObject fiveVolts = limitsObj.value("5Volts").toObject();
        Form->ui->fiveVoltsMax->setValue(fiveVolts.value("maxOpen").toDouble());
        Form->ui->fiveVoltsMin->setValue(fiveVolts.value("minOpen").toDouble());
        Form->ui->fiveVoltsMaxShort->setValue(fiveVolts.value("max").toDouble());
        Form->ui->fiveVoltsMinShort->setValue(fiveVolts.value("min").toDouble());
        
        QJsonObject twelve = limitsObj.value("12Volts").toObject();
        Form->ui->twelveVoltsMax->setValue(twelve.value("maxOpen").toDouble());
        Form->ui->twelveVoltsMin->setValue(twelve.value("minOpen").toDouble());
        Form->ui->twelveVoltsMaxShort->setValue(twelve.value("max").toDouble());
        Form->ui->twelveVoltsMinShort->setValue(twelve.value("min").toDouble());
        
        QJsonObject fifteen = limitsObj.value("15Volts").toObject();
        Form->ui->fifteenVoltsMax->setValue(fifteen.value("maxOpen").toDouble());
        Form->ui->fifteenVoltsMin->setValue(fifteen.value("minOpen").toDouble());
        Form->ui->fifteenVoltsMaxShort->setValue(fifteen.value("max").toDouble());
        Form->ui->fifteenVoltsMinShort->setValue(fifteen.value("min").toDouble());
        
        QJsonObject uBat = limitsObj.value("battery").toObject();
        Form->ui->ubatMax->setValue(uBat.value("maxOpen").toDouble());
        Form->ui->ubatMin->setValue(uBat.value("minOpen").toDouble());
        Form->ui->ubatMaxShort->setValue(uBat.value("max").toDouble());
        Form->ui->ubatMinShort->setValue(uBat.value("min").toDouble());
        
        QJsonObject twentyFour = limitsObj.value("24Volts").toObject();
        Form->ui->twentyfourVoltsMax->setValue(twentyFour.value("maxOpen").toDouble());
        Form->ui->twentyfourVoltsMin->setValue(twentyFour.value("minOpen").toDouble());
        Form->ui->twentyfourVoltsMaxShort->setValue(twentyFour.value("max").toDouble());
        Form->ui->twentyfourVoltsMinShort->setValue(twentyFour.value("min").toDouble());
        
        QJsonObject oxy = limitsObj.value("24VoltsOxy").toObject();
        Form->ui->oxyMax->setValue(oxy.value("maxOpen").toDouble());
        Form->ui->oxyMin->setValue(oxy.value("minOpen").toDouble());
        Form->ui->oxyMaxShort->setValue(oxy.value("max").toDouble());
        Form->ui->oxyMinShort->setValue(oxy.value("min").toDouble()); 
    }
}

bool JSON_handler::getLimits(std::vector<double>* limits_open, std::vector<double>* limits_short)
{
    limits_open->clear();
    limits_short->clear();
    if(confFile.open(QIODevice::ReadOnly))
    {
        QString data = (QString)confFile.readAll();
        confFile.close();
        QJsonDocument confDoc = QJsonDocument::fromJson(data.toUtf8());
        QJsonObject confObj = confDoc.object();
        QJsonObject limitsObj = confObj.value("limits").toObject();

        QJsonObject fiveVoltsCon = limitsObj.value("5VoltKon").toObject();
        limits_open->push_back(fiveVoltsCon.value("maxOpen").toDouble());
        limits_open->push_back(fiveVoltsCon.value("minOpen").toDouble());
        limits_short->push_back(fiveVoltsCon.value("max").toDouble());
        limits_short->push_back(fiveVoltsCon.value("min").toDouble());
        
        QJsonObject fiveVolts = limitsObj.value("5Volts").toObject();
        limits_open->push_back(fiveVolts.value("maxOpen").toDouble());
        limits_open->push_back(fiveVolts.value("minOpen").toDouble());
        limits_short->push_back(fiveVolts.value("max").toDouble());
        limits_short->push_back(fiveVolts.value("min").toDouble());
        
        QJsonObject twelve = limitsObj.value("12Volts").toObject();
        limits_open->push_back(twelve.value("maxOpen").toDouble());
        limits_open->push_back(twelve.value("minOpen").toDouble());
        limits_short->push_back(twelve.value("max").toDouble());
        limits_short->push_back(twelve.value("min").toDouble());
        
        QJsonObject fifteen = limitsObj.value("15Volts").toObject();
        limits_open->push_back(fifteen.value("maxOpen").toDouble());
        limits_open->push_back(fifteen.value("minOpen").toDouble());
        limits_short->push_back(fifteen.value("max").toDouble());
        limits_short->push_back(fifteen.value("min").toDouble());
        
        QJsonObject uBat = limitsObj.value("battery").toObject();
        limits_open->push_back(uBat.value("maxOpen").toDouble());
        limits_open->push_back(uBat.value("minOpen").toDouble());
        limits_short->push_back(uBat.value("max").toDouble());
        limits_short->push_back(uBat.value("min").toDouble());
        
        QJsonObject twentyFour = limitsObj.value("24Volts").toObject();
        limits_open->push_back(twentyFour.value("maxOpen").toDouble());
        limits_open->push_back(twentyFour.value("minOpen").toDouble());
        limits_short->push_back(twentyFour.value("max").toDouble());
        limits_short->push_back(twentyFour.value("min").toDouble());
        
        QJsonObject oxy = limitsObj.value("24VoltsOxy").toObject();
        limits_open->push_back(oxy.value("maxOpen").toDouble());
        limits_open->push_back(oxy.value("minOpen").toDouble());
        limits_short->push_back(oxy.value("max").toDouble());
        limits_short->push_back(oxy.value("min").toDouble()); 
        
        return true;
    }
    else
        return false;
}

QString JSON_handler::getDefaultPath()
{
    if(confFile.open(QIODevice::ReadOnly))
    {
        QString data = (QString)confFile.readAll();
        confFile.close();
        QJsonDocument confDoc = QJsonDocument::fromJson(data.toUtf8());
        if(!confDoc.isObject()){
            return nullptr;
        }
        QJsonObject confObj = confDoc.object();
        return confObj.value("defaultPath").toString();
    }
    else
        return nullptr;
}

void JSON_handler::setDefaultPath(QString fileName)
{
    QString defaultDir = fileName.section('/', 0, -2).append("/");
    if(confFile.open(QIODevice::ReadWrite))
    {
        QString data = (QString)confFile.readAll();
        QJsonDocument confDoc = QJsonDocument::fromJson(data.toUtf8());
        if(!confDoc.isObject()){
            QMessageBox::information(nullptr, "defaultPath", "fuky fuk", QMessageBox::Ok);
            return;
        }
        QJsonObject confObj = confDoc.object();
        confObj.insert("defaultPath", defaultDir);
        confDoc.setObject(confObj);
        confFile.resize(0);
        confFile.write(confDoc.toJson());
        confFile.close();
    }
}

bool JSON_handler::getConstants(double* constantsValues)
{
    if (confFile.open(QIODevice::ReadOnly))
    {
        QString data = (QString)confFile.readAll();
        confFile.close();
        QJsonDocument confDoc = QJsonDocument::fromJson(data.toUtf8());
        if(!confDoc.isObject())
            return false;
        QJsonObject confObj = confDoc.object();
        QJsonArray constants = confObj.value("calibration").toArray();
        if(MEAS_TYPES_COUNT != constants.size())
            return false;
        for (int i = 0; i < constants.size(); i++)
        {
            constantsValues[i] = constants.at(i).toDouble();
        }
        
        return true;
    }
    else
        return false;
}

bool JSON_handler::saveConstants(double* constants)
{
    if(confFile.open(QIODevice::ReadWrite))
    {
        QByteArray data = confFile.readAll();
        QJsonDocument confDoc = QJsonDocument::fromJson(data);
        QJsonObject confObj = confDoc.object();
        QJsonArray constantsArray = confObj.value("calibration").toArray();
        /*if(MEAS_TYPES_COUNT != constantsArray.size())
            return false;*/
        for (int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            constantsArray.replace(i, QJsonValue(constants[i]));
            //constantsArray.at(i).toDouble(constants[i]);
        }
        confObj.insert("calibration", constantsArray);
        confDoc.setObject(confObj);
        confFile.resize(0);
        confFile.write(confDoc.toJson());
        confFile.close();
        return true;
    }
    return false;
}
