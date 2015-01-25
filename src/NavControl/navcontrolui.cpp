#include "navcontrolui.h"

navControlUI::navControlUI(QWidget *parent) :
    QVBoxLayout(parent)
{
    //Control Box
    controlBox = new QGroupBox("Control");
    control = new droneControl();

    initControlButton = new QPushButton("Init");
    stopControlButton = new QPushButton("Stop");
    emergencyButton = new QPushButton("Emergency");
    QHBoxLayout * initStopLayout = new QHBoxLayout();
    initStopLayout->addWidget(initControlButton);
    initStopLayout->addWidget(stopControlButton);
    initStopLayout->addWidget(emergencyButton);
    calibHPlaneButton = new QPushButton("Calibrate H. plane");
    calibMagnButton = new QPushButton("Calibrate magneto.");
    takeOffButton = new QPushButton("Take Off");
    landButton = new QPushButton("Land");

    QHBoxLayout * calibLayout = new QHBoxLayout();
    calibLayout->addWidget(calibHPlaneButton);
    calibLayout->addWidget(calibMagnButton);

    upButton = new QPushButton("Up");
    downButton = new QPushButton("Down");
    forwardButton = new QPushButton("Forward");
    leftButton = new QPushButton("Left");
    backwardButton = new QPushButton("Backward");
    rightButton = new QPushButton("Right");
    rLeftButton = new QPushButton("RLeft");
    rRightButton = new QPushButton("RRight");

    initControlButton->setFocusPolicy( Qt::NoFocus );
    stopControlButton->setFocusPolicy( Qt::NoFocus );
    calibHPlaneButton->setFocusPolicy( Qt::NoFocus );
    calibMagnButton->setFocusPolicy( Qt::NoFocus );
    takeOffButton->setFocusPolicy( Qt::NoFocus );
    landButton->setFocusPolicy( Qt::NoFocus );
    upButton->setFocusPolicy( Qt::NoFocus );
    downButton->setFocusPolicy( Qt::NoFocus );
    forwardButton->setFocusPolicy( Qt::NoFocus );
    leftButton->setFocusPolicy( Qt::NoFocus );
    backwardButton->setFocusPolicy( Qt::NoFocus );
    rightButton->setFocusPolicy( Qt::NoFocus );
    rLeftButton->setFocusPolicy( Qt::NoFocus );
    rRightButton->setFocusPolicy( Qt::NoFocus );

    QHBoxLayout * upDownLayout = new QHBoxLayout();
    upDownLayout->addWidget(upButton);
    upDownLayout->addWidget(downButton);

    QGridLayout * grid = new QGridLayout();
    grid->addWidget(rLeftButton,0,0);
    grid->addWidget(forwardButton,0,1);
    grid->addWidget(rRightButton,0,2);
    grid->addWidget(leftButton,1,0);
    grid->addWidget(backwardButton,1,1);
    grid->addWidget(rightButton,1,2);

    controlLayout = new QVBoxLayout();
    controlLayout->addLayout(initStopLayout);
    controlLayout->addLayout(calibLayout);
    controlLayout->addWidget(takeOffButton);
    controlLayout->addWidget(landButton);
    controlLayout->addLayout(upDownLayout);
    controlLayout->addLayout(grid);
    controlBox->setLayout(controlLayout);
    //controlBox->setFixedSize(250,260);

    QObject::connect(initControlButton,SIGNAL(clicked()),this,SLOT(onClickInitControl()));
    QObject::connect(stopControlButton,SIGNAL(clicked()),this,SLOT(onClickStopControl()));
    QObject::connect(emergencyButton,SIGNAL(clicked()),this,SLOT(onClickEmergency()));
    QObject::connect(calibHPlaneButton,SIGNAL(clicked()),this,SLOT(onClickCalibHPlane()));
    QObject::connect(calibMagnButton,SIGNAL(clicked()),this,SLOT(onClickCalibMagn()));
    QObject::connect(takeOffButton,SIGNAL(clicked()),this,SLOT(onClickTakeOff()));
    QObject::connect(landButton,SIGNAL(clicked()),this,SLOT(onClickLand()));

    QObject::connect(upButton,SIGNAL(pressed()),this,SLOT(onClickUp()));
    QObject::connect(upButton,SIGNAL(released()),this,SLOT(onReleaseUp()));
    QObject::connect(downButton,SIGNAL(pressed()),this,SLOT(onClickDown()));
    QObject::connect(downButton,SIGNAL(released()),this,SLOT(onReleaseDown()));
    QObject::connect(forwardButton,SIGNAL(pressed()),this,SLOT(onClickForward()));
    QObject::connect(forwardButton,SIGNAL(released()),this,SLOT(onReleaseForward()));
    QObject::connect(leftButton,SIGNAL(pressed()),this,SLOT(onClickLeft()));
    QObject::connect(leftButton,SIGNAL(released()),this,SLOT(onReleaseLeft()));
    QObject::connect(backwardButton,SIGNAL(pressed()),this,SLOT(onClickBackward()));
    QObject::connect(backwardButton,SIGNAL(released()),this,SLOT(onReleaseBackward()));
    QObject::connect(rightButton,SIGNAL(pressed()),this,SLOT(onClickRight()));
    QObject::connect(rightButton,SIGNAL(released()),this,SLOT(onReleaseRight()));
    QObject::connect(rRightButton,SIGNAL(pressed()),this,SLOT(onClickRLeft()));
    QObject::connect(rRightButton,SIGNAL(released()),this,SLOT(onReleaseRLeft()));
    QObject::connect(rLeftButton,SIGNAL(pressed()),this,SLOT(onClickRRight()));
    QObject::connect(rLeftButton,SIGNAL(released()),this,SLOT(onReleaseRRight()));

    //NavData Box
    navBox = new QGroupBox("NavData");
    navData = new droneNavData(control);
    adi = new qfi_ADI();
    hsi = new qfi_HSI();
    asi = new qfi_ASI();

    QHBoxLayout * hsiAsiLayout = new QHBoxLayout();
    hsiAsiLayout->addWidget(hsi);
    hsiAsiLayout->addWidget(asi);

    checkMarkImage = new QPixmap(":/img/images/checkmark16.png");
    warningMarkImage = new QPixmap(":/img/images/warningmark16.png");
    xMarkImage = new QPixmap(":/img/images/xmark16.png");

    QHBoxLayout * batLayout = new QHBoxLayout();
    batImg = new QLabel();
    batImg->setPixmap(*xMarkImage);
    batLabel = new QLabel("Battery:\n0%");
    batLayout->addWidget(batImg,0,Qt::AlignLeft);
    batLayout->addWidget(batLabel,1,Qt::AlignLeft);

    QHBoxLayout * stateLayout = new QHBoxLayout();
    stateImg = new QLabel();
    stateImg->setPixmap(*xMarkImage);
    stateLabel = new QLabel("State:\nDefault");
    stateLayout->addWidget(stateImg,0,Qt::AlignCenter);
    stateLayout->addWidget(stateLabel,1,Qt::AlignLeft);

    QHBoxLayout * batStateLayout = new QHBoxLayout();
    batStateLayout->addLayout(batLayout);
    batStateLayout->addLayout(stateLayout);

    navLayout = new QVBoxLayout();
    navLayout->addWidget(adi,0,Qt::AlignCenter);
    navLayout->addLayout(hsiAsiLayout);
    navLayout->addLayout(batStateLayout);
    navBox->setLayout(navLayout);
    navBox->setFixedHeight(370);

    QObject::connect(navData,SIGNAL(newNavData(int, int, int, int, int, double, int, int, int)),this,SLOT(onChangeNavData(int, int, int, int, int, double, int, int, int)));

    //Widget
    addWidget(controlBox,0,Qt::AlignTop);
    addWidget(navBox,1,Qt::AlignTop);

    seqNumber = 1;
    consecutiveTakeOffCmd = 0;
    flying = false;
    initClicked = false;

    movement = false;
    emergencyClicked = false;
    landState = 0;
    landed = true;
    calibHPlaneClicked = false;
    calibMagnClicked = false;
    takeOffClicked = false;
    upClicked = false;
    upPressed = false;
    downClicked = false;
    downPressed = false;
    forwardClicked = false;
    forwardPressed = false;
    backwardClicked = false;
    backwardPressed = false;
    rightClicked = false;
    rightPressed = false;
    leftClicked = false;
    leftPressed = false;
    rRightClicked = false;
    rRightPressed = false;
    rLeftClicked = false;
    rLeftPressed = false;

    controler = DRONE_CTRL ;
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(controlManager()));
}

void navControlUI::controlManager()
{
    float lrTilt = 0.0;
    float fbTilt = 0.0;
    float vSpeed = 0.0;
    float aSpeed = 0.0;

    if(initClicked) {
        if (controler == PC_CTRL)
        {
            seqNumber = 1;
            navData->init(seqNumber);
        }
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_INIT_NAVDATA)) ;

        initClicked = false;
    }
    else if(landState==1) {
        if (controler == PC_CTRL)
            control->sendMovement(seqNumber,1,0.0,0.0,0.0,0);
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_LAND)) ;

        landState = 2;
    }
    else if(landState==2) {
        if (controler == PC_CTRL)
            control->sendLand(seqNumber);
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_LAND)) ;

        landState = 0;
    }
    else if(calibHPlaneClicked) {
        if (controler == PC_CTRL)
            control->sendCalibHPlan(seqNumber);
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_FTRIM)) ;

        calibHPlaneClicked = false;
    }
    else if (calibMagnClicked) {
        if (controler == PC_CTRL)
            control->sendCalibMagn(seqNumber);
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_CALIB_MAGNO)) ;

        calibMagnClicked = false;
    }
    else if (takeOffClicked && landed) {
        if (controler == PC_CTRL)
            control->sendTakeOff(seqNumber);
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_TAKE_OFF)) ;

        consecutiveTakeOffCmd++;
        if(consecutiveTakeOffCmd>=MAX_CONSECUTIVE_TAKE_OFF_CMD)
            consecutiveTakeOffCmd = 0;

        takeOffClicked = false;
    }
    else if (takeOffClicked && !landed) {
        if (controler == PC_CTRL)
        {
            control->sendMovement(seqNumber,0,0.0,0.0,0.0,0);
            consecutiveTakeOffCmd = 0;
            takeOffClicked = false;
        }
    }
    else if (emergencyClicked) {
        if (controler == PC_CTRL)
            control->sendEmergency(seqNumber);
        else
            udpSocket->sendFrameDrone(createCmdFrame(CMD_EMERGENCY)) ;

        emergencyClicked = false ;
    }
    else if (upClicked || upPressed || downClicked || downPressed || forwardClicked || forwardPressed || backwardClicked || backwardPressed || rightClicked || rightPressed || leftClicked || leftPressed || rLeftClicked || rLeftPressed || rRightClicked || rRightPressed) {

        if(controler == PC_CTRL)
        {
            if (upClicked || upPressed) {
                vSpeed += 0.6;
                upClicked = false;
            }
            if (downClicked || downPressed) {
                vSpeed += -0.6;
                downClicked = false;
            }
            if (forwardClicked || forwardPressed) {
                fbTilt += -0.4;
                forwardClicked = false;
            }
            if (backwardClicked || backwardPressed) {
                fbTilt += 0.4;
                backwardClicked = false;
            }
            if (rightClicked || rightPressed) {
                lrTilt += 0.4;
                rightClicked = false;
            }
            if (leftClicked || leftPressed) {
                lrTilt += -0.4;
                leftClicked = false;
            }
            if (rLeftClicked || rLeftPressed) {
                aSpeed += -0.6;
                rLeftClicked = false;
            }
            if (rRightClicked || rRightPressed) {
                aSpeed += 0.6;
                rRightClicked = false;
            }
            control->sendMovement(seqNumber,1,lrTilt,fbTilt,vSpeed,aSpeed);
        }
        else
        {
            if (upClicked || upPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_UP)) ;
                upClicked = false;
            }
            if (downClicked || downPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_DOWN)) ;
                downClicked = false;
            }
            if (forwardClicked || forwardPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_FWD)) ;
                forwardClicked = false;
            }
            if (backwardClicked || backwardPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_BWD)) ;
                backwardClicked = false;
            }
            if (rightClicked || rightPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_RIGHT)) ;
                rightClicked = false;
            }
            if (leftClicked || leftPressed) {
                udpSocket->sendFrameDrone(createCmdFrame( CMD_LEFT)) ;
                leftClicked = false;
            }
            if (rLeftClicked || rLeftPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_ROTATE_LEFT)) ;
                rLeftClicked = false;
            }
            if (rRightClicked || rRightPressed) {
                udpSocket->sendFrameDrone(createCmdFrame(CMD_ROTATE_RIGHT)) ;
                rRightClicked = false;
            }
        }

        movement = true;
    }
    else if (movement) {
        control->sendMovement(seqNumber,0,0.0,0.0,0.0,0);
        movement = false;
    }
    else {
        if (controler == PC_CTRL)
        {
            control->sendResetWatchdog(seqNumber);
        }
    }

    seqNumber++;
}

void navControlUI::onClickInitControl()
{
    timer->start(30);
    initClicked = true;
}

void navControlUI::onClickStopControl()
{
    timer->stop();
}

void navControlUI::onClickEmergency()
{
    emergencyClicked = true;
}

void navControlUI::onClickCalibHPlane()
{
    calibHPlaneClicked = true;
}

void navControlUI::onClickCalibMagn()
{
    calibMagnClicked = true;
}

void navControlUI::onClickTakeOff()
{
    takeOffClicked = true;
    flying = true;
}

void navControlUI::onClickLand()
{
    landState = 1;
    flying = false;
}

void navControlUI::onClickUp()
{
    upClicked = true;
    upPressed = true;
}

void navControlUI::onReleaseUp()
{
    upPressed = false;
}

void navControlUI::onClickDown()
{
    downClicked = true;
    downPressed = true;
}

void navControlUI::onReleaseDown()
{
    downPressed = false;
}

void navControlUI::onClickForward()
{
    forwardClicked = true;
    forwardPressed = true;
}

void navControlUI::onReleaseForward()
{
    forwardPressed = false;
}

void navControlUI::onClickBackward()
{
    backwardClicked = true;
    backwardPressed = true;
}

void navControlUI::onReleaseBackward()
{
    backwardPressed = false;
}

void navControlUI::onClickRight()
{
    rightClicked = true;
    rightPressed = true;
}

void navControlUI::onReleaseRight()
{
    rightPressed = false;
}

void navControlUI::onClickLeft()
{
    leftClicked = true;
    leftPressed = true;
}

void navControlUI::onReleaseLeft()
{
    leftPressed = false;
}

void navControlUI::onClickRLeft()
{
    rLeftClicked = true;
    rLeftPressed = true;
}

void navControlUI::onReleaseRLeft()
{
    rLeftPressed = false;
}

void navControlUI::onClickRRight()
{
    rRightClicked = true;
    rRightPressed = true;
}

void navControlUI::onReleaseRRight()
{
    rRightPressed = false;
}

void navControlUI::onChangeNavData(int bat, int state, int pitch, int roll, int yaw, double alt, int vx, int vy, int vz)
{
    //battery
    if(bat > 25) {
        batImg->setPixmap(*checkMarkImage);
    }
    else if(bat > 0) {
        batImg->setPixmap(*warningMarkImage);
    }
    else {
        batImg->setPixmap(*xMarkImage);
    }
    char batData[64];
    sprintf(batData,"%d",bat);
    batLabel->setText("Battery:\n"+QString(batData)+"%");

    //state
    char* stateTab[10] = {(char *)"Default",(char *)"Control Init",(char *)"Landed",(char *)"Flying",(char *)"Hovering",(char *)"Test",(char *)"GoToFix",(char *)"TakeOff",(char *)"Intermediate",(char *)"Landing"} ;
    char stateData[64];
    int i = state >> 16 ;
    if( i<10 )
    {
        if(i==2) {
            landed = true;
        }
        else {
            landed = false;
        }
        if(state==0) {
            stateImg->setPixmap(*xMarkImage);
        }
        else {
            stateImg->setPixmap(*checkMarkImage);
        }
        sprintf(stateData,"%s",stateTab[i]);
        stateLabel->setText("State:\n"+QString(stateData));
    }
    else
    {
        stateImg->setPixmap(*warningMarkImage);
        sprintf(stateData,"error");
        stateLabel->setText(stateData);
    }

    //pitch/roll
    adi->setPitch(pitch);
    adi->setRoll(roll);
    adi->update();

    //heading
    hsi->setHeading(yaw);
    hsi->update();

    //speed
    asi->setAirspeed(sqrt(pow(vx,2)+pow(vy,2)+pow(vz,2)));
    asi->update();

    emit newAltFromBarometer(alt);
}

void navControlUI::takeOffOrLand()
{
    if(!flying) {
        onClickTakeOff();
    }
    else {
        onClickLand();
    }
}

void navControlUI::setControler(char controler)
{
    this->controler = controler ;
}

void navControlUI::setUdpSocket(UdpSocket * sock)
{
    udpSocket = sock;
}
