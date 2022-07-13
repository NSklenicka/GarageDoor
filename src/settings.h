#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    //Settings();

    unsigned int static const OutletToggleTimeout_ms();
    unsigned int static const DoorPoll_ms();
    QString static const WebhookKeyFilePath();
    QString static const WebhookKey();
    QString static const SettingsPath();

};

#endif // SETTINGS_H
