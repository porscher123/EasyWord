#include "answerscene.h"

AnswerScene::AnswerScene(int level, int amount, QString account,QWidget *parent)
    : QWidget{parent}
{ 
    this->level = level;
    this->wordsAmount = amount;
    this->account = account;
    this->currentWordIndex = -1; // 下标初始化为-1, 因为是先++, 后显示
    this->set_windowBase();
    this->load_words(); // 导入单词库
    this->shuffleWords(); // 打乱单词
    this->set_font();
    this->set_bgsource();
    this->set_btn();
    this->set_label();
}
void AnswerScene::set_windowBase()
{
    this->setFixedSize(440,670);
    this->setWindowTitle(tr("西瓜背词"));
    this->setWindowIcon(QIcon(":/01/images/西瓜图标.png"));
}
void AnswerScene::set_font()
{
    font.setFamily("AR PL KaitiM Gb");
    font.setPixelSize(20);
}

void AnswerScene::set_label()
{
    this->set_labelWord();
    this->font.setPixelSize(15);
    this->set_labelKown();
    this->set_labelUnkown();
    this->set_labelSkip();
    this->set_labelClick();
    this->set_labelBookmark();
}
void AnswerScene::set_labelKown()
{
    this->label_kown = new QLabel(tr("认识"), this);

    this->label_kown->setFont(this->font);
    this->label_kown->setFixedSize(50 ,20);
    this->label_kown->move(45, 525);
    this->label_kown->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_kown->setAlignment(Qt::AlignHCenter);

}
void AnswerScene::set_labelUnkown()
{
    this->label_unkown = new QLabel(tr("不认识"), this);
    this->label_unkown->setFont(this->font);
    this->label_unkown->setFixedSize(50, 20);
    this->label_unkown->move(194, 525);
    this->label_unkown->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_unkown->setAlignment(Qt::AlignHCenter);
}
void AnswerScene::set_labelSkip()
{
    this->label_skip = new QLabel(tr("跳过"), this);
    this->label_skip->setFont(this->font);
    this->label_skip->setFixedSize(50, 20);
    this->label_skip->move(335, 525);
    this->label_skip->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_skip->setAlignment(Qt::AlignHCenter);

}
void AnswerScene::set_labelWord()
{
    //  设置单词标签的背景颜色和字体字号
    label_word = new QLabel(this);
    label_word->move(58, 30);
    label_word->setFixedSize(this->btn_word->size());
    this->font.setBold(true);
    label_word->setFont(font);

    label_word->setAttribute(Qt::WA_TransparentForMouseEvents);//设置让鼠标进行穿透
    label_word->setAlignment(Qt::AlignCenter);
    this->update_word();
}
// 点击查看释义的标签
void AnswerScene::set_labelClick()
{
    this->label_clickPixmap = new QLabel(this);
    QPixmap pixmap(":/01/images/西瓜底衬350129.png");
    this->label_clickPixmap->setPixmap(pixmap);
    this->label_clickPixmap->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_clickPixmap->move(18, -10);

    this->label_clickWords = new QLabel(this);
    this->label_clickWords->setText(tr("点击单词查看单词释义"));
    this->label_clickWords->setAlignment(Qt::AlignCenter);
    this->label_clickWords->setFont(this->font);
    this->label_clickWords->setFixedSize(350, 129);
    this->label_clickWords->move(35, -10);
}
// 添加红色的书签图案
void AnswerScene::set_labelBookmark()
{
    this->label_bookmark = new QLabel(this);
    QPixmap pixmap(":/01/images/西瓜书签150150.png");
    this->label_bookmark->setPixmap(pixmap);
    this->label_bookmark->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->label_bookmark->move(315, 0);
}

void AnswerScene::set_btn()
{
    this->font.setPointSize(25);
    this->set_btnWord();
    this->set_btnKown();
    this->set_btnUnkown();
    this->set_btnSkip();
    this->set_btnBack();
    this->set_btnSwapb();
}
void AnswerScene::set_btnKown()
{
    btn_kown = new MyPushButton(":/01/images/西瓜按钮150.png");
    btn_kown->setParent(this);
    btn_kown->move(5, 450);
    connect(this->btn_kown, &QPushButton::clicked, this, [=](){
        this->btn_kown->zoom_upDown();
        // 如果当前单词是unknown里的就移除
        // 将set更新后, 将set里的单词保存到文件
        QString currWord = this->allwordsVec[this->currentWordIndex];
        if(this->unkownWordsSet.contains(currWord)) {
            this->unkownWordsSet.remove(currWord);
            this->save_unkownWords();
        }

        this->update_word();  //更新单词
    });
    connect(this->btn_kown, &QPushButton::pressed, this, [=](){
        this->label_kown->setText("");
    });
    connect(this->btn_kown, &QPushButton::released, this, [=](){
        this->label_kown->setText("认识");
    });
}

void AnswerScene::set_btnUnkown()
{
    btn_unkown = new MyPushButton(":/01/images/西瓜按钮150.png");
    btn_unkown->setParent(this);
    btn_unkown->move(150, 450);
    connect(this->btn_unkown, &QPushButton::clicked, this, [=]() {
        this->btn_unkown->zoom_upDown();
        this->update_word();

        QString unkown_word = this->allwordsVec.at(this->currentWordIndex);
        this->unkownWordsSet.insert(unkown_word);
        this->save_unkownWords();
    });
    connect(this->btn_unkown, &QPushButton::pressed, this, [=](){
        this->label_unkown->setText("");
    });
    connect(this->btn_unkown, &QPushButton::released, this, [=](){
        this->label_unkown->setText("不认识");
    });
}


void AnswerScene::set_btnSkip()
{
    btn_skip = new  MyPushButton(":/01/images/西瓜按钮150.png");
    btn_skip->setParent(this);
    btn_skip->move(290, 450);
    connect(this->btn_skip, &QPushButton::clicked, this, [=](){
        this->btn_skip->zoom_upDown();
        this->update_word();
        QString unkown_word = this->allwordsVec.at(this->currentWordIndex);
        this->unkownWordsSet.insert(unkown_word);
    });
    connect(this->btn_skip, &QPushButton::pressed, this, [=](){
        this->label_skip->setText("");
    });
    connect(this->btn_skip, &QPushButton::released, this, [=](){
        this->label_skip->setText("跳过");
    });
}


void AnswerScene::set_btnBack()
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
// 初始化显示单词的按钮, 并连接信号槽
void AnswerScene::set_btnWord()
{
    this->btnWordClicked = false;
    this->btn_word = new MyPushButton(":/01/images/单词背景300.png");
    this->btn_word->setParent(this);
    this->btn_word->move(55, 35);
    connect(this->btn_word, &QPushButton::clicked, this, [=](){
        if(this->btnWordClicked == false) {
            this->font.setPixelSize(17);
            this->label_word->setFont(this->font);
            this->label_word->setText(this->dict[this->allwordsVec.at(this->currentWordIndex)]);
            this->btnWordClicked = true;
        } else {
            this->font.setPixelSize(35);
            this->label_word->setFont(this->font);
            this->label_word->setText(this->allwordsVec.at(this->currentWordIndex));
            this->btnWordClicked = false;
        }
    });
}
// 更新单词, 下标在范围内移动后更新单词
void AnswerScene::update_word()
{
    if(this->btnWordClicked) {
        this->btnWordClicked = false;
    }
    this->font.setPixelSize(35);

    this->label_word->setFont(this->font);
    if( this->currentWordIndex < this->allwordsVec.size() - 1)
        this->currentWordIndex++;
    qDebug() << "idx:" << this->currentWordIndex;
    if (this->currentWordIndex < this->wordsAmount && this->currentWordIndex < this->allwordsVec.size() ){
        this->label_word->setText(this->allwordsVec.at(this->currentWordIndex));
     }else{
        QMessageBox::information(this,"提示","训练已完成");
    }
}


void AnswerScene::load_words()
{
    QString cet4 = "./text/CET4.txt";
    QString cet6 = "./text/CET6.txt";
    QString unkown = "./userData/" + this->account + ".txt";

    QFile file;
    qDebug() << "this->level = "<<this->level;
    // 判断是读取那个单词库
    if(this->level == 0) {
        file.setFileName(cet4);
    } else if(this->level == 1) {
        file.setFileName(cet6);
    } else if(this->level == 2){
        file.setFileName(unkown);
    }
    // 资源文件只能读，不能写
    if(!file.open(QFile::ReadOnly)) {
        qDebug() << "CET4单词库打开失败!";
    }

    //将text中的单词和翻译放入Hash表
    QTextStream ra(&file);
    QString word, interpretation;
    qDebug() << "翻译: ";
    while(!ra.atEnd())
    {
        ra >> word >> interpretation;
        this->dict[word] = interpretation;
        //将单词存入set
        if(word != "")
        {
            // qDebug()<<word <<"  ->" << interpretation;
            this->allwordsSet.insert(word);
        }
    }
    // 将set中单词导入vec
    QSetIterator<QString> set_it1(this->allwordsSet);
    while(set_it1.hasNext()) {
        this->allwordsVec.push_back(set_it1.next());
    }
    file.close();

    //********读取不认识的单词**************
    file.setFileName(unkown);
    if(!file.open(QFile::ReadWrite) ){
        qDebug() << "不认识单词库打开失败!";
    }
    QTextStream ru(&file);
    // 将不认识的单词导入set
    while(!ru.atEnd())
    {
        ru >> word >> interpretation;
        if(word != "")
        {
            unkownWordsSet.insert(word);
        }
    }
    //  将set中单词导入vec
    QSetIterator<QString> set_it2(this->unkownWordsSet);
    while(set_it2.hasNext()) {
        unkownWordsVec.push_back(set_it2.next());
    }
    file.close();

    qDebug() << this->account <<"的不熟单词库大小: " << this->unkownWordsVec.size();

}




// 将vec打乱
void AnswerScene::shuffleWords()
{
    auto& vec = this->allwordsVec;
    for(int i = 0; i < vec.size(); i++) {
        int j = i + 1 + rand() % vec.size() ;
        if(i < vec.size() && j < vec.size())
            swap(vec[i], vec[j]);
    }
}

void AnswerScene::save_unkownWords()
{
    QString unkown = "./userData/" + this->account + ".txt";
    QFile file;
    file.setFileName(unkown);
    if(!file.open(QFile::WriteOnly | QFile::Truncate) ){
        qDebug() << "不认识单词库打开失败!";
    }
    QTextStream textOutput(&file);
    QSetIterator<QString> set_it2(this->unkownWordsSet);
    while(set_it2.hasNext()) {
        qDebug() << "保存成功";
        QString s = set_it2.next();
        textOutput << s <<"  "<<this->dict[s]<<"\n";
    }
    file.close();
}


void AnswerScene::set_btnSwapb(){
    this->btn_swapb = new MyPushButton(":/01/images/按钮1.png");
    this->btn_swapb->setParent(this);
    this->btn_swapb->move(360,590);
    this->btn_swapb->resize(100,20);

    connect(this->btn_swapb, &QPushButton::clicked, this, [=](){
            swap(this->p1,this->p2);
            this->update();
    });
}

void AnswerScene::set_bgsource()
{

    this->p1 =":/01/images/西瓜·640.jpg";
    this->p2 =":/01/images/西瓜背景1640.jpg";
}


void AnswerScene::paintEvent(QPaintEvent*)
{
    QPainter p(this);//为画家指定画图设备为当前窗口
    //指定从窗口(0,0)点开始,画窗口大小的图
    QPixmap pixmap(p1);//创建pixmap对象,并加载图片
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);
}


AnswerScene::~AnswerScene()
{

}
