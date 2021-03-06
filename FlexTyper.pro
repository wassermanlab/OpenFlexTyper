######################################################################
# Automatically generated by qmake (3.1) Tue Aug 20 13:25:50 2019
######################################################################

TEMPLATE     = app
TARGET       = flextyper
CONFIG      += c++17
LIBS        += -lstdc++fs -lsdsl -ldivsufsort64     \
               -ldivsufsort \


outputDir.commands = $(MKDIR) $$OUT_PWD/testFiles ; $(COPY_DIR) $$PWD/flextyper/test/testFiles/* $$OUT_PWD/testFiles/ ; $(COPY_DIR) $$PWD/flextyper/test/testFiles/preprocess.sh $$OUT_PWD
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
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_NO_VERSION_TAGGING

INCLUDEPATH += flextyper/includes                     \
	       opt/openFlexTyper/include 	      \
	       opt/miniconda3/include                 \
               fmindex/includes                       \
               flextyper/interfaces                   \
               fmindex/interfaces                   \

HEADERS    += flextyper/includes/utils.h              \
              flextyper/includes/LogClass.h \
              flextyper/includes/directSearch.h \
              flextyper/includes/ftMapClass.h \
              flextyper/includes/ftPropsClass.h \
              flextyper/includes/ftSearch.h \
              flextyper/includes/kmerClass.h \
              flextyper/includes/qkMapClass.h \
              flextyper/includes/queryClass.h \
              flextyper/includes/writerbridge.h       \
              flextyper/includes/kmergenerator.h      \
              flextyper/includes/finder.h             \
              flextyper/includes/queryextractor.h     \
              fmindex/includes/fmindex.h              \
              fmindex/includes/indexPropsClass.h      \

HEADERS    += flextyper/interfaces/ikmergenerator.h   \
              flextyper/interfaces/iqueryextractor.h  \
              flextyper/interfaces/iutils.h           \
              flextyper/interfaces/iwriterbridge.h    \
              flextyper/interfaces/ifinder.h          \
              fmindex/interfaces/iindexPropsClass.h   \
              fmindex/interfaces/ifmindex.h \

SOURCES     +=                \
              flextyper/src/directSearch.cpp \
              flextyper/src/ftMapClass.cpp \
              flextyper/src/ftPropsClass.cpp \
              flextyper/src/ftSearch.cpp \
              flextyper/src/kmerClass.cpp \
              flextyper/src/qkMapClass.cpp \
              flextyper/src/queryClass.cpp \
               flextyper/src/utils.cpp                \
               fmindex/src/fmindex.cpp                \
               flextyper/src/main.cpp                 \
               flextyper/src/writerbridge.cpp         \
               flextyper/src/kmergenerator.cpp        \
               flextyper/src/finder.cpp               \
               flextyper/src/queryextractor.cpp       \
              fmindex/src/indexPropsClass.cpp

DISTFILES += \
    Doxyfile \
    Example_Settings.ini \
    LICENSE \
    OpenFlexTyper_CondaEnv.yml \
    README.md \
    documentation/centeredsearch.png \
    documentation/documentation.md \
    documentation/indexexample.md \
    documentation/installation.md \
    documentation/nonUniqueKmer.png \
    documentation/parameters.md \
    documentation/search.md \
    documentation/searchexample.md \
    documentation/settingini.md \
    documentation/slidingsearch.png \
    documentation/snvsearchexample.md \
    documentation/viralsearchexample.md \
    examples/Example_Settings.ini \
    flextyper/test/testFiles/MixedVirus_100.fasta \
    flextyper/test/testFiles/MixedVirus_100_1.fq.gz \
    flextyper/test/testFiles/MixedVirus_100_2.fq.gz \
    flextyper/test/testFiles/Setting.ini \
    flextyper/test/testFiles/Test.fasta \
    flextyper/test/testFiles/Test.fm9 \
    flextyper/test/testFiles/TestQueries.txt \
    flextyper/test/testFiles/Test_1.fq.gz \
    flextyper/test/testFiles/Test_2.fq.gz \
    flextyper/test/testFiles/Test_Settings.ini \
    flextyper/test/testFiles/Test_indexProps.ini \
    flextyper/test/testFiles/indexProps.ini \
    flextyper/test/testFiles/preprocess.sh \
    install.sh \
    setup.py \
    test.sh


