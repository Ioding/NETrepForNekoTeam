QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Base/File.cpp \
    Base/Log.cpp \
    Base/Path.cpp \
    Base/Singleton.cpp \
    Base/Time.cpp \
    Base/UnicodeUtil.cpp \
    main.cpp \
    opengl.cpp \
    pmdfile.cpp \
    resourcemanage.cpp

HEADERS += \
    Base/File.h \
    Base/Log.h \
    Base/Path.h \
    Base/Singleton.h \
    Base/Time.h \
    Base/UnicodeUtil.h \
    mmdfilestring.h \
    opengl.h \
    pmdfile.h \
    resourcemanage.h

FORMS += \
    opengl.ui

INCLUDEPATH += \
    external/spdlog/include \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
