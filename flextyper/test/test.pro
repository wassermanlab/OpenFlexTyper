######################################################################
# Automatically generated by qmake (3.1) Thu Aug 22 17:24:48 2019
######################################################################

TEMPLATE     = app
TARGET       = test
LIBS        += -lgtest -lgtest_main -lgmock       \
               -lstdc++fs -lsdsl -ldivsufsort64   \
               -ldivsufsort
CONFIG      += c++17


outputDir.commands = $(MKDIR) $$OUT_PWD/testFiles ; $(COPY_DIR) $$PWD/testFiles/* $$OUT_PWD/testFiles/
first.depends = $(first) outputDir
export(first.depends)
export(outputDir.commands)
QMAKE_EXTRA_TARGETS += first outputDir


# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../includes                  \
               ../src                       \
               ../../fmindex/includes/      \
               ../../fmindex/interfaces/      \
               ../../fmindex/src/           \
               ../interfaces/               \
               ../mock/                     \

# Input
SOURCES += tst_queryextractor.cpp           \
    tst_fmindex.cpp \
    tst_ftMapClass.cpp \
    tst_indexPropsClass.cpp \
    tst_kmerClass.cpp \
    tst_qkMapClass.cpp \
    tst_queryClass.cpp \
           tst_writerbridge.cpp             \
           tst_utils.cpp                    \
           tst_finder.cpp                   \
           tst_kmergenerator.cpp            \

SOURCES += mock/mock_fmindex.cpp            \
