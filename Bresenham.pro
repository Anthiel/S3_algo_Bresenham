#-------------------------------------------------
#
# Project created by QtCreator 2019-10-16T23:13:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Bresenham
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32{
    LIBS += -lGLU32\
        -lOpengl32
}

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        qcustomplot.cpp \
    glarea.cpp \
    gl_repere.cpp \
    gl_point.cpp \
    gl_segment.cpp \
    gl_bresenham.cpp \
    espaceprojectif.cpp \
    quaternion.cpp \
    aidewindow.cpp \
    versionauteurwindow.cpp

HEADERS += \
        mainwindow.h \
        qcustomplot.h \
    glarea.h \
    gl_repere.h \
    myglobject.h \
    gl_point.h \
    gl_segment.h \
    gl_bresenham.h \
    espaceprojectif.h \
    quaternion.h \
    aidewindow.h \
    versionauteurwindow.h

FORMS += \
        mainwindow.ui \
    aidewindow.ui \
    versionauteurwindow.ui

RESOURCES += \
        baseVBO.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
