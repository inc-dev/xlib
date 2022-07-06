#-------------------------------------------------
#
# Project created by QtCreator 2012-03-27T13:28:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Obj_RTTI
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
    ../../../../Base/Algorithms/xxPortion.cpp \
    ../../../../Base/Algorithms/xxFind.cpp \
    ../../../../Base/Algorithms/xxCompare.cpp \
    ../../../../Base/NATIVE/xxWindowsAtomicRoutines.cpp \
    ../../../../Base/NATIVE/xxNoThreadAtomicRoutines.cpp \
    ../../../../UNICODE/xxUTF8.cpp \
    ../../../../UNICODE/xxCP1251.cpp \
    ../../../../UNICODE/xxCodePages.cpp \
    ../../../../PubObjects/xxXMLObjSerialization.cpp \
    ../../../../PubObjects/xxStaticPubObject.cpp \
    ../../../../PubObjects/xxPubObjects.cpp \
    ../../../../PubObjects/xxObjSerialization.cpp \
    ../../../../PubObjects/xxFileObj.cpp \
    ../../../../PubObjects/xxDinamicPubObject.cpp \
    ../../../../Utils/xxTxtProvider.cpp \
    ../../../../Utils/xxFileDirWork.cpp \
    ../../../Units/xXML_OBJ_Test.cpp \
    ../../../Units/xxLibTest.cpp \
    ../../../Units/xPTR_Test.cpp \
    ../../../Units/xListTest.cpp \
    ../../../Units/xArrayTest.cpp \
    ../../../Units/DateTime_test.cpp \
    ../../../../Utils/xxLogger.cpp \
    ../../../../Utils/xxConsoleLogger.cpp \
    ../../../../Graphics/xxSimpleSVG.cpp \
    ../../../../Utils/xxThread.cpp \
    ../../../Units/xThreadTest.cpp

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
    ../../../../Base/Algorithms/xxPortion.h \
    ../../../../Base/Algorithms/xxFind.h \
    ../../../../Base/Algorithms/xxCompare.h \
    ../../../../Base/NATIVE/xxWindowsAtomicRoutines.h \
    ../../../../Base/NATIVE/xxNoThreadAtomicRoutines.h \
    ../../../../UNICODE/xxUTF8.h \
    ../../../../UNICODE/xxCP1251.h \
    ../../../../UNICODE/xxCodePages.h \
    ../../../../PubObjects/xxXMLObjSerialization.h \
    ../../../../PubObjects/xxStaticPubObject.h \
    ../../../../PubObjects/xxPubObjects.h \
    ../../../../PubObjects/xxObjSerialization.h \
    ../../../../PubObjects/xxFileObj.h \
    ../../../../PubObjects/xxDinamicPubObject.h \
    ../../../../xxObjects.h \
    ../../../../xxBase.h \
    ../../../../Utils/xxTxtProvider.h \
    ../../../../Utils/xxFileDirWork.h \
    ../../../Units/xXML_OBJ_Test.h \
    ../../../Units/xxLibTest.h \
    ../../../Units/xPTR_Test.h \
    ../../../Units/xListTest.h \
    ../../../Units/xArrayTest.h \
    ../../../Units/DateTime_test.h \
    ../../../../Utils/xxLogger.h \
    ../../../../Utils/xxConsoleLogger.h \
    ../../../../Graphics/xxSimpleSVG.h \
    ../../../../Utils/xxThread.h \
    ../../../Units/xThreadTest.h
