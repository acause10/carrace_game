QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#THIS IS A NEW COMMMENT


SOURCES += \
    AchievementsDialog.cpp \
    Car.cpp \
    DatabaseManager.cpp \
    ExitGameDialog.cpp \
    GameOverScreen.cpp \
    GameScene.cpp \
    HighscoreDialog.cpp \
    Innerbounds.cpp \
    MainScene.cpp \
    Outterbounds.cpp \
    ReceiveAchievementDialog.cpp \
    RouteSelectionScreen.cpp \
    ShopDialog.cpp \
    Startscreen.cpp \
    UserProfile.cpp \
    checkpoint.cpp \
    main.cpp \
    mainwindow.cpp \
    obstacle.cpp \
    startline.cpp

HEADERS += \
    AchievementsDialog.h \
    Car.h \
    DatabaseManager.h \
    ExitGameDialog.h \
    GameOverScreen.h \
    GameScene.h \
    HighscoreDialog.h \
    Innerbounds.h \
    MainScene.h \
    Outterbounds.h \
    ReceiveAchievementDialog.h \
    RouteSelectionScreen.h \
    ShopDialog.h \
    Startscreen.h \
    UserProfile.h \
    checkpoint.h \
    mainwindow.h \
    obstacle.h \
    startline.h

FORMS += \
    Mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources.qrc
