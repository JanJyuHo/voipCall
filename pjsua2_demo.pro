TEMPLATE = app

QT += qml \
      quick \
      widgets

CONFIG += console c++11

SOURCES += \
        main.cpp \
    voipaccount.cpp \
    voipcall.cpp \
    voipstart.cpp

RESOURCES += qml.qrc

HEADERS += \
    voipaccount.h \
    voipcall.h \
    voipstart.h

TARGET = pjsua2_demo

win32 {
LIBS += -LE:\pjproject-2.9\lib \
            -lavcodec \
            -lavdevice \
            -lavfilter \
            -lavformat \
            -lavutil \
            -lpjproject-i386-Win32-vc14-Debug \
            -lpostproc \
            -lSDL2 \
            -lswresample \
            -lswscale \
            -lUser32 \
            -lOleAut32 \
            -lAdvapi32

LIBS += -LE:/pjproject-2.9/pjsip/lib/ \
-lpjsua2-lib-i386-Win32-vc14-Debug \
-lpjsua-lib-i386-Win32-vc14-Debug \
-lpjsip-ua-i386-Win32-vc14-Debug \
-lpjsip-simple-i386-Win32-vc14-Debug \
-lpjsip-core-i386-Win32-vc14-Debug

INCLUDEPATH += E:/pjproject-2.9/pjlib/include \
               E:/pjproject-2.9/pjlib-util/include \
               E:/pjproject-2.9/pjnath/include \
               E:/pjproject-2.9/pjmedia/include \
               E:/pjproject-2.9/pjsip/include

LIBS += -LE:/pjproject-2.9/pjlib/lib \
        -LE:/pjproject-2.9/pjlib-util/lib \
        -LE:/pjproject-2.9/pjnath/lib \
        -LE:/pjproject-2.9/pjmedia/lib \
        -LE:/pjproject-2.9/pjsip/lib \
        -LE:/pjproject-2.9/third_party/lib

DEPENDPATH += E:/pjproject-2.9/lib
} else {
  LIBS += $$system(make -f pj-pkgconfig.mak ldflags)
  QMAKE_CXXFLAGS += $$system(make --silent -f pj-pkgconfig.mak cflags)

  macx {
    QMAKE_CXXFLAGS += -ObjC++
  }
}


#win32:!win32-g++: PRE_TARGETDEPS += E:/pjproject-2.9/lib/pjproject-i386-Win32-vc14-Debug.lib

#INCLUDEPATH += E:/pjproject-2.9/pjlib/include
#INCLUDEPATH +=E:/pjproject-2.9/pjsip/include
#INCLUDEPATH +=E:/pjproject-2.9/pjnath/include
#INCLUDEPATH +=E:/pjproject-2.9/pjmedia/include
#INCLUDEPATH +=E:/pjproject-2.9/pjlib-util/include

#DEPENDPATH += E:/pjproject-2.9/pjlib/include
#DEPENDPATH += E:/pjproject-2.9/pjsip/include
#DEPENDPATH += E:/pjproject-2.9/pjnath/include
#DEPENDPATH += E:/pjproject-2.9/pjmedia/include
#DEPENDPATH += E:/pjproject-2.9/pjlib-util/include

QMAKE_CFLAGS_DEBUG += -MTd
QMAKE_CXXFLAGS_DEBUG += -MTd
