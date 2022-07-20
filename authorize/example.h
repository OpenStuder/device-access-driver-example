#pragma once
#include <siuserauthorizedriver.h>

/*
 * Plugin/Driver entrypoint class. Needs to implement the SIUserAuthorizeDriver interface.
 */
class ExampleUserAuthorizerDriver: public QObject, public SIUserAuthorizeDriver {
    // Q_OBJECT macro is required in order to be able to load the plugin/driver.
    Q_OBJECT

    // Refers to the plugin metadata in JSON format.
    Q_PLUGIN_METADATA(IID SIUserManagementDriver_IID FILE "example.json")

    // Declares that the plugin implements the SIUserAuthorizeDriver interface.
    Q_INTERFACES(SIUserAuthorizeDriver)

  public:
    // This method actually creates a new instance of the actual storage class.
    SIUserAuthorizer* createUserAuthorizerInstance(const QVariantMap& parameters) override;
};
