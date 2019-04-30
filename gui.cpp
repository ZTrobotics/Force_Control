#include"gui.h"
#include"common.h"
#include"forcesensor.h"
#include"robot.h"
#include"QFile"
#include"QTextStream"
#include"QDebug"
ControlWidget::ControlWidget(QWidget *parent):QWidget(parent)
{
    //鍨傜洿甯冨眬
    //QVBoxLayout *leftlayout = new QVBoxLayout(this);
    QGridLayout *leftlayout = new QGridLayout(this);

    camera_open = new QPushButton(tr("open camera"),this);
    //camera_open->setGeometry(QRect(20,40,80,40));
    motor_open= new QPushButton(tr("open motor"),this);
    //motor_open->setGeometry(QRect(120,40,80,40));
    motor_set= new QPushButton(tr("set motor parameter"),this);

    open_camera = new QLabel(tr("open camera"),this);
    open_motor = new QLabel(tr("open motor"),this);
    set_motor = new QLabel(tr("set motor"),this);

    QLabel *speedLabel = new QLabel(tr("90"));


    servo_open = new QPushButton(tr("open the servo"),this);//打开机器人伺服的按钮
    servo_close = new QPushButton(tr("close the servo"),this);
    //affirm_targetlocation = new QPushButton(tr("affirm targetlocation"), this);//确认运动最终位置
    robot_startto_move = new QPushButton(tr("start to move"),this);//机器人开始沿着设置运动的按钮

    readforcetxt = new QPushButton(tr("read force txt"),this);//读取无接触时的力传感器数据



    robotx = new QLabel(tr("x:"),this);
    roboty = new QLabel(tr("y:"),this);
    robotz = new QLabel(tr("z:"),this);
    robotrx = new QLabel(tr("rx:"),this);
    robotry = new QLabel(tr("ry:"),this);
    robotrz = new QLabel(tr("rz:"),this);

    robotxmin = new QLabel(tr("robot x min"),this);
    robotxmin->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotxmax = new QLabel(tr("robot x mix"),this);
    robotxmax->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotymin = new QLabel(tr("robot y min"),this);
    robotymin->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotymax = new QLabel(tr("robot y max"),this);
    robotymax->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotzmin = new QLabel(tr("robot z min"),this);
    robotzmin->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotzmax = new QLabel(tr("robot z max"),this);
    robotzmax->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotrxmin = new QLabel(tr("robot rx min"),this);
    robotrxmin->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotrxmax = new QLabel(tr("robot rx max"),this);
    robotrxmax->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotrymin = new QLabel(tr("robot ry min"),this);
    robotrymin->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotrymax = new QLabel(tr("robot ry max"),this);
    robotrymax->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotrzmin = new QLabel(tr("robot rz min"),this);
    robotrzmin->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotrzmax = new QLabel(tr("robot rz max"),this);
    robotrzmax->setFrameStyle(QFrame::Panel|QFrame::Sunken);


    robotdx = new QLabel(tr("robot x add"),this);
    robotdx->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotdy = new QLabel(tr("robot y add"),this);
    robotdy->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotdz = new QLabel(tr("robot z add"),this);
    robotdz->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotdrx = new QLabel(tr("robot rx add"),this);
    robotdrx->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotdry = new QLabel(tr("robot ry add"),this);
    robotdry->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    robotdrz = new QLabel(tr("robot rz add"),this);
    robotdrz->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    xmin = new QPushButton(this);
    xmax = new QPushButton(this);
    ymin = new QPushButton(this);
    ymax = new QPushButton(this);
    zmin = new QPushButton(this);
    zmax = new QPushButton(this);
    rxmin = new QPushButton(this);
    rxmax = new QPushButton(this);
    rymin = new QPushButton(this);
    rymax = new QPushButton(this);
    rzmin = new QPushButton(this);
    rzmax = new QPushButton(this);

    dx = new QPushButton(this);
    dy = new QPushButton(this);
    dz = new QPushButton(this);
    drx = new QPushButton(this);
    dry = new QPushButton(this);
    drz = new QPushButton(this);

    fx = new QLabel(tr("fx:"),this);
    fx_show = new QLabel(this);
    fy = new QLabel(tr("fy:"),this);
    fy_show = new QLabel(this);
    fz = new QLabel(tr("fz:"),this);
    fz_show = new QLabel(this);
    tx = new QLabel(tr("tx:"),this);
    tx_show = new QLabel(this);
    ty = new QLabel(tr("ty:"),this);
    ty_show = new QLabel(this);
    tz = new QLabel(tr("tz:"),this);
    tz_show = new QLabel(this);

    CurrentPosex = new QLabel(tr("POSE_x:"),this);
    CurrentPosex_show = new QLabel(this);
    CurrentPosey = new QLabel(tr("POSE_y:"),this);
    CurrentPosey_show = new QLabel(this);
    CurrentPosez = new QLabel(tr("POSE_z:"),this);
    CurrentPosez_show = new QLabel(this);
    CurrentPoserx = new QLabel(tr("POSE_rx:"),this);
    CurrentPoserx_show = new QLabel(this);
    CurrentPosery = new QLabel(tr("POSE_ry:"),this);
    CurrentPosery_show = new QLabel(this);
    CurrentPoserz = new QLabel(tr("POSE_rz:"),this);
    CurrentPoserz_show = new QLabel(this);

    robot_moveto_readystation = new QPushButton(tr("ready"),this);
    robot_assemblyforce = new QPushButton(tr("assemble"),this);


    leftlayout->addWidget(robotx,0,27);
    leftlayout->addWidget(robotxmin,0,30);
    leftlayout->addWidget(xmin,0,40);
    leftlayout->addWidget(robotxmax,0,50);
    leftlayout->addWidget(xmax,0,80);
    leftlayout->addWidget(robotdx,0,90);
    leftlayout->addWidget(dx,0,120);

    leftlayout->addWidget(roboty,10,27);
    leftlayout->addWidget(robotymin,10,30);
    leftlayout->addWidget(ymin,10,40);
    leftlayout->addWidget(robotymax,10,50);
    leftlayout->addWidget(ymax,10,80);
    leftlayout->addWidget(robotdy,10,90);
    leftlayout->addWidget(dy,10,120);

    leftlayout->addWidget(robotz,20,27);
    leftlayout->addWidget(robotzmin,20,30);
    leftlayout->addWidget(zmin,20,40);
    leftlayout->addWidget(robotzmax,20,50);
    leftlayout->addWidget(zmax,20,80);
    leftlayout->addWidget(robotdz,20,90);
    leftlayout->addWidget(dz,20,120);

    leftlayout->addWidget(robotrx,30,27);
    leftlayout->addWidget(robotrxmin,30,30);
    leftlayout->addWidget(rxmin,30,40);
    leftlayout->addWidget(robotrxmax,30,50);
    leftlayout->addWidget(rxmax,30,80);
    leftlayout->addWidget(robotdrx,30,90);
    leftlayout->addWidget(drx,30,120);

    leftlayout->addWidget(robotry,40,27);
    leftlayout->addWidget(robotrymin,40,30);
    leftlayout->addWidget(rymin,40,40);
    leftlayout->addWidget(robotrymax,40,50);
    leftlayout->addWidget(rymax,40,80);
    leftlayout->addWidget(robotdry,40,90);
    leftlayout->addWidget(dry,40,120);

    leftlayout->addWidget(robotrz,50,27);
    leftlayout->addWidget(robotrzmin,50,30);
    leftlayout->addWidget(rzmin,50,40);
    leftlayout->addWidget(robotrzmax,50,50);
    leftlayout->addWidget(rzmax,50,80);
    leftlayout->addWidget(robotdrz,50,90);
    leftlayout->addWidget(drz,50,120);


    leftlayout->addWidget(servo_open,60,1);
    leftlayout->addWidget(servo_close,70,1);
    //leftlayout->addWidget(affirm_targetlocation,70,1);
    leftlayout->addWidget(robot_startto_move,80,1);

    leftlayout->addWidget(fx,90,1);
    leftlayout->addWidget(fx_show,90,5);
    leftlayout->addWidget(fy,100,1);
    leftlayout->addWidget(fy_show,100,5);
    leftlayout->addWidget(fz,110,1);
    leftlayout->addWidget(fz_show,110,5);
    leftlayout->addWidget(tx,120,1);
    leftlayout->addWidget(tx_show,120,5);
    leftlayout->addWidget(ty,130,1);
    leftlayout->addWidget(ty_show,130,5);
    leftlayout->addWidget(tz,140,1);
    leftlayout->addWidget(tz_show,140,5);

    leftlayout->addWidget(CurrentPosex,90,30);
    leftlayout->addWidget(CurrentPosex_show,90,35);
    leftlayout->addWidget(CurrentPosey,100,30);
    leftlayout->addWidget(CurrentPosey_show,100,35);
    leftlayout->addWidget(CurrentPosez,110,30);
    leftlayout->addWidget(CurrentPosez_show,110,35);
    leftlayout->addWidget(CurrentPoserx,120,30);
    leftlayout->addWidget(CurrentPoserx_show,120,35);
    leftlayout->addWidget(CurrentPosery,130,30);
    leftlayout->addWidget(CurrentPosery_show,130,35);
    leftlayout->addWidget(CurrentPoserz,140,30);
    leftlayout->addWidget(CurrentPoserz_show,140,35);

    leftlayout->addWidget(robot_moveto_readystation,90,50);
    leftlayout->addWidget(robot_assemblyforce,100,50);
    leftlayout->addWidget(readforcetxt,110,50);


    leftlayout->addWidget(open_camera,170,1);
    leftlayout->addWidget(camera_open,170,20);

    leftlayout->addWidget(open_motor,180,1);
    leftlayout->addWidget(motor_open,180,20);

    leftlayout->addWidget(set_motor,190,1);
    leftlayout->addWidget(motor_set,190,20);

    leftlayout->addWidget(speedLabel,200,1);

    //更改参数，暂时只是X方向
    connect(xmin , SIGNAL(clicked()) , this , SLOT(setxmin()) );
    connect(xmax , SIGNAL(clicked()) , this , SLOT(setxmax()) );
    connect(ymin , SIGNAL(clicked()) , this , SLOT(setymin()) );
    connect(ymax , SIGNAL(clicked()) , this , SLOT(setymax()) );
    connect(zmin , SIGNAL(clicked()) , this , SLOT(setzmin()) );
    connect(zmax , SIGNAL(clicked()) , this , SLOT(setzmax()) );
    connect(rxmin , SIGNAL(clicked()) , this , SLOT(setrxmin()) );
    connect(rxmax , SIGNAL(clicked()) , this , SLOT(setrxmax()) );
    connect(rymin , SIGNAL(clicked()) , this , SLOT(setrymin()) );
    connect(rymax , SIGNAL(clicked()) , this , SLOT(setrymax()) );
    connect(rzmin , SIGNAL(clicked()) , this , SLOT(setrzmin()) );
    connect(rzmax , SIGNAL(clicked()) , this , SLOT(setrzmax()) );
    connect(dx , SIGNAL(clicked()) , this , SLOT(setdx()) );
    connect(dy , SIGNAL(clicked()) , this , SLOT(setdy()) );
    connect(dz , SIGNAL(clicked()) , this , SLOT(setdz()) );
    connect(drx , SIGNAL(clicked()) , this , SLOT(setdrx()) );
    connect(dry , SIGNAL(clicked()) , this , SLOT(setdry()) );
    connect(drz , SIGNAL(clicked()) , this , SLOT(setdrz()) );

   // 伺服连接
    connect(servo_open , SIGNAL(clicked()) , this , SLOT(startservo()) );
    //伺服关闭
    connect(servo_close , SIGNAL(clicked()) , this , SLOT(closeservo()) );
    //确认最终运动位置连接，将参数返回move类
    //connect(affirm_targetlocation , SIGNAL(clicked()) , this , SLOT(affirmtargetlocation()) );
    connect(robot_startto_move , SIGNAL(clicked()) , this , SLOT(starttherobot()) );

    //让机器人运动到一个位置，使它可以准备做轴孔装配动作
    connect(robot_moveto_readystation , SIGNAL(clicked()) , this , SLOT(robot_move_to_beready()) );
    //让机器人开始进行轴孔装配
    connect(robot_assemblyforce , SIGNAL(clicked()) , this , SLOT(robot_start_toassemble()) );
    connect(readforcetxt , SIGNAL(clicked()) , this , SLOT(forcetxt_to_beread() ) );


    connect(camera_open , SIGNAL(clicked()) , this , SLOT(startcamera()) );
    connect(motor_open , SIGNAL(clicked()) , this , SLOT(startmotor()) );
    connect(motor_set , SIGNAL(clicked()) , this , SLOT(setmotorparemeter()) );
}
//延时函数,在头文件中应加入QTime.h
void ControlWidget::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime()<dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
//x最小值，x最大值，x每次的增加分量
void ControlWidget::setxmin()
{
   bool ok ;
   QString changexmin = QInputDialog::getText(this,tr("change the robot x min"),tr("please input robot x min"),QLineEdit::Normal,robotxmin->text(),&ok);
   if (ok && !changexmin.isEmpty())
       robotxmin->setText(changexmin);
}
void ControlWidget::setxmax()
{
   bool ok ;
   QString changexmax = QInputDialog::getText(this,tr("change the robot x max"),tr("please input robot x max"),QLineEdit::Normal,robotxmax->text(),&ok);
   if (ok && !changexmax.isEmpty())
       robotxmax->setText(changexmax);
}
void ControlWidget::setdx()
{
   bool ok ;
   QString changedx = QInputDialog::getText(this,tr("change the robot dx"),tr("please input robot dx"),QLineEdit::Normal,robotdx->text(),&ok);
   if (ok && !changedx.isEmpty())
       robotdx->setText(changedx);
}

//y最小值，最大值，y每次的增加分量
void ControlWidget::setymin()
{
   bool ok ;
   QString changeymin = QInputDialog::getText(this,tr("change the robot y min"),tr("please input robot y min"),QLineEdit::Normal,robotymin->text(),&ok);
   if (ok && !changeymin.isEmpty())
       robotymin->setText(changeymin);
}
void ControlWidget::setymax()
{
   bool ok ;
   QString changeymax = QInputDialog::getText(this,tr("change the robot y max"),tr("please input robot y max"),QLineEdit::Normal,robotymax->text(),&ok);
   if (ok && !changeymax.isEmpty())
       robotymax->setText(changeymax);
}
void ControlWidget::setdy()
{
   bool ok ;
   QString changedy = QInputDialog::getText(this,tr("change the robot dy"),tr("please input robot dy"),QLineEdit::Normal,robotdy->text(),&ok);
   if (ok && !changedy.isEmpty())
       robotdy->setText(changedy);
}
//z最小值，最大值，z每次的增加分量
void ControlWidget::setzmin()
{
   bool ok ;
   QString changezmin = QInputDialog::getText(this,tr("change the robot z min"),tr("please input robot z min"),QLineEdit::Normal,robotzmin->text(),&ok);
   if (ok && !changezmin.isEmpty())
       robotzmin->setText(changezmin);
}
void ControlWidget::setzmax()
{
   bool ok ;
   QString changezmax = QInputDialog::getText(this,tr("change the robot z max"),tr("please input robot z max"),QLineEdit::Normal,robotzmax->text(),&ok);
   if (ok && !changezmax.isEmpty())
       robotzmax->setText(changezmax);
}
void ControlWidget::setdz()
{
   bool ok ;
   QString changedz = QInputDialog::getText(this,tr("change the robot dz"),tr("please input robot dz"),QLineEdit::Normal,robotdz->text(),&ok);
   if (ok && !changedz.isEmpty())
       robotdz->setText(changedz);
}
//rx最小值，最大值，rx每次的增加分量

void ControlWidget::setrxmin()
{
   bool ok ;
   QString changerxmin = QInputDialog::getText(this,tr("change the robot rx min"),tr("please input robot rx min"),QLineEdit::Normal,robotrxmin->text(),&ok);
   if (ok && !changerxmin.isEmpty())
       robotrxmin->setText(changerxmin);
}
void ControlWidget::setrxmax()
{
   bool ok ;
   QString changerxmax = QInputDialog::getText(this,tr("change the robot rx max"),tr("please input robot rx max"),QLineEdit::Normal,robotrxmax->text(),&ok);
   if (ok && !changerxmax.isEmpty())
       robotrxmax->setText(changerxmax);
}
void ControlWidget::setdrx()
{
   bool ok ;
   QString changedrx = QInputDialog::getText(this,tr("change the robot drx"),tr("please input robot drx"),QLineEdit::Normal,robotdrx->text(),&ok);
   if (ok && !changedrx.isEmpty())
       robotdrx->setText(changedrx);
}
//ry最小值，最大值，ry每次的增加分量
void ControlWidget::setrymin()
{
   bool ok ;
   QString changerymin = QInputDialog::getText(this,tr("change the robot ry min"),tr("please input robot ry min"),QLineEdit::Normal,robotrymin->text(),&ok);
   if (ok && !changerymin.isEmpty())
       robotrymin->setText(changerymin);
}
void ControlWidget::setrymax()
{
   bool ok ;
   QString changerymax = QInputDialog::getText(this,tr("change the robot ry max"),tr("please input robot ry max"),QLineEdit::Normal,robotrymax->text(),&ok);
   if (ok && !changerymax.isEmpty())
       robotrymax->setText(changerymax);
}
void ControlWidget::setdry()
{
   bool ok ;
   QString changedry = QInputDialog::getText(this,tr("change the robot dry"),tr("please input robot dry"),QLineEdit::Normal,robotdry->text(),&ok);
   if (ok && !changedry.isEmpty())
       robotdry->setText(changedry);
}
//rz最小值，最大值，rz每次的增加分量
void ControlWidget::setrzmin()
{
   bool ok ;
   QString changerzmin = QInputDialog::getText(this,tr("change the robot rz min"),tr("please input robot rz min"),QLineEdit::Normal,robotrzmin->text(),&ok);
   if (ok && !changerzmin.isEmpty())
       robotrzmin->setText(changerzmin);
}
void ControlWidget::setrzmax()
{
   bool ok ;
   QString changerzmax = QInputDialog::getText(this,tr("change the robot rz max"),tr("please input robot rz max"),QLineEdit::Normal,robotrzmax->text(),&ok);
   if (ok && !changerzmax.isEmpty())
       robotrzmax->setText(changerzmax);
}
void ControlWidget::setdrz()
{
   bool ok ;
   QString changedrz = QInputDialog::getText(this,tr("change the robot drz"),tr("please input robot drz"),QLineEdit::Normal,robotdrz->text(),&ok);
   if (ok && !changedrz.isEmpty())
       robotdrz->setText(changedrz);
}

void ControlWidget::startservo()
{
    emit toopentheservo(true);
}
void ControlWidget::closeservo()
{
    emit toopentheservo(false);
}

//void ControlWidget::affirmtargetlocation()
//{
    //暂时不需要，本来是想作为数值确认的作用
//   = robotxmin->text();
//    robotymin->text();
//    robotzmin->text();
//            robotrxmin->text();
//            robotrymin->text();
//            robotrzmin->text();
//}

void ControlWidget::starttherobot()
{
//    for (int a = robotxmin->text().toDouble() ; a <(robotxmax->text().toDouble()+1) ; a+= robotdx->text().toDouble()){
//        for (int b = robotymin->text().toDouble() ; b <(robotymax->text().toDouble()+1) ; b+= robotdy->text().toDouble()){
//            for (int c = robotzmin->text().toDouble() ; c <(robotzmax->text().toDouble()+1) ; c+= robotdz->text().toDouble()){

//                 for (int e = robotrxmin->text().toDouble() ; e <(robotrxmax->text().toDouble()+1) ; e+= robotdrx->text().toDouble()){
//                    for (int f = robotrymin->text().toDouble() ; f <(robotrymax->text().toDouble()+1) ; f+= robotdry->text().toDouble()){
//                        for (int g = robotrzmin->text().toDouble() ; g <(robotrzmax->text().toDouble()+1) ; g+= robotdrz->text().toDouble()){
    cycle_index = 0;

    move.p.x = -128.883;
    move.p.y = 1123.971;
    move.p.z = -188.746;
//    move.p.rx = 177.8987;
//    move.p.ry = 0.4441;
//    move.p.rz = -54.5387;
                for (double e = 177.3 ; e <178.5 ; e+= 0.105){
                    for (double f = -0.2 ; f <1.2 ; f+= 0.105){
                        for (double g = -55 ; g <-54 ; g+= 0.105){

                            move.p.rx = e;
                            move.p.ry = f;
                            move.p.rz = g;

                            move.moveType=Move::MOVJ;
                            //位姿
                            move.coordType= Move::CART;
                            //脉冲
                            //move.coordType=Move::PULSE;
                            move.speed=5;
                            emit robotstarttomove(move);

                            cycle_index++;
                            sleep(2500);
                        }
                    }
                }
//            }
//        }

//    }


}
void ControlWidget::setRobotPoseData(CurrenPoseWrite CPW)
{
    //这6个参数是要写出来的机器人位姿，是随机器人时间周期（50ms）实时更新的
    robot_writeout_x = CPW.current_x;
    robot_writeout_y = CPW.current_y;
    robot_writeout_z = CPW.current_z;
    robot_writeout_rx = CPW.current_rx;
    robot_writeout_ry = CPW.current_ry;
    robot_writeout_rz = CPW.current_rz;

    QString Robot_x = QString("%1").arg(robot_writeout_x) ;
    QString Robot_y = QString("%1").arg(robot_writeout_y) ;
    QString Robot_z = QString("%1").arg(robot_writeout_z) ;
    QString Robot_rx = QString("%1").arg(robot_writeout_rx) ;
    QString Robot_ry = QString("%1").arg(robot_writeout_ry) ;
    QString Robot_rz = QString("%1").arg(robot_writeout_rz) ;

    CurrentPosex_show->setText(Robot_x);
    CurrentPosey_show->setText(Robot_y);
    CurrentPosez_show->setText(Robot_z);
    CurrentPoserx_show->setText(Robot_rx);
    CurrentPosery_show->setText(Robot_ry);
    CurrentPoserz_show->setText(Robot_rz);

}

void ControlWidget::write_data()
{
    QString robotDatefilename = "E:/robot.txt";
    QFile file(robotDatefilename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        QMessageBox::information(NULL,"ss","adfa");
    }
    QTextStream out(&file);



    out<<"0 "<<cycle_index
     <<" "<<robot_writeout_rx<<" "<<robot_writeout_ry<<" "<<robot_writeout_rz
     <<" "<<force_writeout_fx<<" "<<force_writeout_fy<<" "<<force_writeout_fz
    <<" "<<force_writeout_tx<<" "<<force_writeout_ty<<" "<<force_writeout_tz<<"\n";
}

void ControlWidget::showForceData(Force6D f)
{
    //对力数据做一个实时显示
    QString force_FX = QString("%1").arg(f.fx) ;
    QString force_FY = QString("%1").arg(f.fy) ;
    QString force_FZ = QString("%1").arg(f.fz) ;
    QString force_TX = QString("%1").arg(f.tx) ;
    QString force_TY = QString("%1").arg(f.ty) ;
    QString force_TZ = QString("%1").arg(f.tz) ;

    fx_show->setText(force_FX);
    fy_show->setText(force_FY);
    fz_show->setText(force_FZ);
    tx_show->setText(force_TX);
    ty_show->setText(force_TY);
    tz_show->setText(force_TZ);

    //这6个参数是要写出来的力传感器数据，是随力传感器周期实时更新的
    force_writeout_fx = f.fx;
    force_writeout_fy = f.fy;
    force_writeout_fz = f.fz;
    force_writeout_tx = f.tx;
    force_writeout_ty = f.ty;
    force_writeout_tz = f.tz;


}
void ControlWidget::forcetxt_to_beread()
{
    QFile file("E:/force_nocontact_dealed.txt");
    if (!file.open(QIODevice::ReadOnly)){
        return;
    }
    int line_number=0;

    QString line;
    QStringList lineString;

    while(!file.atEnd()){
        line = file.readLine();
        lineString = line.split(QRegExp("\\s{1,}"));
        for (int i=0; i<lineString.length()-1; i++)
        {
            A[line_number][i] = lineString[i].toFloat();
        }
        line_number++;
        qDebug()<<line_number;
    }
}

void ControlWidget::robot_move_to_beready()
{
    move.p.x = -128.883;
    move.p.y = 1123.971;
    move.p.z = -188.746;
    move.p.rx = 177.8987;
    move.p.ry = 0.4441;
    move.p.rz = -54.5387;

    move.moveType=Move::MOVJ;
    //位姿
    move.coordType= Move::CART;
    //脉冲
    //move.coordType=Move::PULSE;
    move.speed=5;
    emit robotstarttomove(move);

}
void ControlWidget::robot_start_toassemble()
{
    move.p.x = -127.878;
    move.p.y = 1124.972;
    move.p.z = -188.746;
    move.p.rx = 177.8987;
    move.p.ry = 0.4441;
    move.p.rz = -54.5387;
    move.moveType=Move::MOVJ;
    //位姿
    move.coordType= Move::CART;
    //脉冲
    //move.coordType=Move::PULSE;
    move.speed=3;

    float force_contact,force_contact_last;
    int try_number = 1;
    int move_adjust_type;
    int returnpose;
    while (robot_writeout_z > -312)
    {
        for (int i = 0 ; i<1680 ;i++)
        {
            if ((fabs(robot_writeout_rx - A[i][0])<0.06) && (fabs(robot_writeout_ry-A[i][1])<0.06) && (fabs(robot_writeout_rz - A[i][2])<0.06))
            {
                force_contact = (force_writeout_fx- A[i][3])*(force_writeout_fx- A[i][3])+(force_writeout_fy- A[i][4])*(force_writeout_fy- A[i][4])+(force_writeout_fz - A[i][5])*(force_writeout_fz - A[i][5]);
                qDebug()<<force_contact;
            }
        }
        if (force_contact > 500)
        {
            if (try_number == 1)
            {
                //做出一次移动尝试并更新位姿;第一次做rx+;记录力大小，定义移动方式为1;
                force_contact_last = force_contact;
                move_adjust_type = 1;
                try_number = 0;
            }
            else
            {
//                比较上一次力和这一次力的大小关系，如果这一次力小，移动方式不变（不写）,否则改变移动方式;

//                移动方式改变策略;
//                    方式1变为2;
//                    方式2变为3;变量t为1;
//                    方式3变为4;
//                    移动方式4变为1;变量t为2;

//                并记录这次移动的力大小;
                if (force_contact < force_contact_last)
                {
                    //不变
                }
                else
                {
                    if (move_adjust_type ==1)
                    {
                        move_adjust_type=2;
                        qDebug()<<1;
                    }
                    if (move_adjust_type ==2)
                    {
                        move_adjust_type=3;
                        returnpose = 1;
                        qDebug()<<2;
                    }
                    if (move_adjust_type ==3)
                    {
                        move_adjust_type=4;
                        qDebug()<<3;
                    }
                    if (move_adjust_type ==4)
                    {
                        move_adjust_type=1;
                        returnpose = 2;
                        qDebug()<<4;
                    }
                }

            }
            switch (move_adjust_type)
            {
            case 1:
                move.p.rx+=0.105;
                emit robotstarttomove(move);
                sleep(1000);
            case 2:
                move.p.rx-=0.105;
                emit robotstarttomove(move);
                sleep(1000);
            case 3:
                move.p.ry+=0.105;
                emit robotstarttomove(move);
                sleep(1000);
            case 4:
                move.p.ry-=0.105;
                emit robotstarttomove(move);
                sleep(1000);
            }
            if (returnpose ==1)
            {
                move.p.rx+=0.105;
                emit robotstarttomove(move);
                sleep(1000);
                returnpose =0;
            }
            else if (returnpose ==2)
            {
                move.p.ry+=0.105;
                emit robotstarttomove(move);
                sleep(1000);
                returnpose =0;
            }

        }
        else
        {
            //向下移动;
            move.p.z-=0.105;
            emit robotstarttomove(move);
            sleep(1000);
            try_number =0;

        }

    }



//第二版本策略
//    while( robot_writeout_z > 450 )
//    {
//        move.p.z -= 1;
//        emit robotstarttomove(move);
//        sleep(300);
//    }

//    move.p.x = -189.881;
//    move.p.y = 970.817;
//    move.p.z = 540 ;
//    move.p.rx = 178.3939;
//    move.p.ry = 0.5241;
//    move.p.rz = -65.1683;
//    emit robotstarttomove(move);
//    sleep(5000);
//    while( robot_writeout_z > 450 )
//    {
//        if ( robot_writeout_z < 500){move.p.rx = 179;}
//        move.p.z -=1;
//        emit robotstarttomove(move);
//        sleep(300);
//    }

//    move.p.x = -189.881;
//    move.p.y = 970.817;
//    move.p.z = 540 ;
//    move.p.rx = 178.3939;
//    move.p.ry = 0.5241;
//    move.p.rz = -65.1683;
//    emit robotstarttomove(move);
//    sleep(5000);
//    while( robot_writeout_z > 450 )
//    {
//        if ( robot_writeout_z < 500){move.p.rx = 177;}
//        move.p.z -= 1;
//        emit robotstarttomove(move);
//        sleep(300);
//    }

//    move.p.x = -189.881;
//    move.p.y = 970.817;
//    move.p.z = 540 ;
//    move.p.rx = 178.3939;
//    move.p.ry = 0.5241;
//    move.p.rz = -65.1683;
//    emit robotstarttomove(move);
//    sleep(5000);
//    while( robot_writeout_z > 450 )
//    {
//        if ( robot_writeout_z < 500){move.p.ry = 1.5;}
//        move.p.z -= 1;
//        emit robotstarttomove(move);
//        sleep(300);
//    }

//    move.p.x = -189.881;
//    move.p.y = 970.817;
//    move.p.z = 540 ;
//    move.p.rx = 178.3939;
//    move.p.ry = 0.5241;
//    move.p.rz = -65.1683;
//    emit robotstarttomove(move);
//    sleep(5000);
//    while( robot_writeout_z > 450 )
//    {
//        if ( robot_writeout_z < 500){move.p.ry = -0.5;}
//        move.p.z -= 1;
//        emit robotstarttomove(move);
//        sleep(300);
//    }


//第一版本策略
//    float start_Fx = force_writeout_fx;
//    float start_Fy = force_writeout_fy;
//    float start_Fz = force_writeout_fz;

//    float force_writeout_fx_previous = force_writeout_fx;
//    float force_writeout_fy_previous = force_writeout_fy;
//    float force_writeout_fz_previous = force_writeout_fz;
//    while(robot_writeout_z > 422)
//    {
//       if ((fabs(force_writeout_fx) > 38
//               || fabs(force_writeout_fx) < 36)
//               && (fabs(force_writeout_fy) > 767
//               || fabs(force_writeout_fy) < 765)
//               && (fabs(force_writeout_fz) > 377
//               || fabs(force_writeout_fz) < 375))
//       {
//        move.p.z -= 0.105;
//        emit robotstarttomove(move);
//        sleep(300);
//               if ((force_writeout_fx_previous-force_writeout_fx)   > 1 )
//               {

//                   move.p.y +=0.105;
//                   emit robotstarttomove(move);

//                   sleep(200);

//                   move.p.rx -=0.105*2;
//                   move.p.z += 0.105;
//                   emit robotstarttomove(move);
//                   sleep(200);

//                   force_writeout_fx_previous = force_writeout_fx;
//                   force_writeout_fy_previous = force_writeout_fy;
//                   force_writeout_fz_previous = force_writeout_fz;
//               }
//               if ((force_writeout_fx-force_writeout_fx_previous)   > 1 )
//               {

//                   move.p.y -=0.105;
//                   emit robotstarttomove(move);
//                   sleep(200);

//                   move.p.rx +=0.105*2;
//                   move.p.z += 0.105;
//                   emit robotstarttomove(move);
//                   sleep(200);

//                   force_writeout_fx_previous = force_writeout_fx;
//                   force_writeout_fy_previous = force_writeout_fy;
//                   force_writeout_fz_previous = force_writeout_fz;
//               }

//               if ((force_writeout_fy-force_writeout_fy_previous) > 1 )
//               {

//                   move.p.x -=0.105;
//                   emit robotstarttomove(move);

//                   sleep(200);

//                   move.p.ry -=0.105*2;
//                   move.p.z += 0.105;
//                   emit robotstarttomove(move);
//                   sleep(200);

//                   force_writeout_fx_previous = force_writeout_fx;
//                   force_writeout_fy_previous = force_writeout_fy;
//                   force_writeout_fz_previous = force_writeout_fz;
//               }
//               if ((force_writeout_fy_previous-force_writeout_fy) > 1 )
//               {

//                   move.p.x +=0.105;
//                   emit robotstarttomove(move);
//                   sleep(200);

//                   move.p.ry +=0.105*2;
//                   move.p.z += 0.105;
//                   emit robotstarttomove(move);
//                   sleep(200);

//                   force_writeout_fx_previous = force_writeout_fx;
//                   force_writeout_fy_previous = force_writeout_fy;
//                   force_writeout_fz_previous = force_writeout_fz;
//                }
//            }
//       else
//       {

//       }
//    }
}

void ControlWidget::startcamera()
{

}

void ControlWidget::startmotor()
{

}
void ControlWidget::setmotorparemeter()
{

}


ResultWidget::ResultWidget(QWidget *parent):QWidget(parent)
{
    QHBoxLayout *rightlayout = new QHBoxLayout(this);

    QPushButton *showresult = new QPushButton(tr("show result"),this);

    QLabel *componet_detect_result = new QLabel(tr("show result"),this);

    rightlayout->addWidget(componet_detect_result);
    rightlayout->addWidget(showresult);

    connect(showresult , SIGNAL(clicked()) , this , SLOT(show_detect_result()));
}
void ResultWidget::show_detect_result()
{

}


LampWidget::LampWidget(Color color,QWidget *parent):QWidget(parent)
{
    switch(color)
    {
    case GREEN:
        lampOn = QPixmap::fromImage(QImage("icons/green-lamp-24x24.png"));
        break;

    case RED:
        lampOn = QPixmap::fromImage(QImage("icons/red-lamp-24x24.png"));
        break;
    }
    lampOff = QPixmap::fromImage(QImage("icons/gray-lamp-24x24.png"));
//    pmapRed = QPixmap::fromImage(QImage("icons/red-lamp-24x24.png"));
//    pmapGreen = QPixmap::fromImage(QImage("icons/green-lamp-24x24.png"));
//    pmapGray = QPixmap::fromImage(QImage("icons/gray-lamp-24x24.png"));

    lamp = new QLabel(this);
//    lbLamp->setPixmap(pmapGray);
    lamp->setPixmap(lampOff);

    QVBoxLayout *bottomlayout = new QVBoxLayout(this);
    bottomlayout->addWidget(lamp);

    setMinimumSize(lampOff.size());

    QTimer *tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(ontimer()));
}
void LampWidget::ontimer()
{
    if(isblinkOn == true)
    {
        isblinkOn = false;
//        lbLamp->setPixmap(pmapGray);
        lamp->setPixmap(lampOff);

    }
    else
    {
        isblinkOn = true;
//        lbLamp->setPixmap(pmapRed);
        lamp->setPixmap(lampOff);
    }
}

MastercontrolWidget::MastercontrolWidget(QWidget *parent):QWidget(parent)
{
    QVBoxLayout *mastercontrollayout = new QVBoxLayout(this);
    QPushButton *start = new QPushButton(tr("start"),this);
    QPushButton *stop = new QPushButton(tr("stop"),this);

    mastercontrollayout->addWidget(start);
    mastercontrollayout->addWidget(stop);

    connect(start , SIGNAL(clicked()) , this , SLOT(startsystem()));
    connect(stop , SIGNAL(clicked()) , this , SLOT(stopsystem()));
}
void MastercontrolWidget::startsystem()
{

}
void MastercontrolWidget::stopsystem()
{

}

/**************************************          Message Widget              *****************************************/
//右下角消息窗口
MessageWidget::MessageWidget(QWidget *parent)
    :QWidget(parent)
{
    lwMessages = new QListWidget(this);
    msgNumber = 0;

    QHBoxLayout *mLayout = new QHBoxLayout(this);
    mLayout->addWidget(lwMessages);
}

MessageWidget::~MessageWidget()
{

}

void MessageWidget::onReceiveMessage(QString msg)
{
    lwMessages->addItem(msg);
    msgNumber ++;
    lwMessages->setCurrentRow(msgNumber);
}
/**************************************          主窗口  Widget              *****************************************/
MainwindowWidget::MainwindowWidget(QWidget *parent):QWidget(parent)
{
    ConW = new ControlWidget(this);
    ResW = new ResultWidget(this);
    LamW = new LampWidget(LampWidget::GREEN,this);
    MasW = new MastercontrolWidget(this);
    Mess = new MessageWidget(this);

    QHBoxLayout *mainlayout = new QHBoxLayout(this);
    mainlayout->setMargin(15);
    mainlayout->setSpacing(10);

    mainlayout->addWidget(ConW);
    mainlayout->addWidget(ResW);
    mainlayout->addWidget(LamW);
    mainlayout->addWidget(MasW);
    mainlayout->addWidget(Mess);

}
//void MainwindowWidget::onReceiveForceData(Force6D f)
//{
    // Show current force data.
//    wdgForce->onReceiveForceData(f);

//    stwForceSensor->setStatus(1, StatusWidget::ON);

//    if(tspw->ssw != NULL)
//        tspw->ssw->setCurrForce(f);

//}











