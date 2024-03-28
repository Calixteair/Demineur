QT += widgets multimedia core
TEMPLATE = app
TARGET = Demineur
SOURCES +=     main.cpp \
    src/Controllers/ProfileManager.cpp \
    src/Models/Demineur.cpp \
    src/Models/Profile.cpp \
    src/Views/DemineurView.cpp \
    src/Views/MainMenu.cpp \
    src/Views/ProfileList.cpp \
    src/Views/DifficultyWindow.cpp \
    src/Views/MainWindow.cpp \
    src/Views/RulesDialogue.cpp


DESTDIR = release
OBJECTS_DIR = tmp
MOC_DIR = tmp
RCC_DIR = tmp
UI_DIR = tmp

RESOURCES += resources.qrc


HEADERS += \
    headerFiles/Controllers/ProfileManager.h \
    headerFiles/Models/Demineur.h \
    headerFiles/Models/Profile.h \
    headerFiles/Views/DemineurView.h \
    headerFiles/Views/MainMenu.h \
    headerFiles/Views/ProfileList.h \
    headerFiles/Views/DifficultyWindow.h \
    headerFiles/Views/MainWindow.h \
    headerFiles/Views/RulesDialogue.h
    
