#ifndef DRONENAVDATAUI_H
#define DRONENAVDATAUI_H

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include "dronenavdata.h"

class droneNavDataUI : public QGroupBox
{
    Q_OBJECT
public:
    explicit droneNavDataUI(QWidget *parent = 0);

private:
    droneNavData * drone;
    QPushButton * initButton;
    QVBoxLayout * VBLayout;

signals:

public slots:

private slots:
    void onClickInit();

};

#endif // DRONENAVDATAUI_H
