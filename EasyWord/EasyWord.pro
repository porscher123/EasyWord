QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    answerscene.cpp \
    login.cpp \
    main.cpp \
    mainscene.cpp \
    mypushbutton.cpp \
    signin.cpp

HEADERS += \
    answerscene.h \
    login.h \
    mainscene.h \
    mypushbutton.h \
    signin.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    music.qrc

DISTFILES += \
    text/CET4.txt \
    text/CET6.txt \
    text/account.txt \
    text/allWords.txt \
    text/unkownWords.txt \
    userData/123.txt \
    userData/123.txt \
    userData/123456789.txt
