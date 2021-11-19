#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Zahoření zdrojů");

    ui->testPhase->setText("Fáze testu: Test nebyl spuštěn");

    port = new Serial;
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);

    file = new File;
    QString tmp = file->homePath1;
    connect(file, SIGNAL(calibrationOver()), this, SLOT(endCalibration()));

    statusBarTimer = new QTimer;
    statusBarTimer->setSingleShot(true);
    statusBarTimer->setInterval(3000);
    connect(statusBarTimer, SIGNAL(timeout()), ui->statusbar, SLOT(clearMessage()));

    //connect(ui->Power, SIGNAL(clicked()), this, SLOT(powerManage()));
    connect(ui->menuCOM, SIGNAL(aboutToShow()), this, SLOT(getCOMs()));
    connect(ui->menuN_stroje, SIGNAL(triggered(QAction*)), this, SLOT(toolManage(QAction*)));
    connect(ui->menuZaho_en, SIGNAL(triggered(QAction*)), this, SLOT(zahoreniManage(QAction*)));
    connect(port, SIGNAL(readyRead()), this, SLOT(read()));

    //ui->stepBack->setFlat(true);
    //ui->nextStep->setFlat(true);

    timer = new QTimer;
    
    endTimer = new QTimer;
    endTimer->setSingleShot(true);
    endTimer->setInterval(500);
    connect(endTimer, SIGNAL(timeout()), this, SLOT(endMeasure()));

    serialTimer = new QTimer;
    serialTimer->setSingleShot(true);
    serialTimer->setInterval(3000);
    connect(serialTimer, SIGNAL(timeout()), this, SLOT(serialError()));

    ui->COMconnected->setStyleSheet("QLabel { background: red; color: white; font-size: 16px;}");
}

MainWindow::~MainWindow()
{
    serialTimer->stop();
    if(measureInProgress)
    {
        file->makeProtocol();
        port->writePaket(CANCEL_PAKET, 0);
    }
    delete port;
    delete file;
    delete ui;
}

void MainWindow::endMeasure()
{
    //---Ukončení testu---//
    ui->statusbar->showMessage("Ukončení");
    statusBarTimer->start();

    if(!file->makeProtocol()){
        QMessageBox::warning(this, "Ukončení testu", QString("Nedošlo k řádnému ukončení testu."),
        QMessageBox::Ok);
    }
    else
    {
        if(errorCount || warningCount){
            if(QMessageBox::information(nullptr, "Ukončení testu",
            QString("Protokol vygenerován\nPočet vážných chyb: %1\nPočet drobných chyb: %2\n\nPřejete si zobrazit log?").arg(errorCount).arg(warningCount),
                QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
            {
                file->showLog();
            }
        }
        else
        {
            QMessageBox::information(nullptr, "Ukončení testu",
            QString("Protokol vygenerován"),
                QMessageBox::Ok);
        }   
    }
            
    measureInProgress = false;
    errorCount = 0;
    warningCount = 0;
                
    /*if(manualMode){
        ui->stepBack->setFlat(true);
        ui->nextStep->setFlat(true);
        disconnect(ui->nextStep, SIGNAL(clicked()), port, SLOT(next()));
        disconnect(ui->stepBack, SIGNAL(clicked()), port, SLOT(back()));
    }*/

    lastNum = 0;
    commandNum = 0;


}

/*void MainWindow::powerManage(){
    if(ui->Power->isChecked() && port->serialConnected){
        int ret = QMessageBox::information  (this, tr("Zahořování zdrojů"),
                                            tr("Opravdu si přejete spustit napájení zdroje?"),
                                            QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            ui->Power->setChecked(true);
            ui->statusbar->showMessage("Zapínání napájení");
            statusBarTimer->start();
            //---pošli příkaz k zapnutí napájení---//
        }
        else
            ui->Power->setChecked(false);
    }
    else if(ui->Power->isChecked()){
        QMessageBox::warning (this, tr("Zahořování zdrojů"),
                                tr("Nejprve je nutné připojit port!"));
        ui->Power->setChecked(false);
    }
}*/

void MainWindow::zahoreniManage(QAction* action){
    if(action->text() == "Spustit"){
        if(measureInProgress){
            QMessageBox::information(this, "Zahoření zdrojů", "Nejdříve ukončete probíhající test", QMessageBox::Ok);
        }
        else if(port->serialConnected){
            
            serialTimer->stop();
            disconnect(serialTimer, SIGNAL(timeout()), this, SLOT(serialError()));
            //---Kontrola souboru meze---//
            if(!file->limitsCheck()){
                //---Soubor "meze" je narušen nebo chybí---//
                QMessageBox::warning (this, tr("Zahořování zdrojů"),
                                    tr("Nejdříve nastavte krajní hodnoty pro test"));
                return;
            }
            //---Zjistit mod měření---//
            /*bool Ok;
            QStringList list;
            list << "Automatický" << "Manuální";
            if (QInputDialog::getItem(this, "Režim", "Vyberte režim testu", list, 0, false, &Ok) == "Automatický")
            {
                manualMode = false;
                ui->stepBack->setFlat(true);
                ui->nextStep->setFlat(true);
                disconnect(ui->nextStep, SIGNAL(clicked()), port, SLOT(next()));
                disconnect(ui->stepBack, SIGNAL(clicked()), port, SLOT(back()));
            }
            else
            {
                manualMode = true;
                ui->stepBack->setFlat(false);
                ui->nextStep->setFlat(false);
                connect(ui->nextStep, SIGNAL(clicked()), port, SLOT(next()));
                connect(ui->stepBack, SIGNAL(clicked()), port, SLOT(back()));
            }
            if(Ok){*/
            
                //---Zjistit požadovaný název a umístění---//
                file->pathPDF = file->getPath();
                QString path = file->pathPDF.section('.', 0, 0);
                path = path.append(".txt");
                serialTimer->setInterval(1100);
                serialTimer->start();
                connect(serialTimer, SIGNAL(timeout()), this, SLOT(serialError()));
                //---Vytvoř a otevři soubor (režim ReadWrite)---//
                if(!path.isEmpty() && path != nullptr){
                    if(file->createFile(path)){ 
                        measureInProgress = true;
                        file->testResult = true;
                        lastNum = 0;
                        
                        //---odešli příkaz k zahájení testu---//
                        if(QMessageBox::information(this, "Zahoření zdrojů",
                        "Připojte a spustě testovaný zdroj\nPoté stiskněte OK pro pokračování",
                        QMessageBox::Ok) == QMessageBox::Ok){
                            ui->testPhase->setText("Fáze testu: Test spuštěn");
                            ui->actualResult->setText("Průběžný výsledek: Ano");
                            ui->errorCount->setText(ui->errorCount->text().section(':', 0, 0).append(": 0"));
                            ui->resultTable->clearContents();
                            if(manualMode)
                                port->writePaket(MANUAL_PAKET, 0);
                            else
                            {
                                port->writePaket(START_PAKET, 0);
                                startTimer = new QTimer;
                                startTimer->setInterval(2000);
                                startTimer->setSingleShot(true);
                                connect(startTimer, SIGNAL(timeout()), this, SLOT(startError()));
                                startTimer->start();
                            }

                        }
                    }
                }
        }
        else
        {
            QMessageBox::warning(this, "Zahoření zdrojů", "Není připojeno zkušební zařízení pomocí COM portu", QMessageBox::Ok);
        }
        
    }
    else if(action->text() == "Zastavit"){
        if(measureInProgress){
            int ret = QMessageBox::question(this, "Zahořování zdrojů",
                    "Opravdu si přejete ukončit test?", QMessageBox::Ok,
                    QMessageBox::Cancel);
            if(ret == QMessageBox::Ok){
                ui->testPhase->setText("Fáze testu: Test přerušen");
                port->writePaket(CANCEL_PAKET, 0);
                endMeasure();
            }
        }
    }
    else if(action->text() == "Změnit meze"){
        file->limitsSetup();
    }
}

void MainWindow::getCOMs(){
    ui->menuCOM->clear();
    QList<QString> ports = port->getComs();
    if(ports.count()){
        foreach(QString name, ports){
            ui->menuCOM->addAction(name);
        }
        ui->menuCOM->addSeparator();
        ui->menuCOM->addAction(ui->actionOdpojit_port);
    }
    else{
        ui->menuCOM->addAction("Žádný dostupný port");
    }
}

void MainWindow::connectPort(QAction* action){
    if(action->text() == "Odpojit port")
    {
        if(port->serialConnected)
        {
            port->close();
            port->serialConnected = false;
            serialTimer->stop();
            ui->statusbar->showMessage("Odpojeno");
            statusBarTimer->start();
            ui->COMconnected->setText("COM: ODPOJENO");
            ui->COMconnected->setStyleSheet("QLabel { color: white; background: red; font-size: 16px;}");
        }
    }
    else
    {
        if(port->connectPort(action->text()))
        {
            ui->statusbar->showMessage(action->text());
            statusBarTimer->start();
            serialTimer->start();
            ui->COMconnected->setText("COM: PŘIPOJENO");
            ui->COMconnected->setStyleSheet("QLabel { color: white; background: green; font-size: 16px;}");
        }
        else
        {       
            ui->COMconnected->setText("COM: ODPOJENO");
            ui->COMconnected->setStyleSheet("QLabel { color: white; background: red; font-size: 16px;}");
        }
    }
}

void MainWindow::toolManage(QAction* action){
    if(action->text() != "Žádný dostupný port"){
        if(measureInProgress && !comError){
                QMessageBox::warning(this, "Zahoření zdrojů", "Akci nelze provádět v průběhu měření", QMessageBox::Ok);
        }
        else if(action->text() == "Kalibrace"){
            if(QMessageBox::information(nullptr, "Kalibrace", "Připojte a zapněte zdroj", 
                    QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok){
                port->writePaket(CALIB_PAKET, 0);
                calibInProgress = true;
                timer->setInterval(5000);
                timer->setSingleShot(true);
                //disconnect(port, SIGNAL(readyRead()), this, SLOT(read()));
                connect(timer, SIGNAL(timeout()), this, SLOT(calibrationFailure()));
                //connect(port, SIGNAL(readyRead()), this, SLOT(calibrationStart()));
                timer->start();
            }
        }
        else{
            connectPort(action);
        }
    }
}

//_____Funkce pro zpracování paketu_____//
void MainWindow::managePaket(Paket* paket)
{
    switch (paket->type)
    {
    case DATA_PAKET:
        dataManage(paket->data, paket->dataLength);
        break;

    case DATA_BAT_PAKET:
        dataBatManage(paket->data, paket->dataLength);
        break;
    
    case TEST_NUM_PAKET:
        testNumManage(*(paket->data));
        break;

    case TEST_PHASE_PAKET:
        testPhaseManage(*(paket->data));
        break;

    case ACK_PAKET:
        /* code */
        break;

    case REFRESH_PAKET:
        /* code */
        break;
    
    default:
        break;
    }

    //___Uvolni alokovanou paměť___//
    free(paket->data);
    free(paket);
}

void MainWindow::read(){
    //---Přečtení dat---//
    Paket* data = port->readData();
    if(data != nullptr)
    {
        managePaket(data);
    }

    //---Ošetření varování chyby spojení---//
    serialTimer->stop();
    serialTimer->setInterval(1100);
    serialTimer->start();
    ui->COMconnected->setText("COM: PŘIPOJENO");
    ui->COMconnected->setStyleSheet("QLabel { color: white; background: green; font-size: 16px;}");

    if(comError){
        comError = false;
        //QMessageBox::information(this, tr("Komunikace"), tr("Spojení s přípravkem obnoveno"), QMessageBox::Ok);
        if(measureInProgress)
            file->writeLog(COM_RECONNECTION);
    }

}

void MainWindow::serialError(){
    /*QMessageBox::critical(this, "Chyba komunikace", "Došlo k přerušení spojení.\nZkontrolujte připojení přípravku.",
    QMessageBox::Ok);*/
    if(measureInProgress)
    {
        warningCount++;
        file->writeLog(COM_INTERRUPTION);
    }
    serialTimer->stop();
    comError = true;
    ui->COMconnected->setText("COM: NEAKTIVNÍ");
    ui->COMconnected->setStyleSheet("QLabel { color: white; background: red; font-size: 16px;}");
}

void MainWindow::calibrationFailure(){
    timer->stop();
    QMessageBox::warning(this, "Kalibrace", "Zkontrolujte připojení přípravku a opakujte",
        QMessageBox::Ok);
    calibInProgress = false;
}

void MainWindow::endCalibration(){
    QMessageBox::information(this, "Kalibrace", "Kalibrace proběhla úspěšně.", QMessageBox::Ok);
    calibInProgress = false;
}

void MainWindow::testNumManage(char num)
{
    commandNum = num;
        
    if(commandNum != lastNum)
    {
        if(measureInProgress)
        {
            errorCount++;
            file->writeLog(DATA_LOSS, lastNum);
            ui->errorCount->setText(ui->errorCount->text().section(':', 0, 0).append(": ").append(QString::number(errorCount)));
        }
        lastNum = commandNum;
    }
    lastNum++;
}

void MainWindow::testPhaseManage(char phase)
{
    commandLetter = phase;
    //ui->statusbar->showMessage(QString("Command %1 %2").arg(commandLetter).arg(commandNum + 48));
    //statusBarTimer->start();
    
    switch (commandLetter)
    {
    case 'e':   //Konec testu
        endTimer->start();
        ui->testPhase->setText("Fáze testu: Test ukončen");
        break;

    case 's':   //Začátek testu
        ui->testPhase->setText("Fáze testu: Spouštění");
        if(startTimer != nullptr)
        {
            startTimer->stop();
            delete startTimer;
            startTimer = nullptr;
        }
        break;

    case 'm':   //Hlavní test
        ui->testPhase->setText("Fáze testu: Hlavní test v průběhu");
        break;

    case 'b':   //Baterie start
        ui->testPhase->setText("Fáze testu: Spouštění měření baterie");
        break;

    case 'M':   //Hlavní test baterie
        ui->testPhase->setText("Fáze testu: Hlavní test baterie v průběhu");
        break;
        
    default:
        break;
    }
}

void MainWindow::dataManage(char* data, char dataLength)
{
    if(dataLength == 2*MEAS_TYPES_COUNT)
    {
        unsigned int values[MEAS_TYPES_COUNT] = {0};
        for (int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            values[i] |= ((data[2*i] << 8) & 0xFF00);
            values[i] |= (data[2*i + 1] & 0xFF);
        }
        if(calibInProgress)
        {
            timer->stop();
            disconnect(timer, SIGNAL(timeout()), this, SLOT(calibrationFailure()));
            file->calibration(values);
        }
        else
        {
            float result[MEAS_TYPES_COUNT];
            file->makeValues(values, result);
            if(!(file->writeToFile(result, commandLetter, commandNum)))
            {
                errorCount++;
            }
            for (unsigned int i = 0; i < MEAS_TYPES_COUNT; i++)
            {
                QString num = QString::number(result[i], 10, 2);
                QTableWidgetItem* cell = new QTableWidgetItem(num);
                cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
                ui->resultTable->setItem(commandNum, i, cell);
            }
            if(file->testResult)
                ui->actualResult->setText("Průběžný výsledek: Ano");
            else
                ui->actualResult->setText("Průběžný výsledek: Ne");
        }

    }
    else if(commandNum == 0)
    {
        QMessageBox::warning(this, tr("Zahořování zdrojů"), 
        QString("Některé hodnoty chybí, nebo jsou nulové.\nZkontrolujte připojení zdroje."), QMessageBox::Cancel);
        file->writeLog(UNCOMPLETE_DATA, commandNum);
    }
    else
    {
        file->writeLog(UNCOMPLETE_DATA, commandNum);
        return;
    }
}

void MainWindow::dataBatManage(char* data, char dataLength)
{
    if(dataLength == 2)
    {
        unsigned int values[MEAS_TYPES_COUNT] = {0};
        values[4] = (data[0] << 8) + data[1];

        float result[MEAS_TYPES_COUNT];
        file->makeValues(values, result);
        if(!(file->writeToFile(result, commandLetter, commandNum)))
        {
            errorCount++;
        }
        for (unsigned int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            QString num = QString::number(result[i], 10, 2);
            QTableWidgetItem* cell = new QTableWidgetItem(num);
            cell->setFlags(cell->flags() ^ Qt::ItemIsEditable);
            ui->resultTable->setItem(commandNum, i, cell);
        }
        if(file->testResult)
            ui->actualResult->setText("Průběžný výsledek: Ano");
        else
            ui->actualResult->setText("Průběžný výsledek: Ne");

    }
    else
    {
        file->writeLog(UNCOMPLETE_DATA, commandNum);
        return;
    }
}

void MainWindow::startError(){
    if(QMessageBox::critical(this, "Spouštění testu",
    "Spuštění se nezdařilo.\nPřejete si opakovat spuštění?",
    QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
    {
        port->writePaket(START_PAKET, 0);
        startTimer->setInterval(1000);
        startTimer->start();
    }
    else
    {
        measureInProgress = false;
        startTimer->stop();
        delete startTimer;
        startTimer = nullptr;
        file->removeAll();
    }
}