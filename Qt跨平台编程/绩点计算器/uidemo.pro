QT       += core gui webenginewidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editgparules.cpp \
    edusys.cpp \
    gparules.cpp \
    main.cpp \
    mywebengineview.cpp \
    widget.cpp

HEADERS += \
    WindowCompositionAttribute.h \
    editgparules.h \
    edusys.h \
    gparules.h \
    mywebengineview.h \
    widget.h

FORMS += \
    editgparules.ui \
    edusys.ui \
    widget.ui

LIBS += -lAdvAPI32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

DISTFILES += \
    config/default.json

RC_ICONS = eyes.ico

VERSION = 1.2.77
