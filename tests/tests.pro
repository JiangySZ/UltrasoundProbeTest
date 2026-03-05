QT += core testlib

CONFIG += testcase
CONFIG -= app_bundle

TARGET = run_tests
TEMPLATE = app

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../src
INCLUDEPATH += C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/include
INCLUDEPATH += C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/include/QtCore
INCLUDEPATH += C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/include/QtTest

SOURCES += test_configmanager.cpp
HEADERS += test_configmanager.h

SOURCES += ../src/Config/ConfigManager.cpp
SOURCES += ../src/Config/Validator.cpp
SOURCES += ../src/Config/SensitivityImporter.cpp
SOURCES += ../src/Config/JsonLoader.cpp

DEFINES += SRCDIR=\\\"$$PWD/../config\\\"

win32:CONFIG(debug, debug|release) {
    debug {
        !system(xcopy /Y /Q "$$PWD/../config" "$$PWD/debug/config") { error("Copy config failed") }
    }
}
