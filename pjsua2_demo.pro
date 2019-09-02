TEMPLATE = app

QT += qml \
      quick \
      widgets \
      multimedia \
      network \

CONFIG += console c++11

SOURCES += \
        main.cpp \
    VoipAccount.cpp \
    VoipCall.cpp \
    VoipManager.cpp

RESOURCES += qml.qrc

HEADERS += \
    VoipAccount.h \
    VoipCall.h \
    VoipManager.h

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
  macx {
    INCLUDEPATH += $$_PRO_FILE_PWD_/mac/pjproject/2.9/include \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjsip \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjmedia \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjmedia-audiodev \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjmedia-codec \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjmedia-videodev \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjnath \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjlib-util \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjsua-lib \
#                   /Users/hpp/voipCall/pjproject/2.9/include/pjsua2 \
                   $$_PRO_FILE_PWD_/mac/openssl/1.0.2s/include/openssl

    LIBS += -L$$_PRO_FILE_PWD_/mac/pjproject/2.9/lib/ \
            -lpjsua2-x86_64-apple-darwin17.7.0 \
            -lstdc++ \
            -lpjsua-x86_64-apple-darwin17.7.0 \
            -lpjsip-ua-x86_64-apple-darwin17.7.0 \
            -lpjsip-simple-x86_64-apple-darwin17.7.0 \
            -lpjsip-x86_64-apple-darwin17.7.0 \
            -lpjmedia-codec-x86_64-apple-darwin17.7.0 \
            -lpjmedia-x86_64-apple-darwin17.7.0 \
            -lpjmedia-videodev-x86_64-apple-darwin17.7.0 \
            -lpjmedia-audiodev-x86_64-apple-darwin17.7.0 \
            -lpjmedia-x86_64-apple-darwin17.7.0 \
            -lpjnath-x86_64-apple-darwin17.7.0 \
            -lpjlib-util-x86_64-apple-darwin17.7.0 \
            -lsrtp-x86_64-apple-darwin17.7.0 \
            -lresample-x86_64-apple-darwin17.7.0 \
            -lgsmcodec-x86_64-apple-darwin17.7.0 \
            -lspeex-x86_64-apple-darwin17.7.0 \
            -lilbccodec-x86_64-apple-darwin17.7.0 \
            -lg7221codec-x86_64-apple-darwin17.7.0 \
            -lyuv-x86_64-apple-darwin17.7.0 \
            -lwebrtc-x86_64-apple-darwin17.7.0 \
            -lpj-x86_64-apple-darwin17.7.0 \
            -lm \
            -lpthread \
            -framework CoreAudio \
            -framework CoreServices \
            -framework AudioUnit \
            -framework AudioToolbox \
            -framework Foundation \
            -framework AppKit \
            -framework AVFoundation \
            -framework CoreGraphics \
            -framework QuartzCore \
            -framework CoreVideo \
            -framework CoreMedia \
            -framework VideoToolbox \
            -framework Security \
            /usr/lib/libz.dylib \
            /usr/lib/libiconv.dylib \
            /usr/lib/libbz2.dylib

    LIBS += -L$$_PRO_FILE_PWD_/mac/openssl/1.0.2s/lib \
            -lssl \
            -lcrypto
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
