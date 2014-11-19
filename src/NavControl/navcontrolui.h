#ifndef NAVCONTROLUI_H
#define NAVCONTROLUI_H

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
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
    QPushButton * initControlButton;
    QPushButton * stopControlButton;
    QPushButton * calibButton;
    QPushButton * takeOffButton;
    QPushButton * landButton;
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
    QPushButton * initNavDataButton;
    QVBoxLayout * navLayout;
    QLabel * batLabel;
    QLabel * stateLabel;
    QLabel * altLabel;
    QLabel * pitchLabel;
    QLabel * rollLabel;
    QLabel * yawLabel;
    QLabel * vxLabel;
    QLabel * vyLabel;
    QLabel * vzLabel;

    int seqNumber;
    bool movement;
    bool landClicked;
    bool calibClicked;
    bool takeOffClicked;
    bool upClicked;
    bool upPressed;
    bool downClicked;
    bool downPressed;
    bool forwardClicked;
    bool forwardPressed;
    bool backwardClicked;
    bool backwardPressed;
    bool rightClicked;
    bool rightPressed;
    bool leftClicked;
    bool leftPressed;
    bool rRightClicked;
    bool rRightPressed;
    bool rLeftClicked;
    bool rLeftPressed;

    QTimer * timer;

signals:

public slots:
    void onClickInitControl();
    void onClickStopControl();
    void onClickCalib();
    void onClickTakeOff();
    void onClickLand();
    void onClickUp();
    void onReleaseUp();
    void onClickDown();
    void onReleaseDown();
    void onClickForward();
    void onReleaseForward();
    void onClickRight();
    void onReleaseRight();
    void onClickBackward();
    void onReleaseBackward();
    void onClickLeft();
    void onReleaseLeft();
    void onClickRRight();
    void onReleaseRRight();
    void onClickRLeft();
    void onReleaseRLeft();

private slots:
    void onClickInitNavData();
    void onChangeBat(int bat);
    void onChangeState(int state);
    void onChangePitch(int pitch);
    void onChangeRoll(int roll);
    void onChangeYaw(int yaw);
    void onChangeAlt(int alt);
    void onChangeVx(int vx);
    void onChangeVy(int vy);
    void onChangeVz(int vz);

    void controlManager();
};
#endif // NAVCONTROLUI_H
