#include "toolMenu.h"

//_____COM MENU_____//

COMmenu::COMmenu(QMenu* parent = nullptr) : QMenu(parent)
{
    this->setTitle("COM");
    connect(this, SIGNAL(aboutToShow()), this, SLOT(getCOMs()));
    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(handler(QAction*)));

    this->addAction("dumb");
    disconnectAction = new QAction;

    parent->addMenu(this);
}

void COMmenu::getCOMs()
{
    bool connectEnabled = this->actions().at(0)->isEnabled();
    bool disconnectEnabled = disconnectAction->isEnabled();
    this->clear();  //Mazání dříve nalezených portů
    QList<QSerialPortInfo>unconnectedPorts = QSerialPortInfo::availablePorts();
    
    if(unconnectedPorts.count())
    {
        //___Vytvoření seznamu jmen portů___//
        foreach(QSerialPortInfo portInfo, unconnectedPorts){
            QAction* port = this->addAction(portInfo.portName());
            port->setEnabled(connectEnabled);
            
        }
    }
    else
    {
        QAction* noPort = this->addAction("Žádný dostupný port");
        //noPort->setEnabled(false);
    }

    this->addSeparator();
    disconnectAction = this->addAction("Odpojit");
    disconnectAction->setEnabled(disconnectEnabled);
    autoConnect = this->addAction("Automatické připojování");
    autoConnect->setCheckable(true);
    autoConnect->setChecked(autoConnectEnabled);
}

void COMmenu::handler(QAction* action)
{
    if(action == disconnectAction)
        emit disconnectRequest();
    else{
        if (action == autoConnect)
        {
            autoConnectEnabled = autoConnect->isChecked();
            emit autoConnectChanged(autoConnectEnabled);
        }
        else
            emit connectRequest(action);
    }
}

//_____TOOL MENU_____//

toolMenu::toolMenu(QMenuBar* parent = nullptr) : QMenu(parent)
{
    //___COM menu___//
    this->menuCOM = new COMmenu(this);
    this->addMenu(menuCOM);

    //___Kalibrace___//
    this->actionKalibrace = new QAction("Kalibrace");
    this->addAction(actionKalibrace);
    connect(actionKalibrace, SIGNAL(triggered()), this, SLOT(calibration()));

    this->setTitle("N\303\241stroje");

    parent->addMenu(this);
}
