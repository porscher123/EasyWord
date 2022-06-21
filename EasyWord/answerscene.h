#ifndef ANSWERSCENE_H
#define ANSWERSCENE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QHash>
#include <QVector>
#include <QPixmap>
#include <QPalette>
#include <QTextStream>
#include <QFile>
#include <QSet>
#include <random>
#include <QtAlgorithms>
#include "mypushbutton.h"
#include <QTimer>
#include <QPainter>
#include <QTime>
#include "windows.h"

class AnswerScene : public QWidget
{
    Q_OBJECT
public:
    explicit AnswerScene(int level, int amount, QString account, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);//绘图事件,设置背景
    ~AnswerScene();
private:
    int level; // 四级还是六级
    int wordsAmount;    // 此次背词得数量
    int currentWordIndex;   // 当前显示得单词下标
    bool btnWordClicked;
    // 按钮
    MyPushButton* btn_kown;
    MyPushButton* btn_unkown;
    MyPushButton* btn_skip;
    MyPushButton* btn_back;
    MyPushButton* btn_word;
    // 标签
    QLabel* label_word;
    QLabel* label_kown;
    QLabel* label_unkown;
    QLabel* label_skip;
    QLabel* label_clickPixmap;
    QLabel* label_clickWords;
    QLabel* label_bookmark;

    // 存用户所选的单词和他不会的单词, 用vec和set
    QVector<QString> allwordsVec;
    QVector<QString> unkownWordsVec;
    QSet<QString> allwordsSet;
    QSet<QString> unkownWordsSet;

    QPixmap pixmap;
    QFont font;
    // 存储用户账号方便打开用户文件
    QString account;
    // 更换背景用
    QPushButton* btn_swapb;
    QString p1;
    QString p2;
    QHash<QString, QString> dict; // 存单词和其翻译
private:
    // 设置按钮们
    void set_btn();
    void set_btnKown();
    void set_btnUnkown();
    void set_btnSkip();
    void set_btnBack();
    void set_btnWord();
    void set_btnSwapb();

    // 设置标签们
    void set_label();
    void set_labelKown();
    void set_labelUnkown();
    void set_labelSkip();
    void set_labelWord();
    void set_labelClick();
    void set_labelBookmark();

    void set_bgsource();

    void load_words();
    void update_word();


    void set_font();
    void save_unkownWords();
    void shuffleWords();
    void set_windowBase();

signals:
    void back();
};

#endif // ANSWERSCENE_H
