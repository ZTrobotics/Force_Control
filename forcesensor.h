#ifndef FORCESENSOR_H
#define FORCESENSOR_H

#include <QObject>

#include <3rd-party/NI-ATI/NIDAQ/include/NIDAQmx.h>
#include <3rd-party/NI-ATI/ATIDAQ/ftconfig.h>

#include "common.h"

#define FORCE_DIM 6

int32 EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
int32 DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);



class ForceSensor : public QObject
{
    Q_OBJECT
public:
    explicit ForceSensor(QObject *parent = 0);
    ~ForceSensor();

signals:

    // Send a message.
    void sendMessage(QString msg);

    // Send force data
    void sendForceData(Force6D f);

    //
    void initDone(bool isSuccessful);

    //
    void onlineStatus(bool s);


public slots:

    void onInit();


private:
    TaskHandle  taskHandle;
};

#endif // FORCESENSOR_H
