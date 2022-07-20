#pragma once
#include <siextensiondriver.h>

/*
 * Plugin/Driver entrypoint class. Needs to implement the SIExtensionDriver interface.
 */
class ExampleUserAuthorizerDriver: public QObject, public SIExtensionDriver {
    // Q_OBJECT macro is required in order to be able to load the plugin/driver.
    Q_OBJECT

    // Refers to the plugin metadata in JSON format.
    Q_PLUGIN_METADATA(IID SIExtensionDriver_IID FILE "example.json")

    // Declares that the plugin implements the SIExtensionDriver interface.
    Q_INTERFACES(SIExtensionDriver)

  public:
    // This method actually creates a new instance of the actual extension class.
    SIExtension* createExtensionInstance(const QVariantMap& parameters) override;
};
