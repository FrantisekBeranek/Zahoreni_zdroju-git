#ifndef __COMmenu_H__
#define __COMmenu_H__

#include <QMenu>
#include <QSerialPortInfo>
#include <QMenuBar>

class COMmenu : public QMenu
{
    Q_OBJECT

public:
    COMmenu();
    COMmenu(QMenu*);
    ~COMmenu();

public slots:
    void getCOMs();
    void handler(QAction*);
signals:
    void connectRequest(QAction*);
    void disconnectRequest();
};

class toolMenu : public QMenu
{
    Q_OBJECT

public:
    toolMenu();
    toolMenu(QMenuBar*);
    ~toolMenu();
    
    COMmenu* menuCOM;
    QAction* actionKalibrace;

private:

public slots:
    void calibration(){emit calibRequest();};

signals:
    void calibRequest();
};

#endif