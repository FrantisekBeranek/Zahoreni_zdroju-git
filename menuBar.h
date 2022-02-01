#ifndef __MENUBAR_H__
#define __MENUBAR_H__

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "mainwindow.h"
#include "toolMenu.h"
#include "serial.h"
#include "global_macros.h"

class menuZahoreni : public QMenu
{
    Q_OBJECT

public:
    menuZahoreni(QMenuBar*);

    QAction *actionSpustit;
    QAction *actionZastavit;
    QAction *actionZm_nit_meze;

public slots:
    void handler(QAction*);

signals:
    void startRequest();
    void stopRequest();
    void changeLimits();

};

class menuBar : public QMenuBar
{
    Q_OBJECT

public:
    menuBar(QMainWindow* parent);

    toolMenu* tools;
    menuZahoreni* zahoreni;

public slots:
    void setState(appStatus);

};

#endif