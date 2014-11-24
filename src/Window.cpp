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
    //Control widgets
    buttonConnect = new QPushButton("Connect") ;
    buttonDisconnect = new QPushButton("Disconnect") ;
    buttonSimu = new QPushButton("Simulation Display") ;

    labelX = new QLabel("X");
    labelX->setAlignment(Qt::AlignCenter);
    labelY = new QLabel("Y") ;
    labelY->setAlignment(Qt::AlignCenter);
    labelZ = new QLabel("Z") ;
    labelZ->setAlignment(Qt::AlignCenter);

    valueX = new QLabel("none") ;
    valueY = new QLabel("none") ;
    valueZ = new QLabel("none") ;

    QGridLayout *grid = new QGridLayout() ;
    grid->addWidget(buttonConnect,0,0);
    grid->addWidget(buttonDisconnect,0,1);
    grid->addWidget(buttonSimu,1,0);
    grid->addWidget(labelX,2,0);
    grid->addWidget(valueX,2,1);
    grid->addWidget(labelY,3,0);
    grid->addWidget(valueY,3,1);
    grid->addWidget(labelZ,4,0);
    grid->addWidget(valueZ,4,1);

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
    layout->addLayout(grid) ;
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

