QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_ut_motscheduler.cpp \
    ../MOTScheduler/owners.cpp \
    ../MOTScheduler/stations.cpp \
    ../MOTScheduler/testers.cpp \
    ../MOTScheduler/tests.cpp \
    ../MOTScheduler/vehicles.cpp

HEADERS += \
    ../MOTScheduler/owners.h \
    ../MOTScheduler/stations.h \
    ../MOTScheduler/testers.h \
    ../MOTScheduler/tests.h \
    ../MOTScheduler/tests.h \
    ../MOTScheduler/vehicles.h

SUBDIRS += \
    ../MOTScheduler/MOTScheduler.pro

INCLUDEPATH += ../MOTScheduler

DISTFILES +=
