#-------------------------------------------------
#
# Project created by QtCreator 2012-11-08T17:57:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../../../Base/xxTypes.cpp \
    ../../../../Base/xxTypeInfo.cpp \
    ../../../../Base/xxSpinLock.cpp \
    ../../../../Base/xxSmallStr.cpp \
    ../../../../Base/xxPtr.cpp \
    ../../../../Base/xxProperty.cpp \
    ../../../../Base/xxOperators.cpp \
    ../../../../Base/xxList.cpp \
    ../../../../Base/xxDecodeStr.cpp \
    ../../../../Base/xxDateTime.cpp \
    ../../../../Base/xxDataAccess.cpp \
    ../../../../Base/xxContainerAdapters.cpp \
    ../../../../Base/xxAtom.cpp \
    ../../../../Base/xxArray.cpp \
    ../../../../Base/NATIVE/xxWindowsAtomicRoutines.cpp \
    ../../../../Base/NATIVE/xxNoThreadAtomicRoutines.cpp \
    ../../../../Base/Algorithms/xxPortion.cpp \
    ../../../../Base/Algorithms/xxFind.cpp \
    ../../../../Base/Algorithms/xxCompare.cpp \
    ../../../Units/xPTR_Test.cpp \
    ../../../Units/xListTest.cpp \
    ../../../Units/xFindSpeedTest.cpp \
    ../../../Units/xArrayTest.cpp \
    ../../../Units/xArraySpeedTest.cpp

HEADERS += \
    ../../../../Base/xxTypes.h \
    ../../../../Base/xxTypeInfo.h \
    ../../../../Base/xxSpinLock.h \
    ../../../../Base/xxSmallStr.h \
    ../../../../Base/xxPtr.h \
    ../../../../Base/xxProperty.h \
    ../../../../Base/xxOperators.h \
    ../../../../Base/xxList.h \
    ../../../../Base/xxDecodeStr.h \
    ../../../../Base/xxDateTime.h \
    ../../../../Base/xxDataAccess.h \
    ../../../../Base/xxContainerAdapters.h \
    ../../../../Base/xxAtom.h \
    ../../../../Base/xxArray.h \
    ../../../../Base/NATIVE/xxWindowsAtomicRoutines.h \
    ../../../../Base/NATIVE/xxNoThreadAtomicRoutines.h \
    ../../../../Base/Algorithms/xxPortion.h \
    ../../../../Base/Algorithms/xxFind.h \
    ../../../../Base/Algorithms/xxCompare.h \
    ../../../../xxBase.h \
    ../../../Units/xPTR_Test.h \
    ../../../Units/xListTest.h \
    ../../../Units/xFindSpeedTest.h \
    ../../../Units/xArrayTest.h \
    ../../../Units/xArraySpeedTest.h
