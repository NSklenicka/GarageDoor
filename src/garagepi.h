#ifndef GARAGEPI_H
#define GARAGEPI_H

#include <QObject>

#include "outletsensor.h"
#include "doormonitor.h"


class GaragePi : public QObject
{
    Q_OBJECT
public:
    explicit GaragePi(QObject *parent = nullptr);

signals:

public slots:

private:

    void OnOutletStateChanged(OutletState newState);
    void OnDoorStateChanged(DoorState newState);

    OutletSensor* outletSensor;
    DoorMonitor* doorMonitor;

    //send the close signal, and make sure that it actually happens
    bool ToggleDoor();

    //toggle the outlet state, and make it actually happens
    bool ToggleOutlet(DoorState newState);
};

#endif // GARAGEPI_H
