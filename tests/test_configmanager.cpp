#include "test_configmanager.h"

void TestConfigAll::testLoadValidProbeConfig()
{
    QString configDir = "../config";
    ConfigManager* cm = ConfigManager::instance();
    bool result = cm->loadProbeConfig(configDir + "/ProbeConfig.json");

    QVERIFY2(result, qPrintable(cm->lastError()));

    ProbeConfig config = cm->getProbeConfig();
    QCOMPARE(config.probe.id, QString("PROBE-001"));
    qDebug() << "Probe ID:" << config.probe.id;
}

void TestConfigAll::testLoadInvalidJson()
{
    ConfigManager* cm = ConfigManager::instance();
    bool result = cm->loadProbeConfig("nonexistent.json");

    QVERIFY2(!result, "Should fail for nonexistent file");
}

void TestConfigAll::testLoadValidWaveformConfig()
{
    QString configDir = "../config";
    ConfigManager* cm = ConfigManager::instance();
    bool result = cm->loadWaveformConfig(configDir + "/WaveformConfig.json");

    QVERIFY2(result, qPrintable(cm->lastError()));
    qDebug() << "Waveform loaded";
}

void TestConfigAll::testValidateMissingField()
{
    Validator validator;
    ProbeConfig config;
    config.probe.id = "";
    config.probe.elements = 0;

    ValidationResult result = validator.validate(config);

    QVERIFY2(!result.isValid, "Should be invalid with missing fields");
    qDebug() << "Errors:" << result.errors.size();
}

void TestConfigAll::testValidateOutOfRange()
{
    Validator validator;
    ProbeConfig config;
    config.probe.id = "TEST-001";
    config.probe.elements = -5;

    ValidationResult result = validator.validate(config);

    QVERIFY2(!result.isValid, "Should be invalid with negative elements");
}

void TestConfigAll::testValidateValidConfig()
{
    Validator validator;
    ProbeConfig config;
    config.probe.id = "TEST-001";
    config.probe.model = "Test";
    config.probe.type = "linear";
    config.probe.elements = 128;
    config.probe.frequency = 4.0;
    config.test.adcRatio = 0.001;

    ValidationResult result = validator.validate(config);

    qDebug() << "Is valid:" << result.isValid;
}

void TestConfigAll::testImportValidFile()
{
    QString configDir = "../config";
    SensitivityImporter importer;
    QList<double> values = importer.import(configDir + "/SensitivityList.txt");

    QVERIFY2(importer.isValid(), qPrintable(importer.lastError()));
    QVERIFY(values.size() > 0);
    qDebug() << "Imported values:" << values.size();
}

void TestConfigAll::testImportInvalidFormat()
{
    QString configDir = "../config";
    SensitivityImporter importer;
    QList<double> values = importer.import(configDir + "/ProbeConfig.json");

    QVERIFY2(!importer.isValid(), "Should fail for invalid format");
}

void TestConfigAll::testImportEmptyFile()
{
    SensitivityImporter importer;
    QList<double> values = importer.import("nonexistent.txt");

    QVERIFY2(!importer.isValid(), "Should fail for nonexistent file");
}

QTEST_MAIN(TestConfigAll)
