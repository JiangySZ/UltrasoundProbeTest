cmake_minimum_required(VERSION 3.10)
project(UltrasoundProbeTest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt
set(QT_VERSION_MAJOR 5)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Test PrintSupport)

# Thirdparty paths
set(THIRDPARTY_DIR ${CMAKE_SOURCE_DIR}/thirdparty)

# QCustomPlot
set(QCUSTOMPLOT_DIR ${THIRDPARTY_DIR}/qcustomplot)

# FFTW++ (using fftw++ C++ wrapper)
set(FFTWPP_DIR ${THIRDPARTY_DIR}/fftw++-3.03)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${QCUSTOMPLOT_DIR}
    ${FFTWPP_DIR}
)

# Source files
set(SOURCES
    src/main.cpp
    src/UI/MainWindow.cpp
    src/Config/Logger.cpp
    src/Config/JsonLoader.cpp
    src/Config/ConfigManager.cpp
    src/Config/Validator.cpp
    src/Config/SensitivityImporter.cpp
)

set(HEADERS
    include/UI/MainWindow.h
    include/Config/Logger.h
    include/Config/ProbeConfig.h
    include/Config/JsonLoader.h
    include/Config/ConfigManager.h
    include/Config/Validator.h
    include/Config/SensitivityImporter.h
)

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::PrintSupport
)

# Unit tests
enable_testing()
add_subdirectory(tests)

# Install
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
