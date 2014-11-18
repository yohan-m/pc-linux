#ifndef NAVCONTROLUI_H
#define NAVCONTROLUI_H

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include "dronecontrol.h"
#include "dronenavdata.h"

class navControlUI : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit navControlUI(QWidget *parent = 0);

private:
    QGroupBox * controlBox;
    droneControl * control;
    QPushButton * emergencyButton;
    QPushButton * calibButton;
    QPushButton * takeOffButton;
    QPushButton * landButton;
    QPushButton * rstWatchdogButton;
    QPushButton * upButton;
    QPushButton * downButton;
    QPushButton * forwardButton;
    QPushButton * backwardButton;
    QPushButton * leftButton;
    QPushButton * rightButton;
    QPushButton * rLeftButton;
    QPushButton * rRightButton;
    QVBoxLayout * controlLayout;

    QGroupBox * navBox;
    droneNavData * navData;
    QPushButton * initButton;
    QVBoxLayout * navLayout;
    QLabel * batLabel;
    QLabel * altLabel;
    QLabel * vxLabel;
    QLabel * vyLabel;
    QLabel * vzLabel;

    int seqNumber;

signals:

public slots:

private slots:
    void onClickEmergency();
    void onClickCalib();
    void onClickTakeOff();
    void onClickLand();
    void onClickrstWatchdog();

    void onClickUp();
    void onClickDown();
    void onClickForward();
    void onClickRight();
    void onClickBackward();
    void onClickLeft();
    void onClickRRight();
    void onClickRLeft();

    void onChangeBat(int bat);
    void onChangeAlt(int alt);
    void onChangeVx(int vx);
    void onChangeVy(int vy);
    void onChangeVz(int vz);

    void onClickInit();

};
#endif // NAVCONTROLUI_H
