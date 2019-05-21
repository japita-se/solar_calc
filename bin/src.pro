SOURCES += main.cpp \
 myplot.cpp \
 spa.cpp \
 mymath.cpp \
 mainwindow.cpp \
 optimumplot.cpp \
 radiazionereale.cpp \
 settings.cpp \
 gridset.cpp \
 albedo.cpp \
 linearinter.cpp \
 modelsettings.cpp \
 datiradiazione.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 debug_and_release \
 qtestlib
TARGET = ../bin/solar


HEADERS += myplot.h \
spa.h \
mymath.h \
mainwindow.h \
 optimumplot.h \
 radiazioneReale.h \
 settings.h \
 gridset.h \
 albedo.h \
 linearinter.h \
 modelsettings.h \
 datiradiazione.h
INCLUDEPATH += $(QWT)/src

LIBS += -L/home/giuseppe/Software/qwt-5.1.1/lib \
-lqwt
QMAKE_CXXFLAGS_DEBUG += -g \
 -fno-inline \
 -O0

QMAKE_CXXFLAGS_RELEASE += -g \
-02 \
-fno-inline
QT += sql \
 svg \
 network

DISTFILES += del


RESOURCES += resource.qrc

FORMS += settings.ui \
 gridset.ui \
 albedo.ui \
 modelsettings.ui \
 datiradiazione.ui

QT +=  webkit
