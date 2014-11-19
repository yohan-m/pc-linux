#include "navcontrolui.h"

navControlUI::navControlUI(QWidget *parent) :
    QVBoxLayout(parent)
{
    //Control Box
    controlBox = new QGroupBox("Control");
    control = new droneControl();

    initControlButton = new QPushButton("Init");
    stopControlButton = new QPushButton("Stop");
    QHBoxLayout * initStopLayout = new QHBoxLayout();
    initStopLayout->addWidget(initControlButton);
    initStopLayout->addWidget(stopControlButton);
    calibButton = new QPushButton("Calibrate");
    takeOffButton = new QPushButton("Take Off");
    landButton = new QPushButton("Land");

    upButton = new QPushButton("Up");
    downButton = new QPushButton("Down");
    forwardButton = new QPushButton("Forward");
    leftButton = new QPushButton("Left");
    backwardButton = new QPushButton("Backward");
    rightButton = new QPushButton("Right");
    rLeftButton = new QPushButton("RLeft");
    rRightButton = new QPushButton("RRight");

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
    controlLayout->addWidget(calibButton);
    controlLayout->addWidget(takeOffButton);
    controlLayout->addWidget(landButton);
    controlLayout->addLayout(upDownLayout);
    controlLayout->addLayout(grid);
    controlBox->setLayout(controlLayout);
    controlBox->setFixedSize(250,330);

    QObject::connect(initControlButton,SIGNAL(clicked()),this,SLOT(onClickInitControl()));
    QObject::connect(stopControlButton,SIGNAL(clicked()),this,SLOT(onClickStopControl()));
    QObject::connect(calibButton,SIGNAL(clicked()),this,SLOT(onClickCalib()));
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

    initNavDataButton = new QPushButton("Init");

    QHBoxLayout * batLayout = new QHBoxLayout();
    QLabel * batTxt = new QLabel("Bat = ");
    batLabel = new QLabel("0");
    batLayout->addWidget(batTxt,0,Qt::AlignLeft);
    batLayout->addWidget(batLabel,1,Qt::AlignLeft);

    QHBoxLayout * stateLayout = new QHBoxLayout();
    QLabel * stateTxt = new QLabel("State = ");
    stateLabel = new QLabel("0");
    stateLayout->addWidget(stateTxt,0,Qt::AlignLeft);
    stateLayout->addWidget(stateLabel,1,Qt::AlignLeft);

    QHBoxLayout * altLayout = new QHBoxLayout();
    QLabel * altTxt = new QLabel("Alt = ");
    altLabel = new QLabel("0");
    altLayout->addWidget(altTxt,0,Qt::AlignLeft);
    altLayout->addWidget(altLabel,1,Qt::AlignLeft);

    QHBoxLayout * pitchLayout = new QHBoxLayout();
    QLabel * pitchTxt = new QLabel("Pitch = ");
    pitchLabel = new QLabel("0");
    pitchLayout->addWidget(pitchTxt,0,Qt::AlignLeft);
    pitchLayout->addWidget(pitchLabel,1,Qt::AlignLeft);

    QHBoxLayout * rollLayout = new QHBoxLayout();
    QLabel * rollTxt = new QLabel("Roll = ");
    rollLabel = new QLabel("0");
    rollLayout->addWidget(rollTxt,0,Qt::AlignLeft);
    rollLayout->addWidget(rollLabel,1,Qt::AlignLeft);

    QHBoxLayout * yawLayout = new QHBoxLayout();
    QLabel * yawTxt = new QLabel("Yaw = ");
    yawLabel = new QLabel("0");
    yawLayout->addWidget(yawTxt,0,Qt::AlignLeft);
    yawLayout->addWidget(yawLabel,1,Qt::AlignLeft);

    QHBoxLayout * vxLayout = new QHBoxLayout();
    QLabel * vxTxt = new QLabel("Vx = ");
    vxLabel = new QLabel("0");
    vxLayout->addWidget(vxTxt,0,Qt::AlignLeft);
    vxLayout->addWidget(vxLabel,1,Qt::AlignLeft);

    QHBoxLayout * vyLayout = new QHBoxLayout();
    QLabel * vyTxt = new QLabel("Vy = ");
    vyLabel = new QLabel("0");
    vyLayout->addWidget(vyTxt,0,Qt::AlignLeft);
    vyLayout->addWidget(vyLabel,1,Qt::AlignLeft);

    QHBoxLayout * vzLayout = new QHBoxLayout();
    QLabel * vzTxt = new QLabel("Vz = ");
    vzLabel = new QLabel("0");
    vzLayout->addWidget(vzTxt,0,Qt::AlignLeft);
    vzLayout->addWidget(vzLabel,1,Qt::AlignLeft);

    navLayout = new QVBoxLayout();
    navLayout->addWidget(initNavDataButton);
    navLayout->addLayout(batLayout);
    navLayout->addLayout(stateLayout);
    navLayout->addLayout(pitchLayout);
    navLayout->addLayout(rollLayout);
    navLayout->addLayout(yawLayout);
    navLayout->addLayout(altLayout);
    navLayout->addLayout(vxLayout);
    navLayout->addLayout(vyLayout);
    navLayout->addLayout(vzLayout);
    navBox->setLayout(navLayout);
    navBox->setFixedSize(200,280);

    QObject::connect(initNavDataButton,SIGNAL(clicked()),this,SLOT(onClickInitNavData()));
    QObject::connect(navData,SIGNAL(newBat(int)),this,SLOT(onChangeBat(int)));
    QObject::connect(navData,SIGNAL(newState(int)),this,SLOT(onChangeState(int)));
    QObject::connect(navData,SIGNAL(newPitch(int)),this,SLOT(onChangePitch(int)));
    QObject::connect(navData,SIGNAL(newRoll(int)),this,SLOT(onChangeRoll(int)));
    QObject::connect(navData,SIGNAL(newYaw(int)),this,SLOT(onChangeYaw(int)));
    QObject::connect(navData,SIGNAL(newAlt(int)),this,SLOT(onChangeAlt(int)));
    QObject::connect(navData,SIGNAL(newVx(int)),this,SLOT(onChangeVx(int)));
    QObject::connect(navData,SIGNAL(newVy(int)),this,SLOT(onChangeVy(int)));
    QObject::connect(navData,SIGNAL(newVz(int)),this,SLOT(onChangeVz(int)));

    //Widget
    addWidget(controlBox,0,Qt::AlignTop);
    addWidget(navBox,0,Qt::AlignTop);

    seqNumber = 1;

    movement = false;
    landClicked = false;
    calibClicked = false;
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

    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(controlManager()));
}

void navControlUI::controlManager()
{
    if(landClicked) {
        control->sendLand(seqNumber);
        landClicked = false;
    }
    else if(calibClicked) {
        control->sendCalib(seqNumber);
        calibClicked = false;
    }
    else if (takeOffClicked) {
        control->sendTakeOff(seqNumber);
        takeOffClicked = false;
    }
    else if (upClicked || upPressed) {
        control->sendMovement(seqNumber,1,0.0,0.0,0.5,0.0);
        upClicked = false;
        movement = true;
    }
    else if (downClicked || downPressed) {
        control->sendMovement(seqNumber,1,0.0,0.0,-0.5,0.0);
        downClicked = false;
        movement = true;
    }
    else if (forwardClicked || forwardPressed) {
        control->sendMovement(seqNumber,1,0.0,-0.5,0.0,0.0);
        forwardClicked = false;
        movement = true;
    }
    else if (backwardClicked || backwardPressed) {
        control->sendMovement(seqNumber,1,0.0,0.5,0.0,0.0);
        backwardClicked = false;
        movement = true;
    }
    else if (rightClicked || rightPressed) {
        control->sendMovement(seqNumber,1,0.5,0.0,0.0,0.0);
        rightClicked = false;
        movement = true;
    }
    else if (leftClicked || leftPressed) {
        control->sendMovement(seqNumber,1,-0.5,0.0,0.0,0.0);
        leftClicked = false;
        movement = true;
    }
    else if (rLeftClicked || rLeftPressed) {
        control->sendMovement(seqNumber,1,0.0,0.0,0.0,0.6);
        rLeftClicked = false;
        movement = true;
    }
    else if (rRightClicked || rRightPressed) {
        control->sendMovement(seqNumber,1,0.0,0.0,0.0,-0.6);
        rRightClicked = false;
        movement = true;
    }
    else if (movement) {
        control->sendMovement(seqNumber,0,0.0,0.0,0.0,0);
        movement = false;
    }
    else {
        control->sendResetWatchdog(seqNumber);
    }

    seqNumber++;
}

void navControlUI::onClickInitControl()
{
    timer->start(30);
}

void navControlUI::onClickStopControl()
{
    timer->stop();
}

void navControlUI::onClickCalib()
{
    calibClicked = true;
}

void navControlUI::onClickTakeOff()
{
    takeOffClicked = true;
}

void navControlUI::onClickLand()
{
    landClicked = true;
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

void navControlUI::onClickInitNavData()
{
    navData->init(seqNumber);
    seqNumber++;
}

void navControlUI::onChangeBat(int bat)
{
    char data[64];
    sprintf(data,"%d",bat);
    batLabel->setText(data);
}

void navControlUI::onChangeState(int state)
{
    char data[64];
    sprintf(data,"%d",state);
    stateLabel->setText(data);
}

void navControlUI::onChangeAlt(int alt)
{
    char data[64];
    sprintf(data,"%d",alt);
    altLabel->setText(data);
}

void navControlUI::onChangePitch(int pitch)
{
    char data[64];
    sprintf(data,"%d",pitch);
    pitchLabel->setText(data);
}

void navControlUI::onChangeRoll(int roll)
{
    char data[64];
    sprintf(data,"%d",roll);
    rollLabel->setText(data);
}

void navControlUI::onChangeYaw(int yaw)
{
    char data[64];
    sprintf(data,"%d",yaw);
    yawLabel->setText(data);
}

void navControlUI::onChangeVx(int vx)
{
    char data[64];
    sprintf(data,"%d",vx);
    vxLabel->setText(data);
}

void navControlUI::onChangeVy(int vy)
{
    char data[64];
    sprintf(data,"%d",vy);
    vyLabel->setText(data);
}

void navControlUI::onChangeVz(int vz)
{
    char data[64];
    sprintf(data,"%d",vz);
    vzLabel->setText(data);
}

