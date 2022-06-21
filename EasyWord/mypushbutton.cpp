#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg)
{
    this->normalImgPath=normalImg;
    this->set_base(normalImg);
}


void MyPushButton::set_base(QString normalImg)
{
    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret)//如果没加载成功
    {
        qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");//呈现按钮本来形状
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
//点击  向下跳动
void MyPushButton::zoom_up()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象c
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
//向下跳后弹起
void MyPushButton::zoom_down()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象c
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::zoom_left()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象c
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x()+10,this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
void MyPushButton::zoom_right()
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象c
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x()+10,this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushButton::zoom_leftRight()
{
    this->zoom_left();
    this->zoom_right();
}
void MyPushButton::zoom_upDown()
{
    this->zoom_up();
    this->zoom_down();
}

