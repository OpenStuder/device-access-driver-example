#pragma once
#include <sistoragedriver.h>

/*
 * Plugin/Driver entrypoint class. Needs to implement the SIStorageDriver interface.
 */
class ExampleStorageDriver: public QObject, public SIStorageDriver {
    // Q_OBJECT macro is required in order to be able to load the plugin/driver.
    Q_OBJECT

    // Refers to the plugin metadata in JSON format.
    Q_PLUGIN_METADATA(IID SIStorageDriver_IID FILE "example.json")

    // Declares that the plugin implements the SIStorageDriver interface.
    Q_INTERFACES(SIStorageDriver)

  public:
    // This method actually creates a new instance of the actual storage class.
    SIStorage* createStorageInstance(const QVariantMap& parameters) override;
};
