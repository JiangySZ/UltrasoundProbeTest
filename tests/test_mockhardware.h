#ifndef TEST_MOCKHARDWARE_H
#define TEST_MOCKHARDWARE_H

#include <QtTest/QtTest>
#include <QDebug>
#include "HAL/MockHardwareDriver.h"
#include "HAL/HardwareFactory.h"

class TestMockHardware : public QObject
{
    Q_OBJECT

private slots:
    void testAcquireDataReturnsValidSize();
    void testAcquireDataWaveformGeneration();
    void testReadProbeIdFormat();
    void testGetTemperatureInRange();
    void testMotorStartStop();

    void testCreateMockDriver();
    void testModeSwitch();
};

#endif
