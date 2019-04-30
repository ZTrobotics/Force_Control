#include "system.h"
#include <QTime>
#include<QTimer>

SCASystem::SCASystem(QWidget *parent):QWidget(parent)
{
    //所有的成员在开始没有创建
    isFSObjectCreated = false;
    isRobotObjectCreated = false;

    mw = new MainwindowWidget(0);
    mw->showMaximized();


    //建立新的线程
    fsThread = new ForceSensorThread();
    robotThread = new RobotThread();

    //连接信号,线程已经建立好后，发出建立好的信号，传递到槽函数，槽函数将bool型变量置为true
    connect(fsThread, SIGNAL(objectCreated()), this, SLOT(onFSObjectCreated()));
    connect(robotThread, SIGNAL(robotObjectCreated()), this, SLOT(onRobotObjectCreated()));
    //线程开始执行run（）
    fsThread->start();
    robotThread->start();

    //新建定时器，100ms，不停的检测是否每个线程都创建了
    tmr = new QTimer(this);
    tmr->start(100);
    connect(tmr, SIGNAL(timeout()), this, SLOT(onTmrCheckObjectCreated()));

}
SCASystem::~SCASystem(){}


//所有线程建立好的槽函数，bool都将置为true
void SCASystem::onFSObjectCreated()
{
    isFSObjectCreated = true;
}

void SCASystem::onRobotObjectCreated()
{
    isRobotObjectCreated = true;
}


//定时间每100ms会执行这个函数，来检测每个线程是否都建立了，即bool型是否都为真
void SCASystem::onTmrCheckObjectCreated()
{
    //如果所有线程bool型都为true
    if (isFSObjectCreated == true
            && isRobotObjectCreated == true)
    {
        //连接所有信号与槽，并停止检测定时器
        makeConnections();
        tmr->stop();
        emit initRobot();
    }
}

int SCASystem::makeConnections()
{
    //第一个信号，是由定时器到时的函数发出的，标志着开始机器人的初始化，也就是第一个线程的初始化
    connect(this , SIGNAL(initRobot()) , robotThread->rbt , SLOT(onInit()) , Qt::QueuedConnection);
    //机器人初始化结束之后，会发出initDone的信号,标志机器人初始化成功，传给槽函数，槽函数会让下一个线程开始初始化，也就是一个串行的过程
    connect(robotThread->rbt, SIGNAL(initDone(bool)), this, SLOT(onRobotInitDone(bool)), Qt::QueuedConnection);


    //第二个线程，因为第一个线程发出的槽函数开始初始化
    connect(this, SIGNAL(initFS()), fsThread->fs, SLOT(onInit()), Qt::QueuedConnection);
    connect(fsThread->fs, SIGNAL(initDone(bool)), this, SLOT(onFSInitDOne(bool)), Qt::QueuedConnection);

    //mw->Conw是主窗口的控制窗口指针，它的信号定义在控制窗口下，可以对其他线程发出信号
    //在控制窗口的类中定义了toopentheservo（打开伺服）这样一个信号
    //槽函数通知Robot去打开伺服
    //之后工作的步骤可以这样：在各个窗口下建立控件，在窗口类中定义信号，将信号与要做的槽函数在system.cpp中进行连接
    //在控件触发函数中发出这些信号，由这些信号去控制其他线程的操作
    connect(mw->ConW , SIGNAL(toopentheservo(bool)), robotThread->rbt, SLOT(onServoOnOff(bool)), Qt::QueuedConnection);

    //set Move to be a callback in signal and slot
    qRegisterMetaType<Move>("Move");
    connect(mw->ConW , SIGNAL(robotstarttomove(Move)) , robotThread->rbt , SLOT(onMoveRobot(Move)), Qt::QueuedConnection);

    //每一次发出信号都将机器人当前位姿，传递给控制窗口
    qRegisterMetaType<CurrenPoseWrite>("CurrenPoseWrite");
    connect(robotThread->rbt, SIGNAL(sendRobotPoseData(CurrenPoseWrite)), mw->ConW, SLOT(setRobotPoseData(CurrenPoseWrite)),
            Qt::QueuedConnection);


    // Force sensor send force data to UI
    qRegisterMetaType<Force6D>("Force6D");
    connect(fsThread->fs, SIGNAL(sendForceData(Force6D)), mw->ConW, SLOT(showForceData(Force6D)),
            Qt::QueuedConnection);


    // Robot object send messsages to UI
    connect(robotThread->rbt, SIGNAL(sendMessage(QString)), mw->Mess, SLOT(onReceiveMessage(QString)),
            Qt::QueuedConnection);



    // Force Sensor send message to UI
    connect(fsThread->fs, SIGNAL(sendMessage(QString)), mw->Mess, SLOT(onReceiveMessage(QString)),
            Qt::QueuedConnection);

    tmrinput = new QTimer(this);
    connect(tmrinput,SIGNAL(timeout()),mw->ConW,SLOT(write_data()));
    tmrinput->start(50);

    return 1;
}

void SCASystem::onRobotInitDone(bool isSuccessful)
{
    emit initFS();
}
void SCASystem::onFSInitDOne(bool isSuccessful)
{
    //发出初始化下一个线程的信号
    //emit initIOBoard();
}












