TEMPLATE = app

DESTDIR = $$PWD/bin

CONFIG += console c++11
CONFIG -= app_bundle

CONFIG += precompile_header
PRECOMPILED_HEADER = src/pch.h

SOURCES += \
    src/main.cpp \
    src/cond_var_example.cpp \
    src/lock_example.cpp \
    src/call_once.cpp \
    src/future.cpp

HEADERS += \
    src/cond_var_example.h \
    src/lock_example.h \
    src/call_once.h \
    src/future.h
