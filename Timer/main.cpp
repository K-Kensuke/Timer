#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setGeometry(0, 0, 900, 600); // ウィンドウの位置とサイズを再設定する
    w.show();

    return a.exec();
}
