#include "test_mockhardware.h"

void TestMockHardware::testAcquireDataReturnsValidSize()
{
    MockHardwareDriver driver;
    driver.initialize();
    driver.connect();

    WaveformData data;
    bool result = driver.acquireData(data, 0);

    QVERIFY2(result, qPrintable(driver.lastError()));
    QCOMPARE(data.sampleRate, 40000000);
    QVERIFY(data.samples.size() > 0);

    driver.disconnect();
}

void TestMockHardware::testAcquireDataWaveformGeneration()
{
    MockHardwareDriver driver;
    driver.initialize();
    driver.connect();

    WaveformData data;
    driver.acquireData(data, 0);

    bool hasPositive = false;
    bool hasNegative = false;
    for (double v : data.samples) {
        if (v > 0) hasPositive = true;
        if (v < 0) hasNegative = true;
    }
    QVERIFY(hasPositive && hasNegative);

    driver.disconnect();
}

void TestMockHardware::testReadProbeIdFormat()
{
    MockHardwareDriver driver;
    driver.initialize();
    driver.connect();

    QString probeId;
    bool result = driver.readProbeId(probeId);

    QVERIFY2(result, qPrintable(driver.lastError()));
    QVERIFY(probeId.startsWith("MOCK-PROBE-"));

    driver.disconnect();
}

void TestMockHardware::testGetTemperatureInRange()
{
    MockHardwareDriver driver;
    driver.initialize();
    driver.connect();

    int temperature;
    bool result = driver.getTemperature(temperature);

    QVERIFY2(result, qPrintable(driver.lastError()));
    QVERIFY(temperature >= 20);
    QVERIFY(temperature <= 35);

    driver.disconnect();
}

void TestMockHardware::testMotorStartStop()
{
    MockHardwareDriver driver;
    driver.initialize();
    driver.connect();

    bool result = driver.motorStart(100);
    QVERIFY2(result, qPrintable(driver.lastError()));

    result = driver.motorStop();
    QVERIFY2(result, qPrintable(driver.lastError()));

    driver.disconnect();
}

void TestMockHardware::testCreateMockDriver()
{
    HardwareInterface* driver = HardwareFactory::create(HardwareFactory::Mode::Mock);
    QVERIFY(driver != nullptr);
    delete driver;
}

void TestMockHardware::testModeSwitch()
{
    HardwareFactory::Mode mode = HardwareFactory::getDefaultMode();
    QCOMPARE(mode, HardwareFactory::Mode::Mock);

    HardwareFactory::setDefaultMode(HardwareFactory::Mode::Real);
    mode = HardwareFactory::getDefaultMode();
    QCOMPARE(mode, HardwareFactory::Mode::Real);

    HardwareFactory::setDefaultMode(HardwareFactory::Mode::Mock);

    QString str = HardwareFactory::modeToString(HardwareFactory::Mode::Mock);
    QCOMPARE(str, QString("mock"));

    HardwareFactory::Mode m = HardwareFactory::stringToMode("real");
    QCOMPARE(m, HardwareFactory::Mode::Real);
}

QTEST_MAIN(TestMockHardware)
