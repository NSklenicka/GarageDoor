#ifndef PINS_H
#define PINS_H

#include <QDebug>
#define cout qDebug()

#define OUTLET_POLL_MS 2000
#define DOOR_POLL_MS 4000

#define PIN_OUTLET_SENSOR RPI_V2_GPIO_P1_31 //31
#define PIN_DOOR_SENSOR RPI_V2_GPIO_P1_29 //29
#define PIN_OUTPUT_SWITCH "UNDEFINED"

#endif // PINS_H


