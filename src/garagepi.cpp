#include "garagepi.h"
#include <bcm2835.h>
#include "defines.h"


GaragePi::GaragePi(QObject *parent) : QObject(parent)
{
    if (!bcm2835_init())
        cout << "bcm2835_init() failed";

    //setup output pin

    //create
    doorMonitor = new DoorMonitor(this);
    outletSensor = new OutletSensor(this);

    //connects
    connect(outletSensor, &OutletSensor::OutletStateChanged, this, &GaragePi::OnOutletStateChanged);
    connect(doorMonitor, &DoorMonitor::DoorStateChanged, this, &GaragePi::OnDoorStateChanged);

    //begin
    outletSensor->WaitForStateChanged();
    doorMonitor->WaitForStateChanged();
}

void GaragePi::OnOutletStateChanged(OutletState newState)
{
    if(doorMonitor->GetDoorState() == newState )
        return;

    //toggle the door
    if(!GaragePi::ToggleDoor())
    {
        //handle serious error
    }
}

void GaragePi::OnDoorStateChanged(DoorState newState)
{
    //when the door opens or closes manually, we need to account for that by changing the outlet state
    //stop the outlet sensor
    outletSensor->Stop();
}

bool GaragePi::ToggleOutlet(DoorState newState)
{
    //toggle the outlet state, and make it actually happens

}


bool GaragePi::ToggleDoor()
{
    //send the pulse signal, and make sure that the door actually toggles
}
