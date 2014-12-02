#include "Window.h"

Window::Window()
{
    initWindow() ;
    initWidgets() ;

    setWindowTitle("Localization system - AR.Drone 2.0");

    QObject::connect(buttonDisconnect,SIGNAL(clicked()),this,SLOT(disconnect())) ;
    QObject::connect(buttonConnect,SIGNAL(clicked()),this,SLOT(connect())) ;
    QObject::connect(buttonSimu,SIGNAL(clicked()),this,SLOT(simu())) ;
    QObject::connect(navControl,SIGNAL(newAltFromBarometer(double)),this,SLOT(onChangeAltitudeFromBarometer(double)));
    QObject::connect(launchMissionButton,SIGNAL(clicked()),this,SLOT(onLaunchMissionClicked()));
    QObject::connect(stopMissionButton,SIGNAL(clicked()),this,SLOT(onStopMissionClicked()));

    socketIsActive = false ;
    setFocusPolicy(Qt::StrongFocus) ;

    missionState = STOP_MISSION ;
}

Window::~Window()
{}

void Window::initWindow()
{   
    setFixedSize(1500,700);

    QDesktopWidget desktop ;
    QWidget *screen = desktop.screen() ;
    move(screen->width()/2- this->width()/2,screen->height()/2- this->height()/2) ;
}

void Window::initWidgets()
{
    //Communication
    buttonConnect = new QPushButton("Connect") ;
    buttonDisconnect = new QPushButton("Disconnect") ;
    buttonSimu = new QPushButton("Simulation Display") ;

    QGridLayout *grid = new QGridLayout() ;
    grid->addWidget(buttonConnect,0,0);
    grid->addWidget(buttonDisconnect,0,1);
    grid->addWidget(buttonSimu,1,0,1,2);

    //Box Position
    valueX = new QLabel("0.0") ;
    valueY = new QLabel("0.0") ;
    valueZ = new QLabel("0.0") ;

    QFormLayout *formPosition = new QFormLayout() ;
    formPosition->addRow("Position x", valueX) ;
    formPosition->addRow("Position y", valueY) ;
    formPosition->addRow("Position z", valueZ) ;
    formPosition->setHorizontalSpacing(50);

    //Box Mission
    launchMissionButton = new QPushButton("Start Mission") ;
    stopMissionButton = new QPushButton("Stop Mision") ;
    stateMissionLabel = new QLabel("STOPPED") ;

    spinX = new QDoubleSpinBox() ;
    spinY = new QDoubleSpinBox() ;
    spinZ = new QDoubleSpinBox() ;

    QGridLayout *controlMission = new QGridLayout() ;
    controlMission->addWidget(launchMissionButton,1,1);
    controlMission->addWidget(stopMissionButton,1,2);
    controlMission->addWidget(new QLabel("State Mission :"),2,1) ;
    controlMission->addWidget(stateMissionLabel,2,2) ;
    QFormLayout *formMission = new QFormLayout() ;
    formMission->addRow("Position x", spinX) ;
    formMission->addRow("Position y", spinY) ;
    formMission->addRow("Position z", spinZ) ;
    formMission->setVerticalSpacing(30);
    formMission->setHorizontalSpacing(25);
    QVBoxLayout *layoutMission = new QVBoxLayout() ;
    layoutMission->addLayout(controlMission);
    layoutMission->addLayout(formMission);

    //Left Layout
    QVBoxLayout *leftLayout = new QVBoxLayout() ;
    leftLayout->addLayout(grid);
    leftLayout->addLayout(formPosition);
    leftLayout->addLayout(layoutMission);
    leftLayout->setSpacing(20) ;
    leftLayout->setContentsMargins(20,60,20,60) ;
    //leftLayout->setAlignment(Qt::AlignTop) ;

    //2D display widget
    plot = new Plot(this) ;

    //Height slider
    slider = new QwtSlider() ;
    slider->setScalePosition(QwtSlider::LeadingScale);
    slider->setReadOnly(true);
    slider->setScale(0,2.8) ;
    slider->setScaleStepSize(0.25);
    slider->setContentsMargins(30,20,20,10);
    slider->setFixedHeight(600);

    //Control box
    navControl = new navControlUI();

    //Main Layout
    QHBoxLayout *layout = new QHBoxLayout() ;
    layout->addLayout(leftLayout) ;
    layout->addWidget(plot) ;
    layout->addWidget(slider);
    layout->addLayout(navControl);

    this->setLayout(layout);
}

void Window::update(double x, double y, double z)
{
    //Update label
    valueX->setText(QString::number(x));
    valueY->setText(QString::number(y));
    valueZ->setText(QString::number(z));

    //Update 2D display
    plot->setPosX(x);
    plot->setPosY(y);
    plot->replot();

    //Update height slider
    slider->setValue(z);
}


void Window::onChangeAltitudeFromBarometer(double alt)
{
    valueZ->setText(QString::number(alt));
    slider->setValue(alt);
}

void Window::connect()
{
    socketIsActive = true ;
    udpSocket = new UdpSocket() ;
    QObject::connect(udpSocket,SIGNAL(wifiFrameRead(double, double, double)),this,SLOT(update(double, double, double))) ;
    QObject::connect(udpSocket,SIGNAL(missionStateChanged(char)),this,SLOT(onChangeMissionState(char)));
}

void Window::disconnect()
{
    socketIsActive = false ;
    delete udpSocket ;
}

void Window::simu()
{
    if(socketIsActive)
        udpSocket->simuDisplay();
}

void Window::onLaunchMissionClicked()
{
    double xMission = spinX->value() ;
    double yMission = spinY->value() ;
    double zMission = spinZ->value() ;

    wifiFrame wf = createWifiFrame(MISSION_FRAME,xMission,yMission,zMission,LAUNCH_MISSION) ;
    char *frame = wifiFrameToChar(wf) ;

    while(missionState != LAUNCH_MISSION)
    {
        udpSocket->writeDatagram(frame,sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), 31000) ;
        QThread::sleep(1) ;
    }
}

void Window::onStopMissionClicked()
{
    wifiFrame wf = createWifiFrame(MISSION_FRAME,0.0,0.0,0.0,STOP_MISSION) ;
    char *frame = wifiFrameToChar(wf) ;

    while(missionState != STOP_MISSION)
    {
        udpSocket->writeDatagram(frame,sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), 31000) ;
        QThread::sleep(1) ;
    }
}

void Window::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        navControl->onClickLeft() ;
    }
    else if(event->key() == Qt::Key_Right)
    {
        navControl->onClickRight() ;
    }
    else if(event->key() == Qt::Key_Up)
    {
        navControl->onClickForward() ;
    }
    else if(event->key() == Qt::Key_Down)
    {
        navControl->onClickBackward(); ;
    }
    else if(event->key() == Qt::Key_2)
    {
        navControl->onClickDown();
    }
    else if(event->key() == Qt::Key_8)
    {
        navControl->onClickUp();
    }
    else if(event->key() == Qt::Key_4)
    {
        navControl->onClickRLeft();
    }
    else if(event->key() == Qt::Key_6)
    {
        navControl->onClickRRight();
    }
}

void Window::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
    {
        navControl->onReleaseLeft();
    }
    else if(event->key() == Qt::Key_Right)
    {
        navControl->onReleaseRight();
    }
    else if(event->key() == Qt::Key_Up)
    {
        navControl->onReleaseForward();
    }
    else if(event->key() == Qt::Key_Down)
    {
        navControl->onReleaseBackward();
    }
    else if(event->key() == Qt::Key_2)
    {
        navControl->onReleaseDown();
    }
    else if(event->key() == Qt::Key_8)
    {
        navControl->onReleaseUp();
    }
    else if(event->key() == Qt::Key_4)
    {
        navControl->onReleaseRLeft();
    }
    else if(event->key() == Qt::Key_6)
    {
        navControl->onReleaseRRight();
    }
    else if(event->key() == Qt::Key_Space)
    {
        navControl->takeOffOrLand();
    }
}

void Window::onChangeMissionState(char state)
{
    missionState = state ;
    QString str ;

    if (state == LAUNCH_MISSION)
        str = "Mission Started" ;
    else if (state == STOP_MISSION)
        str = "Mission Stopped" ;
    else if(state == MISSION_FINISHED)
        str = "Mission Finished" ;

    stateMissionLabel->setText(str);
}
