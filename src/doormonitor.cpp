#include "doormonitor.h"
#include <bcm2835.h>
#include "defines.h"
#include <QElapsedTimer>
#include <QThread>

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

bool DoorMonitor::WaitForState(DoorState newState)
{
    //get initial state
    if(GetDoorState() == newState)
    {
        log << "that's weird, DoorMonitor::WaitForState() door was already in state!";
        return true;
    }

    //start polling timer
    timer->start(DoorPoll_ms());

    //start a timeout timer
    QElapsedTimer timeoutTimer;
    timeoutTimer.start();

    while(timer->isActive())//until we stop polling
    {
        //check for timeout every n ms
        QThread::msleep(50);
        if(timeoutTimer.elapsed() > Settings::OutletToggleTimeout_ms())
        {
            timer->stop();
            return false;
        }
    }

    //we're good
    return true;
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
