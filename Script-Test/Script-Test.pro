#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T14:33:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Script-Test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

VAT_VERSION = Base

#QMAKE_PRE_LINK += $$quote($$_PRO_FILE_PWD_\script\test.bat $$_PRO_FILE_PWD_ $$VAT_VERSION)
PseudoTarget.target = pseudo.cpp
PseudoTarget.commands = $$_PRO_FILE_PWD_\script\test.bat $$_PRO_FILE_PWD_ $$VAT_VERSION
#FakeTarget.depends = FORCE

QMAKE_EXTRA_TARGETS += PseudoTarget
PRE_TARGETDEPS += pseudo.cpp
