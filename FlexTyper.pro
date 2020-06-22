######################################################################
# Automatically generated by qmake (3.1) Tue Aug 20 13:25:50 2019
######################################################################

TEMPLATE     = app
TARGET       = flextyper
CONFIG      += c++17
LIBS        += -lstdc++fs -lsdsl -ldivsufsort64     \
               -ldivsufsort \

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_NO_VERSION_TAGGING

INCLUDEPATH += flextyper/includes                     \
	       opt/openFlexTyper/include 	      \
	       opt/miniconda3/include                 \
               fmindex/includes                       \
               flextyper/interfaces                   \

HEADERS    += flextyper/includes/utils.h              \
    flextyper/includes/FTMapClass.h \
              flextyper/includes/ftsearch.h           \
    flextyper/includes/kmerClass.h \
    flextyper/includes/queryClass.h \
    flextyper/includes/resultsClass.h \
    flextyper/includes/typedefs.h \
              fmindex/includes/ifmindex.h             \
              fmindex/includes/fmindex.h              \
              flextyper/includes/stats.h              \
              flextyper/includes/writerbridge.h       \
              flextyper/includes/kmergenerator.h      \
              flextyper/includes/finder.h             \
              flextyper/includes/resultprocessor.h    \
              flextyper/includes/queryextractor.h     \

HEADERS    += flextyper/interfaces/ikmergenerator.h   \
              flextyper/interfaces/iqueryextractor.h  \
              flextyper/interfaces/iresultprocessor.h \
              flextyper/interfaces/istats.h           \
              flextyper/interfaces/iutils.h           \
              flextyper/interfaces/iwriterbridge.h    \
              flextyper/interfaces/ifinder.h          \


SOURCES     += flextyper/src/stats.cpp                \
    flextyper/src/FTMapClass.cpp \
    flextyper/src/kmerClass.cpp \
    flextyper/src/queryClass.cpp \
    flextyper/src/resultsClass.cpp \
               flextyper/src/utils.cpp                \
               fmindex/src/fmindex.cpp                \
               flextyper/src/ftsearch.cpp             \
               flextyper/src/main.cpp                 \
               flextyper/src/writerbridge.cpp         \
               flextyper/src/kmergenerator.cpp        \
               flextyper/src/finder.cpp               \
               flextyper/src/resultprocessor.cpp      \
               flextyper/src/queryextractor.cpp       \
