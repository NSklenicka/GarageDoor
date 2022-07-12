#include "doormonitor.h"
#include <bcm2835.h>
#include "defines.h"

DoorMonitor::DoorMonitor(QObject *parent) : QObject(parent)
{
    bcm2835_gpio_fsel(PIN_DOOR_SENSOR, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(PIN_DOOR_SENSOR, BCM2835_GPIO_PUD_DOWN);//may change

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DoorMonitor::PollForStateChanged);
}

void DoorMonitor::WaitForStateChanged()
{
    //get initial state
    m_initialState = GetDoorState();

    //start polling timer
    timer->start(DOOR_POLL_MS);
}

void DoorMonitor::Stop()
{
    timer->stop();
}

DoorState DoorMonitor::GetDoorState()
{
    if(HIGH == bcm2835_gpio_lev(PIN_OUTLET_SENSOR))
        return DoorIsOpen;
    else return DoorIsClosed;
}

void DoorMonitor::PollForStateChanged()
{
    DoorState currentState = GetDoorState();
    if(currentState != m_initialState)
    {
        Stop();//stop polling
        emit DoorStateChanged(currentState);
    }
}
