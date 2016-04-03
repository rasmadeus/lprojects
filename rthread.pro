TEMPLATE = app
CONFIG += console c++11 precompile_header thread
CONFIG -= app_bundle
CONFIG -= qt

PRECOMPILED_HEADER = pch.h

SOURCES += main.cpp \
    utils.cpp

HEADERS += \
    pch.h \
    utils.h \
    accumulate.h
