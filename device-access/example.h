#pragma once
#include <QObject>
#include <sideviceaccessdriver.h>

/*
 * Plugin/Driver entrypoint class. Needs to implement the SIDeviceAccessDriver interface.
 */
class ExampleDeviceAccessDriver: public QObject, public SIDeviceAccessDriver {
    // Q_OBJECT macro is required in order to be able to load the plugin/driver.
	Q_OBJECT

    // Refers to the plugin metadata in JSON format.
	Q_PLUGIN_METADATA(IID SIDeviceAccessDriverPlugin_IID FILE "example.json")

    // Declares that the plugin implements the SIDeviceAccessDriver interface.
	Q_INTERFACES(SIDeviceAccessDriver)

  public:
    // This method actually creates a new instance of the actual storage class.
	SIDeviceAccess* createDeviceAccessInstance(const QString& id, const QVariantMap& parameters) override;
};
