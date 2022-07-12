#include <QCoreApplication>

#include "garagepi.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GaragePi gp;

    return a.exec();
}
