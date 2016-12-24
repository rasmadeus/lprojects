TEMPLATE = app

DESTDIR = $$PWD/bin

CONFIG += console c++11
CONFIG -= app_bundle

CONFIG += precompile_header
PRECOMPILED_HEADER = src/pch.h

SOURCES += \
    src/main.cpp
