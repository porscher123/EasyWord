#include "signin.h"

SignIn::SignIn(QWidget *parent)
    : QWidget{parent}
{
    this->load_userData();
    this->set_windowBase();
    this->set_label();
    this->set_lineEdit();
    this->set_bgsource();
    this->set_btn();

}
void SignIn::set_windowBase()
{
    this->setFixedSize(440,670);
    //设置图标
    this->setWindowIcon(QIcon(":/01/images/西瓜图标.png"));
    //设置标题
    this->setWindowTitle("西瓜背词");
}
void SignIn::set_btn()
{
    this->set_btnSignIn();
    this->set_btnBack();
    this->set_btnEye1();
    this->set_btnEye2();
    this->set_btnSwapb();
}
void SignIn::set_btnSwapb()
{
    this->btn_swapb = new MyPushButton(":/01/images/按钮1.png");
    this->btn_swapb->setParent(this);
    this->btn_swapb->move(360,590);
    this->btn_swapb->resize(100,20);

    connect(this->btn_swapb, &QPushButton::clicked, this, [=](){
            swap(this->p1,this->p2);
            this->update();
    });

}
void SignIn::set_btnBack()
{
    this->btn_back = new MyPushButton(":/01/images/返回按钮50.png");
    this->btn_back->setParent(this);
    this->btn_back->move(10, 10);
    connect(this->btn_back, &QPushButton::clicked, this, [=](){
        this->btn_back->zoom_leftRight();
        QTimer::singleShot(400,this,[=](){
           emit this->back();   //给主场景发送返回信号
        });
    });
}

void SignIn::set_btnEye1()
{
    this->btnEye1Clicked = false;
    this->btn_eye1 = new MyPushButton(":/01/images/眼界20.png");
    this->btn_eye1->setParent(this);
    this->btn_eye1->move(180 + this->lineEdit_password->width() , 208);
    connect(this->btn_eye1, &MyPushButton::clicked, this, [=](){
        if(this->btnEye1Clicked) {
            this->lineEdit_password->setEchoMode(QLineEdit::Password);
            this->btnEye1Clicked = false;
        } else {
            this->lineEdit_password->setEchoMode(QLineEdit::Normal);
            this->btnEye1Clicked = true;
        }
    });
}
void SignIn::set_btnEye2()
{
    this->btnEye2Clicked = false;
    this->btn_eye2 = new MyPushButton(":/01/images/眼界20.png");
    this->btn_eye2->setParent(this);
    this->btn_eye2->move(180 + this->lineEdit_rePassword->width(), 255);
    connect(this->btn_eye2, &MyPushButton::clicked, this, [=](){
        if(this->btnEye2Clicked) {
            this->lineEdit_rePassword->setEchoMode(QLineEdit::Password);
            this->btnEye2Clicked = false;
        } else {
            this->lineEdit_rePassword->setEchoMode(QLineEdit::Normal);
            this->btnEye2Clicked = true;
        }
    });
}

// 将所有用户的账号导入, 以便检查账号是否存在
void SignIn::load_userData()
{
    QFile file;
    file.setFileName("./text/account.txt");
    file.open(QFile::ReadWrite);
    QTextStream in(&file);
    QString has_account,has_password;
    while(!in.atEnd() ){
        in >> has_account >> has_password;
        map_hasAccount[has_account] = has_password;
    }
    file.close();
}
// 保存用户的账号和密码,并为用户生成一个文件
void SignIn::save_account(QString account, QString password)
{
    QFile file;
    file.setFileName("./text/account.txt");
    if(!file.open(QFile::WriteOnly | QFile::Append)) {
        qDebug() << "account文件打开失败!";
    }
    QTextStream ts(&file);
    ts << account <<"  "<< password << "\n";
    file.close();

    file.setFileName("./userData/" + account + ".txt");
    if(!file.open(QFile::WriteOnly)){
        qDebug() << "账户信息文件打开失败！";
    }
    file.close();
}
void SignIn::set_btnSignIn()
{
    QFont font;
    font.setPixelSize(20);
    this->btn_signIn = new QPushButton(tr("注册"), this);
    this->btn_signIn->setFont(font);
    this->btn_signIn->setFixedSize(100, 50);
    this->btn_signIn->setStyleSheet("QPushButton{color:black}"
                                   "QPushButton:hover{color:red}"
                                   "QPushButton{background-color:rgb(78,255,255)}"
                                   "QPushButton{border:2px}"
                                   "QPushButton{border-radius:10px}"
                                   "QPushButton{padding:2px 4px}");
    this->btn_signIn->move(160, 350);
    // 用户点击注册按钮, 进行检查
    connect(this->btn_signIn, &QPushButton::clicked, this, [=](){
        QString account = this->lineEdit_account->text();
        QString password1 = this->lineEdit_password->text();
        QString password2 = this->lineEdit_rePassword->text();
        this->box = new QMessageBox(this);
        this->box->setFixedSize(100, 100);

        if(account.isEmpty()) {
            QMessageBox::information(this,"提示","账号为空");
        } else if( account.size() < 8){
            QMessageBox::warning(this,"提示","账号长度不得小于8位");
            this->lineEdit_account->clear();

        } else if(password1.isEmpty() || password2.isEmpty()) {
            QMessageBox::information(this,"提示","密码未填写");
        } else if( password1.size() < 8){
            QMessageBox::warning(this,"提示","密码长度不得小于8位");

            this->lineEdit_password->clear();
            this->lineEdit_rePassword->clear();
        } else if(password1 != password2) {
            QMessageBox::warning(this,"提示","两次输入密码不一致");

            this->lineEdit_password->clear();
            this->lineEdit_rePassword->clear();

        } else if(map_hasAccount.count(lineEdit_account->text()) ){
            QMessageBox::warning(this,"提示","该账号已存在");

            this->lineEdit_account->clear();
            this->lineEdit_password->clear();
            this->lineEdit_rePassword->clear();

        } else if(password1 == password2) {
            this->box->setWindowTitle("已完成");
            this->box->setText(tr("注册成功!"));
            qDebug() << "注册成功, 你的账号密码是:\n"<<account<<" "<<password1;
            //将账号密码放入account.txt中
            this->save_account(account, password1);

            this->box->show();
            this->account = account;
            this->password = password1;

            this->lineEdit_account->clear();
            this->lineEdit_password->clear();
            this->lineEdit_rePassword->clear();

            emit this->signIn_successfully();
        }
    });
}

void SignIn::set_label()
{
    QFont font;
    font.setPixelSize(20);

    this->label_account = new QLabel(tr("账号: "), this);
    this->label_account->setFont(font);
    this->label_account->move(120, 150);


    this->label_password = new QLabel(tr("密码: "), this);
    this->label_password->setFont(font);
    this->label_password->move(120, 200);


    this->label_rePassword = new QLabel(tr("确认密码: "), this);
    this->label_rePassword->setFont(font);
    this->label_rePassword->move(82, 250);
}

void SignIn::set_lineEdit()
{
    this->set_lineEditAccount();
    this->set_lineEditPassword();
    this->set_lineEditRePassword();

    //限制账号只能由数字组成
    QRegularExpression regx1 ("^[0-9]{8,12}$");
    QValidator* validator1 = new QRegularExpressionValidator(regx1,this->lineEdit_account);
    this->lineEdit_account->setValidator(validator1);


    //限制密码不能有空格
    QRegularExpression regx2 ("^\\S{8,14}$"); // 匹配8-14位非空格字符
    QValidator* validator2 = new QRegularExpressionValidator(regx2,this->lineEdit_password);
    this->lineEdit_password->setValidator(validator2);
    this->lineEdit_password->setMaxLength(14);


    QValidator* validator3 = new QRegularExpressionValidator(regx2,this->lineEdit_rePassword);
    this->lineEdit_rePassword->setValidator(validator3);
    this->lineEdit_rePassword->setMaxLength(14);

}
void SignIn::set_lineEditAccount()
{
    this->lineEdit_account = new QLineEdit(this);
    this->lineEdit_account->setFixedHeight(this->label_account->height());
    this->lineEdit_account->setFixedWidth(200);
    this->lineEdit_account->setPlaceholderText(tr("请输入账号(8-12位数字)"));
    this->lineEdit_account->move(170, 150);
}
void SignIn::set_lineEditPassword()
{
    this->lineEdit_password = new QLineEdit(this);
    this->lineEdit_password->setFixedHeight(this->label_password->height());
    this->lineEdit_password->setFixedWidth(200);
    this->lineEdit_password->setEchoMode(QLineEdit::Password);
    this->lineEdit_password->setPlaceholderText(tr("密码应为8-14位非空格字符"));
    this->lineEdit_password->move(170, 200);
}

void SignIn::set_lineEditRePassword()
{
    this->lineEdit_rePassword = new QLineEdit(this);
    this->lineEdit_rePassword->setFixedHeight(this->label_rePassword->height());
    this->lineEdit_rePassword->setFixedWidth(200);
    this->lineEdit_rePassword->setEchoMode(QLineEdit::Password);
    this->lineEdit_rePassword->setPlaceholderText(tr("请再次输入密码"));
    this->lineEdit_rePassword->move(170, 250);
}

QString SignIn::getAccount()
{
    return this->account;
}
QString SignIn::getPassword()
{
    return this->password;
}

void SignIn::paintEvent(QPaintEvent*)
{
    QPainter p(this);//为画家指定画图设备为当前窗口
    //指定从窗口(0,0)点开始,画窗口大小的图
    QPixmap pixmap(p1);//创建pixmap对象,并加载图片
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);
}



void SignIn::set_bgsource()
{

    this->p1 =":/01/images/西瓜背景640.jpg";
    this->p2 =":/01/images/西瓜3.jpg";
}
