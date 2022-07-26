#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
*   V Programu se objevují rozdíly pro manual a auto mód měření. Manuální mód ovšem není v 
*   novém řešení implementován.
*/

//_____Konstruktor_____//
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Zahoření zdrojů");

    ui->testPhase->setText("Fáze testu: Test nebyl spuštěn");

    port = new Serial;

    file = new File;
    connect(file, SIGNAL(calibrationOver()), this, SLOT(endCalibration()));
    connect(file, SIGNAL(calibrationCancelled()), this, SLOT(endCalibration()));

    status.calibInProgress = 0;
    status.COMstate = PORT_DISCONNECTED;
    status.manualMode = false;
    status.measureInProgress = false;

    //___Timer pro automatické mazání zpráv ze statusBar___//
    statusBarTimer = new QTimer;
    statusBarTimer->setSingleShot(true);
    statusBarTimer->setInterval(3000);
    connect(statusBarTimer, SIGNAL(timeout()), ui->statusbar, SLOT(clearMessage()));
    connect(ui->statusbar, SIGNAL(messageChanged(QString)), this, SLOT(statusBarTiming()));

    //___Propojení signálů a slotů___//
    connect(ui->menubar->tools->menuCOM, SIGNAL(connectRequest(QAction*)), this, SLOT(connectPort(QAction*)));
    connect(ui->menubar->tools->menuCOM, SIGNAL(disconnectRequest()), this, SLOT(disconnectPort()));

    connect(ui->menubar->tools, SIGNAL(calibRequest()), this, SLOT(calibManage(/*QAction**/)));
    //connect(ui->menubar->zahoreni, SIGNAL(triggered(QAction*)), this, SLOT(zahoreniManage(QAction*)));
    connect(ui->menubar->zahoreni, SIGNAL(startRequest()), this, SLOT(startManage()));
    connect(ui->menubar->zahoreni, SIGNAL(stopRequest()), this, SLOT(stopManage()));
    connect(ui->menubar->zahoreni, SIGNAL(changeLimits()), this, SLOT(limitsManage()));
    connect(this, SIGNAL(statusChanged(appStatus)), ui->menubar, SLOT(setState(appStatus)));
    connect(port, SIGNAL(statusChanged(Serial*)), this, SLOT(portStatusChanged(Serial*)));
    ui->menubar->zahoreni->actionZastavit->setEnabled(false);
    ui->menubar->tools->menuCOM->disconnectAction->setEnabled(false);
    ui->menubar->tools->actionKalibrace->setEnabled(false);
    ui->menubar->zahoreni->actionSpustit->setEnabled(false);

    connect(port, SIGNAL(readyRead()), this, SLOT(read()));
    connect(port, SIGNAL(statusChanged(Serial*)), ui->COMconnected, SLOT(setState(Serial*)));
    connect(port, SIGNAL(paketFound(Paket*)), this, SLOT(managePaket(Paket*)));
    connect(ui->menubar->tools->menuCOM, SIGNAL(autoConnectChanged(bool)), port, SLOT(setAutoConnect(bool)));

    timer = new QTimer;
    startTimer = nullptr;
    
    //___Timer pro drobné zpoždění ukončení testu___//
    endTimer = new QTimer;
    endTimer->setSingleShot(true);
    endTimer->setInterval(500);
    connect(endTimer, SIGNAL(timeout()), this, SLOT(endMeasure()));

    ui->COMconnected->setStyleSheet("QLabel { background: red; color: white; font-size: 16px;}");

    //___Database___//
    db = new Database;
}

//_____Destruktor____//
MainWindow::~MainWindow()
{
    if(status.measureInProgress)
    {
        file->makeProtocol();
        port->writePaket(CANCEL_PAKET, 0);
    }
    delete port;
    delete file;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    ui->resizeEvent(event);
}

//___Ukončení testu___//
void MainWindow::endMeasure()
{
    endMeasure(true);
}

//___Ukončení testu___//
void MainWindow::endMeasure(bool continueInMeasure)
{
    ui->statusbar->showMessage("Ukončení");

    if(!file->makeProtocol()){
        //___Chyba zápisu do protokolu___//
        QMessageBox::warning(this, "Ukončení testu", QString("Nedošlo k řádnému ukončení testu."),
        QMessageBox::Ok);
    }
    else
    {
        //___Protokol v pořádku vygenerován___//
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
    db->writeResult(file->testResult);

    //___Výchozí nastavení proměnných___//
    errorCount = 0;
    warningCount = 0;

    lastNum = 0;
    commandNum = 0;

    if(!continueInMeasure)
        suppliesToTest.clear();

    if(suppliesToTest.isEmpty())
    {
        status.measureInProgress = false;
        emit statusChanged(status);
        ui->testPhase->setText("Fáze testu: Test ukončen");
    }
    else
    {
        testProperties* properties = suppliesToTest.dequeue();
        supplyInTesting = properties->retPointer();
        
        ui->testPhase->setText("Fáze testu: Test spuštěn");
        ui->actualResult->setText("Průběžný výsledek: Ano");
        ui->errorCount->setText(ui->errorCount->text().section(':', 0, 0).append(": 0"));
        ui->resultTable->clearContents();
        
        port->writePaket(START_PAKET, properties->retPointer());
        status.measureInProgress = true;
        emit statusChanged(status);
        file->testResult = true;
        lastNum = 0;

        startTimer = new QTimer;
        startTimer->setSingleShot(true);
        startTimer->setInterval(5000);
        connect(startTimer, SIGNAL(timeout()), this, SLOT(startError()));
        startTimer->start();
    }
    
}

void MainWindow::startManage()
{
    if(status.COMstate != PORT_OK)
    {
        QMessageBox::information (this, tr("Zahořování zdrojů"),
                            tr("Není přípojen přípravek pomocí COM portu"));
        return;
    }
    //---Kontrola souboru meze---//
    if(!file->limitsCheck()){
        //---Soubor "meze" je narušen nebo chybí---//
        QMessageBox::warning (this, tr("Zahořování zdrojů"),
                            tr("Nejdříve nastavte krajní hodnoty pro test"));
        return;
    }

    std::vector<int> suppliesToTest_pointers;
    for (int i = 0; i < suppliesToTest.count(); i++)
    {
        suppliesToTest_pointers.push_back(suppliesToTest.at(i)->retPointer());
    }
    if(status.measureInProgress)
        suppliesToTest_pointers.push_back(supplyInTesting);
    

    testProperties* properties = new testProperties;
    if(properties->init(supplyCount, suppliesToTest_pointers) == false)
    {
        delete properties;
        return;
    }
    file->pathPDF = properties->retPath();
    file->setSerialNumber(properties->retSerialNumber());
    file->setWorker(properties->retWorker());
    supplyInTesting = properties->retPointer();

    ui->statusbar->showMessage(QString::number(supplyInTesting));

    QString path = file->pathPDF.section('.', 0, 0);
    path = path.append(".txt");
    //---Vytvoř a otevři soubor (režim ReadWrite)---//
    if(!path.isEmpty()){
        if(file->createFile(path)){ 
            db->writeNewSupply(properties->retSerialNumber(), properties->retWorker(), (QDateTime::currentDateTime()).toString("yyyy-mm-dd hh:mm:ss:sss"));
            //---odešli příkaz k zahájení testu---//
            if(QMessageBox::information(this, "Zahoření zdrojů",
            "Připojte a spustě testovaný zdroj\nPoté stiskněte OK pro pokračování",
            QMessageBox::Ok) == QMessageBox::Ok){
                if(!status.measureInProgress)
                {
                    ui->testPhase->setText("Fáze testu: Test spuštěn");
                    ui->actualResult->setText("Průběžný výsledek: Ano");
                    ui->errorCount->setText(ui->errorCount->text().section(':', 0, 0).append(": 0"));
                    ui->resultTable->clearContents();
                    
                    port->writePaket(START_PAKET, supplyInTesting);
                    status.measureInProgress = true;
                    emit statusChanged(status);
                    file->testResult = true;
                    lastNum = 0;

                    startTimer = new QTimer;
                    startTimer->setSingleShot(true);
                    startTimer->setInterval(5000);
                    connect(startTimer, SIGNAL(timeout()), this, SLOT(startError()));
                    startTimer->start();
                }
                else
                {
                    suppliesToTest.enqueue(properties);
                }
            }
        }
    }
}

void MainWindow::stopManage()
{
    int ret = QMessageBox::question(this, "Zahořování zdrojů",
            "Opravdu si přejete ukončit test?", QMessageBox::Ok,
            QMessageBox::Cancel);
    if(ret == QMessageBox::Ok){
        ui->testPhase->setText("Fáze testu: Test přerušen");
        port->writePaket(CANCEL_PAKET, 0);
        endMeasure(true);
    }
}

void MainWindow::limitsManage()
{
    file->limitsSetup();
}

//___Požadavek na kalibraci___//
void MainWindow::calibManage(){   
    if(!status.measureInProgress)
    {
        if(QMessageBox::information(nullptr, "Kalibrace", "Připojte a zapněte zdroj", 
                QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
        {
            status.calibInProgress = true;
            emit statusChanged(status);
            timer->setInterval(5000);
            timer->setSingleShot(true);
            connect(timer, SIGNAL(timeout()), this, SLOT(calibrationFailure()));
            timer->start();
            port->writePaket(CALIB_PAKET, 0);
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
        supplyCount = *paket->data;
        break;

    case REFRESH_PAKET:
        /* code */
        break;

    case CANCEL_FROM_USER_PAKET:
        if(status.measureInProgress)
            endMeasure(false);
        break;
    
    default:
        break;
    }

    //___Uvolni alokovanou paměť___//
    free(paket->data);
    free(paket);
}

//_____Čtení dat_____//
void MainWindow::read(){
    port->readData();

    if(status.COMstate == PORT_UNACTIVE){
        status.COMstate = PORT_OK;
        emit statusChanged(status);
        if(status.measureInProgress)
            file->writeLog(COM_RECONNECTION);
    }

}

//_____Chyba kalibrace (vypršel čas)_____//
void MainWindow::calibrationFailure(){
    timer->stop();
    QMessageBox::warning(this, "Kalibrace", "Zkontrolujte připojení přípravku a opakujte",
        QMessageBox::Ok);
    status.calibInProgress = false;
    port->writePaket(CALIB_PAKET, 1);
    emit statusChanged(status);
}

//_____Ukončení kalibrace uživatelem_____//
void MainWindow::cancelCalibration(){
    status.calibInProgress = false;
    port->writePaket(CALIB_PAKET, 1);
    emit statusChanged(status);
}

//_____Úspěšné dokončení kalibrace_____//
void MainWindow::endCalibration(){
    QMessageBox::information(this, "Kalibrace", "Kalibrace proběhla úspěšně.", QMessageBox::Ok);
    status.calibInProgress = false;
    port->writePaket(CALIB_PAKET, 1);
    emit statusChanged(status);
}

//_____testNum paket_____//
void MainWindow::testNumManage(char num)
{
    commandNum = num;
        
    if(commandNum != lastNum)
    {
        if(status.measureInProgress)
        {
            errorCount++;
            file->writeLog(DATA_LOSS, lastNum);
            ui->errorCount->setText(ui->errorCount->text().section(':', 0, 0).append(": ").append(QString::number(errorCount)));
        }
        lastNum = commandNum;
    }
    lastNum++;
}

//_____testPhase paket_____//
void MainWindow::testPhaseManage(char phase)
{
    commandLetter = phase;
    
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
            disconnect(startTimer, SIGNAL(timeout()), this, SLOT(startError()));
            delete startTimer;
            startTimer = nullptr;
        }
        break;

    case 'm':   //Hlavní test
        ui->testPhase->setText("Fáze testu: Hlavní test v průběhu");
        break;

    case 'b':   //Baterie start
        ui->testPhase->setText("Fáze testu: Hlavní test baterie v průběhu");
        break;

    case 'M':   //Hlavní test baterie
        ui->testPhase->setText("Fáze testu: Hlavní test baterie v průběhu");
        break;
        
    default:
        break;
    }
}

//_____Datový paket_____//
void MainWindow::dataManage(char* data, char dataLength)
{
    /*
    *    U15V, U15V_CURRENT,		//kanál 7, 10
    *    U12V, U12V_CURRENT,		//kanál 14, 12
    *    U24VO2, U24VO2_CURRENT,	//kanál 5, 11
    *    U24V, U24V_CURRENT,		//kanál 9, 2
    *    U5VK, U5VK_CURRENT,		//kanál 15, 0
    *    U5V, U5V_CURRENT,          //kanál 8, 1
    *    U_BAT,                     //kanál 6
    *    PAD9, PAD15,               //kanál 4, 13
    *    U48V_CURRENT               //kanál 3
    */
    int swap[MEAS_TYPES_COUNT] = {3, 2, 6, 5, 0, 1, 4};
    if(dataLength == 2*MEAS_TYPES_COUNT)    // Ošetření délky dat
    {
        unsigned int values[MEAS_TYPES_COUNT] = {0};
        for (int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            values[swap[i]] |= ((data[2*i] << 8) & 0xFF00);
            values[swap[i]] |= (data[2*i + 1] & 0xFF);
        }

        if(status.calibInProgress)
        {
            timer->stop();
            disconnect(timer, SIGNAL(timeout()), this, SLOT(calibrationFailure()));
            file->calibration(values);
        }
        else
        {
            float result[MEAS_TYPES_COUNT];
            file->makeValues(values, result);
            db->writeRow(result, commandLetter, commandNum);
            if(!(file->writeToFile(result, commandLetter, commandNum)))
            {
                errorCount++;
            }
            for (unsigned int i = 0; i < MEAS_TYPES_COUNT; i++)
            {
                QString num = QString::number(result[i], 10, 1);
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

//_____Paket dat měření baterie_____//
void MainWindow::dataBatManage(char* data, char dataLength)
{
    if(dataLength == 2) // Ošetření délky dat
    {
        unsigned int values[MEAS_TYPES_COUNT] = {0};
        //values[4] = (data[0] << 8) + data[1];
        values[4] |= ((data[0] << 8) & 0xFF00);
        values[4] |= (data[1] & 0xFF);

        float result[MEAS_TYPES_COUNT];
        file->makeValues(values, result);
        if(!(file->writeToFile(result, commandLetter, commandNum)))
        {
            errorCount++;
        }
        for (unsigned int i = 0; i < MEAS_TYPES_COUNT; i++)
        {
            QString num;
            if(i == 4)
                num = QString::number(result[i], 10, 1);
            else
                num = tr("--");
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

//_____Chyba spuštění testu_____//
void MainWindow::startError(){
    if(QMessageBox::critical(this, "Spouštění testu",
    "Spuštění se nezdařilo.\nPřejete si opakovat spuštění?",
    QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
    {
        port->writePaket(START_PAKET, supplyInTesting);
        startTimer->setInterval(1000);
        startTimer->start();
    }
    else
    {
        status.measureInProgress = false;
        emit statusChanged(status);
        startTimer->stop();
        delete startTimer;
        startTimer = nullptr;
        port->writePaket(CANCEL_PAKET, supplyInTesting);
        file->removeAll();
        ui->testPhase->setText("Fáze testu: Přerušeno");
    }
}

void MainWindow::portStatusChanged(Serial* port)
{
    status.COMstate = port->getStatus();
    emit statusChanged(status);
}
