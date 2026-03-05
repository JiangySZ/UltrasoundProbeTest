#ifndef PROBE_CONFIG_H
#define PROBE_CONFIG_H

#include <QString>
#include <QList>
#include <QMap>

struct ProbeConfig {
    struct Probe {
        QString id;
        QString model;
        QString type;
        int elements;
        double frequency;
    };

    struct Test {
        double startDepth;
        double adcRatio;
        QList<int> excludeElements;
        QList<int> calibrationElements;
    };

    struct Threshold {
        double nominal;
        double tolerance;
    };

    struct Thresholds {
        Threshold sensitivity;
        Threshold centerFrequency;
        Threshold bandwidth6dB;
        Threshold bandwidth20dB;
        Threshold pulseLength20dB;
    };

    Probe probe;
    Test test;
    Thresholds thresholds;
    QString sensitivityList;
};

struct WaveformConfig {
    struct Waveform {
        QString name;
        QString type;
        double txVoltage;
        double frequency;
        int cycles;
        QList<double> points;
    };

    Waveform waveform;
};

#endif // PROBE_CONFIG_H
