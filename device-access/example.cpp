#include "example.h"
#include <sidevice.h>
#include <sideviceaccess.h>

class ExampleDevice: public SIDevice {
  public:
    inline explicit ExampleDevice(const QString& id): SIDevice("Example Device", id, false, SIDeviceFunction::All) {}

  private:
    const QVector<SIProperty>& properties_() const override {
        static QVector<SIProperty> properties = {
            {42, SIPropertyType::Bool, SIAccessLevel::Basic, SIPropertyFlag::Readable | SIPropertyFlag::Writeable, "Switch", ""},
        };
        return properties;
    }
    SIPropertyReadResult readProperty_(SIPropertyID id) const override {
        if (id == 42) {
            return {id, SIStatus::Success, switch_};
        } else {
            return {id, SIStatus::NoProperty, {}};
        }
    }
    SIPropertyWriteResult writeProperty_(SIPropertyID id, const QVariant& value, SIPropertyWriteFlags flags) override {
        if (id == 42) {
            switch_ = value.toBool();
            return {id, SIStatus::Success};
        } else {
            return {id, SIStatus::NoProperty};
        }
    }

    bool switch_ = false;
};

class ExampleDeviceAccess: public SIDeviceAccess {
  public:
    inline explicit ExampleDeviceAccess(const QString& id): SIDeviceAccess(id) {}

  private:
    bool enumerateDevices_(QVector<SIDevice*>& devices) override {
        if (devices.isEmpty()) {
            devices.append(new ExampleDevice("example"));
        }
        return true;
    }
};

SIDeviceAccess* ExampleDriver::createDeviceAccessInstance(const QString& id, const QVariantMap& parameters) {
    Q_UNUSED(parameters)

    return new ExampleDeviceAccess(id);
}