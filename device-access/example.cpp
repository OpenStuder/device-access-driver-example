#include "example.h"
#include <sidevice.h>
#include <sideviceaccess.h>

/*
 * Minimal example device. It offers only one property that represents a simple switch that can be turned on/off.
 */
class ExampleDevice: public SIDevice {
  public:
    inline explicit ExampleDevice(const QString& id): SIDevice("Example Device", id, false, SIDeviceFunction::All) {}

  private:
    /**
     * @brief This method of a device should return the list of properties that is supported by the device.
     *
     * @return List of properties.
     */
    const QVector<SIProperty>& properties_() const override {
        static QVector<SIProperty> properties = {
            {42, SIPropertyType::Bool, SIAccessLevel::Basic, SIPropertyFlag::Readable | SIPropertyFlag::Writeable, "Switch", ""},
        };
        return properties;
    }

    /**
     * @brief This method should try to read a property from the device and return the value and status of the operation.
     *
     * @param id    ID of the property to read.
     * @return      Result of the read operation.
     */
    SIPropertyReadResult readProperty_(SIPropertyID id) const override {
        if (id == 42) {
            return {id, SIStatus::Success, switch_};
        } else {
            return {id, SIStatus::NoProperty, {}};
        }
    }

    /**
     * @brief This method should try to write  property to the actual device and return the status of the operation.
     *
     * @param id        ID of the property to write.
     * @param value     Value to write.
     * @param flags     Write flags. The only flag that exists is the Permanent flag. In that case the value should be written permanently so that after
     *                  a restart of the device, the value is kept.
     * @return          Result of the write operation.
     */
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

/*
 * Minimal example device access. A device access instance should offer the functionality to enumerate devices on a bus or any other communication facility.
 */
class ExampleDeviceAccess: public SIDeviceAccess {
  public:
    inline explicit ExampleDeviceAccess(const QString& id): SIDeviceAccess(id) {}

  private:
    /**
     * @brief The device access should enumerate the available devices on the bus or other the communication facility and update the passed list of devices.
     *
     * @param devices   List of devices that are already enumerated. The device access instance has to remove the devices that are not available anymore and add
     *                  newly detected devices to that list.
     * @return          True if the enumeration was successful, false otherwise.
     */
    bool enumerateDevices_(QVector<SIDevice*>& devices) override {
        if (devices.isEmpty()) {
            devices.append(new ExampleDevice("example"));
        }
        return true;
    }
};

SIDeviceAccess* ExampleDeviceAccessDriver::createDeviceAccessInstance(const QString& id, const QVariantMap& parameters) {
    Q_UNUSED(parameters)

    return new ExampleDeviceAccess(id);
}