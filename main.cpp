#include <QCoreApplication>
#include <QDebug>
#include <canlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    canHandle hnd;
    canInitializeLibrary();
    hnd = canOpenChannel(0, canOPEN_ACCEPT_VIRTUAL);
    if (hnd < 0) {
        char msg[64];
        canGetErrorText((canStatus)hnd, msg, sizeof(msg));
        fprintf(stderr, "canOpenChannel failed (%s)\n", msg);
        exit(1);
    }
    canSetBusParams(hnd, canBITRATE_250K, 0, 0, 0, 0, 0);
    canSetBusOutputControl(hnd, canDRIVER_NORMAL);
    canBusOn(hnd);
    canWrite(hnd, 123, (void*) "HELLO!", 6, 0);
    canWriteSync(hnd, 500);
    canBusOff(hnd);
    canClose(hnd);
    qDebug() << "The end";

    return a.exec();
}

