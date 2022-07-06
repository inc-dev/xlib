#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T17:03:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = BaseTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../../../Base/xTypes.cpp \
    ../../../../Base/xTypeInfo.cpp \
    ../../../../Base/xPtr.cpp \
    ../../../../Base/xProperty.cpp \
    ../../../../Base/xOperators.cpp \
    ../../../../Base/xList.cpp \
    ../../../../Base/xDataAccess.cpp \
    ../../../../Base/xAtom.cpp \
    ../../../../Base/xArray.cpp \
    ../../../../Base/NATIVE/xWindowsAtomicRoutines.cpp \
    ../../../../Base/NATIVE/xNoThreadAtomicRoutines.cpp \
    ../../../../Base/Algorithms/xPortion.cpp \
    ../../../../Base/Algorithms/xFind.cpp \
    ../../../../Base/Algorithms/xCompare.cpp \
    ../../../Units/xPTR_Test.cpp \
    ../../../Units/xListTest.cpp \
    ../../../Units/xFindSpeedTest.cpp \
    ../../../Units/xArrayTest.cpp \
    ../../../Units/xArraySpeedTest.cpp \
    ../../../../Base/xDecodeStr.cpp \
    ../../../../Base/xSmallStr.cpp \
    ../../../../PubObjects/xPubObjects.cpp \
    ../../../../PubObjects/xDinamicPubObject.cpp \
    ../../../../Base/xAdapters.cpp \
    ../../../../PubObjects/xStaticPubObject.cpp

HEADERS += \
    ../../../../Base/xTypes.h \
    ../../../../Base/xTypeInfo.h \
    ../../../../Base/xPtr.h \
    ../../../../Base/xProperty.h \
    ../../../../Base/xOperators.h \
    ../../../../Base/xList.h \
    ../../../../Base/xDataAccess.h \
    ../../../../Base/xAtom.h \
    ../../../../Base/xArray.h \
    ../../../../Base/NATIVE/xWindowsAtomicRoutines.h \
    ../../../../Base/NATIVE/xNoThreadAtomicRoutines.h \
    ../../../../Base/Algorithms/xPortion.h \
    ../../../../Base/Algorithms/xFind.h \
    ../../../../Base/Algorithms/xCompare.h \
    ../../../Units/xPTR_Test.h \
    ../../../Units/xListTest.h \
    ../../../Units/xFindSpeedTest.h \
    ../../../Units/xArrayTest.h \
    ../../../Units/xArraySpeedTest.h \
    ../../../../Base/xDecodeStr.h \
    ../../../../Base/xSmallStr.h \
    ../../../../xBase.h \
    ../../../../PubObjects/xPubObjects.h \
    ../../../../PubObjects/xDinamicPubObject.h \
    ../../../../Base/xAdapters.h \
    ../../../../PubObjects/xStaticPubObject.h
