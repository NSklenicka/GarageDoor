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

    void HandleError(QString error);

    OutletSensor* outletSensor;
    DoorMonitor* doorMonitor;

    //send the toogle door signal, and make sure that it actually happens
    void ToggleDoor();

    //toggle the outlet state, and make it actually happens
    bool SetOutletState(DoorState newState);
};

#endif // GARAGEPI_H
