#include "mainscene.h"
#include <windows.h>
#include <QFont>
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    Sleep(1500);
    this->set_windowBase();
    this->set_startBtn();
    this->set_levelBtn();
    this->set_btnBack();

    this->set_btnSwapb();
    this->set_bgsource();
    this->set_label();
    this->set_combBox();
}
// 判断不认识的单词库是否为空
bool MainScene::check_unknownWordsEmpty()
{
    QFile file;
    QString unkown = "./userData/" + this->account + ".txt";
    file.setFileName(unkown);
    if(!file.open(QFile::ReadWrite) ){
        qDebug() << "不认识单词库打开失败!";
    }
    QSet<QString> set;
    QTextStream ru(&file);
    // 将不认识的单词导入set
    QString word, interpretation;
    while(!ru.atEnd())
    {
        ru >> word >> interpretation;
        if(word != "")
        {
            set.insert(word);
        }
    }
    if(set.isEmpty())
        return true;
    return false;
}

// 让登录界面能给给主界面传参
void MainScene::set_account(QString account)
{
    this->account = account;
}
// 设置主窗口基础
void MainScene::set_windowBase()
{
    //设置固定大小
    this->setFixedSize(440,670);
    //设置图标
    this->setWindowIcon(QIcon(":/01/images/西瓜图标.png"));
    //设置标题
    this->setWindowTitle("西瓜背词");
}



void MainScene::set_btnBack()
{
    this->btn_back = new MyPushButton(":/01/images/返回按钮50.png");
    this->btn_back->setParent(this);
    this->btn_back->move(10, 600);
    connect(this->btn_back, &QPushButton::clicked, this, [=](){
        this->btn_back->zoom_leftRight();
        QTimer::singleShot(400,this,[=](){
           emit this->back();   //给主场景发送返回信号
        });
    });
}

// 设置开始按钮
void MainScene::set_startBtn()
{
    btn_start = new MyPushButton(":/01/images/开始按钮2.png");
    btn_start->setParent(this);
    this->btn_start->move(this->width()*0.5-btn_start->width()*0.5,this->height()*0.7);//设置到水平中心


    connect(btn_start, &QPushButton::clicked, this, [=](){
        if(!(this->four_clicked || this->six_clicked || this->unkown_clicked)) {
            choose_message->setText(tr("请选择词汇库"));
            choose_message->show();
            return;
        }
        btn_start->zoom_upDown(); // 实现按钮跳动效果

        // 重新创建一个答题场景
        int amount = this->combBox_amount->currentText().toInt();
        int level;
        if(this->four_clicked) {
            level = 0;
        } else if(this->six_clicked) {
            level = 1;
        } else {
            level = 2;
        }
        //
        if(level == 2 && check_unknownWordsEmpty()) {
            choose_message->setText(tr("你还没有未知的单词"));
            choose_message->show();
            return;
        }

        qDebug()<<"你选择的单词数: " << amount ;
        qDebug() <<"选择的词库是" << level;
        this->answer_scene = new AnswerScene(level, amount , account);  //构建下个场景
        qDebug()<<"MainScene里的account: "<< this->account ;

        // 连接新场景的返回信号
        connect(this->answer_scene, &AnswerScene::back, this, [=](){
            this->answer_scene->hide();
            this->setGeometry(this->answer_scene->geometry());
            delete this->answer_scene;
            this->answer_scene = nullptr;
            this->show();
        });
        //延时进入选择关卡场景
        QTimer::singleShot(500,this,[=](){
            qDebug()<<"点击了开始";
            //隐藏主场景,显示选择关卡的场景
            this->hide();//隐藏主窗口
            answer_scene->setGeometry(this->geometry());//防止窗口移动
            answer_scene->show();
        });
    });
}




// 实现点击按钮选择难度
void MainScene::set_levelBtn()
{
    this->four_clicked = false;
    this->six_clicked = false;
    this->unkown_clicked = false;

    this->font.setFamily("微软雅黑");
    this->font.setPixelSize(20);

    this->font.setBold(true);

    this->set_fourBtn();
    this->set_sixBtn();
    this->set_unkownBtn();


    this->choose_message = new QMessageBox(this);
    choose_message->setWindowTitle(tr("词汇选择"));
    choose_message->setWindowIcon(QIcon(":/01/images/西瓜图标2.png"));
}


void MainScene::set_fourBtn()
{
    btn_four = new MyPushButton(":/01/images/四级词汇.jpg");
    btn_four->setParent(this);

    btn_four->setAutoFillBackground(true);
    btn_four->setFont(this->font);
    btn_four->setFixedSize(80,150);
    btn_four->move(40, 120);

    connect(this->btn_four, &QPushButton::clicked, this, [=](){
        choose_message->setText(tr("你选择了四级词汇"));
        choose_message->show();

        this->btn_four->setIconSize(QSize(0, 0));
        this->btn_four->setText(tr("四\n级\n词\n汇"));
        this->btn_four->setStyleSheet("background-color: rgb(228,82,103)");

        this->four_clicked = true;

        if(this->six_clicked || this->unkown_clicked) {
            this->six_clicked = false;
            this->unkown_clicked = false;
            this->btn_six->setIconSize(QSize(this->btn_six->width(), this->btn_six->height()));
            this->btn_six->setText("");
            this->btn_unkown->setIconSize(QSize(this->btn_unkown->width(), this->btn_unkown->height()));
            this->btn_unkown->setText("");
        }
    });
}

void MainScene::set_sixBtn()
{
    btn_six = new MyPushButton(":/01/images/六级词汇.jpg");
    btn_six->setParent(this);
    btn_six->setFont(font);
    btn_six->setAutoFillBackground(true);
    btn_six->setFixedSize(80,150);
    btn_six->move(170, 120);

    connect(this->btn_six, &QPushButton::clicked, this, [=](){
        choose_message->setText(tr("你选择了六级词汇"));
        choose_message->show();

        this->btn_six->setIconSize(QSize(0, 0));
        this->btn_six->setText(tr("六\n级\n词\n汇"));
        this->btn_six->setStyleSheet("background-color: rgb(228,82,103)");


        this->six_clicked = true;

        if(this->four_clicked || this->unkown_clicked) {
            this->four_clicked = false;
            this->unkown_clicked = false;

            this->btn_four->setIconSize(QSize(this->btn_four->width(), this->btn_four->height()));
            this->btn_four->setText("");
            this->btn_unkown->setIconSize(QSize(this->btn_unkown->width(), this->btn_unkown->height()));
            this->btn_unkown->setText("");
        }
    });
}


void MainScene::set_unkownBtn()
{
    btn_unkown = new MyPushButton(":/01/images/未知词汇.jpg");
    btn_unkown->setParent(this);

    btn_unkown->setFont(font);
    btn_unkown->setAutoFillBackground(true);
    btn_unkown->setFixedSize(80,150);
    btn_unkown->move(300, 120);

    connect(this->btn_unkown, &QPushButton::clicked, this, [=](){
        choose_message->setText(tr("你选择了不熟词汇"));
        choose_message->show();

        this->btn_unkown->setIconSize(QSize(0, 0));
        this->btn_unkown->setText(tr("不\n熟\n词\n汇"));
        this->btn_unkown->setStyleSheet("background-color: rgb(228,82,103)");

        this->unkown_clicked = true;

        if(this->four_clicked || this->six_clicked) {
            this->four_clicked = false;
            this->six_clicked = false;
            this->btn_four->setIconSize(QSize(this->btn_four->width(), this->btn_four->height()));
            this->btn_four->setText("");
            this->btn_six->setIconSize(QSize(this->btn_six->width(), this->btn_six->height()));
            this->btn_six->setText("");
        }
    });
}

void MainScene::set_label()
{
    this->set_label_bg_amount();
    this->set_label_bg_level();
    this->set_label_amount();
    this->set_label_level();
}

void MainScene::set_label_bg_level()
{
    this->label_bg_level = new QLabel(this);
    QPixmap pixmap(":/01/images/西瓜底衬400.png");
    this->label_bg_level->setPixmap(pixmap);
    this->label_bg_level->setFixedSize(400, 150);
    this->label_bg_level->move(10, -30);
    this->label_bg_level->setAttribute(Qt::WA_TransparentForMouseEvents);

}
void MainScene::set_label_bg_amount()
{
    this->label_bg_amount = new QLabel(this);
    QPixmap pixmap(":/01/images/西瓜底衬400.png");
    this->label_bg_amount->setPixmap(pixmap);
    this->label_bg_amount->setFixedSize(400, 150);
    this->label_bg_amount->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_bg_amount->move(10, 250);
}
void MainScene::set_label_level()
{
    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(20);
    this->label_choose_level = new QLabel(tr("请选择词汇"), this);
    this->label_choose_level->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_choose_level->setFont(font);
    this->label_choose_level->setFixedSize(150, 40);
    this->label_choose_level->setAlignment(Qt::AlignHCenter);
    this->label_choose_level->move(120, 40);
}


void MainScene::set_label_amount()
{
    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(20);
    this->label_choose_amount = new QLabel(tr("请选择单词数"), this);
    this->label_choose_amount->setFont(font);
    this->label_choose_amount->setAlignment(Qt::AlignHCenter);
    this->label_choose_amount->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_choose_amount->setFixedSize(170, 40);
    this->label_choose_amount->move(115, 315);

}


void MainScene::set_combBox()
{
    combBox_amount = new QComboBox(this);
    combBox_amount->addItem(QString::number(10));
    combBox_amount->addItem(QString::number(20));
    combBox_amount->addItem(QString::number(30));
    combBox_amount->addItem(QString::number(40));
    combBox_amount->setAutoFillBackground(true);

    this->combBox_amount->setFixedSize(100, 40);
    this->combBox_amount->move(160, 387);
    QFont font("ZYSong18030", 15);
    font.setBold(true);
    this->combBox_amount->setFont(font);
}

void MainScene::set_btnSwapb(){
    this->btn_swapb = new MyPushButton(":/01/images/按钮1.png");
    this->btn_swapb->setParent(this);
    this->btn_swapb->move(360,590);
    this->btn_swapb->resize(100,20);

    connect(this->btn_swapb, &QPushButton::clicked, this, [=](){
            swap(this->p1,this->p2);
            this->update();
    });
}

void MainScene::set_bgsource()
{
    this->p1 =":/01/images/西瓜背景.jpg";
    this->p2 =":/01/images/西瓜 780.jpg";
}

//绘图事件,设置背景
void MainScene::paintEvent(QPaintEvent*)
{
    QPainter p(this);//为画家指定画图设备为当前窗口
    //指定从窗口(0,0)点开始,画窗口大小的图
    QPixmap pixmap(p1);//创建pixmap对象,并加载图片
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
