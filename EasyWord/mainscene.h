#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QIcon>
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include "answerscene.h"
#include <QTimer>
#include <QComboBox>
#include <QMessageBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);//绘图事件,设置背景
private:
    void set_fourBtn();
    void set_sixBtn();
    void set_unkownBtn();
    void set_label_level();
    void set_label_amount();
    void set_label_bg_level();
    void set_label_bg_amount();

public:
    void set_windowBase();
    void set_startBtn();
    void set_levelBtn();
    void set_btnBack();
    void set_label();
    void set_combBox();
    void set_layout();
    bool check_unknownWordsEmpty();

    void set_btnSwapb();//
    void set_bgsource();//
    // 实现点击按钮改变颜色


    void set_account(QString account);
    void load_unknownWords();
private:
    bool four_clicked;
    bool six_clicked;
    bool unkown_clicked;
    MyPushButton* btn_start;
    MyPushButton* btn_back;
    MyPushButton* btn_four;
    MyPushButton* btn_six;
    MyPushButton* btn_unkown;

    QPushButton* btn_swapb;
    QString p1;
    QString p2;

    QComboBox* combBox_amount;
    AnswerScene* answer_scene;
    QMessageBox* choose_message;
    QLabel* label_choose_level;
    QLabel* label_choose_amount;
    QLabel* label_bg_level;
    QLabel* label_bg_amount;

    QVBoxLayout* main_layout;
    QHBoxLayout* amount_label_layout;
    QHBoxLayout* level_label_layout;
    QHBoxLayout* level_layout;
    QHBoxLayout* amount_layout;
    QHBoxLayout* start_btn_layout;

    QFont font;

    QString account;

signals:
    void back();

};
#endif // MAINSCENE_H
