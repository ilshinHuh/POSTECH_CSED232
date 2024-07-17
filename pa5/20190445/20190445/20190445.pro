QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game/block.cpp \
    game/board.cpp \
    game/game.cpp \
    main.cpp \
    ui/blockui.cpp \
    ui/gameui.cpp

HEADERS += \
    game/block.h \
    game/board.h \
    game/game.h \
    ui/blockui.h \
    ui/gameui.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
