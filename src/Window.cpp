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
    QObject::connect(navControl,SIGNAL(newAltFromBarometer(double)),this,SLOT(onChangeAltitudeFromBarometer(double)));
    QObject::connect(launchMissionButton,SIGNAL(clicked()),this,SLOT(onLaunchMissionClicked()));
    QObject::connect(stopMissionButton,SIGNAL(clicked()),this,SLOT(onStopMissionClicked()));

    socketIsActive = false ;
    setFocusPolicy(Qt::StrongFocus) ;
}

Window::~Window()
{}

void Window::initWindow()
{   
    setFixedSize(1530,700);

    QDesktopWidget desktop ;
    QWidget *screen = desktop.screen() ;
    move(screen->width()/2- this->width()/2,screen->height()/2- this->height()/2) ;
}

void Window::initWidgets()
{
    //Box Communication
    buttonConnect = new QPushButton("Connect") ;
    buttonDisconnect = new QPushButton("Disconnect") ;

    QGridLayout *grid = new QGridLayout() ;
    grid->addWidget(buttonConnect,0,0);
    grid->addWidget(buttonDisconnect,0,1);

    QGroupBox *boxCommunication = new QGroupBox("Communication", this);
    boxCommunication->setLayout(grid) ;
    boxCommunication->setFixedWidth(230);

    //Box Position
    valueX = new QLabel("3.4") ;
    valueY = new QLabel("4.2") ;
    valueZ = new QLabel("1.0") ;

    QFormLayout *formPosition = new QFormLayout() ;
    formPosition->addRow("Position x (m)", valueX) ;
    formPosition->addRow("Position y (m)", valueY) ;
    formPosition->addRow("Position z (m)", valueZ) ;
    formPosition->setHorizontalSpacing(60);
    formPosition->setVerticalSpacing(40) ;

    QGroupBox *boxPosition = new QGroupBox("Position", this);
    boxPosition->setLayout(formPosition) ;
    boxPosition->setFixedWidth(230);

    //Box Mission
    launchMissionButton = new QPushButton("Start Mission") ;
    stopMissionButton = new QPushButton("Stop Mision") ;
    stateMissionLabel = new QLabel("No Mission") ;

    spinX = new QDoubleSpinBox() ;
    spinX->setMaximum(4.2) ;
    spinX->setValue(2.40);
    spinX->setSingleStep(0.1) ;
    spinY = new QDoubleSpinBox() ;
    spinY->setMaximum(6.6) ;
    spinY->setValue(4.40);
    spinX->setSingleStep(0.1) ;
    spinZ = new QDoubleSpinBox() ;
    spinZ->setMaximum(2.9) ;
    spinZ->setValue(1.0);
    spinX->setSingleStep(0.1) ;
    spinAngle = new QDoubleSpinBox() ;
    spinAngle->setMaximum(360) ;

    QGridLayout *controlMission = new QGridLayout() ;
    controlMission->addWidget(launchMissionButton,0,0);
    controlMission->addWidget(stopMissionButton,0,1);
    QLabel *label = new QLabel("Sate Mission") ;
    label->setContentsMargins(0,0,0,20);
    controlMission->addWidget(label,1,0) ;
    stateMissionLabel->setContentsMargins(0,0,0,20);
    controlMission->addWidget(stateMissionLabel,1,1) ;
    controlMission->setVerticalSpacing(40) ;
    QFormLayout *formMission = new QFormLayout() ;
    formMission->addRow("Position x (m)", spinX) ;
    formMission->addRow("Position y (m)", spinY) ;
    formMission->addRow("Position z (m)", spinZ) ;
    formMission->addRow("Angle (°)", spinAngle) ;
    formMission->setVerticalSpacing(40);
    formMission->setHorizontalSpacing(15);
    QVBoxLayout *layoutMission = new QVBoxLayout() ;
    layoutMission->addLayout(controlMission);
    layoutMission->addLayout(formMission);
    layoutMission->setSpacing(20);

    QGroupBox *boxMission = new QGroupBox("Mission", this);
    boxMission->setLayout(layoutMission) ;
    boxMission->setFixedWidth(230);

    //Left Layout
    QVBoxLayout *leftLayout = new QVBoxLayout() ;
    leftLayout->addWidget(boxCommunication);
    leftLayout->addWidget(boxPosition);
    leftLayout->addWidget(boxMission);
    leftLayout->setSpacing(10) ;
    leftLayout->setContentsMargins(20,15,20,15) ;

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
    slider->setValue(1);

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

void Window::onLaunchMissionClicked()
{
    wifiFrame wf ;
    char *tab ;

    /*wf = createChangeMasterFrame(DRONE_CTRL) ;
    tab = (char*)&wf ;
    udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;
    navControl->setControler(DRONE_CTRL);

    QThread::sleep(0.5) ;*/

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

    wf = createMissionFrame(xMission*100,yMission*100,zMission*100,angle,LAUNCH_MISSION) ;
    tab = (char*)&wf ;

    udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;

    stateMissionLabel->setText("Mission Started") ;

    plot->drawTarget(xMission, yMission) ;
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

        wifiFrame wf = createMissionFrame(0.0,0.0,0.0,0.0,STOP_MISSION) ;
        char *tab = (char*)&wf ;

        udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;
    }
}


/*void Window::updateMission()
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
}*/

void Window::onChangeButtonMissionCarre()
{
    numMission = 0 ;

    wifiFrame wf = createMissionFrame(x1*100,y1*100,z1*100,angleDrone,LAUNCH_MISSION)  ;
    char *tab = (char*)&wf ;
    udpSocket->writeDatagram(tab, sizeof(char)*CONVERTED_WIFI_FRAME_SIZE, QHostAddress("192.168.1.1"), DRONE_PORT) ;

    stateMissionLabel->setText("Mission 1") ;

}
