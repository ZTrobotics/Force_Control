#include "system.h"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //显示主窗口
    //ComponetDetectDialog *w = new ComponetDetectDialog;
    //设置窗口大小，1900列，1000行
    //w->resize(1900,1000);
    //w->show();



    SCASystem *scas = new SCASystem();
    return a.exec();
}
