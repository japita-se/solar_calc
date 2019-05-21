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
 datiradiazione.cpp \
 addpv.cpp \
 datipannello.cpp \
 energyout.cpp \
 datiinverter.cpp \
 doubledelegate.cpp \
 xmlengine.cpp \
 lm_eval.c \
 lmmin.c \
 proprieta.cpp \
 chooselang.cpp \
 suggest.cpp
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
 datiradiazione.h \
 addpv.h \
 datipannello.h \
 data.h \
 energyout.h \
 datiinverter.h \
 doubledelegate.h \
 xmlengine.h \
 lm_eval.h \
 lmmin.h \
 generalValues.h \
 proprieta.h \
 chooselang.h \
 suggest.h


QT += sql \
 svg \
 network

DISTFILES += del


RESOURCES += resource.qrc

FORMS += settings.ui \
 gridset.ui \
 albedo.ui \
 modelsettings.ui \
 datiradiazione.ui \
 addpv.ui \
 datipannello.ui \
 datiinverter.ui \
 proprieta.ui \
 chooselang.ui \
 suggest.ui \
 about.ui

QT +=  xml \
  core

TRANSLATIONS = solarcalc_en.tsLIBS += -lqwt




INCLUDEPATH += /home/giuseppe/Download/qwt-5.1/src

LIBS += -L/home/giuseppe/Download/qwt-5.1/lib \
  -lqwt

TRANSLATIONS -= -L/home/giuseppe/Download/qwt-5.1/lib

