#include "Window.h"

#define x1  1.60
#define y1  4.40
#define z1  0.80

#define x2  1.60
#define y2  4.40
#define z2  0.80

#define x3  3.00
#define y3  4.50
#define z3  0.80

#define x4  3.00
#define y4  2.00
#define z4  0.80

#define angleDrone  0.0


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
    QObject::connect(radioButtonDrone,SIGNAL(clicked()),this,SLOT(onChangeRadioButton()));
    QObject::connect(radioButtonPc,SIGNAL(clicked()),this,SLOT(onChangeRadioButton()));
    QObject::connect(buttonMissionCarre,SIGNAL(clicked()),this,SLOT(onChangeButtonMissionCarre()));

    socketIsActive = false ;
    setFocusPolicy(Qt::StrongFocus) ;
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
    radioButtonDrone = new QRadioButton("Drone control") ;
    radioButtonPc = new QRadioButton("PC control") ;
    radioButtonDrone->setChecked(true);

    QGridLayout *grid = new QGridLayout() ;
    grid->addWidget(buttonConnect,0,0);
    grid->addWidget(buttonDisconnect,0,1);
    grid->addWidget(buttonSimu,1,0,1,2);
    grid->addWidget(radioButtonDrone,2,0);
    grid->addWidget(radioButtonPc,2,1);
    grid->setVerticalSpacing(20) ;

    QGroupBox *boxCommunication = new QGroupBox("Communication", this);
    boxCommunication->setLayout(grid) ;

    //Box Position
    valueX = new QLabel("0.0") ;
    valueY = new QLabel("0.0") ;
    valueZ = new QLabel("0.0") ;

    QFormLayout *formPosition = new QFormLayout() ;
    formPosition->addRow("Position x", valueX) ;
    formPosition->addRow("Position y", valueY) ;
    formPosition->addRow("Position z", valueZ) ;
    formPosition->setHorizontalSpacing(100);
    formPosition->setVerticalSpacing(20) ;

    QGroupBox *boxPosition = new QGroupBox("Position", this);
    boxPosition->setLayout(formPosition) ;

    //Box Mission
    launchMissionButton = new QPushButton("Start Mission") ;
    stopMissionButton = new QPushButton("Stop Mision") ;
    buttonMissionCarre = new QPushButton("Mission carré") ;
    stateMissionLabel = new QLabel("No Mission") ;

    spinX = new QDoubleSpinBox() ;
    spinX->setMaximum(4.2) ;
    spinX->setSingleStep(0.1) ;
    spinY = new QDoubleSpinBox() ;
    spinY->setMaximum(6.6) ;
    spinX->setSingleStep(0.1) ;
    spinZ = new QDoubleSpinBox() ;
    spinZ->setMaximum(2.9) ;
    spinX->setSingleStep(0.1) ;
    spinAngle = new QDoubleSpinBox() ;
    spinAngle->setMaximum(360) ;

    QGridLayout *controlMission = new QGridLayout() ;
    controlMission->addWidget(launchMissionButton,0,0);
    controlMission->addWidget(stopMissionButton,0,1);
    controlMission->addWidget(new QLabel("State Mission :"),1,0) ;
    controlMission->addWidget(stateMissionLabel,1,1) ;
    controlMission->addWidget(buttonMissionCarre,2,0) ;
    controlMission->setVerticalSpacing(20) ;
    QFormLayout *formMission = new QFormLayout() ;
    formMission->addRow("Position x (m)", spinX) ;
    formMission->addRow("Position y (m)", spinY) ;
    formMission->addRow("Position z (m)", spinZ) ;
    formMission->addRow("Angle (°)", spinAngle) ;
    formMission->setVerticalSpacing(20);
    formMission->setHorizontalSpacing(20);
    QVBoxLayout *layoutMission = new QVBoxLayout() ;
    layoutMission->addLayout(controlMission);
    layoutMission->addLayout(formMission);
    layoutMission->setSpacing(20);

    QGroupBox *boxMission = new QGroupBox("Mission", this);
    boxMission->setLayout(layoutMission) ;

    //Left Layout
    QVBoxLayout *leftLayout = new QVBoxLayout() ;
    leftLayout->addWidget(boxCommunication);
    leftLayout->addWidget(boxPosition);
    leftLayout->addWidget(boxMission);
    leftLayout->setSpacing(30) ;
    leftLayout->setContentsMargins(20,25,20,25) ;

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
    if (x < 4.3)
        valueX->setText(QString::number(x));
    else
        valueX->setText("> 4.3");

    if (y < 6.6)
        valueY->setText(QString::number(y));
    else
        valueY->setText("> 6.6");

    if (z < 2.8)
        valueZ->setText(QString::number(z));
    else
        valueZ->setText("> 2.8");

    //Update 2D display
    plot->setPosX(x);
    plot->setPosY(y);
    plot->replot();
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
    navControl->setUdpSocket(udpSocket);
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
    if (spinX->value() == 0.0)
        spinX->setValue(valueX->text().toDouble()) ;

    if (spinY->value() == 0.0)
        spinY->setValue(valueY->text().toDouble()) ;

    if (spinZ->value() == 0.0)
        spinZ->setValue(valueZ->text().toDouble()) ;

    double xMission = spinX->value() ;
    double yMission = spinY->value() ;
    double zMission = spinZ->value() ;
    double angle = spinAngle->value() ;

    wifiFrame wf = createMissionFrame(xMission*100,yMission*100,zMission*100,angle,LAUNCH_MISSION) ;
    char *tab = (char*)&wf ;

    udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;

    stateMissionLabel->setText("Mission Started") ;
}

void Window::onStopMissionClicked()
{
    wifiFrame wf = createMissionFrame(0.0,0.0,0.0,0.0,STOP_MISSION) ;
    char *tab = (char*)&wf ;

    udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;

    stateMissionLabel->setText("Mission Stopped") ;

    numMission = 4 ;
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
    qDebug() << "on change mission state called";
    if(state == MISSION_FINISHED)
    {
        stateMissionLabel->setText("Mission Finished");
        updateMission() ;
    }
}

void Window::onChangeRadioButton()
{
    wifiFrame wf ;

    if (radioButtonPc->isChecked())
    {
         wf = createChangeMasterFrame(PC_CTRL) ;
         char *tab = (char*)&wf ;
         udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;
         navControl->setControler(PC_CTRL);
    }
    else if (radioButtonDrone->isChecked())
    {
         wf = createChangeMasterFrame(DRONE_CTRL) ;

         char *tab = (char*)&wf ;
         udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;
         navControl->setControler(DRONE_CTRL);
    }
}

void Window::updateMission()
{
    numMission ++ ;
    wifiFrame wf ;

    switch (numMission)
    {
        case 1 :
            QThread::sleep(2) ;
            wf = createMissionFrame(x2*100,y2*100,z2*100,angleDrone,LAUNCH_MISSION)  ;
            stateMissionLabel->setText("Mission 2") ;
            break ;
        case 2 :
            QThread::sleep(2) ;
            wf = createMissionFrame(x3*100,y3*100,z3*100,angleDrone,LAUNCH_MISSION) ;
            stateMissionLabel->setText("Mission 3") ;
            break ;
        case 3 :
            QThread::sleep(2) ;
            wf = createMissionFrame(x4*100,y4*100,z4*100,angleDrone,LAUNCH_MISSION) ;
            stateMissionLabel->setText("Mission 4") ;
            break ;
        default:
            wf = createMissionFrame(0.0,0.0,0.0,0.0,STOP_MISSION) ;
            stateMissionLabel->setText("Mission Stop") ;
            break ;
   }

            char *tab = (char*)&wf ;
            udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;
}

void Window::onChangeButtonMissionCarre()
{
    numMission = 0 ;

    wifiFrame wf = createMissionFrame(x1*100,y1*100,z1*100,angleDrone,LAUNCH_MISSION)  ;
    char *tab = (char*)&wf ;
    udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;

    stateMissionLabel->setText("Mission 1") ;

}
