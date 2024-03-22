QT += widgets
TEMPLATE = app
TARGET = Demineur
SOURCES += main.cpp \
    Mainwindow.cpp \
    DifficultyWindow.cpp \
    MainMenu.cpp
DESTDIR = release
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp

HEADERS += \
    MainWindow.h

HEADERS += \
    MainWindow.h \
    DifficultyWindow.h \
    MainMenu.h
    
