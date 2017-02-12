TEMPLATE = app

DESTDIR = ../../../bin

CONFIG += console c++14
CONFIG -= app_bundle

CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

include(../boost.pri)

HEADERS += \
    pch.h \
    resolver.h

SOURCES += \
    main.cpp
