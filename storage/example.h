#pragma once
#include <sistoragedriver.h>

class ExampleStorageDriver: public QObject, public SIStorageDriver {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SIStorageDriver_IID FILE "example.json")
    Q_INTERFACES(SIStorageDriver)

  public:
    SIStorage* createStorageInstance(const QVariantMap& parameters) override;
};
