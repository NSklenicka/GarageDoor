#include "outletsensor.h"
#include <bcm2835.h>
#include "defines.h"
#include <QElapsedTimer>
#include <QThread>
#include "settings.h"

OutletSensor::OutletSensor(QObject *parent) : QObject(parent)
{
    bcm2835_gpio_fsel(PIN_OUTLET_SENSOR, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(PIN_OUTLET_SENSOR, BCM2835_GPIO_PUD_DOWN);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &OutletSensor::PollForStateChanged);
}

void OutletSensor::WaitForStateChanged()
{
    //get initial state
    m_initialState = GetOutletState();

    //start polling timer
    timer->start(OUTLET_POLL_MS);
}

void OutletSensor::Stop()
{
    timer->stop();
}

bool OutletSensor::WaitForState(int state)
{
    //get initial state
    if(state == GetOutletState())
    {
        return true;
    }

    //start polling timer
    timer->start(OUTLET_POLL_MS);

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

OutletState OutletSensor::GetOutletState()
{
    if(HIGH == bcm2835_gpio_lev(PIN_OUTLET_SENSOR))
        return DoorOpen;
    else return DoorClose;
}

void OutletSensor::PollForStateChanged()
{
    OutletState currentState = GetOutletState();
    if(currentState != m_initialState)
    {
        Stop();//stop polling
        emit OutletStateChanged(currentState);
    }
}
