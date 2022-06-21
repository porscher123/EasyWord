#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QMessageBox>
#include "mypushbutton.h"
#include "mainscene.h"
#include <QLineEdit>
#include <QLabel>
#include <QAction>
#include <QHash>
#include <QSet>
#include <QPair>
#include <QString>
#include <QVector>
#include <QListWidget>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFile>
#include "signin.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMediaPlayer>
#include <QAudioOutput>
class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);//绘图事件,设置背景
public:
    void set_mainScene(); // 初始化主界面
    /// void set_windowSignin(); // 初始化注册界面
    void set_lineEdit();
    void set_label();
    void set_btn();
private:
    void set_lineEditAccount();
    void set_lineEditPassword();
    void set_lineEditSearch();

    void set_btnLogin();
    void set_btnEye();
    void set_btnSignIn();
    void set_btnSwapb();


    void set_labelAccount();
    void set_labelPassword();

    void set_actSearch();

    void set_windowBase();

    void set_bgsource();

    // 播放音乐相关函数
    void play_music();
    void stop_music();

    // 两个导入相关函数
    void load_userData();
    void load_words();
private:
    bool btnEyeClicked;
    //  按钮
    MyPushButton* btn_login;
    MyPushButton* btn_eye;
    QPushButton* btn_signIn;
    QPushButton* btn_logIn;
    QPushButton* btn_search;
    // 更换背景相关
    QPushButton* btn_swapb;
    QString p1;
    QString p2;
    // 信息提示相关
    QMessageBox* box;
    // 登录部分的标签和输入框
    QLineEdit* lineEdit_account;
    QLabel* label_account;
    QLineEdit* lineEdit_password;
    QLabel* label_password;
    QLineEdit* lineEdit_search;
    QAction* action_search;
    // 两个map
    QHash<QString,QString> map_account; // 存储账号到密码
    QHash<QString,QString> dict; // 存储英文到翻译
    // 两个窗口
    MainScene* mainScene; // 主场景
    SignIn* window_signIn; // 注册界面
    //  播放音乐相关
    QMediaPlayer* player;
    QAudioOutput* audioOutput ;
    QString account;
signals:

};

#endif // LOGIN_H
