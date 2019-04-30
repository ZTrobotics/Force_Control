/*********************************
UI头文件，包括窗口所有按妞布局等的定义
**********************************/
#ifndef GUI_H
#define GUI_H

#include<iostream>
#include<QString>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include <QLineEdit>
#include <QImage>
#include <QTimer>
#include<QInputDialog>
#include<QListWidget>
#include<QTime>
#include<QCoreApplication>
#include"common.h"
#include"robot.h"

/*********************************
控制窗口，包括相机、电机的控制按钮
**********************************/
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    ControlWidget(QWidget *parent=0);

    QVBoxLayout *leftlayout;


    Move move;
    QPushButton *camera_open;//相机初始化按钮
    QPushButton *motor_open;//电机初始化按钮
    QPushButton *motor_set;//电机参数设置按钮
    QPushButton *servo_open;//open the servo
    QPushButton *servo_close;//close the servo
   // QPushButton *affirm_targetlocation;
    QPushButton *robot_startto_move;

    QPushButton *robot_moveto_readystation; // Button: robot to one station
    QPushButton *robot_assemblyforce; //Button: robot to assemble

    QPushButton *readforcetxt;


    QLabel *open_camera;
    QLabel *open_motor;
    QLabel *set_motor;


    QLabel *robotx ;
    QLabel *roboty ;
    QLabel *robotz ;
    QLabel *robotrx ;
    QLabel *robotry ;
    QLabel *robotrz ;

    QLabel *robotxmin ;
    QLabel *robotxmax ;
    QLabel *robotymin ;
    QLabel *robotymax ;
    QLabel *robotzmin ;
    QLabel *robotzmax ;
    QLabel *robotrxmin ;
    QLabel *robotrxmax ;
    QLabel *robotrymin ;
    QLabel *robotrymax ;
    QLabel *robotrzmin ;
    QLabel *robotrzmax ;


    QLabel *robotdx ;
    QLabel *robotdy ;
    QLabel *robotdz ;
    QLabel *robotdrx ;
    QLabel *robotdry ;
    QLabel *robotdrz ;

    QPushButton *xmin ;
    QPushButton *xmax ;
    QPushButton *ymin ;
    QPushButton *ymax ;
    QPushButton *zmin ;
    QPushButton *zmax ;
    QPushButton *rxmin ;
    QPushButton *rxmax ;
    QPushButton *rymin ;
    QPushButton *rymax ;
    QPushButton *rzmin ;
    QPushButton *rzmax ;

    QPushButton *dx ;
    QPushButton *dy ;
    QPushButton *dz ;
    QPushButton *drx ;
    QPushButton *dry ;
    QPushButton *drz ;

    QLabel *fx;
    QLabel *fy;
    QLabel *fz;
    QLabel *tx;
    QLabel *ty;
    QLabel *tz;
    QLabel *fx_show;
    QLabel *fy_show;
    QLabel *fz_show;
    QLabel *tx_show;
    QLabel *ty_show;
    QLabel *tz_show;

    QLabel *CurrentPosex;
    QLabel *CurrentPosey;
    QLabel *CurrentPosez;
    QLabel *CurrentPoserx;
    QLabel *CurrentPosery;
    QLabel *CurrentPoserz;
    QLabel *CurrentPosex_show;
    QLabel *CurrentPosey_show;
    QLabel *CurrentPosez_show;
    QLabel *CurrentPoserx_show;
    QLabel *CurrentPosery_show;
    QLabel *CurrentPoserz_show;


    float force_writeout_fx;
    float force_writeout_fy;
    float force_writeout_fz;
    float force_writeout_tx;
    float force_writeout_ty;
    float force_writeout_tz;

    float robot_writeout_x;
    float robot_writeout_y;
    float robot_writeout_z;
    float robot_writeout_rx;
    float robot_writeout_ry;
    float robot_writeout_rz;

    int cycle_index ;

    float A[1700][9];

    void sleep(unsigned int msec);

private slots:

    void startservo();//robot servo open
    void closeservo();//robot servo close

    //void affirmtargetlocation();
    void starttherobot();//robot start to move
    void startcamera();//相机初始化
    void startmotor();//电机初始化
    void setmotorparemeter();//电机参数设置

    void setxmin();
    void setxmax();
    void setymin();
    void setymax();
    void setzmin();
    void setzmax();
    void setrxmin();
    void setrxmax();
    void setrymin();
    void setrymax();
    void setrzmin();
    void setrzmax();
    void setdx();
    void setdy();
    void setdz();
    void setdrx();
    void setdry();
    void setdrz();

    void robot_move_to_beready();//robot move to one station to be ready
    void robot_start_toassemble();// robot start to assemble

    void forcetxt_to_beread();

    void write_data();
    void showForceData(Force6D f);
    void setRobotPoseData(CurrenPoseWrite CPW);

signals:
    void toopentheservo(bool s);

    void robotstarttomove(Move m);



};


/*********************************
零件监测结果显示窗口
**********************************/
class ResultWidget : public QWidget
{
    Q_OBJECT
public:
    ResultWidget(QWidget *parent=0);
    QHBoxLayout *rightlayout;
    QPushButton *showresult;
    QPixmap componet_handle_result;
    QLabel componet_detect_result;
private slots:
    void show_detect_result();//显示匹配图像
};

/*********************************
指示灯窗口，包括各项信息的状态
**********************************/
class LampWidget : public QWidget
{
    Q_OBJECT
public:
    enum Color{GREEN, RED};
    LampWidget(Color color, QWidget *parent=0);
    QVBoxLayout *bottomlayout;
    enum Status{ON, OFF, BLINK};
    void setStatus(Status s);
private:
    QLabel *lamp;
    QPixmap lampOn, lampOff;
    Status currentstatus;
    QTimer *tmr;

    bool isblinkOn;
private slots:
    void ontimer();
};


/***********************************************
设备终端控制窗口，包括全部开始和全部终止两个按钮
************************************************/
class MastercontrolWidget : public QWidget
{
    Q_OBJECT
public:
    MastercontrolWidget(QWidget *parent=0);
    QVBoxLayout *mastercontrollayout;
    QPushButton *start;
    QPushButton *stop;
private slots:
    void startsystem();
    void stopsystem();
};
/*********************************
 Message窗口
**********************************/
//右下角消息窗口
class MessageWidget : public QWidget
{
    Q_OBJECT
public:
    MessageWidget(QWidget *parent =0);
    ~MessageWidget();

public slots:
    void onReceiveMessage(QString msg);

private:
    QListWidget *lwMessages;
    int msgNumber;
};

/*********************************
 force窗口
**********************************/
//class ForceWidget : public QWidget
//{
//    Q_OBJECT
//public:
//    ForceWidget(QWidget *parent);

//public slots:
//    void onReceiveForceData(Force6D f);

//private:
//    static const int FORCE_DIM = 6;
//    QLabel* lbForce[FORCE_DIM];
//    QLineEdit* leForce[FORCE_DIM];
//    QLabel* lbUnit[FORCE_DIM];

//};



/*********************************
 主窗口，完成各个子窗口的布局
**********************************/
class MainwindowWidget : public QWidget
{
    Q_OBJECT
public:
    MainwindowWidget(QWidget *parent=0);

    ControlWidget *ConW ;
    ResultWidget *ResW ;
    LampWidget *LamW ;
    MastercontrolWidget *MasW ;
    MessageWidget *Mess;
    //ForceWidget *ForW;
    QHBoxLayout *mainlayout;

//public slots:
//    // Receive current force data
//    void onReceiveForceData(Force6D f);
};
#endif // GUI_H
