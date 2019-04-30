/*
 * File: robot.h
 * Encoding: utf-8
 * Function: Control the robot.
 * Version: 1.5.0
 * Date: 2016-07-07
 * Author: QinZhengke
 * E-Mail: qinzhengke@qq.com
 *
 */

#include "robot.h"
#include"forcesensor.h"

#include"QFile"
#include"QTextStream"



Robot::Robot(QObject *parent) :
    QObject(parent)
{
    isOnline = false;
}

// Initialization cannot be put into constructor, because the constructor is executed before connect function,
// The message from the init function cannot be send to the system
// Initialization after receiving command
void Robot::onInit()
{
    emit sendMessage(tr("Initializing the robot..."));

    //
    // Open the communication port
    LONG err = ESOpen(1, "192.168.255.1", &hdlRobot);
//    if(err == )

    // To test if the robot is on-line
    ESStatusData status;
    if(ESGetStatus(hdlRobot, &status) == 0)
    {
        tmr = new QTimer(this);
        connect(tmr,SIGNAL(timeout()),this,SLOT(onTimer()));
        tmr->start(50);
        onServoOnOff(false);
        isOnline = true;
        emit sendMessage(tr("Success."));
    }
    else
    {
        isOnline = false;
        emit sendMessage(tr("Failed"));
    }

    //
    emit initDone(true);
}

Robot::~Robot()
{
    ESClose(hdlRobot);
}

int Robot::move(Move m)
{
    // Inform UI moving the robot
    emit sendMessage(tr("Moving the robot..."));

    // If robot servo is off, emit this message
    if(!isServoOn)
    {
        emit motionServoOff();
        return -1;
    }

    // If already reach destination
    if(m.coordType == Move::CART)
    {
        if(isPoseEqual(currPose, m.p))
        {
            emit motionDone();
            emit sendMessage(tr("Done."));
            return 1;
        }
    }
    else if(m.coordType == Move::PULSE)
    {
        if(isPulseEqual(currPulse, m.p))
        {
            emit motionDone();
            emit sendMessage(tr("Done"));
            return 1;
        }

    }

    if(isOnline == false)
    {
        emit sendMessage(tr("Cannot move robot, because robot is off-line!"));
        return -1;
    }

    LONG moveType;
    switch (m.moveType)
    {
    case Move::MOVJ:
        moveType = 1;
        break;
    case Move::MOVL:
        moveType = 2;
        break;
    }

    if(m.coordType == Move::CART)
    {
        ESCartMoveData cmd;
        cmd.moveData.robotNo = 1;
        cmd.moveData.stationNo = 0;

        if(m.moveType == Move::MOVJ)
            cmd.moveData.speedType = 0;
        else if(m.moveType == Move::MOVL)
            cmd.moveData.speedType = 1;

        cmd.moveData.speed = m.speed;
        cmd.robotPos.dataType = 17;
        cmd.robotPos.fig = 0;
        // The tool number must be 4 (OPL in demostrator)
        cmd.robotPos.toolNo = 4;
        cmd.robotPos.userFrameNo = 0;
        cmd.robotPos.exFig = 0;

        cmd.robotPos.axesData.axis[0] = m.p.x;
        cmd.robotPos.axesData.axis[1] = m.p.y;
        cmd.robotPos.axesData.axis[2] = m.p.z;
        cmd.robotPos.axesData.axis[3] = m.p.rx;
        cmd.robotPos.axesData.axis[4] = m.p.ry;
        cmd.robotPos.axesData.axis[5] = m.p.rz;
        cmd.robotPos.axesData.axis[6] = 0;
        cmd.robotPos.axesData.axis[7] = 0;

        for(int i = 0; i < 3; i++)
            cmd.basePos.axis[i] = 0;
        for(int i = 0; i < 6; i++)
            cmd.stationPos.axis[i] = 0;

        long inf = ESCartMove(hdlRobot, moveType, cmd);

        return inf;

    }
    else if(m.coordType == Move::PULSE)
    {

        ESPulseMoveData cmd;
        if(m.moveType == Move::MOVJ)
            cmd.moveData.speedType = 0;
        else if(m.moveType == Move::MOVL)
            cmd.moveData.speedType = 1;

        cmd.moveData.robotNo = 1;
        cmd.moveData.stationNo = 0;
        cmd.moveData.speed = m.speed;
        cmd.toolNo = 4;

        cmd.robotPos.axis[0] = m.p.x;
        cmd.robotPos.axis[1] = m.p.y;
        cmd.robotPos.axis[2] = m.p.z;
        cmd.robotPos.axis[3] = m.p.rx;
        cmd.robotPos.axis[4] = m.p.ry;
        cmd.robotPos.axis[5] = m.p.rz;
        cmd.robotPos.axis[6] = 0;
        cmd.robotPos.axis[7] = 0;

        for(int i = 0; i < 3; i++)
            cmd.basePos.axis[i] = 0;
        for(int i = 0; i < 6; i++)
            cmd.stationPos.axis[i] = 0;

        long inf = ESPulseMove(hdlRobot, moveType, cmd);
        return inf;
    }

    return -1;
}

void Robot::onTimer()
{
    ESStatusData status;
    ESPositionData esPose;
    ESPositionData esPulse;

    // Fill esPose by getting a pose from robot.

    // If robot does not respond correctly, the robot is off-line
    if(     ESGetStatus(hdlRobot, &status) != 0 // Get status
            || ESGetPosition(hdlRobot, 101, &esPose) != 0 // Get cartisian coordinate
            || ESGetPosition(hdlRobot, 1, &esPulse) != 0) // Get pulse coordinate
    {
        // The robot is off-line
        emit onOffline(false);
    }
    else
    {

        // The robot is on-line
        emit onOffline(true);

        // Send status whether the robot is moving.
        isMoving = ((status.status1 & 0x08) != 0x00);
        emit movingStatus(isMoving);


        // Send status whether the robot servo is on.
        isServoOn = (status.status2 & 0x40) != 0x00;
        emit servoStatus(isServoOn);

        // Modify the move data.
        currPose.x = esPose.axesData.axis[0];
        currPose.y = esPose.axesData.axis[1];
        currPose.z = esPose.axesData.axis[2];
        currPose.rx = esPose.axesData.axis[3];
        currPose.ry = esPose.axesData.axis[4];
        currPose.rz = esPose.axesData.axis[5];
        // Send the current pose.

        currPulse.x = esPulse.axesData.axis[0];
        currPulse.y = esPulse.axesData.axis[1];
        currPulse.z = esPulse.axesData.axis[2];
        currPulse.rx = esPulse.axesData.axis[3];
        currPulse.ry = esPulse.axesData.axis[4];
        currPulse.rz = esPulse.axesData.axis[5];

        //暂时赋值给6个变量
        float xxx = currPose.x;
        float yyy = currPose.y;
        float zzz = currPose.z;
        float rxxx = currPose.rx;
        float ryyy = currPose.ry;
        float rzzz = currPose.rz;


        // To check robot motion is done.
        if(isMoving0 == true && isMoving == false)// Robot stop moving
        {
            switch(dstMove.coordType)
            {
            case Move::CART:
                if(isPoseEqual(currPose, dstMove.p) == true)// Reach to destination position
                    emit motionDone();


                else
                    emit emergencyStop(); // Do not Reach to destination position
                break;
            case Move::PULSE:
                if(isPulseEqual(currPulse, dstMove.p) == true)
                    emit motionDone();
                else
                    emit emergencyStop();
                break;
            }
        }
        isMoving0 = isMoving;

        emit currPoseReady(currPose);
        emit currPulseReady(currPulse);

        //发出信号去传递机器人当前位姿，用上面自定义的6个参数去传递数值
        emit sendRobotPoseData(CurrenPoseWrite(xxx,yyy,zzz,rxxx,ryyy,rzzz));
    }

}

// Receive message to move robot
void Robot::onMoveRobot(Move m)
{
    dstMove = m;
    move(m);
}

// Receive message to turn on or turn off the servo.
void Robot::onServoOnOff(bool status)
{
    if(status == true)
    {
        ESServo(hdlRobot,1);
    }
    else
    {
        // time delay before servo off
        QThread::msleep(500);
        ESServo(hdlRobot,2);
    }

    // Wait for switching servo.
    QThread::msleep(500);

    emit servoDone();
}

bool Robot::isPoseEqual(Pose p1, Pose p2)
{
    double minTranslate = 0.1;
    double minAngle = 0.1;

    if(abs(p1.x-p2.x) < minTranslate && abs(p1.y-p2.y) < minTranslate && abs(p1.z-p2.z) < minTranslate
            && abs(p1.rx-p2.rx) < minAngle && abs(p1.ry-p2.ry) < minAngle && abs(p1.rz-p2.rz) < minAngle)
        return true;
    else
        return false;
}

bool Robot::isPulseEqual(Pose p1, Pose p2)
{
    double minPulse = 10;
    if(abs(p1.x-p2.x) < minPulse && abs(p1.y-p2.y) < minPulse && abs(p1.z-p2.z) < minPulse
            && abs(p1.rx-p2.rx) < minPulse && abs(p1.ry-p2.ry) < minPulse && abs(p1.rz-p2.rz) < minPulse)
        return true;
    else
        return false;
}
