#ifndef OUTLETSENSOR_H
#define OUTLETSENSOR_H

#include <QObject>
#include <QTimer>

enum OutletState
{
    DoorOpen,
    DoorClose
};

class OutletSensor : public QObject
{
    Q_OBJECT
public:
    explicit OutletSensor(QObject *parent = nullptr);

    //begin polling. emit signal when state changes
    void WaitForStateChanged();

    //stop polling
    void Stop();

    //wait for a specific state
    //return false for timeout
    bool WaitForState(int state);

    OutletState GetOutletState();

signals:
    void OutletStateChanged(OutletState newState);

public slots:

private:

    QTimer *timer;

    OutletState m_initialState;

    void PollForStateChanged();
};

#endif // OUTLETSENSOR_H
