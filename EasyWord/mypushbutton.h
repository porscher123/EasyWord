#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTime>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
     MyPushButton(QString normalImg);//重写构造函数

private:
     QString normalImgPath;
     void zoom_up();
     void zoom_down();
     void zoom_left();
     void zoom_right();
public:
     void set_base(QString btn_img);
     void zoom_upDown();
     void zoom_leftRight();

signals:

};

#endif // MYPUSHBUTTON_H
