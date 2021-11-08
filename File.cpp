#include "File.h"
#include "ui_limits.h"

File::File()
{
    //---Nastavení cesty k souboru meze podle domovského adresáře---//
    QString tmp = homePath1;
    limitsFile.setFileName(tmp.append(limitsPath));
    if(!limitsFile.exists()){
        tmp = homePath2;
        limitsFile.setFileName(tmp.append(limitsPath));
        if(limitsFile.exists())
            homePath1 = homePath2;  //homePath1 je výsledná platná adresa
        else
        {
            QMessageBox::critical(nullptr, "Chyba souborového systému!",
                "Důležité soubory neexistují, nebo byly přesunuty", QMessageBox::Ok);
        }
        
    }
    limitsPath = limitsFile.fileName();
    
    defaultPath.prepend(homePath1);
    calibPath.prepend(homePath1);
    patternPath.prepend(homePath1);

    logFile = new QFile;
}

File::~File()
{
    if(this->isOpen())
        this->close();
}

QString File::getPath()
{
    QString dateStr = QDateTime::currentDateTime().toString("_dd_MM_yy");
    bool Ok;
    serialNumber = QInputDialog::getText(nullptr, "Sériové číslo",
            "Zadejte sériové číslo testovaného zdroje", QLineEdit::Normal, 
            "Zde zapište sériové číslo", &Ok);
    if (!Ok)    return nullptr;
    QString fileName = serialNumber;
    fileName.append(dateStr);
    worker = QInputDialog::getText(nullptr, "Jméno pracovníka",
            "Zadejte své jméno", QLineEdit::Normal, 
            "", &Ok);
    if (!Ok)    return nullptr;
    QFile file;
    file.setFileName(defaultPath);
    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        QString filePath = file.readLine();
        fileName = QFileDialog::getSaveFileName(nullptr,
            tr("Vytvořit soubor"), filePath.append(fileName),
            tr("PDF File (*.pdf);;All Files (*)"));
    }
    else{
        fileName = QFileDialog::getSaveFileName(nullptr,
            tr("Vytvořit soubor"), "",
            tr("PDF File (*.pdf);;All Files (*)"));
    }
    return fileName;
}

int File::createFile(QString path)
{
    //-----------------TXT-------------------//
    this->setFileName(path);
    this->path = path;
    if(!(QFile::copy(this->patternPath, path))){
        QMessageBox::warning(nullptr, tr("Zahořování zdrojů"), tr("Nepodařilo se otevřít soubor %1").arg(path), QMessageBox::Cancel);
        return 0;
    }
    QString defaultDir = dir.absoluteFilePath(path);
    defaultDir = defaultDir.section('/', 0, -2);
    defaultDir.append("/");
    QFile file;
    file.setFileName(defaultPath);
    if(file.open(QIODevice::WriteOnly) | QIODevice::Truncate)
    {
        file.write(defaultDir.toLatin1());
        file.close();
    }

    //----------------PDF--------------------//

    doc = new QTextDocument;
    cursor = new QTextCursor(doc);
    cursor->movePosition(QTextCursor::Start);
    /*QTextCharFormat font;
    font.setFontPointSize(16000);
    cursor->insertText(QString("Zahoření Zdroje\n\n"), font);
    QTextTableFormat format;
    format.setHeaderRowCount(1);
    format.setBorderCollapse(true);
    QVector<QTextLength> lenghtVec;
    for (int i = 0; i < 8; i++)
    {
        QTextLength lenght(QTextLength::FixedLength, 100);
        lenghtVec.push_back(lenght);
    }
    format.setColumnWidthConstraints(lenghtVec);
    QTextTable* table = cursor->insertTable(6, 8, format);
    QTextTableCell headerCell;
    std::vector<QString> headerRow = {"", "5V/1", "5V KON", "12V", "15V", "24V O2", "24V", "U_BAT"};
    for (int i = 0; i < 8; i++)
    {
        headerCell = table->cellAt(0, i);
        QTextCursor cellCursor = headerCell.firstCursorPosition();
        cellCursor.insertText(headerRow.at(i));
    }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(pathPDF);

    //doc->setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc->print(&printer);*/
    

    return 1;
}

bool File::getConstants()
{
    QFile calibFile;
    calibFile.setFileName(calibPath);
    if(calibFile.open(QIODevice::ReadOnly)){
        QTextStream in(&calibFile);
        QString calibData = in.readLine();
        for (int i = 0; i < 7; i++)
        {
            transfer[i] = calibData.section(';', i, i).toDouble();
        }
        return true;
    }
    return false;
}

std::vector<QString> File::makeArray(QString message, int testNum)
{
    std::vector<QString> values;
    if(testNum >= (START_MEAS_COUNT + MAIN_MEAS_COUNT))  //měření baterie
    {
        values.resize(MEAS_TYPES_COUNT);
        values.at(4) = message.section(';', 0, 0);
    }
    else
    {    
        for (int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            QString val = message.section(';', i, i);
            if(val.isEmpty() || val == "0") //Hodnota chybí nebo je nulová
            {
                std::vector<QString> nullVec;
                return nullVec;
            }
            //QMessageBox::information(nullptr, "Kalibrace", val, QMessageBox::Ok);
            values.push_back(val);
        }
    }
    return values;
}

std::vector<QString> File::makeValues(std::vector<QString> valuesADC)
{
    std::vector<QString> values;
    for (int i = 0; i < MEAS_TYPES_COUNT; i++)
    {
        getConstants();
        double voltage = valuesADC.at(i).toDouble()*transfer[i];
        int prec = (voltage >= 10)? 4 : 3;
        QString val = (voltage == 0)? "-" : QString::number(voltage, 'g', prec);
        values.push_back(val);
    }
    
    return values;
}

bool File::writeToFile(std::vector<QString> values, unsigned char testType, unsigned char testNum)
{
    static bool bat = false;
    unsigned int retVal = 0;
    this->setFileName(path);
    QTextStream out2(this), meze(&limitsFile);

    QString divLine = "+---------+---------+---------+---------+---------+---------+---------+---------+\n";

    if(this->isOpen())
        this->close();
    if(limitsFile.isOpen())
        limitsFile.close();

    retVal = this->open(QIODevice::WriteOnly | QIODevice::Append) | (limitsFile.open(QIODevice::ReadOnly) << 1);
        //3 -> vše v pořádku
        //2 -> chyba protokolu
        //1 -> chyba limitsfile
        //0 -> chyba všeho

    if(retVal == 3){
        QString testName;

        if(testNum == 0)
        {
            out2 << "Seriove cislo zdroje: " << serialNumber << "\n\n";
            out2 << divLine;
            out2 << "|         | 5V_KON  | 5V      | 12V     | 15V     | U_bat   | 24V     | 24V_O2  |\n";
        }

        if(testNum < START_MEAS_COUNT) //Start testu
        {
            //out2 << "začátek\n";
            testName = "start    ";
            bat = false;
        }

        else if(testNum < (START_MEAS_COUNT + MAIN_MEAS_COUNT))   //hlavní test
        {
            //out2 << "Hlavní test\n";
            if(testNum == START_MEAS_COUNT)   //První měření hlavního testu
            {
                out2 << divLine;
            }
            testName = QString("Mereni %1").arg(testNum-START_MEAS_COUNT+1).leftJustified(9, ' ');
            bat = false;
        }

        else if(testNum < (START_MEAS_COUNT + MAIN_MEAS_COUNT + BAT_START_MEAS_COUNT))   //baterie start
        {
            //out2 << "baterie\n";
            out2 << divLine << '\n' << "Baterie\n";
            testName = "baterie  ";
            bat = true;
        }
        
        else  //test baterie
        {
            //out2 << "baterie test\n";
            testName = QString("Mereni %1").arg(testNum-(START_MEAS_COUNT + MAIN_MEAS_COUNT + BAT_START_MEAS_COUNT)+1).leftJustified(9, ' ');
            bat = true;
        }

        

        if(bat)
        {
            divLine = "+---------+---------+\n";
        }

        out2 << divLine;
        out2 << '|' << testName << '|';

        for(int i = 0; i < MEAS_TYPES_COUNT; i++){
            //---Načti a zpracuj limitní hodnoty---//
            QString limitsLine = meze.readLine();

            if(bat)
            {
                i = 4;
                for (int j = 0; j < i-1; j++)
                {
                    limitsLine = meze.readLine();
                }
                
            }
            
            double max, min;
            if(testNum == 0){
                //---První měření, tj. zdroj naprázdno---//
                max = limitsLine.section(';', 0, 0).toDouble();
                min = limitsLine.section(';', 1, 1).toDouble();
            }
            else
            {
                //---Další měření, tj. zdroj v zátěži---//
                max = limitsLine.section(';', 2, 2).toDouble();
                min = limitsLine.section(';', 3, 3).toDouble();
            }
            double voltage = values.at(i).toDouble();
            //---Vyhodnoť a převeď data---//
            if((voltage < min || voltage > max) && bat == false){
                //---Změřená hodnota je mimo dané meze---//
                testResult = false;
                values.at(i).append(" -");
            }
            else
            {
                values.at(i).append(" +");
            }
                    
                    
            if(values.at(i).length() > 9){
                //---Zkrať na sedm a přidej ".."---//
                values.at(i).resize(7);
                values.at(i).append("..|");
                out2 << values.at(i);
            }
            else
            {
                        
                out2 << values.at(i);
                for (int x = 0; x < 9 - values.at(i).length(); x++)
                {
                    out2 << ' ';
                }
                out2 << '|';
            }
            if(bat)
                break;
        }
        meze.seek(0);
        out2 << "\n";

        this->close();
        return true;
    }
    else{
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
        writeLog(err);
        return false;
    }
}

int File::makeProtocol()
{
    QTextStream out(this);

        QString divLine = "+---------+---------+\n";
        this->setFileName(path);
        if(limitsFile.isOpen())
            limitsFile.close();
        if(this->isOpen())
            this->close();

        if(this->open(QIODevice::WriteOnly | QIODevice::Append)){   
            out << divLine  << "\n\n" << "Vysledek: ";
            if(testResult)
                out << "+";
            else
                out << "-";
            
            out << "\nProvedl: " << worker << "    dne: " << QDateTime::currentDateTime().toString("dd.MM.yyyy");

            this->close();

            this->open(QIODevice::ReadOnly);

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(pathPDF);
            printer.setOrientation(QPrinter::Landscape);

            QTextDocument doc;

            this->seek(0);
            QFont font("Courier", 1);
            font.setFixedPitch(true);
            doc.setDefaultFont(font);
            doc.setPlainText(QString::fromLatin1(this->readAll()));

            doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
            doc.print(&printer);

            this->close();

            this->remove();

            return 1;
        }
        else
        {
            return 0;  
        }
}

//====Práce s mezemi====//

bool File::limitsCheck()
{
    bool ret;
    limitsFile.setFileName(limitsPath);
    ret = limitsFile.open(QIODevice::ReadOnly);
    ret = ret && limitsFile.size();
    limitsFile.close();
    return ret;
}

void File::saveLimits()
{
    if(limitsFile.isOpen())
        limitsFile.close();
    if(limitsFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QTextStream out(&limitsFile);
        //---Přečti a ulož hodnoty z formuláře---//
        out << (QString::number(Form->ui->fiveVoltsMax->value())).append(';');
        out << (QString::number(Form->ui->fiveVoltsMin->value())).append(';');
        out << (QString::number(Form->ui->fiveVoltsMaxShort->value())).append(';');
        out << (QString::number(Form->ui->fiveVoltsMinShort->value())).append(';');
        out << '\n';
        out << (QString::number(Form->ui->fiveVoltsConMax->value())).append(';');
        out << (QString::number(Form->ui->fiveVoltsConMin->value())).append(';');
        out << (QString::number(Form->ui->fiveVoltsConMaxShort->value())).append(';');
        out << (QString::number(Form->ui->fiveVoltsConMinShort->value())).append(';');
        out << '\n';
        out << (QString::number(Form->ui->twelveVoltsMax->value())).append(';');
        out << (QString::number(Form->ui->twelveVoltsMin->value())).append(';');
        out << (QString::number(Form->ui->twelveVoltsMaxShort->value())).append(';');
        out << (QString::number(Form->ui->twelveVoltsMinShort->value())).append(';');
        out << '\n';
        out << (QString::number(Form->ui->fifteenVoltsMax->value())).append(';');
        out << (QString::number(Form->ui->fifteenVoltsMin->value())).append(';');
        out << (QString::number(Form->ui->fifteenVoltsMaxShort->value())).append(';');
        out << (QString::number(Form->ui->fifteenVoltsMinShort->value())).append(';');
        out << '\n';
        out << (QString::number(Form->ui->ubatMax->value())).append(';');
        out << (QString::number(Form->ui->ubatMin->value())).append(';');
        out << (QString::number(Form->ui->ubatMaxShort->value())).append(';');
        out << (QString::number(Form->ui->ubatMinShort->value())).append(';');
        out << '\n';
        out << (QString::number(Form->ui->twentyfourVoltsMax->value())).append(';');
        out << (QString::number(Form->ui->twentyfourVoltsMin->value())).append(';');
        out << (QString::number(Form->ui->twentyfourVoltsMaxShort->value())).append(';');
        out << (QString::number(Form->ui->twentyfourVoltsMinShort->value())).append(';');
        out << '\n';
        out << (QString::number(Form->ui->oxyMax->value())).append(';');
        out << (QString::number(Form->ui->oxyMin->value())).append(';');
        out << (QString::number(Form->ui->oxyMaxShort->value())).append(';');
        out << (QString::number(Form->ui->oxyMinShort->value())).append(';');


        //---Uveď vše do původního stavu---//
        limitsFile.close();
        disconnect(Form, SIGNAL(accepted()), this, SLOT(saveLimits()));
        delete(Form);
    }
    else
    {
        QMessageBox::warning(nullptr, "Nastavení mezí", "Nedošlo k uložení hodnot", QMessageBox::Ok);
    }
}

bool File::limitsSetup()
{
    limitsFile.setFileName(limitsPath);

    //---Vytvořit okno s formulářem pro nastavení---//
    Form = new limits;
    Form->setWindowTitle("Nastavení mezních hodnot");
    //---Výchozí hodnoty nastav dle existujících hodnot---//
    if(limitsFile.open(QIODevice::ReadOnly))
    {
        double val[MEAS_TYPES_COUNT][4];
        for(int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            QString line = limitsFile.readLine();
            for (int j = 0; j < 4; j++)
            {
                val[i][j] = line.section(';', j, j).toDouble();
            }   
        }
        Form->ui->fiveVoltsConMax->setValue(val[0][0]);
        Form->ui->fiveVoltsConMin->setValue(val[0][1]);
        Form->ui->fiveVoltsConMaxShort->setValue(val[0][2]);
        Form->ui->fiveVoltsConMinShort->setValue(val[0][3]);

        Form->ui->fiveVoltsMax->setValue(val[1][0]);
        Form->ui->fiveVoltsMin->setValue(val[1][1]);
        Form->ui->fiveVoltsMaxShort->setValue(val[1][2]);
        Form->ui->fiveVoltsMinShort->setValue(val[1][3]);
        
        Form->ui->twelveVoltsMax->setValue(val[2][0]);
        Form->ui->twelveVoltsMin->setValue(val[2][1]);
        Form->ui->twelveVoltsMaxShort->setValue(val[2][2]);
        Form->ui->twelveVoltsMinShort->setValue(val[2][3]);
        
        Form->ui->fifteenVoltsMax->setValue(val[3][0]);
        Form->ui->fifteenVoltsMin->setValue(val[3][1]);
        Form->ui->fifteenVoltsMaxShort->setValue(val[3][2]);
        Form->ui->fifteenVoltsMinShort->setValue(val[3][3]);
        
        Form->ui->ubatMax->setValue(val[4][0]);
        Form->ui->ubatMin->setValue(val[4][1]);
        Form->ui->ubatMaxShort->setValue(val[4][2]);
        Form->ui->ubatMinShort->setValue(val[4][3]);
        
        Form->ui->twentyfourVoltsMax->setValue(val[5][0]);
        Form->ui->twentyfourVoltsMin->setValue(val[5][1]);
        Form->ui->twentyfourVoltsMaxShort->setValue(val[5][2]);
        Form->ui->twentyfourVoltsMinShort->setValue(val[5][3]);
        
        Form->ui->oxyMax->setValue(val[6][0]);
        Form->ui->oxyMin->setValue(val[6][1]);
        Form->ui->oxyMaxShort->setValue(val[6][2]);
        Form->ui->oxyMinShort->setValue(val[6][3]);
    }
    limitsFile.close();
    //---Po potvrzení zapsat hodnoty do souboru---//
    connect(Form, SIGNAL(accepted()), this, SLOT(saveLimits()));
    //---Spušť formulář---//
    Form->exec();
}


//=====Formulář mezí=====//
limits::limits(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::limits)
{
    ui->setupUi(this);
}

limits::~limits()
{
    delete ui;
}

//=====Kalibrace=====//
void File::calibration(std::vector<QString> values)
{
    QString voltages[7] = {"5V_Kon", "5V", "12V", "15V", "U_bat", "24V", "24V_O2"};
    double voltagesNum[7] = {5, 5, 12, 15, 8, 24, 24};
    bool Ok;
    QFile calibFile;
    calibFile.setFileName(calibPath);
    if(calibFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
                
        QTextStream out(&calibFile);

        for (int i = 0; i < 7; i++)
        {
            voltages[i].prepend("Změřte napětí ");
            double value = QInputDialog::getDouble(nullptr, "Kalibrace", 
                    voltages[i], voltagesNum[i], voltagesNum[i] - 2, voltagesNum[i] + 2, 1, &Ok);
            if(Ok){
                //Přepočti na konstantu
                QString meas = values.at(i);
                double constant = value/meas.toDouble();
                out << constant << ';';
            }
            else
            {
                if (QMessageBox::question(nullptr, "Kalibrace", "Opravdu chtete ukončit kalibraci?",
                    QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok){
                        break;
                    }
            }
            
        } 

        calibFile.close();
        emit calibrationOver();
    }
}

//====Logování chyb====//

void File::writeLog(errorLogs error, int argument)
{

    QString logFilePath = this->fileName().section('.', 0, 0);
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
        
        default:
            break;
        }
        
        out << timeStamp << "\t" << message << '\n';
        logFile->close();
    }
}

void File::writeLog(errorLogs error)
{
    QString logFilePath = this->fileName().section('.', 0, 0);
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
        case DATA_LOSS: //Ztráta dat
            message = QString("!!!Ztráta dat %1!!!");
            break;

        case UNCOMPLETE_DATA: //Neúplný datový řádek
            message = QString("!!!Neúplný datový řetězec %1!!!");
            break;

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
        
        default:
            break;
        }

        out << timeStamp << "\t" << message << '\n';
        logFile->close();
    }
}

void File::showLog()
{
    if(logFile->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(nullptr, "Průběh testu", QString::fromLatin1(logFile->readAll()), QMessageBox::Ok);
        logFile->close();
    }
}

void File::removeAll()
{
    this->remove();
    if(logFile != nullptr)
    {
        logFile->remove();
        delete logFile;
    }
}
