#include "garagepi.h"
#include <bcm2835.h>
#include "defines.h"


GaragePi::GaragePi(QObject *parent) : QObject(parent)
{
    if (!bcm2835_init())
    {
        HandleError("bcm2835_init() failed");
        return;
    }

    //setup output pins
    //here

    //create
    doorMonitor = new DoorMonitor(this);
    outletSensor = new OutletSensor(this);

    //connects
    connect(outletSensor, &OutletSensor::OutletStateChanged, this, &GaragePi::OnOutletStateChanged);
    connect(doorMonitor, &DoorMonitor::DoorStateChanged, this, &GaragePi::OnDoorStateChanged);

    //when we start, check garage door state against outlet state
    auto outletState = outletSensor->GetOutletState();
    if(doorMonitor->GetDoorState() != outletState)
    {
        ToggleDoor();
    }

    //begin
    outletSensor->WaitForStateChanged();
    doorMonitor->WaitForStateChanged();
}

void GaragePi::OnOutletStateChanged(OutletState newState)
{
    if(doorMonitor->GetDoorState() == newState )
        return;

    ToggleDoor();
}

void GaragePi::OnDoorStateChanged(DoorState newState)
{
    //when the door opens or closes manually, we need to account for that by changing the outlet state
    //stop the outlet sensor
    outletSensor->Stop();
    SetOutletState(newState);

    //restart our sensors
    outletSensor->WaitForStateChanged();
    doorMonitor->WaitForStateChanged();
}

void GaragePi::HandleError(QString error)
{
    cout << "Error: " << error;
    //post hook
}



bool GaragePi::SetOutletState(DoorState newState)
{
    //toggle the outlet state, and make sure it actually happens
    bool ok;
    QString error;

    if(DoorState::DoorIsOpen == newState)
    {
        //set the outlet to "door should be open"
        //post request, "enableOutlet" = Event Name

        //wait for it to actually happen
        ok = outletSensor->WaitForState(newState);
        if(!ok) error = "Timeout waiting for outlet state to be 'door should be open'";
    }
    else if(DoorState::DoorIsClosed == newState)
    {
        //set the outlet to "door should be closed"
        //post request, "disbableOutlet" = Event Name

        //wait for it to actually happen
        ok = outletSensor->WaitForState(newState);
        if(!ok) error = "Timeout waiting for outlet state to be 'door should be closed'";
    }
    else
    {
        ok = false;
        error = "Unknown state: " + QString::number(newState);
    }

    if(!ok)
    {
        HandleError(error);
        return false;
    }

    return true;
}


void GaragePi::ToggleDoor()
{
    //send the pulse signal, and make sure that the door actually toggles

    //post the event

    //

}
