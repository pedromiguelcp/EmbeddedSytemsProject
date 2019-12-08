QT += qml core quick quickcontrols2 sql serialport

CONFIG += c++11

static{
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        daemon.cpp \
        daemonsinterface.cpp \
        dash.cpp \
        ddriver.cpp \
        ledstripinterface.cpp \
        main.cpp \
        music.cpp \
        network.cpp \
        uartstm.cpp

RESOURCES += qml.qrc
#LIBS += -lcurl -lcjson -lpthread
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    daemon.h \
    daemonsinterface.h \
    dash.h \
    ddriver.h \
    ledstripinterface.h \
    music.h \
    network.h \
    uartstm.h


CONFIG += disable-desktop qtvirtualkeyboard.pro
QMAKE_LIBS += -lrt
