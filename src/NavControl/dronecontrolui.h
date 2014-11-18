#ifndef DRONECONTROLUI_H
#define DRONECONTROLUI_H

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "dronecontrol.h"

class droneControlUI : public QGroupBox
{
    Q_OBJECT
public:
    explicit droneControlUI(QWidget *parent = 0);

private:
    droneControl * drone;
    int seqNumber;

    QPushButton * emergencyButton;
    QPushButton * calibButton;
    QPushButton * takeOffButton;
    QPushButton * landButton;
    QPushButton * rstWatchdogButton;

    QVBoxLayout * VBLayout;

signals:

private slots:
    void onClickEmergency();
    void onClickCalib();
    void onClickTakeOff();
    void onClickLand();
    void onClickrstWatchdog();

};

#endif // DRONECONTROLUI_H
