#ifndef __COMmenu_H__
#define __COMmenu_H__

#include <QMenu>
#include <QSerialPortInfo>
#include <QMenuBar>

class COMmenu : public QMenu
{
    Q_OBJECT

public:
    COMmenu(QMenu* parent);

    QAction* disconnectAction;

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
    toolMenu(QMenuBar*parent);
    
    COMmenu* menuCOM;
    QAction* actionKalibrace;

private:

public slots:
    void calibration(){emit calibRequest();};

signals:
    void calibRequest();
};

#endif