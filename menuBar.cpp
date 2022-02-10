#include "menuBar.h"

menuBar :: menuBar(QMainWindow* parent) : QMenuBar(parent)
{
    connect(parent, SIGNAL(statusChanged()), this, SLOT(setState()));

    tools = new toolMenu(this);
    zahoreni = new menuZahoreni(this);
}

void menuBar :: setState(appStatus status)
{
    if(status.measureInProgress || status.calibInProgress)
    {
        if(status.COMstate == PORT_OK)
        {
            foreach(QAction* port, this->tools->menuCOM->actions()){
                port->setEnabled(false);
            }
        }
        else
        {
            foreach(QAction* port, this->tools->menuCOM->actions()){
                port->setEnabled(true);
            }
        }
            this->tools->menuCOM->disconnectAction->setEnabled(false);
            this->tools->actionKalibrace->setEnabled(false);
            this->zahoreni->actionSpustit->setEnabled(false);
            this->zahoreni->actionZm_nit_meze->setEnabled(false);
            this->zahoreni->actionZastavit->setEnabled(true);
    }
    else
    {
        if(status.COMstate == PORT_OK)
        {
            foreach(QAction* port, this->tools->menuCOM->actions()){
                port->setEnabled(true);
            }
            this->tools->menuCOM->disconnectAction->setEnabled(true);
            this->tools->actionKalibrace->setEnabled(true);
            this->zahoreni->actionSpustit->setEnabled(true);
        }
        else
        {
            foreach(QAction* port, this->tools->menuCOM->actions()){
                port->setEnabled(true);
            }
            this->tools->menuCOM->disconnectAction->setEnabled(false);
            this->tools->actionKalibrace->setEnabled(false);
            this->zahoreni->actionSpustit->setEnabled(false);
        }
        this->zahoreni->actionZastavit->setEnabled(false);
        this->zahoreni->actionZm_nit_meze->setEnabled(true);
    }
}


menuZahoreni :: menuZahoreni(QMenuBar* parent) : QMenu(parent)
{
    actionSpustit = new QAction(this);
    this->addAction(actionSpustit);
    actionZastavit = new QAction(this);
    this->addAction(actionZastavit);
    actionZm_nit_meze = new QAction(this);
    this->addAction(actionZm_nit_meze);

    this->setTitle("Zaho\305\231en\303\255");

    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(handler(QAction*)));

    parent->addMenu(this);
}

void menuZahoreni :: handler(QAction* sender)
{
    if(sender == this->actionSpustit)
    {
        emit startRequest();
    }
    else if(sender == this->actionZastavit)
    {
        emit stopRequest();
    }
    else
    {
        emit changeLimits();
    }
}