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
#include "wifiFrame.h"
#include "dronecontrol.h"
#include "dronenavdata.h"
#include "UdpSocket.h"
#include "qfi_ADI.h"
#include "qfi_HSI.h"
#include "qfi_ASI.h"

#define MAX_CONSECUTIVE_TAKE_OFF_CMD 30
/**
 * @class navControlUI
 * @brief Graphical interface for the control/NavData
 */
class navControlUI : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit navControlUI(QWidget *parent = 0);

    /**
     * @brief The drone take off if it's landed, or land.
     */
    void takeOffOrLand();

    void setControler(char controler);

    void setUdpSocket(UdpSocket * sock);

private:
    QGroupBox * controlBox;
    droneControl * control;
    QPushButton * initControlButton;
    QPushButton * stopControlButton;
    QPushButton * emergencyButton;
    QPushButton * calibHPlaneButton;
    QPushButton * calibMagnButton;
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
    int consecutiveTakeOffCmd;
    bool initClicked;
    bool emergencyClicked;
    bool flying;
    bool movement;
    int landState;
    bool landed;
    bool calibHPlaneClicked;
    bool calibMagnClicked;
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

    char controler ;
    UdpSocket* udpSocket ;

    QTimer * timer;

signals:
    /**
     * @brief newAltFromBarometer
     * @param alt
     */
    void newAltFromBarometer(double alt);

public slots:
    void onClickInitControl();
    void onClickStopControl();
    void onClickEmergency();
    void onClickCalibHPlane();
    void onClickCalibMagn();
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
    void onChangeNavData(int bat, int state, int pitch, int roll, int yaw, double alt, int vx, int vy, int vz);
    void controlManager();
};
#endif // NAVCONTROLUI_H
