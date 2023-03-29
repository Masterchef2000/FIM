QT += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatwindow.cpp \
    friendlist.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    memberinfo.cpp \
    myserver.cpp \
    mysocket.cpp \
    mysqldb.cpp \
    qwaiting.cpp \
    register.cpp \
    serverthread.cpp \
    serverwork.cpp \
    userwidget.cpp

HEADERS += \
    chatwindow.h \
    friendlist.h \
    login.h \
    mainwindow.h \
    memberinfo.h \
    myserver.h \
    mysocket.h \
    mysqldb.h \
    qwaiting.h \
    register.h \
    serverthread.h \
    serverwork.h \
    userwidget.h

FORMS += \
    chatwindow.ui \
    friendlist.ui \
    login.ui \
    mainwindow.ui \
    qwaiting.ui \
    register.ui \
    tcpserver.ui \
    userwidget.ui

CONFIG  += C++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    MyResource.qrc

DISTFILES += \
    finger/101_2.tif \
    finger/FP_In_C.exe \
    finger/abc.tif \
    finger/libtiff.dll
