#include "Window.h"

Window::Window()
{
    initWindow() ;
    initWidgets() ;

    QObject::connect(buttonDisconnect,SIGNAL(clicked()),this,SLOT(disconnect())) ;
    QObject::connect(buttonConnect,SIGNAL(clicked()),this,SLOT(connect())) ;
    QObject::connect(buttonSimu,SIGNAL(clicked()),this,SLOT(simu())) ;

    socketIsActive = false ;
}

Window::~Window()
{}

void Window::initWindow()
{   
    setFixedSize(1200,700);

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
    slider->setScale(0,3.5) ;
    slider->setScaleStepSize(0.25);
    slider->setContentsMargins(30,20,20,10);
    slider->setFixedHeight(600);

    //Main Layout
    QHBoxLayout *layout = new QHBoxLayout() ;
    layout->addLayout(grid) ;
    layout->addWidget(plot) ;
    layout->addWidget(slider);

    this->setLayout(layout);
}

void Window::update()
{
    //Get the new position sent from the drone
    double x = udpSocket->getPosX() ;
    double y = udpSocket->getPosY() ;
    double z = udpSocket->getPosZ() ;

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

void Window::connect()
{
    socketIsActive = true ;
    udpSocket = new UdpSocket() ;
    QObject::connect(udpSocket,SIGNAL(wifiFrameRead()),this,SLOT(update())) ;
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


