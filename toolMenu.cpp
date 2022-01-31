#include "toolMenu.h"

//_____COM MENU_____//

COMmenu::COMmenu()
{
    this->setTitle("COM");
    //connect(this, SIGNAL(aboutToShow()), this, SLOT(getCOMs()));
    //connect(this, SIGNAL(triggered(QAction*)), this, SLOT(handler(QAction*)));
}


COMmenu::~COMmenu()
{

}

void COMmenu::getCOMs()
{
    this->clear();  //Mazání dříve nalezených portů
    QList<QSerialPortInfo>unconnectedPorts = QSerialPortInfo::availablePorts();
    
    if(unconnectedPorts.count())
    {
        //___Vytvoření seznamu jmen portů___//
        foreach(QSerialPortInfo portInfo, unconnectedPorts){
            QAction* port = new QAction(portInfo.portName());
            this->addAction(port);
        }
    }
    else
    {
        QAction* noPort = new QAction("Žádný dostupný port");
        noPort->setEnabled(false);
        this->addAction(noPort);
    }

    this->addSeparator();
    this->addAction("Odpojit");
}

void COMmenu::handler(QAction* action)
{
    if(action->text() == "Odpojit")
        emit disconnectRequest();
    else
        emit connectRequest(action);
}

//_____TOOL MENU_____//

toolMenu::toolMenu()
{
    //___COM menu___//
    this->menuCOM = new COMmenu();
    this->addAction(menuCOM->menuAction());
    
    connect(menuCOM, SIGNAL(aboutToShow()), menuCOM, SLOT(getCOMs()));
    connect(menuCOM, SIGNAL(triggered(QAction*)), menuCOM, SLOT(handler(QAction*)));

    //___Kalibrace___//
    this->actionKalibrace = new QAction("Kalibrace");
    this->addAction(actionKalibrace);
}

toolMenu::toolMenu(QMenuBar* menuBar)
{
    toolMenu();
    menuBar->addAction(this->menuAction());
}

toolMenu::~toolMenu()
{

}