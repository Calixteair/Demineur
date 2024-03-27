QT += widgets multimedia core
TEMPLATE = app
TARGET = Demineur
SOURCES += main.cpp \
    Mainwindow.cpp \
    DifficultyWindow.cpp \
    MainMenu.cpp \
    RulesDialogue.cpp \
    Profile.cpp \
    ProfileList.cpp \
    ProfileManager.cpp \
    Demineur.cpp \
    DemineurView.cpp
DESTDIR = release
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp

HEADERS += \
    MainWindow.h
RESOURCES += resources.qrc


HEADERS += \
    MainWindow.h \
    DifficultyWindow.h \    
    MainMenu.h \ 
    RulesDialogue.h \
    Profile.h \
    ProfileList.h \
    ProfileManager.h \
    Demineur.h \
    DemineurView.h 
    
