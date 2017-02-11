TEMPLATE = app

DESTDIR = ../../bin

CONFIG += console c++14
CONFIG -= app_bundle

CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

SOURCES += \
    main.cpp \
    cond_var_example.cpp \
    lock_example.cpp \
    call_once.cpp \
    future.cpp \
    gui_thread.cpp \
    asynch.cpp \
    promise.cpp \
    pack_task.cpp

HEADERS += \
    cond_var_example.h \
    lock_example.h \
    call_once.h \
    future.h \
    gui_thread.h \
    asynch.h \
    promise.h \
    pack_task.h \
    pch.h
