#include "mainscene.h"
#include "login.h"
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/01/images/西瓜图标2.png");
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();
    Login w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
