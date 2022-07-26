#ifndef __COMmenu_H__
#define __COMmenu_H__

#include <QMenu>
#include <QSerialPortInfo>
#include <QMenuBar>

class COMmenu : public QMenu
{
    Q_OBJECT

    bool autoConnectEnabled = true;

public:
    COMmenu(QMenu* parent);

    QAction* disconnectAction;
    QAction* autoConnect;
    
    bool isAutoConnectEnabled();

public slots:
    void getCOMs();
    void handler(QAction*);
signals:
    void connectRequest(QAction*);
    void disconnectRequest();
    void autoConnectChanged(bool);
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
