#include "navcontrolui.h"

navControlUI::navControlUI(QWidget *parent) :
    QVBoxLayout(parent)
{
    //Control Box
    controlBox = new QGroupBox("Control");
    control = new droneControl();

    emergencyButton = new QPushButton("Emergency");
    calibButton = new QPushButton("Calibrate");
    takeOffButton = new QPushButton("Take Off");
    landButton = new QPushButton("Land");
    rstWatchdogButton = new QPushButton("Reset Watchdog");

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
    controlLayout->addWidget(emergencyButton);
    controlLayout->addWidget(rstWatchdogButton);
    controlLayout->addWidget(calibButton);
    controlLayout->addWidget(takeOffButton);
    controlLayout->addWidget(landButton);
    controlLayout->addLayout(upDownLayout);
    controlLayout->addLayout(grid);
    controlBox->setLayout(controlLayout);
    controlBox->setFixedSize(250,330);

    QObject::connect(emergencyButton,SIGNAL(clicked()),this,SLOT(onClickEmergency()));
    QObject::connect(calibButton,SIGNAL(clicked()),this,SLOT(onClickCalib()));
    QObject::connect(takeOffButton,SIGNAL(clicked()),this,SLOT(onClickTakeOff()));
    QObject::connect(landButton,SIGNAL(clicked()),this,SLOT(onClickLand()));
    QObject::connect(rstWatchdogButton,SIGNAL(clicked()),this,SLOT(onClickrstWatchdog()));

    QObject::connect(upButton,SIGNAL(clicked()),this,SLOT(onClickUp()));
    QObject::connect(downButton,SIGNAL(clicked()),this,SLOT(onClickDown()));
    QObject::connect(forwardButton,SIGNAL(clicked()),this,SLOT(onClickforward()));
    QObject::connect(leftButton,SIGNAL(clicked()),this,SLOT(onClickLeft()));
    QObject::connect(backwardButton,SIGNAL(clicked()),this,SLOT(onClickBackward()));
    QObject::connect(rightButton,SIGNAL(clicked()),this,SLOT(onClickRight()));

    //NavData Box
    navBox = new QGroupBox("NavData");
    navData = new droneNavData(control);

    initButton = new QPushButton("Init");

    QHBoxLayout * batLayout = new QHBoxLayout();
    QLabel * batTxt = new QLabel("Bat = ");
    batLabel = new QLabel("0");
    batLayout->addWidget(batTxt,0,Qt::AlignLeft);
    batLayout->addWidget(batLabel,1,Qt::AlignLeft);

    QHBoxLayout * altLayout = new QHBoxLayout();
    QLabel * altTxt = new QLabel("Alt = ");
    altLabel = new QLabel("0");
    altLayout->addWidget(altTxt,0,Qt::AlignLeft);
    altLayout->addWidget(altLabel,1,Qt::AlignLeft);

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
    navLayout->addWidget(initButton);
    navLayout->addLayout(batLayout);
    navLayout->addLayout(altLayout);
    navLayout->addLayout(vxLayout);
    navLayout->addLayout(vyLayout);
    navLayout->addLayout(vzLayout);
    navBox->setLayout(navLayout);
    navBox->setFixedSize(200,180);

    QObject::connect(initButton,SIGNAL(clicked()),this,SLOT(onClickInit()));
    QObject::connect(navData,SIGNAL(newBat(int)),this,SLOT(onChangeBat(int)));
    QObject::connect(navData,SIGNAL(newAlt(int)),this,SLOT(onChangeAlt(int)));
    QObject::connect(navData,SIGNAL(newVx(int)),this,SLOT(onChangeVx(int)));
    QObject::connect(navData,SIGNAL(newVy(int)),this,SLOT(onChangeVy(int)));
    QObject::connect(navData,SIGNAL(newVz(int)),this,SLOT(onChangeVz(int)));

    //Widget
    addWidget(controlBox,0,Qt::AlignTop);
    addWidget(navBox,0,Qt::AlignTop);

    seqNumber = 1;
}

void navControlUI::onChangeBat(int bat)
{
    char data[64];
    sprintf(data,"%d",bat);
    batLabel->setText(data);
}

void navControlUI::onChangeAlt(int alt)
{
    char data[64];
    sprintf(data,"%d",alt);
    altLabel->setText(data);
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

void navControlUI::onClickUp()
{

}

void navControlUI::onClickDown()
{

}

void navControlUI::onClickForward()
{

}

void navControlUI::onClickRight()
{

}

void navControlUI::onClickBackward()
{

}

void navControlUI::onClickLeft()
{

}

void navControlUI::onClickRLeft()
{

}

void navControlUI::onClickRRight()
{

}

void navControlUI::onClickEmergency()
{
    control->sendEmergency(seqNumber);
    seqNumber++;
}

void navControlUI::onClickCalib()
{
    control->sendCalib(seqNumber);
    seqNumber++;
}

void navControlUI::onClickTakeOff()
{
    control->sendTakeOff(seqNumber);
    seqNumber++;
}

void navControlUI::onClickLand()
{
    control->sendLand(seqNumber);
    seqNumber++;
}

void navControlUI::onClickrstWatchdog()
{
    control->sendResetWatchdog(seqNumber);
    seqNumber++;
}

void navControlUI::onClickInit()
{
    navData->init(seqNumber);
    seqNumber++;
}
