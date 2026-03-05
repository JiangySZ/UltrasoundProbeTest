QT += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = UltrasoundProbeTest
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# Thirdparty
INCLUDEPATH += $$PWD/thirdparty/qcustomplot
INCLUDEPATH += $$PWD/thirdparty/fftw++-3.03
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/src

# Source files
SOURCES += \
    src/main.cpp \
    src/UI/MainWindow.cpp \
    src/Config/Logger.cpp \
    src/Config/JsonLoader.cpp \
    src/Config/ConfigManager.cpp \
    src/Config/Validator.cpp \
    src/Config/SensitivityImporter.cpp

# Header files
HEADERS += \
    include/UI/MainWindow.h \
    include/Config/Logger.h \
    include/Config/ProbeConfig.h \
    include/Config/JsonLoader.h \
    include/Config/ConfigManager.h \
    include/Config/Validator.h \
    include/Config/SensitivityImporter.h

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = $$[QT_INSTALL_PREFIX]/bin
!isEmpty(target.path): INSTALLS += target
