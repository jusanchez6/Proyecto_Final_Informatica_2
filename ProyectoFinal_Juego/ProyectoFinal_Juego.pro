QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/main.cpp \
    src/GameObject.cpp \
    src/Level1Scene.cpp \
    src/Player.cpp \
    src/DogAgent.cpp \
    src/Physics.cpp \
    src/Level2Scene.cpp \
    src/Level3Scene.cpp \ 
    src/Plane.cpp \
    src/AnimatedSprite.cpp

HEADERS += \
    include/GameObject.hpp \
    include/Level1Scene.hpp \
    include/Player.hpp \
    include/DogAgent.hpp \
    include/Physics.hpp \
    include/Level2Scene.hpp \
    include/Level3Scene.hpp \ 
    include/Plane.hpp \
    include/AnimatedSprite.hpp

RESOURCES += resources.qrc

INCLUDEPATH += include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
