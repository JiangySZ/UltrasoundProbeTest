#include "HAL/HardwareFactory.h"
#include "HAL/MockHardwareDriver.h"

HardwareFactory::Mode HardwareFactory::s_defaultMode = HardwareFactory::Mode::Mock;

HardwareInterface* HardwareFactory::create(Mode mode)
{
    switch (mode) {
    case Mode::Mock:
        return new MockHardwareDriver();
    case Mode::Real:
        return nullptr;
    default:
        return nullptr;
    }
}

void HardwareFactory::setDefaultMode(Mode mode)
{
    s_defaultMode = mode;
}

HardwareFactory::Mode HardwareFactory::getDefaultMode()
{
    return s_defaultMode;
}

QString HardwareFactory::modeToString(Mode mode)
{
    switch (mode) {
    case Mode::Real:
        return "real";
    case Mode::Mock:
        return "mock";
    default:
        return "unknown";
    }
}

HardwareFactory::Mode HardwareFactory::stringToMode(const QString& str)
{
    if (str.toLower() == "real") {
        return Mode::Real;
    } else if (str.toLower() == "mock") {
        return Mode::Mock;
    }
    return Mode::Mock;
}
