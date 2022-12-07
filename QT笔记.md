

# 基础知识

+ **默认创建窗口类,可以选择三种基类:QWidget,QMainWindow,QDialog**

  

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220129205858264.png" alt="image-20220129205858264" style="zoom: 67%;" />

## main.cpp内容

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220129210039813.png" alt="image-20220129210039813" style="zoom: 80%;" />

## pro文件内容解释

```c++
QT       += core gui //包含模块

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets//给主版本大于4加上widget模块

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
//源文件
SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

```

## widget.h文件

```c++
//防止头文件重复包含
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>//包含窗口类头文件

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }//在ui命名空间里有一个wigdget类
QT_END_NAMESPACE
//widget类的定义
class Widget : public QWidget//继承
{
    Q_OBJECT //宏,使用qt信号与信号槽机制必须添加
	//允许类中使用信号和槽机制
public:
    Widget(QWidget *parent = nullptr);//*默认构造
    ~Widget();

private:
    Ui::Widget *ui;//ui::widget类型的一个指针,指向可视化界面
};
#endif // WIDGET_H

```



+ **widget.cpp文件**

```c++
#include "widget.h"
#include "ui_widget.h"
//widget类的实现
							//初始化列表
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


```

## 按钮创建

```c++
#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>//包含头文件
//widget类的实现
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    //第一个按钮
    QPushButton *btn=new QPushButton;//创建对象指针
    btn->show();//show()以顶层弹出窗口
 
    btn->setParent(this); //让btn对象以来在widget窗口中
   
    btn->setText("第一个按钮"); //在按钮上显示文本


    //创建第二个按钮,按控件的大小创建窗口
    QPushButton* btn2=new QPushButton("第二个按钮",this);

    resize(600,400);

    
    btn->move(100,100);//移到按钮

    
    setWindowTitle("第一个窗口");//设置窗口标题

    
    setFixedSize(800,600);//设置固定窗口大小
    
   
    btn2->resize(250,180);  //改变按钮大小

    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


```

## 对象树

​	当创建的对象再堆区时,如果指定其父亲是QObject的派生类,会将对象放入对象树中,不用管理其释放操作,简化了内存回收机制

​	构造从上到下,析构从下到上

```c++
MyPushButton* mybtn=new MyPushButton;
mybtn->setText("我自己的按钮");
mybtn->move(200,0);
mybtn->setParent(this);//设置到对象树中
ui->setupUi(this);
```

+ 容器与迭代

  ```c++
  //QList
  void MainWindow::on_pushButton_clicked()
  {
      QList<QString> l;
      QString s("this is a demo");
      l.append(s);
      l<<"hello";
      qDebug()<<l[0];
      qDebug()<<l[1];
  
      qDebug()<<"长度:"<<l.length();
      qDebug()<<"首元素"<<l.first();
      qDebug()<<"尾元素"<<l.last();
  
      l.remove(1);
      qDebug()<<"长度:"<<l.length();
      qDebug()<<"首元素"<<l.first();
      qDebug()<<"尾元素"<<l.last();
  
      QVector<QString> v;
      v<<"hello world";
      qDebug()<<v[0];
  }
  
  //java只读迭代
  void MainWindow::on_pushButton_2_clicked()
  {
      QList<int> l;
      l<<10<<20<<30<<40<<50;
      QListIterator<int> l_it(l);
      while(l_it.hasNext())
      {
          qDebug()<<l_it.next();
      }
      qDebug()<<"-----------------------------";
      while(l_it.hasPrevious())
      {
          qDebug()<<l_it.previous();
      }
  
      /*
      l_it.toBack();
      l_it.toFront()
      l_it.peekNext();
      l_it.peekPrevious();
      */
  }
  
  //STL风格迭代
  void MainWindow::on_pushButton_3_clicked()
  {
      QList<int> l;
      for(int i=0;i<10;i++)
      {
          l.insert(l.end(),i);
      }
      QList<int>::iterator it;
      for(it=l.begin();it!=l.end();it++)
      {
          qDebug()<<*it;
          *it*=10;
      }
      QList<int>::const_iterator cit;
      for(cit=l.constBegin();cit!=l.constEnd();cit++)
      {
          qDebug()<<(*cit);
      }
  }
  //字典类
  //Java风格迭代
  void MainWindow::on_pushButton_4_clicked()
  {
     QMap<QString,QString> mp;
     mp.insert("北京","222");
     mp.insert("沈阳","024");
     mp.insert("上海","021");
     mp.insert("西安","029");
  
    QMapIterator<QString,QString> m_it1(mp);
    while(m_it1.hasNext())
    {
        qDebug()<<m_it1.peekNext().key()<<" "<<m_it1.next().value();
    }
    QMutableMapIterator<QString,QString> m_m_it(mp);
    if(m_m_it.findNext("222"))
    {
        m_m_it.setValue("010");
    }
    QMapIterator<QString,QString> m_it2(mp);
    while(m_it2.hasNext())
    {
        qDebug()<<m_it2.peekNext().key()<<" "<<m_it2.next().value();
    }
  }
  //STL风格迭代
  
  void MainWindow::on_pushButton_5_clicked()
  {
      QMap<QString,QString> mp;
      mp.insert("北京","222");
      mp.insert("沈阳","024");
      mp.insert("上海","021");
      mp.insert("西安","029");
      QMap<QString,QString>::const_iterator cit1;
      for(cit1=mp.constBegin();cit1!=mp.constEnd();cit1++)
      {
          qDebug()<<cit1.key()<<" "<<cit1.value();
      }
      QMap<QString,QString>::iterator mit;
      mit=mp.find("北京");
      if(mit!=mp.end())
      {
          mit.value()="010";
      }
      QMap<QString,QString>::const_iterator cit2;
      for(cit2=mp.constBegin();cit2!=mp.constEnd();cit2++)
      {
          qDebug()<<cit2.key()<<" "<<cit2.value();
      }
  }
  //foreach 迭代
  void MainWindow::on_pushButton_6_clicked()
  {
      //迭代list
      QString s;
      QList<QString> l;
      l<<"hello"<<"world"<<"I love you"<<"face";
      foreach(QString s,l)
      {
          qDebug()<<s;
      }
      //迭代map
      QMap<QString,QString> mp;
      mp.insert("北京","222");
      mp.insert("沈阳","024");
      mp.insert("上海","021");
      mp.insert("西安","029");
      foreach(const QString key,mp.keys())
      {
          qDebug()<<key<<"->"<<mp.value(key);
      }
  }
  
  //万能类
  void MainWindow::on_pushButton_7_clicked()
  {
     QVariant v(123);
     qDebug()<<v.toInt();
     QVariant w("i love you");
     qDebug()<<w.toString();
  
      QMap<QString,QVariant> mp;
      mp["int"]=132;
      mp["double"]=123.321;
      mp["string"]="fucking doge king";
      mp["color"]=QColor(255,0,0);
      qDebug()<<mp["string"]<<" " <<mp["string"].toString();
  
      QStringList l;
      l<<"123"<<"abc"<<"haha";
      QVariant variant(l);
      if(variant.metaType().id()==QMetaType::fromName("QStringList").id())
      {
          QStringList ls=variant.toStringList();
          for(int i=0;i<ls.size();i++)
          {
              qDebug()<<ls.at(i);
          }
      }
  
  }
  
  
  ```

  ## QString

  ```c++
  void MainWindow::on_pushButton_clicked()
  {
      //1.
      QString str1="hello ";
      str1=str1+"world";
      QString str2="I love ";
      str2+="you";
      cout <<str1.toStdString()<<endl<<str2.toStdString()<<endl;
      cout<<"--------------------------------"<<endl;
      //2.
      QString str3="welcome ";
      QString str4="to ";
      str3.append(str4);
      str3.append("Beijing");
      cout<<str3.toStdString()<<endl;
      cout<<"--------------------------------"<<endl;
      //3.arg函数
      //百分号站位
     QString str5;
     str5=QString("I bought %1 pounds of %2 apples.").arg(10).arg("red");
     cout<<str5.toStdString()<<endl;
      cout<<"--------------------------------"<<endl;
      //4.asprintf("%s")
     QString str6;
     str6=str6.asprintf("%s","Welcome to my heart");
     QByteArray ba= str6.toLocal8Bit();
     const char* c_str=ba.data();
     str6=QString::asprintf("%s %s %s",c_str,"lll","hhaha");
     cout<<str6.toStdString()<<endl;
     cout<<"--------------------------------"<<endl;
  
  
     //插入字符串
     str5.insert(11,"0");
     cout<<str5.toStdString()<<endl;
     cout<<"--------------------------------"<<endl;
     //头插
     str5.prepend("hello ");
     cout<<str5.toStdString()<<endl;
     cout<<"--------------------------------"<<endl;
     //替换
     str5.replace(29,10,"yellow banana");
     cout<<str5.toStdString()<<endl;
     cout<<"--------------------------------"<<endl;
  
  
     //去空格
     QString str7="  he   ll  o  ";
     cout<<str7.toStdString()<<endl;
     cout<<str7.trimmed().toStdString()<<endl;//去掉首位空格
     cout<<str7.simplified().trimmed().toStdString()<<endl;//保留中间一个空格,首位空格
     cout<<"--------------------------------"<<endl;
  
  }
  
  //查询字符串和比较字符串
  //前缀,后缀,子字符串
  void MainWindow::on_pushButton_2_clicked()
  {
      //判断前缀
      QString str1="welcome to my heart!";
      cout<<str1.startsWith("welcome")<<endl;//默认大小写敏感
      cout<<str1.startsWith("welcome",Qt::CaseSensitive)<<endl;
      cout<<str1.startsWith("Welcome",Qt::CaseInsensitive)<<endl;
      cout<<"--------------------------------"<<endl;
      //判断后缀
      cout<<str1.endsWith("!")<<endl;
      cout<<"--------------------------------"<<endl;
      //判断字串
      cout<<str1.contains("to")<<endl;
      cout<<"--------------------------------"<<endl;
  
  
       //比较字符串
       cout<<(QString("a")<QString("b"))<<endl;//1
       cout<<(QString("A")<QString("b"))<<endl;//1
       cout<<"--------------------------------"<<endl;
  
       cout<<QString::localeAwareCompare("a","b");//使用本地字符集,与平台有关
       cout<<QString("c").compare("b")<<endl;//使用Unicode编码,与平台无关
  }
  
  
  void MainWindow::on_pushButton_3_clicked()
  {
      QString s1="123";
      cout<<s1.toInt()<<endl;
      bool sta;
      cout<<s1.toInt(&sta,16)<<endl;
  
  
      QString s2="welcome to the future!";
      QByteArray  ba=s2.toLocal8Bit();
      qDebug()<<ba;
      ba.append("hahaha");
      qDebug()<<ba;
  
      //NUll与empty
      //NULL:
      //QString的默认构造函数,创建对象是NULL
      //empty是长度为0的字符串
      //NULL-->empty
      qDebug()<<QString().isNull();//1
      qDebug()<<QString().isEmpty();//1
      qDebug()<<QString("").isNull();//0
      qDebug()<<QString("").isEmpty();//1
  }
  
  
  ```

  

## 将输入到文本框的内容输出到终端



```c++
void MainWindow::on_pushButton_clicked()
{
    // cout<<"hello world!"<<endl;
    //将输入到文本框内的文本转成标准字符串输出到控制台
    cout<<ui->textEdit->toPlainText().toStdString()<<endl;
}
```

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220204175847669.png" alt="image-20220204175847669" style="zoom: 50%;" />



## 计算圆面积

+ 连接信号和槽时, 使用SIGNAL()和SLOT()这两个宏,它们将参数转换为C字符串(const cahr*)
+ 槽函数放在private slots:下
+ 使用了布局管理器对窗口控件布局

```cpp
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
     QPushButton* btn_calculate;   //计算圆面积按钮
     QLabel* label_radius;  // 提示输入半径
     QLabel* label_area;    // 显示圆面积
     QLineEdit* input_radius;   //输入半径的编辑框
private slots:
     void showArea();
};
#endif // DIALOG_H

```

```cpp
#include "dialog.h"
#include <QGridLayout>  //布局管理器头文件
const static double PI = 3.1416;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    // 为数据成员分配内存空间
    this->label_radius = new QLabel(this);
    this->label_area = new QLabel(this);
    this->btn_calculate = new QPushButton(this);
    this->input_radius = new QLineEdit(this);
    // 设置文本内容
    this->label_radius->setText(tr("请输入圆的半径: "));
    this->btn_calculate->setText(tr("显示对应圆的面积"));
    // 添加布局管理器
    QGridLayout* mainLayout = new QGridLayout(this);
    // 将控件设置到布局管理器中
    mainLayout->addWidget(this->label_radius, 0, 0);
    mainLayout->addWidget(this->input_radius, 0, 1);
    mainLayout->addWidget(this->label_area, 1, 0);
    mainLayout->addWidget(this->btn_calculate, 1, 1);
    // 连接信号和槽
    connect(btn_calculate, SIGNAL(clicked()), this, SLOT(showArea()));// 连接计算按钮的点击事件和窗口的显示面积槽函数
    connect(this->input_radius, SIGNAL(textChanged(QString)), this, SLOT(showArea()));  //连接半径输入宽的文本改变信号和显示面积的槽函数
    // 将布局管理器添加到窗口
    setLayout(mainLayout);

}
// 窗口的槽函数
void Dialog::showArea()
{
    double value = this->input_radius->text().toInt();
    value = value * value * PI;
    this->label_area->setText(QString().setNum(value));
}
```

+ 效果

![image-20220409213612768](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220409213612768.png)













# 信号与槽

​	connect(信号发送者,发送的具体信号,信号接收者,信号的处理(槽))

​	信号槽的优点:松散耦合,发送端与接受端本身无关联,通过链接将两端耦合在一起

 + 实现关闭窗口

   ```c++
   		//    函数地址,按钮的 					槽函数地址,处理窗口的
   connect(mybtn,&QPushButton::clicked,this,&Widget::close);
   ```

   

## 自定义信号和槽

```c++
//Teacher类,发送信号
class Teacher : public QObject
{
//自定义信号写道signal下
//返回值是void,只需要声名不需要实现
//可以右参,可以重载
signals://老师发出信号
    void hungry();
};

//学生类,写槽函数,响应
class Student : public QObject
{
public:
    //槽函数写到public作用域下
    //返回值是void,需要声名和实现
    //可以有参数,可以重载
    void treat();
};

//在窗口类中定义老师和学生类的指针,和触发老师信号的函数
private:
    Ui::Widget *ui;
    Teacher *t;
    Student *s;
    void classover();

//在窗口中实现connect
//创建老师和学生
this->t=new Teacher(this);
this->s=new Student(this);
//链接
connect(t,&Teacher::hungry,s,&Student::treat);
classover();//触发

//下课后使老师饥饿
void Widget:: classover()
{
    //
    emit t->hungry();//触发信号用emit
}

```

## 自定义信号和槽发生重载时

​	利用函数指针明确指出信号函数和槽函数的地址,再进行连接(connect)

```c++
void(Teacher:: *teachersignal)(QString)=&Teacher::hungry;//指向有参的成员函数
void(Student:: *studentslot)(QString)=&Student::treat;
connect(t,teachersignal,s,studentslot);


void Widget:: classover()
{
    //
    //emit t->hungry();
    emit t->hungry("宫保鸡丁");
}

```

## 信号连接信号

实现按钮点击的信号触发老师饿了的信号然后触发学生请客的槽函数

```c++
QPushButton *btn= new QPushButton("下课",this);//创建按钮并指定标题和父亲
void(Teacher:: *teachersignal2)(void)=&Teacher::hungry;//指向无参的成员函数
void(Student:: *studentslot2)(void)=&Student::treat;
connect(t,teachersignal2,s,studentslot2);//信号连接槽(老师饿了的信号连接学生请客的槽)
connect(btn,&QPushButton::clicked,t,teachersignal2);//信号连接信号(按钮信号连接老师饿了的信号)
```

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220206210000226.png" alt="image-20220206210000226" style="zoom:50%;" />

断开连接

```c++
disconnect(btn,&QPushButton::clicked,t,teachersignal2);//参数与连接时相同
```

+ 拓展

1. 信号连接多个槽函数

2. 多个信号连接同一个槽函数

3. 信号和槽函数的参数,必须类型一一对应

   ```c++
   void(Teacher:: *teachersignal2)(void)=&Teacher::hungry;//指向有参的成员函数
   void(Student:: *studentslot2)(void)=&Student::treat;
   ```

4. 信号和槽的参数个数可以不一致,信号参数个数可多于槽函数的参数个数

   ```c++
   void(Teacher:: *teachersignal)(QString,int)=&Teacher::hungry;
   void(Student:: *studentslot)(QString)=&Student::treat;
   ```

   

## lambda表达式

+ 值传递=

  ```c++
   [=](){
          btn->setText("王新超");
      }();
  ```

+ 某个值

  ```c++
   [btn](){
          btn->setText("666");
      }();
  ```

+ 指定返回值->

  ```c++
  int ret=[]()->int{return 1000;}();
      qDebug()<<ret;
  ```

+ lambda表达式做槽函数实现多个功能

  ```c++
  QPushButton* btn2=new QPushButton("关闭",this);
  btn2->move(100,0);
  connect(btn2,&QPushButton::clicked,this,[=](){
      this->close();
      emit t->hungry("shit");
      btn2->setText("close");
  });
  ```



## 作业

1. 实现两个按钮控制另一个窗口的开关

   ```c++
   QWidget* w=new QWidget;
   w->setWindowTitle("new window");
   QPushButton* btn1=new QPushButton("open",this);
   btn1->move(200,0);
   QPushButton* btn2=new QPushButton("close",this);
   btn2->move(0,200);
   //两个connect连接两个按钮与新窗口的开关
   connect(btn1,&QPushButton::clicked,w,&QWidget::show);
   connect(btn2,&QPushButton::clicked,w,&QWidget::close);
   ```

   

2. 实现一个按钮控制另一个窗口的开关

   ```c++
   QPushButton* btn =new QPushButton("open",this);//创建初始open按钮
   QWidget* w=new QWidget;//创建一个窗口,但不显示
   w->setWindowTitle("new window");
   //lambda表达式+if-else
   //一个connect连接新窗口的开关
   connect(btn,&QPushButton::clicked,this,[=](){
       if(btn->text()=="open")
       {
           w->show();
           btn->setText("close");
       }
       else
       {
           w->close();
           btn->setText("open");
       }
   });
   ```

   

## 总结思维导图

![image-20220207123035093](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207123035093.png)

# MainWindow

+ 在窗口中只能有一个的设置时用set,可有多个的设置时用add

## 菜单栏

​	一个菜单栏有多个菜单,一个菜单有多个菜单项

```c++
//菜单栏最多只能有一个
//创建菜单栏
QMenuBar* bar= menuBar();//创建菜单栏对象,用指针指向
setMenuBar(bar);//把菜单栏加到窗口
//创建菜单
QMenu* filemenu=bar->addMenu("文件");//添加"文件"的菜单,并用菜单指针接受
QMenu* editmenu=bar->addMenu("编辑");
//创建菜单项
QAction* newaction= filemenu->addAction("新建");//给"文件"菜单添加菜单项"新建",并使用QAction指针接受
//在菜单项之间添加分隔符,在某个菜单后面加分割线
filemenu->addSeparator();
QAction* openaction=filemenu->addAction("打开");
```

## 工具栏

```c++
//工具栏可以有多个
QToolBar* toolbar=new QToolBar(this);//创建工具栏指针
addToolBar(Qt::LeftToolBarArea,toolbar);//把工具栏加到窗口左侧,并加上枚举参数(Qt::)
//设置停靠范围,秩序在左右停靠
toolbar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);

//设置浮动
toolbar->setFloatable(false);
//设置移动
toolbar->setMovable(false);
//设置内容
toolbar->addAction(openaction);//添加菜单项
//添加分割线
toolbar->addSeparator();
toolbar->addAction(newaction);
//工具栏添加一些控件,按钮
QPushButton* btn=new QPushButton("666",this);
toolbar->addWidget(btn);
```

## 状态栏

```c++
//状态栏,最多有一个
QStatusBar* stbar= statusBar();//指向状态栏
setStatusBar(stbar);//状态栏只能有一个,用set
//放一些标签控件
QLabel* label=new QLabel("提示信息",this);
stbar->addWidget(label);//状态栏调用addWidget添加表示状态的控件
//信息放右侧
QLabel* label2=new QLabel("提示信息2",this);
stbar->addPermanentWidget(label2);
```

## 铆接部件(浮动窗口)

```c++
 //铆接部件(浮动窗口),可以有多个
QDockWidget* dockwidget=new QDockWidget("浮动窗口",this);
addDockWidget(Qt::BottomDockWidgetArea,dockwidget);//使用窗口的方法addDockWidget添加浮动窗口
dockwidget->setAllowedAreas(Qt::TopDockWidgetArea|Qt::BottomDockWidgetArea);//设置停靠范围
```

## 中心部件

```c++
//设置中心部件(文本编辑)
QTextEdit* edit=new QTextEdit(this);
setCentralWidget(edit);
```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207141740820.png" alt="image-20220207141740820" style="zoom:50%;" />

## 添加资源文件

1. 将图片文件拷贝到项目位置

   ![image-20220207181040586](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207181040586.png)

2. 右键项目,点击添加新文件

   <img src="file:///D:\qqfile\2415571314\Image\C2C\BYV5$SQ746OE%DMV7RU`00M.png" alt="img" style="zoom:50%;" />

3. 编辑source文件

   ![image-20220207181821346](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207181821346.png)

4. 添加前缀,添加文件

   ![](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207181933301.png)

5. 使用 -> QIcon(":/前缀名+文件名")

   ```c++
   ui->actionopen->setIcon(QIcon(":/images/kobe.jfif"));// QIcon(":/前缀名+文件名")
   ```

## 总结思维导图

![image-20220208190855208](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208190855208.png)

![image-20220208191022644](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208191022644.png)

# 对话框

## 模态对话框

不可以对其他窗口进行操作,阻塞   .exec()

触发对话框---QAction::triggered

```c++
#include<QDialog>
//实现点击新建,弹出对话框
connect(ui->actionnew,&QAction::triggered,[=](){
    //模态:
    QDialog dialog(this);创建对话框
    dialog.resize(400,270);//设置对话框大小
    dialog.exec();//执行后阻塞,不能操作其它窗口
    //阻塞,点击×才关闭
    qDebug()<<"模态对话框弹出";
});
```
## 非模态对话框

可以对其他窗口进行操作	.show()

```c++
#include<QDialog>
connect(ui->actionnew,&QAction::triggered,[=](){
    //非模态
    QDialog* dialog2=new QDialog(this);//防止一闪而过,创建在堆区
    dialog2->show();
    dialog2->resize(200,150);
    dialog2->setAttribute(Qt::WA_DeleteOnClose);//设置属性,使得在关闭对话框时释放对话框对象所占堆区内存
    qDebug()<<"非模态对话框弹出";//随点随打印
});
```

## 消息对话框

​	#include < QMessageBox >

1. 错误对话框

   ```c++
   QMessageBox::critical(this,"critical","错误");//指定父亲,标题,内容
   ```

   ![image-20220207192103659](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207192103659.png)

2. 信息对话框

   ```c++
   QMessageBox::information(this,"info","这里是信息内容");//指定父亲,标题,内容
   ```

   ![image-20220207192141997](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207192141997.png)

3. 提问对话框

   ```c++
          	//返回值是按键类型,利用返回值判断用户选择
   if(QMessageBox::Save==QMessageBox::question(this,"question","我是否帅气",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel)) //父亲, 标题 ,内容,按键类型(A|B),默认关联回车的按钮
   {
       qDebug()<<"保存成功";
   }
   else
   {
       qDebug()<<"已取消";
   }
   ```

   ![image-20220207192159631](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207192159631.png)

4. 警告对话框

   ```c++
    QMessageBox::warning(this,"warning","警告");
   ```

   ![image-20220207192216136](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220207192216136.png)

## 颜色对话框

QColorDialog::getColor()

```c++
#include <QColorDialog>
QColor color=QColorDialog::getColor(QColor(255,0,0));//返回用户选择的颜色
qDebug()<<"r="<<color.red()<<",g="<<color.green()<<",b="<<color.blue();
```

## 文件对话框

QFileDialog::getOpenFileName()

```c++
#include <QFileDialog>
//返回值值是选取文件的路径
QString str=QFileDialog::getOpenFileName(this,"打开文件","D:/","(*.cpp)");//父亲,标题,默认打开路径,过滤的通配符
qDebug()<<str;
```

## 字体对话框

QFontDialog::getFont()

```c++
#include <QFontDialog>
bool flag;
QFont font= QFontDialog::getFont(&flag,QFont("华文彩云",36));//返回用户选择的字体
qDebug()<<"字体:"<<font.family().toUtf8().data()<<"是否加粗:"<<font.bold()<<"是否倾斜:"<<font.italic();
```

## 总结思维导图

![image-20220208191249344](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208191249344.png)

![image-20220208191308586](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208191308586.png)

![image-20220208191329399](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208191329399.png)

# 登陆窗口布局

## 设置固定窗口大小

点击窗口,将最大和最小的长宽设置为一样

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208173018858.png" alt="image-20220208173018858" style="zoom:50%;" />

## 输入密码模式

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208173253340.png" alt="image-20220208173253340" style="zoom: 50%;" />

## 使得widget框和控件所占大小一致

使用垂直策略

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208174119460.png" alt="image-20220208174119460" style="zoom:50%;" />![image-20220208174358643](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208174358643.png)

## 布局

+ 使用label设置标签,line edit设置单行输入

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208174419097.png" alt="image-20220208174419097" style="zoom:50%;" />

+ 使用widget框住组件,进行水平,垂直,栅格布局

+ 利用弹簧使组件居中

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208174714209.png" alt="image-20220208174714209" style="zoom:50%;" />

## 固定弹簧

选择弹簧,设置固定,设置长宽

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208175129431.png" alt="image-20220208175129431" style="zoom:50%;" />

# 控件

## 按钮组

### QPushButton

+ 设置按钮图标,在资源文件中选择

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208181407995.png" alt="image-20220208181407995" style="zoom:50%;" />![image-20220208182043152](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208182043152.png)

### Tool Button工具按钮

用于显示图片,想显示文字就修改风格

+ 图片佐文字

![image-20220208182058720](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208182058720.png)

+ 突起效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208182338627.png" alt="image-20220208182338627" style="zoom:50%;" />

### Radio Button单选按钮

+ 利用group box放进一组

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208182927403.png" alt="image-20220208182927403" style="zoom:50%;" />

+ 设置默认(setchecked)选中,并且选中女性打印信息

  ```c++
  #include<QPushButton>
  #include<QDebug>
  //设置单选按钮,默认选男
  ui->radioButtonMan->setChecked(true);
  bool sex;
  //选中女性打印信息
  connect(ui->radioButtonWoman,&QPushButton::clicked,[&](){
      qDebug()<<"选中女性";
      sex=1;
  });
  ```

### Check Box多选按钮

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208185025564.png" alt="image-20220208185025564" style="zoom:50%;" />![image-20220208185334937](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208185334937.png)

```c++
//多选按钮 ,2->选中,1->半选中,0->未选中
//点击后返回状态
connect(ui->checkBox_price,&QCheckBox::stateChanged,[=](int state){
    qDebug()<<state;
});
```

![image-20220208185340193](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220208185340193.png)

## QList Widget 列表容器

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209131750885.png" alt="image-20220209131750885" style="zoom:50%;" />

```c++
//利用listwidget写诗,一个item是一行
QListWidgetItem* item=new QListWidgetItem("锄禾日当午");
//将一行内容放入(add)listwidget
ui->listWidget->addItem(item);
//一行内容可以设置(set)vh居中
item->setTextAlignment(Qt::AlignHCenter);

//一次性添加多行内容,但不能居中
//additems(QStringList)
QStringList str_list;
str_list<<"锄禾日当午"
        <<"汗滴禾下土"
        <<"谁知盘中餐"
        <<"粒粒皆辛苦";
ui->listWidget->addItems(str_list);
```

## Tree Widget 树控件

+ 创建

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209135048759.png" alt="image-20220209135048759" style="zoom:50%;" />

+ 编辑

  ```c++
  //树控件
  //设置水平头setHeaderLabels
  ui->treeWidget->setHeaderLabels(QStringList()<<"英雄"<<"英雄介绍");//匿名对象
  //创建根结点
  QTreeWidgetItem* power=new QTreeWidgetItem(QStringList()<<"力量");
  QTreeWidgetItem* swift=new QTreeWidgetItem(QStringList()<<"敏捷");
  QTreeWidgetItem* wise=new QTreeWidgetItem(QStringList()<<"智力");
  //添加根结点到树控件
  ui->treeWidget->addTopLevelItem(power);
  ui->treeWidget->addTopLevelItem(swift);
  ui->treeWidget->addTopLevelItem(wise);
  //追加子结点
  //1.
  QStringList hero1;
  hero1<<"猪八戒"<<"好吃懒做";
  QTreeWidgetItem* power_hero_1=new QTreeWidgetItem(hero1);//用qstringlist创建树控件的item
  power->addChild(power_hero_1);//将item添加到power根结点下
  
  QStringList hero2;
  hero2<<"孙悟空"<<"打怪厉害";
  QTreeWidgetItem* power_hero_2=new QTreeWidgetItem(hero2);
  power->addChild(power_hero_2);
  //2.
  QStringList hero3;
  hero3<<"娜可露露"<<"骑鸟打架";
  QTreeWidgetItem* swift_hero_1=new QTreeWidgetItem(hero3);
  swift->addChild(swift_hero_1);
  
  QStringList hero4;
  hero4<<"阿珂"<<"背后偷袭";
  QTreeWidgetItem* swift_hero_2=new QTreeWidgetItem(hero4);
  swift->addChild(swift_hero_2);
  //3.
  QStringList hero5;
  hero5<<"诸葛亮"<<"神机妙算";
  QTreeWidgetItem* wise_hero_1=new QTreeWidgetItem(hero5);
  wise->addChild(wise_hero_1);
  
  QStringList hero6;
  hero6<<"韩信"<<"多多益善";
  QTreeWidgetItem* wise_hero_2=new QTreeWidgetItem(hero6);
  wise->addChild(wise_hero_2);
  ```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209135512953.png" alt="image-20220209135512953" style="zoom:50%;" />

## Table Widget 表格控件

+ 创建

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209141509085.png" alt="image-20220209141509085" style="zoom:50%;" />

+ 编辑

  ```c++
  //设置列数
  ui->tableWidget->setColumnCount(3);
  //设置水平表头
  ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"性别"<<"年龄");
  //设置行数
  ui->tableWidget->setRowCount(5);
  
  //设置正文
  //ui->tableWidget->setItem(0,0,new QTableWidgetItem("亚瑟"));
  
  QStringList name_list;//姓名列表
  name_list<<"亚瑟"<<"孙悟空"<<"赵云"<<"张飞"<<"关羽";
  
  QList<QString> sex_list;//性别列表
  sex_list<<"男"<<"女"<<"男"<<"女"<<"男";
  
  QList<QString> age_list;//年龄列表
  age_list<<QString::number(18)<<QString::number(145)<<QString::number(500)<<QString::number(458)<<QString::number(546);
  //遍历每行
  for(int i=0;i<5;i++)
  {
      int column=0;//改变列数
      					//传入坐标与表格item的内容
      ui->tableWidget->setItem(i,column++,new QTableWidgetItem(name_list[i]));
      ui->tableWidget->setItem(i,column++,new QTableWidgetItem(sex_list[i]));
      ui->tableWidget->setItem(i,column++,new QTableWidgetItem(age_list[i]));
  }
  ```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209141824700.png" alt="image-20220209141824700" style="zoom:50%;" />

## 其它控件

### Scrool Area 卷轴

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209143045436.png" alt="image-20220209143045436" style="zoom:50%;" />

### Tool Box 

+ 创建

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209143622869.png" alt="image-20220209143622869" style="zoom:50%;" />

+ 编辑标题

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209143806211.png" alt="image-20220209143806211" style="zoom: 50%;" />

  

+ 插入新折叠

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209143937071.png" alt="image-20220209143937071" style="zoom:50%;" />

+ 添加内容

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209144155179.png" alt="image-20220209144155179" style="zoom:50%;" />

### Tab Widget网页

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209144741783.png" alt="image-20220209144741783" style="zoom:50%;" />

### Stacked Widget 切换页面

+ 创建

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209150809047.png" alt="image-20220209150809047" style="zoom:50%;" />

+ 连接按钮与每个页面

  ```c++
  //设置初始页面
  ui->stackedWidget->setCurrentIndex(0);
  //栈控件的使用
  //scroll
  //实现点击按钮切换页面
  connect(ui->btn_scroll,&QPushButton::clicked,[=](){
  	ui->stackedWidget->setCurrentIndex(0);//切换页面
  });
  connect(ui->btn_tool,&QPushButton::clicked,[=](){
  	ui->stackedWidget->setCurrentIndex(1);
  });
  connect(ui->btn_tab,&QPushButton::clicked,[=](){
  	ui->stackedWidget->setCurrentIndex(2);
  });
  ```

+ 插入新页面

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209151122505.png" alt="image-20220209151122505" style="zoom:50%;" />

+ 更改按钮对象的名称,方便编辑

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209151221240.png" alt="image-20220209151221240" style="zoom:50%;" />

### Combo Box 下拉框

+ 创建

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209152658675.png" alt="image-20220209152658675" style="zoom:50%;" />

+ 点击按钮选中某个内容

  ```c++
  //向下拉框中添加内容
  ui->comboBox->addItem("奔驰");//0
  ui->comboBox->addItem("宝马");//1
  ui->comboBox->addItem("保时捷");//2
  
  //点击按钮选中保时捷
  connect(ui->btn_porsche,&QPushButton::clicked,[=](){
      ui->comboBox->setCurrentIndex(2);
      ui->comboBox->setCurrentText("保时捷");
  });
  ```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209152834943.png" alt="image-20220209152834943" style="zoom:33%;" />

### Qlabel

+ 显示图片

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220209165400447.png" alt="image-20220209165400447" style="zoom:50%;" />

+ 显示动图

  ```c++
  #include<QMovie>
  //label设置动图
  QMovie* movie=new QMovie(":/images/53e4f604ec71bb0e4477161783725275.gif");//创建qmovie对象
  ui->lb_movie->setMovie(movie);//在窗口的标签中设置动画
  movie->start();//播放动画
  ```

  

# 事件

## 自定义控件封装

### 创建Qt设计师界面类

<img src="file:///D:\qqfile\2415571314\Image\C2C\WOA4X4I`EZD4$EM%]G[Q`IE.png" alt="img" style="zoom:50%;" />

<img src="file:///D:\qqfile\2415571314\Image\C2C\RZ`77QJV0XBJ5NOORV7{Q~8.png" alt="img" style="zoom:50%;" />

+ 获得.h.cpp.ui文件

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210132146885.png" alt="image-20220210132146885" style="zoom:50%;" />![img](file:///D:\qqfile\2415571314\Image\C2C\O7CPN8QEFGLFO[ZNA8RL`I8.png)



+ 在新ui文件中添加两个控件

  <img src="file:///D:\qqfile\2415571314\Image\C2C\O7CPN8QEFGLFO[ZNA8RL`I8.png" alt="img" style="zoom:50%;" />

+ 在旧的ui文件中加上widget,进行提升

  <img src="file:///D:\qqfile\2415571314\Image\C2C\@]BGTEQV9~_376RS%BP1FIT.png" alt="img" style="zoom:50%;" />

+ 修改提升的类名

  <img src="file:///D:\qqfile\2415571314\Image\C2C\S@A1B@G0~HKV@KEGZ@$P~E2.png" alt="img" style="zoom: 33%;" />

### 连接两个组件

使得相互影响

```c++
//spin box增减,Qslider跟着移动
connect(ui->spinBox,&QSpinBox::valueChanged,ui->horizontalSlider,&QSlider::setValue);
//Qslider移动,spin box随之增减
connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
```

### 关联两个按钮与组合起来的控件

+ 在SmallWidget类中添加成员函数,实现设置和获得组件的值

  ```c++
  //.h中的声名
  void set_num(int num);
  int get_num();
  //.cpp中的实现
  void SmallWidget::set_num(int num)
  {
      ui->spinBox->setValue(num);
  }
  int SmallWidget::get_num()
  {
      return ui->spinBox->value();
  }
  ```

+ 连接按钮和SmallWidget类的成员函数

  ```c++
  //点击获取,获取控件当前的值
  connect(ui->btn_get,&QPushButton::clicked,[=](){
      qDebug()<<ui->small_widget->get_num();//调用大窗口里的小窗口的get_num函数
  });
  //设置到一半
  connect(ui->btn_set,&QPushButton::clicked,[=](){
      ui->small_widget->set_num(50);
  });
  ```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210133252288.png" alt="image-20220210133252288" style="zoom:50%;" />

### 自定义封装界面类思维导图

![image-20220210202841240](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210202841240.png)

## 鼠标事件

### 进入事件,离开事件

+ 放置标签捕获鼠标创建自己的标签类MyLabel

```c++
//mylabel.h中的声名
void enterEvent(QEnterEvent *);//鼠标进入事件
void leaveEvent(QEvent *);//鼠标离开事件
```

```c++
//mylabel.cpp中的实现
void MyLabel::enterEvent(QEnterEvent *)//鼠标进入事件
{
    qDebug()<<"鼠标进入";
}
void MyLabel::leaveEvent(QEvent *)//鼠标离开事件
{
    qDebug()<<"鼠标离开";
}
```

### 点击释放移动事件

+ ev->buttons()&Qt::LeftButton
+ ev->position()
+ ev->button()==Qt::LeftButton

```c++
//mylabel.h中的声名
virtual void mouseMoveEvent(QMouseEvent *ev) ;//鼠标移动
virtual void mousePressEvent(QMouseEvent *ev) ;//鼠标按下
virtual void mouseReleaseEvent(QMouseEvent *ev) ;//鼠标释放
```

```c++
//mylabel.cpp中的实现
//鼠标移动
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(ev->buttons()&Qt::LeftButton)//判断持续的状态,当持续按下左键
    {
        QString s=QString("鼠标移动到了x=%1  y=%2 ,globalX=%3 globalY=%4").arg(ev->position().x()).arg(ev->position().y()).arg(ev->globalPosition().x()).arg(ev->globalPosition().y());//格式化字符串
        qDebug()<<s;//输出当前坐标
    }
}
//鼠标按下
void MyLabel::mousePressEvent(QMouseEvent *ev)
{
       //普通x基于标签,global基于屏幕
      //当鼠标左键按下提示信息
    if(ev->button()==Qt::LeftButton)//当按下左键
    {
        QString s=QString("鼠标按下了x=%1  y=%2 ,globalX=%3 globalY=%4").arg(ev->position().x()).arg(ev->position().y()).arg(ev->globalPosition().x()).arg(ev->globalPosition().y());
        qDebug()<<s;
    }
}
//鼠标释放
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)//从左键释放
    {
        QString s=QString("鼠标在x=%1  y=%2 ,globalX=%3 globalY=%4释放了").arg(ev->position().x()).arg(ev->position().y()).arg(ev->globalPosition().x()).arg(ev->globalPosition().y());
        qDebug()<<s;
    }
}
```

### 捕获鼠标移动

```c++
 setMouseTracking(true);//捕获鼠标移动
```

### 鼠标事件思维导图

![image-20220210203007487](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210203007487.png)

## 定时器--QTimer

### 利用定时器事件

+ 比较麻烦

+  timerEvent(QTimerEvent *ev)

+ QString::number()将数字转成QString

```c++
//.h
#include <QWidget>
public:
    int id_1;//定时器1的唯一标识
    int id_2;//定时器2的唯一标识
    void timerEvent(QTimerEvent *ev);
```

```c++
//.cpp

//重写定时器事件
id_1=startTimer(1000);//参数代表间隔
id_2=startTimer(2000);//返回值是定时器的唯一标识

void Widget::timerEvent(QTimerEvent *ev)
{
    //判断是哪个定时器
    if(ev->timerId()==id_1)
    {
        static int num=1;
        ui->label_2->setText(QString::number(num++));
    }
    if(ev->timerId()==id_2)
    {
        static int num2=1;
        ui->label_3->setText(QString::number(num2++));
    }

}
```

### 利用定时器类

```c++
#include<QTimer>
QTimer* timer=new QTimer(this);//创建定时器对象,并添加到对象树上
//启动定时器
timer->start(100);//间隔0.1秒,发送信号,进行connect
//监听timeout信号
connect(timer,&QTimer::timeout,[=](){
    static double num=10;
    ui->label_4->setText(QString::number(num));
    num-=0.1;
});
```

### 点击两个按钮开始或暂停计时

```c++
//定时器的第二种方式
QTimer* timer=new QTimer(this);
//启动定时器
//点击开始按钮,开始计时
connect(ui->btn_start,&QPushButton::clicked,this,[=](){
    timer->start(100);
});
//监听timeout信号
connect(timer,&QTimer::timeout,this,[=](){
    static double num=10;
    ui->label_4->setText(QString::number(num)+"s");
    num-=0.1;
});
//点击暂停按钮,暂停计时
connect(ui->btn_pause,&QPushButton::clicked,this,[=](){
    timer->stop();
});
```

### 定时器思维导图

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210202741706.png" alt="image-20220210202741706" style="zoom: 67%;" />

## 事件分发与过滤

### 事件分发

+ static_cast<QMouseEvent*>(e) 静态类型转换
+ 不建议用事件分发做拦截操作
+ e->type()判断事件类型

```c++
//.h
//通过event事件分发器,拦截鼠标按下事件
bool event(QEvent*e);
```

```c++
//.cpp
bool MyLabel::event(QEvent*e)
{
    //如果事件是鼠标按下
    if(e->type()==QEvent::MouseButtonPress)//如果是鼠标的摁下,在event事件分发中做拦截
    {
        QMouseEvent* ev= static_cast<QMouseEvent*>(e);//静态转换,将QEvent*->QMouseEvent*
        QString s=QString("event鼠标按下了x=%1  y=%2 ,globalX=%3 globalY=%4").arg(ev->position().x()).arg(ev->position().y()).arg(ev->globalPosition().x()).arg(ev->globalPosition().y());
        qDebug()<<s;
        return true;//表示用户自己处理这个事件,不在向下分发
    }
    //其它事件交给父类处理
    return QLabel::event(e);
}
```

### 事件过滤器

在程序将事件分发到事件分发器之前,可以利用过滤器拦截

1. 给控件安装事件过滤器

   ```c++
   //.h
   bool eventFilter(QObject* ,QEvent* );//声名事件过滤器成员函数
   //.cpp
   ui->label->installEventFilter(this);//给标签安装事件过滤器
   ```

2. 重写eventfilter事件

   ```c++
   bool Widget::eventFilter(QObject* obj,QEvent* e)
   {
       if(obj==ui->label)//如果对象是标签
       {
           if(e->type()==QEvent::MouseButtonPress)//如果事件是按压鼠标
           {
               QMouseEvent* ev= static_cast<QMouseEvent*>(e);//静态转换,将QEvent*->QMouseEvent*
               QString s=QString("filter鼠标按下了x=%1  y=%2 ,globalX=%3 globalY=%4")//表示拦截
                   	.arg(ev->position().x()).arg(ev->position().y()).arg(ev->globalPosition().x()).arg(ev-						>globalPosition().y());
               qDebug()<<s;
               return true;//表示用户自己处理这个事件,不在向下分发
           }
       }
       //其它事件交给父亲
       return QWidget::eventFilter(obj,e);
   }
   ```

### 思维导图

![image-20220210203104331](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210203104331.png)

![image-20220210203137161](C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220210203137161.png)

## 绘图事件



+ 绘图事件---void paintEvent(QPaintEvent*)
+ 声名画家对象,指定绘图设备---QPainter painter(this)

```c++
//重写绘图事件,系统自动调用
void Widget::paintEvent(QPaintEvent*)
{
    //画笔
    QPen pen(QColor(255,0,0));//创建画笔
    pen.setWidth(5);//设置画笔
    pen.setStyle(Qt::PenStyle::DotLine);
    //画刷填充颜色
    QBrush brush(Qt::cyan);//设置画刷颜色,传入枚举值
    brush.setStyle(Qt::BrushStyle::Dense7Pattern);//画刷团风格
    //让画家使用画刷

    //实例化画家对象
    QPainter painter(this);//this指定在哪绘图,在当前窗口画
    //为画家设置笔和刷子
    painter.setPen(pen);
    painter.setBrush(brush);
    //画线
    painter.drawLine(QPoint(0,0),QPoint(100,100));
    //画椭圆
    painter.drawEllipse(QPoint(100,100),50,50);
    //画矩形
    painter.drawRect(QRect(100,100,200,150));
    //画文字
    painter.drawText(QRect(200,200,200,150),"好好学习,天天向上");
}

```

+ 思维导图

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220211130820181.png" alt="image-20220211130820181" style="zoom:67%;" />

### QPainter高级设置

+ 抗锯齿,效率低---setRenderHint(QPainter::Antialiasing)
+ 移动画家---translate
+ 标记位置---save()
+ 返回位置---restore()

```c++
QPainter p(this);
p.drawEllipse(QPoint(100,50),50,50);
//设置,抗锯齿能力,效率低
p.setRenderHint(QPainter::Antialiasing);
p.drawEllipse(QPoint(200,50),50,50);


//draw a rectangle
p.drawRect(QRect(20,20,50,50));
//move the painter
p.translate(100,0);

p.save();// flag the position
p.drawRect(QRect(20,20,50,50));
p.translate(100,0);

p.restore();// return to the flag
p.drawRect(QRect(20,20,50,50));
```

### 手动调用绘图事件

+ 手动调用绘图事件,用update更新

+ 点击按钮,移动图片

  ```c++
  
  //声名数据成员
  public:
      int posx;
  //连接按钮与数据成员改变,并手动调用事件
  connect(ui->btn_move,&QPushButton::clicked,[=](){
      //手动调用绘图事件,用update更新
      posx+=20;
      update();
  });
  ```

+ 点击按钮图片移动,点击暂停图片停止,超出范围重新开始

  ```c++
  QTimer* t=new QTimer(this);//创建计数器对象
  //连接按钮与按钮标签的改变,与计数器的开始与暂停
  connect(ui->btn_move,&QPushButton::clicked,[=](){
      if(ui->btn_move->text()=="移动")
      {
          t->start(100);//0.1秒就移动一次
          ui->btn_move->setText("暂停");
      }
      else
      {
          t->stop();
          ui->btn_move->setText("移动");
      }
  
  });
  //连接计数器与图片位置的改变,并手动调用绘图事件
  connect(t,&QTimer::timeout,[=](){
      posx+=10;
      update();
  });
  ```

+ 绘图事件的内容

  ```c++
  QPainter p(this);
  //超出屏幕,从0开始
  if(posx>this->width())
  {
      posx=0;
  }
  p.drawPixmap(posx,0,QPixmap(":/new/prefix1/photos/kobe.jfif"));
  ```

## 绘图设备

+ 都是保存到硬盘上
+ 先创建设备,再创建画家在设备上画
+ QWidget也是绘图设备

### QPixmap

```c++
#include<QPixmap>
//draw on pixmap
QPixmap pm(300,300);//创建pixmap,并设定大小
QPainter p(&pm);//为画家指定设备
p.setPen(QPen(QColor(Qt::cyan)));
p.drawEllipse(QPoint(150,150),50,50);
//save
pm.save("E:/pixmap.png");
```

### QImage

+ 选择颜色---QImage::Format_RGB32

```c++
#include<QImage>
//Qimage
QImage img(300,300,QImage::Format_RGB32);//可以对像素访问
img.fill(Qt::white);//填充底色
QPainter p(&img);//为画家指定设备
p.setPen(QPen(QColor(Qt::cyan)));
p.drawEllipse(QPoint(150,150),50,50);

img.save("E:/Qimage.png");//保存图片
```

+ 可以直接对像素访问---setPixel()

```c++
//重写绘图事件
void Widget::paintEvent(QPaintEvent*)
{
    //对image像素修改
    QImage img;
    img.load(":/picture/rbt.jfif");
    QPainter p(this);//在当前窗口绘图
    //修改像素点
    for(int i=50;i<100;i++)
    {
        for(int j=50;j<100;j++)
        {
            QRgb rgb_value=qRgb(255,0,0);
            img.setPixel(i,j,rgb_value);
        }
    }
    p.drawImage(0,0,img);
}
```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220211144546321.png" alt="image-20220211144546321" style="zoom:50%;" />

### QPicture

+ 不是用来画画的,用来记录和重现绘图指令

+ 记录

```c++
#include<QPicture>
//Qpicture记录和重现绘图指令
QPicture pic;
QPainter p;
p.begin(&pic);//开始在pic作画
p.setPen(QPen(QColor(Qt::red)));
p.drawEllipse(QPoint(150,150),50,50);
p.end();//结束作画
```

+ 保存

```c++
//保存到磁盘
pic.save("E:/picture.zt");//无法打开
```

+ 利用QPainter.drawPicture重现

```c++
//重现Qpicture的绘图指令
QPainter p(this);
QPicture pic;
pic.load("E:/picture.zt");
p.drawPicture(0,0,pic);
```

## 文件读写

### QFile文件读写操作

+ 读操作,默认支持编码格式
+ 打开文件对话框---QFileDialog::getOpenFileName
+ readAll()
+ readLine()
+ atEnd()

```c++
//点击选取文件按钮,弹出文件对话框
// QString getOpenFileName(QWidget *parent = nullptr, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Options options = Options())
connect(ui->pushButton,&QPushButton::clicked,[=](){
    
    QString path=QFileDialog::getOpenFileName(this,"打开文件","C:/Users/王新超/Desktop");
    ui->lineEdit->setText(path);//把路径名称放到lineedit里

    //读取内容放到textedit里
    QFile file(path);//创建文件对象,参数是读取的文件路径
    file.open(QIODevice::ReadOnly);//设置打开方式
    QByteArray ba;
    ba=file.readAll();//一次全读取完
    
    //按行读
    QByteArray ba;
    while(!file.atEnd())
    {
        ba+=file.readLine();
    }
    
    //设置打开方式
    //将读取的数据放入textedit里
    ui->textEdit->setText(ba.data());
});

```

+ 写操作

```c++
//写入
//设置打开方式
file.open(QIODevice::Append);//追加方式写
file.write("45465456454645656");//传入QString
file.close();
```

### QFileInfo读取文件信息

```c++
//QFileInfo读取文件信息
QFileInfo info(path);//创建对象,传入文件路径
qDebug()<<"文件大小:"<<info.size()
        <<"\n后缀名:"<<info.suffix()
        <<"\n文件名称:"<<info.fileName()
        <<"\n文件路径:"<<info.filePath()
        <<"\n创建日期:"<<info.birthTime().toString("yyyy/MM/dd hh:mm:ss")//格式化打印Qtime
        <<"\n最后修改日期:"<<info.lastModified().toString("yyyy-MM-dd hh:mm:ss");
```

# 翻金币案例

## 基本配置

### 创建项目,添加资源

+ 创建MainWindow,在github上下载资源文件
+ 将资源文件添加到项目

### 主界面基本配置

+ 配置主场景

```c++
//设置固定大小
this->setFixedSize(400,600);
//设置图标
this->setWindowIcon(QIcon(":/resource/Coin0001.png"));
//设置标题
this->setWindowTitle("翻金币");
```

+ 去掉工具栏,状态栏
+ 添加菜单栏,添加退出选项

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220212133804724.png" alt="image-20220212133804724" style="zoom:50%;" />

+ 实现退出选项,信号是triggered

```c++
//退出按钮实现
connect(ui->actionquit,&QAction::triggered,[=](){
    this->close();
});
```

+ 设置背景图片---添加绘图事件

```c++
#include<QPainter>
#include<QPixmap>
//重写绘图事件
void MainScene::paintEvent(QPaintEvent*)
{
    QPainter p(this);//为画家指定画图设备为当前窗口
    QPixmap pixmap(":/resource/MenuSceneBg.png");//创建pixmap对象,并加载图片
    			//指定从窗口(0,0)点开始,画窗口大小的图(拉伸)
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);//只传(0,0)图片占不满
}
```

+ 画一个背景上的图标,仍在绘图事件中

```c++
//画一个背景上的图标
pixmap.load(":/resource/Title.png");//重写加载图标图片
pixmap=pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);//对图标进行缩放
p.drawPixmap(10,30,pixmap);//从(10,30)点开始作画
```

+ 效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220212142343338.png" alt="image-20220212142343338" style="zoom: 67%;" />

### 添加开始按钮

+ 创建mypushbutton类

```c++
#include<QPushButton>
class MyPushButton : public QPushButton
{
public:
                //常规图片需要传进,默认无按压图片
    MyPushButton(QString normalImg,QString pressImg="");//重写构造函数
    //保存用户传入的默认显示路径和按下后显示的图片路径
     QString normalImgPath;
     QString pressImgPath;
};
```

```c++
//声名中有默认参数,实现不写默认参数
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
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
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
```

+ 设置按钮

```c++
//创建开始按钮
MyPushButton* btn_start=new MyPushButton(":/resource/MenuSceneStartButton.png");//创建按钮
btn_start->setParent(this);//添加到窗口
btn_start->move(this->width()*0.5-btn_start->width()*0.5,this->height()*0.7);//设置到水平中心,距顶端0.7
```

+ 添加按钮后效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220212213552885.png" alt="image-20220212213552885" style="zoom:67%;" />

### 开始按钮动态跳跃特效

```c++
//只显示新添加的
class MyPushButton : public QPushButton
{
    friend  MainScene;//声名MainScene为友元
   	enum direction{UP,DOWN};//声名私有枚举值,友元后使得MainScene可访问
public:
    void zoom_down();
    void zoom_up();
    void zoom(direction d);//一个函数实现向上或向下跳
};
```

+ 两个函数分别实现向上向下跳
  + setEasingCurve
  + setDuration
  + setStartValue
  + setEndValue

```c++
#include<QPropertyAnimation>
//向下跳
void MyPushButton::zoom_down()
{
    //创建动画特效对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象
    //设置动画的时间间隔
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
```

```c++
//向上跳
void MyPushButton::zoom_up()
{
    //创建动画特效对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象
    //设置动画的时间间隔
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
```

+ 一个成员函数实现上下跳

```c++
void MyPushButton::zoom(direction d)
{
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");//用按钮初始化对象
    animation->setDuration(200);//设置动画的时间间隔
    if(d==MyPushButton::UP)//判断传入的枚举值
    {
        //起始位置,这些位置都是为跳动之前的位置,+表示向下
        animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
        //结束位置
        animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    }
    else
    {
        //起始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //结束位置
        animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    }
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

```

+ 主窗口中连接

```c++
#include"mypushbutton.h"
connect(btn_start,&QPushButton::clicked,[=](){
    //弹起特效
    btn_start->zoom(MyPushButton::DOWN);
    btn_start->zoom(MyPushButton::UP);
});
```

## 选择界面配置

### 创建场景类

+ 创建新的选择窗口类---ChooseLevelScene
+ 在MainScene中创建数据成员

```c++
ChooseLevelScene* choose_scene=nullptr;//添加选择场景
```

+ 在主场景中创建

```c++
//实例化选择关卡场景
this->choose_scene=new ChooseLevelScene;//在主场景添加选择场景
```

### 窗口切换

+ 隐藏主界面,显示选择界面,实现切换效果
+ 添加延迟效果---QTimer::singleShot(time,object,lambda)
+ 在lambda中继续添加,切换窗口的内容

```c++
#include<QTimer>
//进入选择关卡场景
//延时进入选择关卡,才能看到跳动效果
connect(btn_start,&QPushButton::clicked,this,[=](){
    //弹起特效
    btn_start->zoom(MyPushButton::Down);
    btn_start->zoom(MyPushButton::Up);
    //进入选择关卡场景
    //延时进入选择关卡
    QTimer::singleShot(500,this,[=](){		//延迟0.5s后,主窗口(this)触发一个lambda表达式
        qDebug()<<"点击了开始";
        //隐藏主场景,显示选择关卡的场景
        this->hide();//隐藏主窗口
        choose_scene->show();
    });
});
```

### 界面要素

+ 在界面设置菜单栏(QMenuBar)
+ 在菜单栏上添加菜单(QMenu)
+ 在菜单里添加菜单项(QAction)
+ 触发菜单项---QAction::triggered

```c++
//配置选择关卡场景
this->setFixedSize(400,600);//大小与主界面相同
this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));
this->setWindowTitle("选择关卡场景");
//代码实现菜单栏
QMenuBar* bar=this->menuBar();//创建菜单栏
this->setMenuBar(bar);//将菜单栏设置到选择关卡界面
//创建开始菜单
//添加声名返回声名
//注意区分 菜单栏(QMenuBar)   菜单(QMenu)   菜单项(QAction)
QMenu* menu_start=bar->addMenu("开始");
QAction* menu_quit=menu_start->addAction("退出");//创建菜单项
//点击退出菜单项,实现退出
connect(menu_quit,&QAction::triggered,[=](){
    this->close();
});
```

### 界面背景

```c++
//重写绘图事件
void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    //设置背景
    QPainter p(this);//指定画家的绘图设备为此窗口
    QPixmap pixmap(":/resource/OtherSceneBg.png");//创建pixmap对象,加载图片
    //从(0,0)宽为画窗宽,高为窗口高的pixmap
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //画一个背景上的图标
    pixmap.load(":/resource/Title.png");
    p.drawPixmap(0.5*(this->width()-pixmap.width()),0.05*(this->height()-		pixmap.height()),pixmap.width(),pixmap.height(),pixmap);
}
```

### 返回按钮

#### 添加返回按钮

```c++
//返回按钮
MyPushButton* btn_back=new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");//创建按钮,加载两种情况的图片
btn_back->setParent(this);//添加到当前窗口
btn_back->move(this->width()-btn_back->width(),this->height()-btn_back->height());//设置在右下角
```

#### 实现图片变化效果

​	实现点击返回按钮后图片变为按压状态,释放按钮后图片变回正常

+ 实现改变图片成员函数

```c++
//MyPushButton新增成员
enum Back{Normal,Pressed};
void transfer(Back);
```

```c++
void MyPushButton::transfer(Back back)//更换按钮图片的成员函数实现
{
    if(back==MyPushButton::Normal)
    {
        QPixmap pix;
        bool ret=pix.load(this->normalImgPath);
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
    if(back==MyPushButton::Pressed)
    {
        QPixmap pix;
        bool ret=pix.load(this->pressImgPath);
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
}
```

+ 重写鼠标按下,释放事件

```c++
//重写鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent*ev )
{
    //拦截
    if(this->pressImgPath!="")//传入的按下图片不为空,使得第一个开始按钮不会出现图片转换效果
    {
         this->transfer(this->Pressed);
    }
    //让父类执行其它内容
    return QPushButton::mousePressEvent(ev);

}
//重写鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent*ev)
{
    if(this->pressImgPath!="")
    {
         this->transfer(this->Normal);
    }
    return QPushButton::mouseReleaseEvent(ev);

}
```

#### 实现返回主页面效果

+ 给ChooseLevelScene自定义back信号

```c++
//写一个自定义信号,告诉主场景,点击了返回
signals:
    void back();//不需要实现
```

+ 在MainScene监听ChooseLevelScene的back信号

```c++
connect(choose_scene,&ChooseLevelScene::back,this,[=](){//监听到返回信号,实现场景切换,连接一次即可
    choose_scene->hide();//隐藏ChooseLevelScene
    this->show();//重新显示MainScene
});
```

+ 在ChooseLevelScene中触发back信号

```c++
//点击返回,切换到主场景
connect(btn_back,&QPushButton::clicked,this,[=](){
    emit this->back();//emit触发信号
});
```

+ 延迟触发back信号,实现延迟返回

```c++
//点击返回
connect(btn_back,&QPushButton::clicked,this,[=](){
    qDebug()<<"点击了返回按钮";
    QTimer::singleShot(400,this,[=](){
        emit this->back();
    });
});
```

### 选择关卡按钮

+ 取模和除法加一个for循环生成二维矩阵
+ 通过label给按钮上添加数字,并文本居中

```c++
//创建选择关卡按钮
for(int i=0;i<20;i++)//通过取模和除法实现一个for循环生成二维矩阵
{
    MyPushButton* btn_level=new MyPushButton(":/resource/LevelIcon.png");//创建按钮
    btn_level->setParent(this);//设置父亲
    
    //初始横轴坐标
    int x=65;
    int y=150;
    //每次增加的量
    x+=70*(i%4);//横向间距70
    y+=65*(i/4);//纵向间距65
    btn_level->move(x,y);
    
    
    // 通过label给按钮上添加数字
    QLabel* label=new QLabel;
    label->setParent(this);
    label->setFixedSize(btn_level->width(),btn_level->height());//大小设置为与按钮一样大
    label->setText(QString::number(i+1));//给便签加上序号
    label->move(x,y);//移动到按钮所在位置,左上对齐,按钮本质大小也是一个矩形框
    label->setAlignment(Qt::AlignCenter);//让标签上的数字居中,即在按钮中心
}
```

+ 设置鼠标穿透

```c++
//在for循环里
label->setAttribute(Qt::WA_TransparentForMouseEvents);//设置让鼠标进行穿透,点击后穿透标签点击按钮
```

+ 连接每个按钮

```c++
//在for循环里
//使得点击按钮打印其上数字
connect(btn_level,&MyPushButton::clicked,[=](){//连接每个按钮
    qDebug()<<QString("点击的是第%1关").arg(i+1);
});
```

+ 效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220213195539799.png" alt="image-20220213195539799" style="zoom:67%;" />

## 具体游戏界面

### 基本场景设置

+ 创建游戏场景PlayScene类

```c++
class PlayScene : public QMainWindow
{
public:
    PlayScene(int level_num);
    int level_index;//记录所选关卡
    void paintEvent(QPaintEvent*);
signals:
    void back();
};
```

+ 重写构造函数

```c++
PlayScene::PlayScene(int level_num)
{
    this->level_index=level_num;
    qDebug()<<QString("进入了第%1关").arg(level_num);
    //初始化游戏场景
    this->setFixedSize(400,650);

    this->setWindowTitle(QString("第%1关").arg(this->level_index));//窗口标题
    this->setWindowIcon(QPixmap(":/resource/Coin0001.png"));//图标

    //代码实现菜单栏
    QMenuBar* bar=this->menuBar();//创建菜单栏
    this->setMenuBar(bar);//将菜单栏设置到选择关卡界面
    //创建开始菜单
    //添加声名返回声名
    //注意区分 菜单栏(QMenuBar)   菜单(QMenu)   菜单项(QAction)
    QMenu* menu_start=bar->addMenu("开始");
    QAction* action_quit=menu_start->addAction("退出");//创建菜单项
   //点击退出菜单项,实现退出
    connect(action_quit,&QAction::triggered,this,[=](){
        this->close();
    });
}
```

+ 重写绘图事件设置背景

```c++
//重写绘图事件
void PlayScene::paintEvent(QPaintEvent*)
{
    //设置背景
    QPainter p(this);//指定画家的绘图设备为此窗口
    QPixmap pixmap(":/resource/PlayLevelSceneBg.png");//创建pixmap对象,加载图片
    //从(0,0)宽为画窗宽,高为窗口高的pixmap
    p.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //画一个背景上的图标
    pixmap.load(":/resource/Title.png");
    pixmap=pixmap.scaled(0.5*pixmap.width(),0.5*pixmap.height());//赋值缩放
    p.drawPixmap(10,30,pixmap);
}
```

+ 在ChooseLevelScene类中增加PlayScene类的数据成员

```c++
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    //绘图事件
    void paintEvent(QPaintEvent*);
    //创建游戏场景
    PlayScene* playscene=nullptr;
signals:
    void back();
};
```

+ 从关卡界面进入具体游戏界面

```c++
connect(btn_level,&MyPushButton::clicked,this,[=](){//连接每个按钮
    qDebug()<<QString("点击的是第%1关").arg(i+1);
    //进入游戏场景
    this->hide();//隐藏关卡场景
    this->playscene=new PlayScene(i+1);//场景游戏场景
    this->playscene->show();//显示游戏场景
});
```

### 添加返回按钮

+ 实现点击返回按钮,延时后触发PlayScene的back信号

```c++
#include<QTimer>
#include"mypushbutton.h"

MyPushButton* btn_back=new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
btn_back->setParent(this);//添加到游戏窗口
btn_back->move(this->width()-btn_back->width(),this->height()-btn_back->height());//设置位置
//点击返回按钮,延时后返回关卡界面
connect(btn_back,&QPushButton::clicked,this,[=](){
    QTimer::singleShot(400,this,[=](){
        emit this->back();
    });
});
```

+ 关卡界面监听具体游戏界面的back信号

```c++
connect(btn_level,&MyPushButton::clicked,this,[=](){//连接每个按钮
    qDebug()<<QString("点击的是第%1关").arg(i+1);
    //进入游戏场景
    this->hide();//隐藏关卡场景
    this->playscene=new PlayScene(i+1);//场景游戏场景,点击关卡按钮才创建具体关卡游戏
    this->playscene->show();//显示游戏场景
    connect(this->playscene,&PlayScene::back,this,[=](){
        //直接释放游戏场景,使得下一次进入是重新开始
        delete this->playscene;
        this->playscene=nullptr;
        this->show();
    });
});
```

### 添加关卡号标签

```c++
#include<QLabel>
#include<QFont>

QLabel* label=new QLabel;
label->setParent(this);
label->setText(QString("Level %1").arg(this->level_index));
label->setAlignment(Qt::AlignCenter);//垂直水平居中
label->setFixedSize(175,80);
//设置字体
QFont font;
font.setFamily("华文新魏");
font.setPointSize(20);
label->setFont(font);//为标签设置字体
label->move(0,this->height()-label->height());
```

+ 效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220213195728007.png" alt="image-20220213195728007" style="zoom:67%;" />

## 金币类

### 设置金币背景

```c++
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        //绘制背景图片
        QLabel* label=new QLabel;
        QPixmap pixmap(":/resource/BoardNode.png");
        //label->setGeometry(0,0,50,50);
        label->setFixedSize(pixmap.width(),pixmap.height());
        label->setPixmap(pixmap);
        label->setParent(this);
        label->move(i*50+90,j*50+190);
    }
}
```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220214114349113.png" alt="image-20220214114349113" style="zoom:67%;" />

### 金币类内容

```c++
class MyCoin : public QPushButton//mycoin其实是一个按钮,通过设置icon,就形成金币样式
{
    Q_OBJECT
public:
        MyCoin(QString btn_img);
signals:
};
```

```c++
#include<QString>
#include<QPixmap>
#include<QDebug>
MyCoin::MyCoin(QString btn_img)//参数代表传入的是金币路径还是银币
{
    QPixmap pixmap;
    bool ret=pixmap.load(btn_img);
    if(!ret)
    {
        qDebug()<<"图片"+btn_img+"加载失败!";
        return;
    }
    this->setFixedSize(pixmap.width(),pixmap.height());//将按钮的大小设置为与金币图案相同
    this->setStyleSheet("QPushButton{border:0px;}");//无边框
    this->setIcon(pixmap);//将金币图案设置为图标
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));//将图标的大小设置为与金币图案相同
}
```

### 背景上添加金币

```c++
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        //绘制背景图片
		//略
        
   
        //在背景上添加金币图案
        MyCoin* coin=new MyCoin(":/resource/Coin0001.png");
        coin->setParent(this);
        coin->move(i*50+92,j*50+192);//微调
    }
}
```

+ 效果

  <img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220214121742292.png" alt="image-20220214121742292" style="zoom:67%;" />

## 金币银币布局

+ 给每个关卡设置默认金币银币布局
+ 利用map使得关卡号对应一个二维矩阵
+ 一个map就保存了所有关卡的布局

### 添加配置文件

```c++
class dataConfig : public QObject
{
public:
    //关卡号--->二维数组
    QMap<int, QVector< QVector<int> > >mData;
};
```

```c++
#include "dataconfig.h"
#include <QDebug>
dataConfig::dataConfig(QObject *parent) : QObject(parent)
{
    //   1->金币  0->银币
     int array1[4][4] = {{1, 1, 1, 1},
                        {1, 1, 0, 1},
                        {1, 0, 0, 0},
                        {1, 1, 0, 1} } ;

     QVector< QVector<int>> v;
     for(int i = 0 ; i < 4;i++)//将数组放进容器
     {
         QVector<int>v1;
         for(int j = 0 ; j < 4;j++)
         {

            v1.push_back(array1[i][j]);
         }
         v.push_back(v1);
     }

     mData.insert(1,v);//带上关卡号与矩阵加入map容器中

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array2[4][4] = { {1, 0, 1, 1},
                          {0, 0, 1, 1},
                          {1, 1, 0, 0},
                          {1, 1, 0, 1}} ;

     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array2[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(2,v);


///////////////////////////////////////////关卡3///////////////////////////////////////////////////////
     int array3[4][4] = {  {0, 0, 0, 0},
                           {0, 1, 1, 0},
                           {0, 1, 1, 0},
                           {0, 0, 0, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array3[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(3,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array4[4][4] = {   {0, 1, 1, 1},
                            {1, 0, 0, 1},
                            {1, 0, 1, 1},
                            {1, 1, 1, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array4[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(4,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array5[4][4] = {  {1, 0, 0, 1},
                           {0, 0, 0, 0},
                           {0, 0, 0, 0},
                           {1, 0, 0, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array5[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(5,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array6[4][4] = {   {1, 0, 0, 1},
                            {0, 1, 1, 0},
                            {0, 1, 1, 0},
                            {1, 0, 0, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array6[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(6,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array7[4][4] = {   {0, 1, 1, 1},
                            {1, 0, 1, 1},
                            {1, 1, 0, 1},
                            {1, 1, 1, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array7[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(7,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array8[4][4] = {  {0, 1, 0, 1},
                           {1, 0, 0, 0},
                           {0, 0, 0, 1},
                           {1, 0, 1, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array8[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(8,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array9[4][4] = {   {1, 0, 1, 0},
                            {1, 0, 1, 0},
                            {0, 0, 1, 0},
                            {1, 0, 0, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array9[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(9,v);


///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array10[4][4] = {  {1, 0, 1, 1},
                            {1, 1, 0, 0},
                            {0, 0, 1, 1},
                            {1, 1, 0, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array10[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(10,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array11[4][4] = {  {0, 1, 1, 0},
                            {1, 0, 0, 1},
                            {1, 0, 0, 1},
                            {0, 1, 1, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array11[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(11,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array12[4][4] = {  {0, 1, 1, 0},
                            {0, 0, 0, 0},
                            {1, 1, 1, 1},
                            {0, 0, 0, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array12[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(12,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array13[4][4] = {    {0, 1, 1, 0},
                              {0, 0, 0, 0},
                              {0, 0, 0, 0},
                              {0, 1, 1, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array13[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(13,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array14[4][4] = {    {1, 0, 1, 1},
                              {0, 1, 0, 1},
                              {1, 0, 1, 0},
                              {1, 1, 0, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array14[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(14,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array15[4][4] = {   {0, 1, 0, 1},
                             {1, 0, 0, 0},
                             {1, 0, 0, 0},
                             {0, 1, 0, 1}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array15[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(15,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array16[4][4] = {   {0, 1, 1, 0},
                             {1, 1, 1, 1},
                             {1, 1, 1, 1},
                             {0, 1, 1, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array16[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(16,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array17[4][4] = {  {0, 1, 1, 1},
                            {0, 1, 0, 0},
                            {0, 0, 1, 0},
                            {1, 1, 1, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array17[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(17,v);

///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array18[4][4] = { {0, 0, 0, 1},
                           {0, 0, 1, 0},
                           {0, 1, 0, 0},
                           {1, 0, 0, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array18[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(18,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array19[4][4] = {   {0, 1, 0, 0},
                             {0, 1, 1, 0},
                             {0, 0, 1, 1},
                             {0, 0, 0, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array19[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(19,v);
///////////////////////////////////////////关卡2///////////////////////////////////////////////////////
     int array20[4][4] = {  {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}} ;
     v.clear();
     for(int i = 0 ; i < 4;i++)
     {
          QVector<int>v1;
          for(int j = 0 ; j < 4;j++)
          {
             v1.push_back(array20[i][j]);
          }
          v.push_back(v1);
     }

     mData.insert(20,v);
}

```

### 给每个关卡布局

+ 为具体游戏场景PlayScene添加布局数组,保存当前关卡的金银币布局

```c++
class PlayScene : public QMainWindow
{
public:
    PlayScene(int level_num);
    int level_index;//记录所选关卡
    void paintEvent(QPaintEvent*);
    int layout [4][4];
};
```

+ 初始化每个关卡的laylout数组

```c++
//playscen是某个具体的关卡
dataConfig data;//创建数据对象
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        this->layout[i][j]=data.mData[this->level_index][i][j];
    }
}
```

+ 循环布局

```c++
for(int i=0;i<4;i++)
{
        for(int j=0;j<4;j++)
        {
            //绘制背景图片
            //......                   
           	QString coin_path;
            if(this->layout[i][j]==1)//   1表示创建金币
            {
                coin_path=":/resource/Coin0001.png";

            }
            if(this->layout[i][j]==0)// 0表示创建银币
            {
                coin_path=":/resource/Coin0008.png";
            }
            MyCoin* coin=new MyCoin(coin_path);
            coin->setParent(this);
            coin->move(i*50+92,j*50+192);
            }
        }
    }
```

+ 效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220214125223522.png" alt="image-20220214125223522" style="zoom:67%;" />

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220214125248830.png" alt="image-20220214125248830" style="zoom:67%;" />

## 金币翻动效果

### 金币类新增成员

```c++
#include<QTimer>
#include"playscene.h"
class MyCoin : public QPushButton
{
    friend PlayScene;
    enum Towards{Up,Down};//朝向枚举值
public:
        MyCoin(QString btn_img);//参数代表传入的是金币路径还是银币
        //
    	void change_toward();//改变当前朝向
        int pos_x;
        int pos_y;
        int toward;//记录当前朝向
        QTimer* timer_for_down;//翻成反面的定时器
        QTimer* timer_for_up;//翻成正面的定时器
        int min=1;
        int max=8;
};
```

### 初始化定时器

```c++
//初始化定时器
this->timer_for_down=new QTimer(this);
this->timer_for_up=new QTimer(this);
```

### 坐标属性赋值

```c++
//在具体游戏界面给每个金币/银币属性赋值
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        //......
		coin->pos_x=i;
		coin->pos_y=j;
    }
}
```

### 改变朝向函数实现

+ 判断当前朝向
+ 计数器开始计时
+ 修改当前朝向
+ 不要写两个if,第一个if判断完成后,修改了朝向,使得满足第二个if,使得不能将金币翻成银币

```c++
void MyCoin::change_toward()
{
    if(this->toward==MyCoin::Up)//当前为正面,则正面翻成反面
    {
        //开启定时器
        this->timer_for_down->start(30);//开始下翻定时器
        this->toward=MyCoin::Down;//改变朝向
    }
    else if(this->toward==MyCoin::Down)
    {
        this->timer_for_up->start(30);
        this->toward=MyCoin::Up;
    }
}
```

### 监听计时器

+ 利用字符串格式化与数据成员自增自减实现多图
+ 自增自减达到目标值,计数器停止
+ 在构造函数内实现连接,只连接一次,不然每次点击金币/银币都会连接

```c++
//监听正面翻反面的信号,并且翻成反面
connect(this->timer_for_down,&QTimer::timeout,this,[=](){
    QPixmap pixmap;
    QString coin_path=QString(":/resource/Coin000%1.png").arg(this->min++);
    bool ret=pixmap.load(coin_path);
    if(!ret)
    {
        qDebug()<<"图片"+coin_path+"加载失败!";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    if(this->min>this->max)//如果翻完
    {
        this->min=1;
        this->timer_for_down->stop();
    }
});
//监听反面翻正面的信号,并且翻成正面
connect(this->timer_for_up,&QTimer::timeout,this,[=](){
    QPixmap pixmap;
    QString coin_path=QString(":/resource/Coin000%1.png").arg(this->max--);
    bool ret=pixmap.load(coin_path);
    if(!ret)
    {
        qDebug()<<"图片"+coin_path+"加载失败!";
    }
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));

    if(this->min>this->max)//如果翻完
    {
        this->max=8;
        this->timer_for_up->stop();
    }
});
```

### 对每个金币/银币做监听

```c++
//在具体游戏界面,给每个金币/银币点击信号做监听
for(int i=0;i<4;i++)
{
    for(int j=0;j<4;j++)
    {
        //......
        connect(coin,&QPushButton::clicked,this,[=](){
            coin->change_toward();//点击金币/银币,实现翻转
        });
    }
}
```

### 防止翻动过快

+ 新增数据成员

```c++
class MyCoin : public QPushButton
{
	//......
public:
        //......
        bool fliping=false;//记录当是否在翻转
};
```

+ 翻转时设置为正在翻转

```c++
void MyCoin::change_toward()
{
    if(this->toward==MyCoin::Up)//当前为正面,则正面翻成反面
    {
		//......
        this->fliping=true;
    }
    else if(this->toward==MyCoin::Down)
    {
		//......
        this->fliping=true;
    }
}
```

+ 翻转完成设置为false

```c++
if(this->min>this->max)//如果翻完
{
	//......
    this->fliping=false;
}
if(this->min>this->max)//如果翻完
{
	//......
    this->fliping=false;
}
```

+ 正在翻转时进行鼠标拦截

```c++
//正在翻转时进行鼠标拦截
void MyCoin::mousePressEvent(QMouseEvent*ev)
{
    if(this->fliping)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(ev);
    }
}
```

## 四周金币翻转

### 添加新成员

```c++
class PlayScene : public QMainWindow
{
public:
	//......
    MyCoin* coins[4][4];
};
```

### 存金币

+ 将创建的金币存入当前关卡的数组中维护

```c++
this->coins[i][j]=coin;//将金币放到当前关卡的数组里,便于后期维护,内存都相同
```

### 循环翻转

```c++
int xx[]={0,1,0,-1};
int yy[]={1,0,-1,0};
connect(coin,&QPushButton::clicked,this,[=](){
    if(!coin->fliping)//防止翻动正在翻动的
    {
        //翻转中心金币
        coin->change_toward();
        this->layout[i][j]=this->layout[i][j]^1;//相应地,取反,修改二维矩阵中地值
        //延时翻转周围金币
        QTimer::singleShot(300,this,[=](){
            //翻转周围的金币
            for(int i=0;i<4;i++)
            {
                int dx=coin->pos_x+xx[i];
                int dy=coin->pos_y+yy[i];
                if(dx>=0&&dx<4&&dy>=0&&dy<4)
                {
                    this->coins[dx][dy]->change_toward();
                    this->layout[dx][dy]=this->layout[dx][dy]^1;
                }
            }
        });
    }
});
```

## 判断胜利

### 金币类新增成员

+ is_win
+ mousePressEvent

```c++
class MyCoin : public QPushButton
{
    Q_OBJECT//防止循环包含头文件(即两个类互相包含)
    enum Towards{Down,Up};
public:
		//......
        //正在翻转和已经胜利时进行鼠标拦截
        void mousePressEvent(QMouseEvent*);
        bool is_win=false;
signals:

};
```

+ 正在翻转和已经胜利时进行鼠标拦截

```c++
//正在翻转和已经胜利时进行鼠标拦截
//重写点击事件
void MyCoin::mousePressEvent(QMouseEvent*ev)
{
    if(this->fliping||this->is_win)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(ev);
    }
}
```

### 游戏界面的成员函数

+ 新增成员函数
+ 判断是否胜利
+ 把所有金币的is_win属性设置为true
+ 当金币设置为true时,无法点击金币(因为已经做了拦截)

```c++
class PlayScene : public QMainWindow
{
public:
    //......
    bool is_win();//判断是否胜利
    void set_all_coins_win();//把所有金币的is_win属性设置为true
signals:
    //......
};
```

```c++
//判断是否胜利
bool PlayScene::is_win()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(this->coins[i][j]->toward==0)//遍历改关卡的所有金币,有反面则不赢
            {
                return false;
            }
        }
    }
    return true;
}
//设置所有金币的is_win为true
void PlayScene::set_all_coins_win()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->coins[i][j]->is_win=1;
        }
    }
}
```

## 胜利图片展示

### 游戏场景新增成员

```c++
class PlayScene : public QMainWindow
{
public:
    //......
    QLabel* win_label=nullptr;//胜利标签
    void show_win_label(QLabel*);//下坠展示胜利标签
signals:
    void back();
};
```

### 构造函数中初始化

+ 在构造函数中初始化win_label
+ 不能放在其它地方初始化

```c++
this->win_label = new QLabel;
QPixmap tmpPix;
tmpPix.load(":/resource/LevelCompletedDialogBg.png");
this->win_label ->setGeometry(0,0,tmpPix.width(),tmpPix.height());
this->win_label ->setPixmap(tmpPix);
this->win_label ->setParent(this);
this->win_label ->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
```

### 封装展示成员函数

```c++
void PlayScene::show_win_label(QLabel*winLabel)//传入胜利标签
{
    QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");
   //设置时间间隔
   animation->setDuration(1000);
   //设置开始位置
   animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
   //设置结束位置
   animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
   //设置缓和曲线
   animation->setEasingCurve(QEasingCurve::OutBounce);
   //执行动画
   animation->start();
}
```

### 效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220214194044567.png" alt="image-20220214194044567" style="zoom:67%;" />

## 防止过快点击

### 封装成员函数

```c++
//设置所有金币的is_win为true
void PlayScene::set_all_coins_win()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->coins[i][j]->is_win=1;
        }
    }
}
void PlayScene::set_all_coins_unwin()
{   
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->coins[i][j]->is_win=0;
        }
    }
}
```

### 在点击后禁用所有按钮

```c++
connect(coin,&QPushButton::clicked,this,[=](){
    //点击瞬间禁用所有按钮
    this->set_all_coins_win();
    //......
});
```

### 周围金币翻完后,解开禁用

```c++
connect(coin,&QPushButton::clicked,this,[=](){
    //......
    QTimer::singleShot(300,this,[=](){                        
        for(int i=0;i<4;i++)
        {
            int dx=coin->pos_x+xx[i];
            int dy=coin->pos_y+yy[i];
            if(dx>=0&&dx<4&&dy>=0&&dy<4)
            {
                this->coins[dx][dy]->change_toward();
                this->layout[dx][dy]=this->layout[dx][dy]^1;
            }
        }
        //周围所有金币翻完,还原解禁
        this->set_all_coins_unwin();
     	//......
    });
```

## 添加音效

### 增加multimedia模块

+ 在项目文件中添加多媒体模块

```c++
QT +=multimedia
```

+ 使用时包含头文件

```c++
#include<QSoundEffect>//音效头文件
```

### 点击开始按钮的音效

+ 在主界面中准备开始按钮的音效

```c++
#include<QSoundEffect>
//准备开始按钮的音效
QSoundEffect* start_sound=new QSoundEffect;
start_sound->setSource(QUrl::fromLocalFile(":/resource/TapButtonSound.wav"));
```

+ 连接点击开始按钮的事件与音效播放

```c++
connect(btn_start,&QPushButton::clicked,this,[=](){
    start_sound->play();//点击按钮有音效
   //......
});
```

### 点击关卡音效

+ 在关卡界面中准备音效

```c++
//准备音效
QSoundEffect* level_sound=new QSoundEffect;
level_sound->setSource(QUrl::fromLocalFile(":/resource/TapButtonSound.wav"));
```

+ 连接点击事件与音效

```c++
connect(btn_level,&MyPushButton::clicked,this,[=](){//连接每个按钮
    //连接每个按钮的点击事件与音效
    level_sound->play();
    //......
});
```

### 返回按钮音效

+ 在关卡界面中准备音效

```c++
//准备返回按钮音效
QSoundEffect* back_sound=new QSoundEffect;
back_sound->setSource(QUrl("qrc:/resource/BackButtonSound.wav"));
```

+ 连接返回按钮的点击事件和音效播放

```c++
//点击返回
connect(btn_back,&QPushButton::clicked,this,[=](){
    back_sound->play();
	//......
});
```

### 金币翻转音效

+ 在游戏场景准备金币翻转音效

```c++
//准备金币翻转音效
QSoundEffect* coin_fliping_sound=new QSoundEffect;
coin_fliping_sound->setSource(QUrl("qrc:/resource/ConFlipSound.wav"));
```

+ 连接每个金币的点击事件和金币翻转音效

```c++
connect(coin,&QPushButton::clicked,this,[=](){
     //连接点击金币翻转事件与音效播放
    coin_fliping_sound->play();
    //......
}
```

### 胜利音效

+ 在游戏场景准备胜利音效

```c++
//准备胜利音效
QSoundEffect* win_sound=new QSoundEffect;
win_sound->setSource(QUrl("qrc:/resource/LevelWinSound.wav"));
```

+ 如果胜利,播放音效

```c++
if(this->is_win())//如果游戏胜利
{
    //......
    win_sound->play();
}
```

## 场景切换保持位置一致

### 主场景进入关卡场景时

+ 点击开始按钮时,设置关卡场景的矩形框为主场景矩形框

```c++
//连接开始按钮////////////////////////////////////////////////////////////////////
connect(btn_start,&QPushButton::clicked,this,[=](){
    //......
    QTimer::singleShot(500,this,[=](){
       	//......
        //设置关卡场景的矩形框为主场景矩形框
        choose_scene->setGeometry(this->geometry());//防止窗口移动
    });
});
```

### 从关卡场景返回主场景

+ 监听到选择关卡场景的自定义返回信号时,设置主场景的矩形框为选择关卡场景的矩形框

```c++
    //监听ChooseLevelScene的back信号,一次连接即可
    connect(choose_scene,&ChooseLevelScene::back,this,[=](){
        choose_scene->hide();
        this->setGeometry(choose_scene->geometry());//监听到选择关卡场景的自定义返回信号时,设置主场景的矩形框为选择关卡场景的矩形框
        this->show();
    });
```

### 从选择关卡场景到游戏场景

+  点击某个关卡的按钮时,设置游戏场景的矩形框为选择关卡的矩形框

```c++
connect(btn_level,&MyPushButton::clicked,this,[=](){//连接每个按钮
	//......
    //进入游戏场景
    this->hide();//隐藏关卡场景
    this->playscene=new PlayScene(i+1);//场景游戏场景,点击后才创建,不需要隐藏,直接释放
    playscene->setGeometry(this->geometry());//设置游戏场景的矩形框为选择关卡的矩形框
    this->playscene->show();//显示游戏场景
	//......
    });
```

### 从游戏场景到选择关卡场景

+ 监听游戏场景的返回信号,设置选择关卡的矩形框为游戏场景的矩形框位置

```c++
//监听游戏场景的返回信号,设置选择关卡的矩形框为游戏场景的矩形框位置
connect(this->playscene,&PlayScene::back,this,[=](){
    this->setGeometry(playscene->geometry());//设置选择关卡的矩形框为游戏场景的矩形框位置
    //删除所退出的游戏场景
    delete this->playscene;
    this->playscene=nullptr; 
    this->show();
});
```

# 奇思妙想

## 关卡封锁

+ 将每个游戏关卡,关卡号标签,封锁标签作为选择关卡的数据成员
+ 获取某个关卡的胜利信号后,解锁,去掉封锁标签
+ 

## 计时

## 使某些位置不放金币

+ 修改配置数据,将不放金币的地方设置为-1

```c++
int array1[4][4] = {{1, 1, 1, 1},
                    {1, 1, 0, 1},
                    {1, 0, -1, 0},
                    {1, 1, 0, 1} } ;
```

+ 在for循环里加上判断是否这个地方有金币

```c++
if(this->coin_layout[i][j]!=-1)
{
    //有金币才连接点击事件
    //才能判断输赢
}
```

+ coin_layout!=-1才设置金币
+ 判断胜利时,空缺处不计入判断

+ 效果

<img src="C:\Users\王新超\AppData\Roaming\Typora\typora-user-images\image-20220219121214091.png" alt="image-20220219121214091" style="zoom:67%;" />