#include "system.h"
#include <QTime>
#include<QTimer>

SCASystem::SCASystem(QWidget *parent):QWidget(parent)
{
    //���еĳ�Ա�ڿ�ʼû�д���
    isFSObjectCreated = false;
    isRobotObjectCreated = false;

    mw = new MainwindowWidget(0);
    mw->showMaximized();


    //�����µ��߳�
    fsThread = new ForceSensorThread();
    robotThread = new RobotThread();

    //�����ź�,�߳��Ѿ������ú󣬷��������õ��źţ����ݵ��ۺ������ۺ�����bool�ͱ�����Ϊtrue
    connect(fsThread, SIGNAL(objectCreated()), this, SLOT(onFSObjectCreated()));
    connect(robotThread, SIGNAL(robotObjectCreated()), this, SLOT(onRobotObjectCreated()));
    //�߳̿�ʼִ��run����
    fsThread->start();
    robotThread->start();

    //�½���ʱ����100ms����ͣ�ļ���Ƿ�ÿ���̶߳�������
    tmr = new QTimer(this);
    tmr->start(100);
    connect(tmr, SIGNAL(timeout()), this, SLOT(onTmrCheckObjectCreated()));

}
SCASystem::~SCASystem(){}


//�����߳̽����õĲۺ�����bool������Ϊtrue
void SCASystem::onFSObjectCreated()
{
    isFSObjectCreated = true;
}

void SCASystem::onRobotObjectCreated()
{
    isRobotObjectCreated = true;
}


//��ʱ��ÿ100ms��ִ����������������ÿ���߳��Ƿ񶼽����ˣ���bool���Ƿ�Ϊ��
void SCASystem::onTmrCheckObjectCreated()
{
    //��������߳�bool�Ͷ�Ϊtrue
    if (isFSObjectCreated == true
            && isRobotObjectCreated == true)
    {
        //���������ź���ۣ���ֹͣ��ⶨʱ��
        makeConnections();
        tmr->stop();
        emit initRobot();
    }
}

int SCASystem::makeConnections()
{
    //��һ���źţ����ɶ�ʱ����ʱ�ĺ��������ģ���־�ſ�ʼ�����˵ĳ�ʼ����Ҳ���ǵ�һ���̵߳ĳ�ʼ��
    connect(this , SIGNAL(initRobot()) , robotThread->rbt , SLOT(onInit()) , Qt::QueuedConnection);
    //�����˳�ʼ������֮�󣬻ᷢ��initDone���ź�,��־�����˳�ʼ���ɹ��������ۺ������ۺ���������һ���߳̿�ʼ��ʼ����Ҳ����һ�����еĹ���
    connect(robotThread->rbt, SIGNAL(initDone(bool)), this, SLOT(onRobotInitDone(bool)), Qt::QueuedConnection);


    //�ڶ����̣߳���Ϊ��һ���̷߳����Ĳۺ�����ʼ��ʼ��
    connect(this, SIGNAL(initFS()), fsThread->fs, SLOT(onInit()), Qt::QueuedConnection);
    connect(fsThread->fs, SIGNAL(initDone(bool)), this, SLOT(onFSInitDOne(bool)), Qt::QueuedConnection);

    //mw->Conw�������ڵĿ��ƴ���ָ�룬�����źŶ����ڿ��ƴ����£����Զ������̷߳����ź�
    //�ڿ��ƴ��ڵ����ж�����toopentheservo�����ŷ�������һ���ź�
    //�ۺ���֪ͨRobotȥ���ŷ�
    //֮�����Ĳ�������������ڸ��������½����ؼ����ڴ������ж����źţ����ź���Ҫ���Ĳۺ�����system.cpp�н�������
    //�ڿؼ����������з�����Щ�źţ�����Щ�ź�ȥ���������̵߳Ĳ���
    connect(mw->ConW , SIGNAL(toopentheservo(bool)), robotThread->rbt, SLOT(onServoOnOff(bool)), Qt::QueuedConnection);

    //set Move to be a callback in signal and slot
    qRegisterMetaType<Move>("Move");
    connect(mw->ConW , SIGNAL(robotstarttomove(Move)) , robotThread->rbt , SLOT(onMoveRobot(Move)), Qt::QueuedConnection);

    //ÿһ�η����źŶ��������˵�ǰλ�ˣ����ݸ����ƴ���
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
    //������ʼ����һ���̵߳��ź�
    //emit initIOBoard();
}












