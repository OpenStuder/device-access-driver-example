#include "example.h"

class ExampleStorage: public SIStorage {
  private:
    bool storePropertyValues_(const QMap<SIGlobalPropertyID, QVariant>& properties, const QDateTime& timestamp) override {
        return false;
    }

    QVector<TimestampedProperty> retrievePropertyValues_(const SIGlobalPropertyID& id, const QDateTime& from, const QDateTime& to, unsigned int limit, SIStatus* status) override {
        return {};
    }

    QVector<SIGlobalPropertyID> availableStoredProperties_(const QDateTime& from, const QDateTime& to, SIStatus* status) override {
        return {};
    }

    bool storeDeviceMessages_(const QVector<SIDeviceMessage>& messages) override {
        messages_.append(messages);
        return true;
    }

    QVector<SIDeviceMessage> retrieveDeviceMessages_(const QDateTime& from, const QDateTime& to, unsigned int limit, SIStatus* status) override {
        QVector<SIDeviceMessage> messages;
        for (const auto& message: messages_) {
            if (message.timestamp() > from && message.timestamp() < to) {
                messages << message;
            }
        }
        if (status) {
            *status = SIStatus::Success;
        }
        if (messages.count() > limit) {
            return messages.mid(0, limit);
        } else {
            return messages;
        }
    }

    QVector<SIDeviceMessage> messages_;
};

SIStorage* ExampleStorageDriver::createStorageInstance(const QVariantMap& parameters) {
    return new ExampleStorage();
}
