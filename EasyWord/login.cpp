#include "login.h"

Login::Login(QWidget *parent)
    : QWidget{parent}
{
    this->set_windowBase(); // 设置登录窗口的基本(尺寸,标题)
    this->load_words();     // 读取单词到字典
    this->load_userData();  // 导入用户信息, 用于验证账号与密码是否匹配
    this->set_mainScene(); // 初始化主窗口, 点击登录按钮后会使用
    this->set_bgsource(); // 设置背景所需图片路径
    this->set_actSearch(); // 设置搜索框
    this->set_label();      //设置标签
    this->set_lineEdit(); // 设置单行的输入框
    this->set_btn(); // 设置按钮, 并连接信号槽
}
// 设置窗体基础
void Login::set_windowBase()
{
    // 设置窗口大小
    this->setFixedSize(440,670);
    //设置图标
    this->setWindowIcon(QIcon(":/01/images/西瓜图标.png"));
    //设置标题
    this->setWindowTitle("西瓜背词");
}
// 将用户的账号和密码从userData文件种读到map中
void Login::load_userData()
{

    QFile file;
    file.setFileName("./text/account.txt");
    file.open(QFile::ReadWrite);
    QTextStream in(&file);
    QString account,password;
    while(!in.atEnd() ){
        in >> account >>password;
        map_account[account] = password;
    }
    file.close();
}
// 读取单词到字典
void Login::load_words()
{
    QFile file1,file2;
    file1.setFileName("./text/CET4.txt");
    file2.setFileName("./text/CET6.txt");
    file1.open(QFile::ReadOnly);
    file2.open(QFile::ReadOnly);
    QTextStream in1(&file1);
    QTextStream in2(&file2);
    QString word,translate;
    while(!in1.atEnd() ){
        in1 >> word >> translate;
        this->dict[word] = translate;
    }
    while(!in2.atEnd() ){
        in2 >> word >> translate;
        this->dict[word] = translate;
    }
    file1.close();
    file2.close();
}

// 播放音乐
void Login::play_music()
{
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("qrc:/02/music/马嘉祺、宋亚轩、张真源 - 剩下的盛夏 (Live).mp3"));
    audioOutput->setVolume(50);
    player->play();
}
// 关闭音乐
void Login::stop_music()
{
    this->player->stop();
}
void Login::set_mainScene()
{
    this->mainScene = new MainScene;
    connect(mainScene,&MainScene::back,this,[=](){
        lineEdit_account->clear();
        lineEdit_password->clear();
        mainScene->hide();
        setGeometry(this->mainScene->geometry());
        this->show();
    });
}
// 设置按钮
void Login::set_btn()
{
    this->set_btnLogin();
    this->set_btnSignIn();
    this->set_btnEye();
    this->set_btnSwapb();
}
//登录按钮
void Login::set_btnLogin()
{
    this->btn_login = new MyPushButton(":/01/images/登录按钮200.png");
    this->btn_login->setParent(this);
    this->btn_login->move(this->width()*0.5-btn_login->width()*0.5,this->height()*0.72);


    // 连接登录按钮的点击事件(就是点击登录按钮后会干嘛)
    connect(this->btn_login, &MyPushButton::clicked, this, [=](){
        this->btn_login->zoom_upDown(); // 按钮弹跳
        QString account = this->lineEdit_account->text();
        QString password = this->lineEdit_password->text();
        if(account.isEmpty()){
            QMessageBox::information(this,"提示","请输入账号");
        } else if(password.isEmpty() ) {
            QMessageBox::information(this,"提示","请输入密码");
        } else if(!map_account.count(account)){
            QMessageBox::information(this,"提示","该账号不存在\n请先进行注册");
        } else if(map_account[account] != password){
            QMessageBox::critical(this,"提示","密码错误！");
        } else{
            //**************下面是成功登录后的代码*********************************
            this->play_music();  // 播放音乐
            qDebug() << account <<"用户登录!";
            QTimer::singleShot(500,this,[=](){
                // 界面切换
                this->hide();
                this->mainScene->setGeometry(this->geometry());
                this->mainScene->show();

                //监听主场景的返回信号(返回按钮被点击)
                connect(mainScene, &MainScene::back, this, [=](){
                    this->stop_music(); // 音乐通知

                    this->mainScene->hide();
                    this->setGeometry(mainScene->geometry());
                    this->show();
                });
            });
        }
    });
}

//密码可视按钮
void Login::set_btnEye()
{
    this->btnEyeClicked = false;
    this->btn_eye = new MyPushButton(":/01/images/眼界20.png");
    this->btn_eye->setParent(this);
    this->btn_eye->move(210 + this->lineEdit_password->width(), 306);
    connect(this->btn_eye, &MyPushButton::clicked, this, [=](){
        if(this->btnEyeClicked) {
            this->lineEdit_password->setEchoMode(QLineEdit::Password);
            this->btnEyeClicked = false;
        } else {
            this->lineEdit_password->setEchoMode(QLineEdit::Normal);
            this->btnEyeClicked = true;
        }
    });
}

//主界面“注册”按钮
void Login::set_btnSignIn()
{
    this->btn_signIn = new QPushButton(tr("注册"), this);
    QFont font;
    font.setPixelSize(25);
    this->btn_signIn->setFont(font);
    this->btn_signIn->setFlat(true);
    this->btn_signIn->move(330, 350);
    this->btn_signIn->setStyleSheet("QPushButton{color:black}"
                                   "QPushButton:hover{color:red}"
                                   "QPushButton{background-color:rgb(78,255,255)}"
                                   "QPushButton{border:2px}"
                                   "QPushButton{border-radius:10px}"
                                   "QPushButton{padding:2px 4px}");


    connect(this->btn_signIn, &QPushButton::clicked, this, [=](){
        // 点击注册按钮后才创建注册界面
        window_signIn = new SignIn;
        this->hide();
        this->window_signIn->setGeometry(this->geometry());
        window_signIn->show();

        // 监听注册界面的返回信号(注册界面的返回按钮的点击事件)
        connect(window_signIn, &SignIn::back, this, [=](){
            window_signIn->hide();
            this->setGeometry(window_signIn->geometry());
            delete this->window_signIn;
            this->window_signIn = nullptr;
            this->show();
        });
        //注册成功，将新注册的账号和密码放入Hash中, 以便用户登录
        connect(this->window_signIn, &SignIn::signIn_successfully, this, [=](){
            this->map_account.insert(this->window_signIn->getAccount(),this->window_signIn->getPassword());
        });
    });
}
// 设置交换背景的按钮
void Login::set_btnSwapb(){
    this->btn_swapb = new MyPushButton(":/01/images/按钮1.png");
    this->btn_swapb->setParent(this);
    this->btn_swapb->move(360,590);
    this->btn_swapb->resize(100,20);

    connect(this->btn_swapb, &QPushButton::clicked, this, [=](){
            swap(this->p1,this->p2);
            this->update();
    });
}
//搜索按钮
void Login::set_actSearch()
{
    action_search = new QAction(this);
    action_search -> setToolTip("搜索");
    action_search -> setIcon(QIcon(":/01/images/search260.png"));
    connect(action_search,&QAction::triggered,this,[&](){
        if(lineEdit_search->text() == ""){
            QMessageBox::warning(this,"提示","请输入后查询！");
        } else if(!this->dict.count(lineEdit_search->text()) ){
            QMessageBox::information(this,"提示","查无此词！");
        } else{
            this->box = new QMessageBox(this);
            this->box->setFixedSize(100, 100);
            this->box->setWindowTitle("查询成功");
            this->box->setText(this->lineEdit_search->text() + "\n" + this->dict[lineEdit_search->text()] );
            this->box->show();
        }
    });
}


void Login::set_lineEdit()
{
    this->set_lineEditAccount();
    this->set_lineEditPassword();
    this->set_lineEditSearch();
}
void Login::set_lineEditAccount()
{
    this->lineEdit_account = new QLineEdit(this);
    this->lineEdit_account->setFixedHeight(this->label_account->height());
    this->lineEdit_account->setPlaceholderText(tr("请输入账号"));
    this->lineEdit_account->move(170, 250);

    connect(this->lineEdit_account,&QLineEdit::editingFinished,this,[=](){
        this->mainScene->set_account(this->lineEdit_account->text());
    });

    //限制账号只能由数字组成
    QRegularExpression regx1 ("[0-9]+$");
    QValidator* validator1 = new QRegularExpressionValidator(regx1,this->lineEdit_account);
    this->lineEdit_account->setValidator(validator1);
    //限制账号长度最多12位
    this->lineEdit_account->setMaxLength(12);
}
void Login::set_lineEditPassword()
{
    this->lineEdit_password = new QLineEdit(this);
    this->lineEdit_password->setFixedHeight(this->label_password->height());
    this->lineEdit_password->setEchoMode(QLineEdit::Password);
    this->lineEdit_password->setPlaceholderText(tr("请输入密码"));
    this->lineEdit_password->move(170, 300);
}
void Login::set_lineEditSearch()
{
    lineEdit_search = new QLineEdit(this);
    lineEdit_search->setGeometry(55,50,300,30);
    this->lineEdit_search->move(0.5*(this->width() - this->lineEdit_search->width()), 20);
    lineEdit_search->setPlaceholderText(tr("搜索框(输入英文查询中文)"));
    //将搜索按钮放在搜索框右边
    lineEdit_search->addAction(action_search,QLineEdit::TrailingPosition);
    //搜索框只能输入英文（小写）
    QRegularExpression regx ("[a-z]+$");
    QValidator* validator = new QRegularExpressionValidator(regx,this->lineEdit_search);
    this->lineEdit_search->setValidator(validator);
}
void Login::set_label()
{
    this->set_labelAccount();
    this->set_labelPassword();
}
void Login::set_labelAccount()
{
    QFont font;
    font.setPixelSize(20);
    this->label_account = new QLabel(tr("账号: "), this);
    this->label_account->setFont(font);
    this->label_account->move(120, 250);
}
void Login::set_labelPassword()
{
    QFont font;
    font.setPixelSize(20);
    this->label_password = new QLabel(tr("密码: "), this);
    this->label_password->setFont(font);
    this->label_password->move(120, 300);
}

// 给背景初始化
void Login::set_bgsource()
{
    this->p1 =":/01/images/西瓜640.jpg";
    this->p2 =":/01/images/西瓜背景640.jpg";
}

void Login::paintEvent(QPaintEvent*)
{
    QPainter p(this);//为画家指定画图设备为当前窗口
    //指定从窗口(0,0)点开始,画窗口大小的图
    QPixmap pixmap(p1);//创建pixmap对象,并加载图片
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);
}
