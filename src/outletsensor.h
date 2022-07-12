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

signals:
    void OutletStateChanged(OutletState newState);

public slots:

private:

    //poll smart outlet
    OutletState GetOutletState();

    QTimer *timer;

    OutletState m_initialState;

    void PollForStateChanged();
};

#endif // OUTLETSENSOR_H
