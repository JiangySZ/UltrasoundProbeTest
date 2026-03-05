#ifndef TEST_CONFIGMANAGER_H
#define TEST_CONFIGMANAGER_H

#include <QtTest/QtTest>
#include <QDebug>
#include "Config/ConfigManager.h"
#include "Config/Validator.h"
#include "Config/SensitivityImporter.h"

class TestConfigAll : public QObject
{
    Q_OBJECT

private slots:
    void testLoadValidProbeConfig();
    void testLoadInvalidJson();
    void testLoadValidWaveformConfig();

    void testValidateMissingField();
    void testValidateOutOfRange();
    void testValidateValidConfig();

    void testImportValidFile();
    void testImportInvalidFormat();
    void testImportEmptyFile();
};

#endif
