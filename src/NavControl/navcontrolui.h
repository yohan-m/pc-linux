#ifndef NAVCONTROLUI_H
#define NAVCONTROLUI_H

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QPixmap>
#include <cmath>
#include "dronecontrol.h"
#include "dronenavdata.h"
#include "qfi_ADI.h"
#include "qfi_HSI.h"
#include "qfi_ASI.h"

class navControlUI : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit navControlUI(QWidget *parent = 0);
    void takeOffOrLand();

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
    QLabel * altLabel;
    QLabel * pitchLabel;
    QLabel * rollLabel;
    QLabel * yawLabel;
    QLabel * vxLabel;
    QLabel * vyLabel;
    QLabel * vzLabel;

    qfi_ADI * adi;
    qfi_HSI * hsi;
    qfi_ASI * asi;

    QLabel * batLabel;
    QLabel * batImg;
    QLabel * stateLabel;
    QLabel * stateImg;
    QPixmap * checkMarkImage;
    QPixmap * warningMarkImage;
    QPixmap * xMarkImage;

    int seqNumber;
    bool flying;
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
    void newAlt(int alt);

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
    void onChangeNavData(int bat, int state, int pitch, int roll, int yaw, int alt, int vx, int vy, int vz);
    void controlManager();
};
#endif // NAVCONTROLUI_H
