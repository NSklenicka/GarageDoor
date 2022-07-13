#include "settings.h"

#include <QStandardPaths>
#include <QSettings>

#define SETTINGS_INIT QSettings settings(SettingsPath(), QSettings::IniFormat)

unsigned int const Settings::OutletToggleTimeout_ms()
{
    return 10*1000;
}

unsigned int const Settings::DoorPoll_ms()
{
    return 500;
}

QString const Settings::WebhookKeyFilePath()
{
    return QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/webhookKey";
}

const QString Settings::WebhookKey()
{
    QSettings webhookSettings(WebhookKeyFilePath(), QSettings::IniFormat);
    return webhookSettings.value("WebhookKey").toString();
}

const QString Settings::SettingsPath()
{
    return QString();
}
