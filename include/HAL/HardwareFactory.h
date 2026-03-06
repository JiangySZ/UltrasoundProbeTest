#ifndef HARDWARE_FACTORY_H
#define HARDWARE_FACTORY_H

#include <QString>
#include "HAL/HardwareInterface.h"

class HardwareFactory
{
public:
    enum class Mode
    {
        Real,
        Mock
    };

    static HardwareInterface* create(Mode mode);
    static void setDefaultMode(Mode mode);
    static Mode getDefaultMode();
    static QString modeToString(Mode mode);
    static Mode stringToMode(const QString& str);

private:
    static Mode s_defaultMode;
};

#endif // HARDWARE_FACTORY_H
