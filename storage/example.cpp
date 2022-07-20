#include "example.h"

/*
 * Very basic storage driver that for simplicity does not store property values, but device messages.
 */
class ExampleStorage: public SIStorage {
  private:
    /**
     * @brief The storage driver should store these property values permanently for the given IDs and timestamp.
     *
     * @param properties    Map of property IDs to their actual value that needs to be saved.
     * @param timestamp     Common timestamp  for all those property values.
     * @return              True on successs, false otherwise.
     */
    bool storePropertyValues_(const QMap<SIGlobalPropertyID, QVariant>& properties, const QDateTime& timestamp) override {
        return false;
    }

    /**
     * @brief The storage driver should read the values of the property with the given ID from the storage according to the passed time window and limit.
     *
     * @param id        ID of the property to read the values from the permanent storage.
     * @param from      Start of the time window that filters the values to return.
     * @param to        End of the time window that filters the values to return.
     * @param limit     Maximal count of values to return. Note that you should return the newer values should the list be fragmented.
     * @param status    If the pointer is not nullptr, the storage driver should write the status of the operation to the location the pointer is pointing to.
     * @return          List of timestamped properties according to the query.
     */
    QVector<TimestampedProperty> retrievePropertyValues_(const SIGlobalPropertyID& id, const QDateTime& from, const QDateTime& to, unsigned int limit, SIStatus* status) override {
        return {};
    }

    /**
     * @brief The storage driver should return a list of property IDs that have data in the given window.
     *
     * @param from      Start of the time window that filters the values to return.
     * @param to        End of the time window that filters the values to return.
     * @param status    If the pointer is not nullptr, the storage driver should write the status of the operation to the location the pointer is pointing to.
     * @return          List of property IDs for whose the storage contains data in the given window.
     */
    QVector<SIGlobalPropertyID> availableStoredProperties_(const QDateTime& from, const QDateTime& to, SIStatus* status) override {
        return {};
    }

    /**
     * @brief The storage driver should store the passed messages.
     *
     * @param messages  List of messages to store.
     * @return          True on success, false otherwise.
     */
    bool storeDeviceMessages_(const QVector<SIDeviceMessage>& messages) override {
        messages_.append(messages);
        return true;
    }

    /**
     * @brief The storage driver should read messages from the storage according to the passed time window and limit.
     *
     * @param from      Start of the time window that filters the messages to return.
     * @param to        End of the time window that filters the messages to return.
     * @param limit     Maximal count of messages to return. Note that you should return the newer messages should the list be fragmented.
     * @param status    If the pointer is not nullptr, the storage driver should write the status of the operation to the location the pointer is pointing to.
     * @return          List of messages in the requested time window.
     */
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
