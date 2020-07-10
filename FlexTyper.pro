######################################################################
# Automatically generated by qmake (3.1) Tue Aug 20 13:25:50 2019
######################################################################

TEMPLATE     = app
TARGET       = flextyper
CONFIG      += c++17
LIBS        += -lstdc++fs -lsdsl -ldivsufsort64     \
               -ldivsufsort \

copydata.commands = $(COPY_DIR) $$PWD/testFiles/* $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

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
               fmindex/interfaces                   \

HEADERS    += flextyper/includes/utils.h              \
              flextyper/includes/ftKPropsClass.h \
              flextyper/includes/ftMapClass.h \
              flextyper/includes/ftPropsClass.h \
              flextyper/includes/ftSearch.h \
              flextyper/includes/kmerClass.h \
              flextyper/includes/queryClass.h \
              flextyper/includes/writerbridge.h       \
              flextyper/includes/kmergenerator.h      \
              flextyper/includes/finder.h             \
              flextyper/includes/resultprocessor.h    \
              flextyper/includes/queryextractor.h     \
              fmindex/includes/fmindex.h              \
              fmindex/includes/indexPropsClass.h      \

HEADERS    += flextyper/interfaces/ikmergenerator.h   \
              flextyper/interfaces/iqueryextractor.h  \
              flextyper/interfaces/iresultprocessor.h \
              flextyper/interfaces/iutils.h           \
              flextyper/interfaces/iwriterbridge.h    \
              flextyper/interfaces/ifinder.h          \
              fmindex/interfaces/iindexPropsClass.h   \
              fmindex/interfaces/ifmindex.h \

SOURCES     +=                \
              flextyper/src/ftKPropsClass.cpp \
              flextyper/src/ftMapClass.cpp \
              flextyper/src/ftPropsClass.cpp \
              flextyper/src/ftSearch.cpp \
              flextyper/src/kmerClass.cpp \
              flextyper/src/queryClass.cpp \
               flextyper/src/utils.cpp                \
               fmindex/src/fmindex.cpp                \
               flextyper/src/main.cpp                 \
               flextyper/src/writerbridge.cpp         \
               flextyper/src/kmergenerator.cpp        \
               flextyper/src/finder.cpp               \
               flextyper/src/resultprocessor.cpp      \
               flextyper/src/queryextractor.cpp       \
              fmindex/src/indexPropsClass.cpp

DISTFILES += \
    install.sh \
    testFiles/MixedVirus_100_1.fq.gz \
    testFiles/MixedVirus_100_2.fq.gz \
    testFiles/Setting.ini \
    testFiles/indexProps.ini \
    testFiles/preprocess.sh \
    testFiles/test.fq.gz \
    testFiles/testQueries.txt

