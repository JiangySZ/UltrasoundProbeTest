QT += core testlib

CONFIG += testcase
CONFIG += moc

TARGET = run_tests
TEMPLATE = app

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../src
INCLUDEPATH += C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/include
INCLUDEPATH += C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/include/QtCore
INCLUDEPATH += C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/include/QtTest

LIBS += -LC:/Qt/Qt5.9.1/5.9.1/msvc2017_64/lib
LIBS += -lQt5Core
LIBS += -lQt5Test

HEADERS += test_mockhardware.h
HEADERS += ../include/HAL/HardwareInterface.h
HEADERS += ../include/HAL/MockHardwareDriver.h
HEADERS += ../include/HAL/HardwareFactory.h

SOURCES += test_mockhardware.cpp
SOURCES += ../src/Config/ConfigManager.cpp
SOURCES += ../src/Config/Validator.cpp
SOURCES += ../src/Config/SensitivityImporter.cpp
SOURCES += ../src/Config/JsonLoader.cpp
SOURCES += ../src/HAL/HardwareInterface.cpp
SOURCES += ../src/HAL/MockHardwareDriver.cpp
SOURCES += ../src/HAL/HardwareFactory.cpp

DEFINES += SRCDIR=\\\"$$PWD/../config\\\"

win32:CONFIG(debug, debug|release) {
    debug {
        !system(xcopy /Y /Q "$$PWD/../config" "$$PWD/debug/config") { error("Copy config failed") }
    }
}
