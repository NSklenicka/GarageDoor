#ifndef DOORMONITOR_H
#define DOORMONITOR_H

#include <QObject>
#include <QTimer>

enum DoorState
{
    DoorIsOpen,
    DoorIsClosed
};

class DoorMonitor : public QObject
{
    Q_OBJECT
public:
    explicit DoorMonitor(QObject *parent = nullptr);

    //begin polling. emit signal when state changes
    void WaitForStateChanged();

    //stop polling
    void Stop();

    //poll door state
    DoorState GetDoorState();

signals:
    void DoorStateChanged(DoorState newState);

public slots:

private:


    QTimer *timer;

    DoorState m_initialState;

    void PollForStateChanged();
};
#endif // DOORMONITOR_H
