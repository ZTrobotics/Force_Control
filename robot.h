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


#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QThread>

#include "common.h"
#include "3rd-party/motocom32/Motocom.h"


class Robot : public QObject
{
    Q_OBJECT
public:
    explicit Robot(QObject *parent = 0);
    ~Robot();

    // To move robot
    int move(Move m);

    // Init robot
//    void init();


private:

    QTimer *tmr;
    HANDLE hdlRobot;

    // Curent pose and pulse.
    Pose currPose, currPulse;

    // Destination motion
    Move dstMove;

    // Whether the robot is on-line
    bool isOnline;

    // Whether the robot servo is on.
    bool isServoOn;


    bool isMoving; // Whether the robot is moving
    bool isMoving0; // isMoving and isMoving0 are used to check the robot motion is complete.

    bool isPoseEqual(Pose p1, Pose p2);
    bool isPulseEqual(Pose p1, Pose p2);

    // For simulation
    QTimer * tmrMoving;

    // End for simulation

signals:
    // Send current pose
    void currPoseReady(Pose p);

    // Send current pulse
    void currPulseReady(Pose p);

    // Whether the robot is moving
    void movingStatus(bool);

    // Whether the robot is online
    void onOffline(bool);

    // Whether the servo is on
    void servoStatus(bool);

    // Initialization is done, s=true -> initialization is successful, s=false -> fail.
    void initDone(bool s);

    // Send a message.
    void sendMessage(QString msg);

    // Motion is done.
    void motionDone();

    // Motion cannot be done, because robot servo is off
    void motionServoOff();

    // Switch servo is done.
    void servoDone();

    // Emergency stop
    void emergencyStop();

    void sendRobotPoseData(CurrenPoseWrite);

public slots:

    // To open or close the servo
    void onServoOnOff(bool status);

    // To move the robot
    void onMoveRobot(Move m);

    // To init the robot
    void onInit();

private slots:

    // Get robot status, including pose, moving status, servo status.
    void onTimer();
    // For simulation

//    void onTmrMoving();

    // End for simulation

};

#endif // ROBOT_H
