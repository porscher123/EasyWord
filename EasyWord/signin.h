#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "mypushbutton.h"
#include <QTimer>
#include <QMessageBox>
#include <QPainter>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

class SignIn : public QWidget
{
    Q_OBJECT
public:
    explicit SignIn(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);//绘图事件,设置背景
private:
    bool btnEye1Clicked;
    bool btnEye2Clicked;
    QLineEdit* lineEdit_account;
    QLabel* label_account;
    QLineEdit* lineEdit_password;
    QLabel* label_password;
    QLineEdit* lineEdit_rePassword;
    QLabel* label_rePassword;

    MyPushButton* btn_eye1;
    MyPushButton* btn_eye2;
    MyPushButton* btn_back;
    QPushButton* btn_signIn;
    // 交换背景
    QPushButton* btn_swapb;
    QString p1;
    QString p2;

    QString account;
    QString password;
    QMessageBox* box;

    QMap<QString,QString> map_hasAccount;

private:
    void set_lineEditAccount();
    void set_lineEditPassword();
    void set_lineEditRePassword();

    void set_btnEye1();
    void set_btnEye2();
    void set_btnBack();

    void set_btnSignIn();
    void set_windowBase();

    void load_userData();

    void save_account(QString account, QString password);
public:
    void set_label();
    void set_btn();
    void set_lineEdit();

    void set_btnSwapb();//
    void set_bgsource();//
    // 为登录界面提供获取新注册的用户的账号和密码
    QString getAccount();
    QString getPassword();



signals:
    void back();
    void signIn_successfully();
};

#endif // SIGNIN_H
