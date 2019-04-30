#ifndef SYSTEM_H
#define SYSTEM_H

#include "forcesensor.h"
#include "robot.h"
#include "gui.h"


class ForceSensorThread : public QThread
{
    Q_OBJECT
public:
    ForceSensorThread(){}
    ForceSensor *fs;
protected:
    void run()
    {
        fs = new ForceSensor();
        emit objectCreated();
        exec();
    }
signals:
    void objectCreated();
};

class RobotThread : public QThread
{
    Q_OBJECT
public:
    RobotThread(){}
    Robot * rbt;
protected:

    // Run in a new thread.
    void run()
    {
        // Create robot component object
        rbt = new Robot();

        // Inform the system that robot object is created.
        emit robotObjectCreated();
        // Qt event loop.
        exec();
    }

signals:
    // Inform the system that robot object is created.
    void robotObjectCreated();
};


class SCASystem : public QWidget
{
    Q_OBJECT
public:
    explicit SCASystem(QWidget *parent=0);
    ~SCASystem();
private:
    MainwindowWidget *mw;


    ForceSensorThread *fsThread;
    RobotThread *robotThread;

    bool isFSObjectCreated;
    bool isRobotObjectCreated;

    QTimer *tmr;
    QTimer *tmrinput;


    int makeConnections();

private slots:

    void onFSObjectCreated();
    void onRobotObjectCreated();

    void onTmrCheckObjectCreated();


    void onRobotInitDone(bool isSucessful);
    void onFSInitDOne(bool isSuccessful);

signals:

    void initFS();
    void initRobot();

};



#endif // SYSTEM_H
