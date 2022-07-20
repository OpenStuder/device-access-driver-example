#include "example.h"
#include <QVector>
#include <algorithm>

/*
 * Example Authorize driver/plugin. Manages users in memory with initial user admin/admin.
 */
class ExampleUserAuthorizer: public SIUserAuthorizer {
  public:
    /**
     * @brief Constructor, creates the default user admin with password admin.
     */
    ExampleUserAuthorizer() {
        users_ << User {
            "admin",
            "admin",
            SIAccessLevel::Expert
        };
    }

  private:
    struct User {
        QString username;
        QString password;
        SIAccessLevel accessLevel = SIAccessLevel::None;
    };

    /**
     * @brief Called on the authorize driver to authenticate and authorize a user. The method has to return the user's access level or SIAccessLevel::None
     *        if the user does not exists, the password is incorrect or the user does not exist.
     *
     * @param username  Username to authenticate and authorize.
     * @param password  User's password.
     * @return          The access level of the authorized user or SIAccessLevel::None to reject authorization.
     */
    SIAccessLevel authorizeUser_(const QString& username, const QString& password) const override {
        for (const auto& user: users_) {
            if (user.username == username) {
                if (user.password == password) {
                    return user.accessLevel;
                } else {
                    return SIAccessLevel::None;
                }
            }
        }

        return SIAccessLevel::None;
    }

    /**
     * @brief Not all authorize drivers must support user management. If it is supported, the method has to return true.
     *
     * @return  True if user management is supported, false otherwise.
     */
    bool managementSupported_() const override {
        return true;
    }

    /**
     * @brief Lists all users.
     *
     * @param status    Pointer to the status boolean. If not nullptr, the authorize plugin has to write the status of the operation to that address.
     * @return          Map of users and their access level.
     */
    QMap<QString, SIAccessLevel> listUsers_(bool* status) const override {
        QMap<QString, SIAccessLevel> users;
        for (const auto& user: users_) {
            users[user.username] = user.accessLevel;
        }
        if (status) *status = true;
        return users;
    }

    /**
     * @brief Add a user.
     *
     * @param username      Username of the new user.
     * @param password      Password of the new user.
     * @param accessLevel   Access level of the new user.
     * @return              True on success, false otherwise.
     */
    bool addUser_(const QString& username, const QString& password, SIAccessLevel accessLevel) override {
        users_ << User {
            username,
            password,
            accessLevel
        };
        return true;
    }

    /**
     * @brief Changes a user's password.
     *
     * @param username  Username of the user to change the password for.
     * @param password  The new password.
     * @return          True on success, false otherwise.
     */
    bool changeUserPassword_(const QString& username, const QString& password) override {
        for (auto& user: users_) {
            if (user.username == username) {
                user.password = password;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Changes a user's access level.
     *
     * @param username      Username of the user to change the access level.
     * @param accessLevel   New access level.
     * @return              True on success, false otherwise.
     */
    bool changeUserAccessLevel_(const QString& username, SIAccessLevel accessLevel) override {
        for (auto& user: users_) {
            if (user.username == username) {
                user.accessLevel = accessLevel;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Removes a user.
     *
     * @param username  Username of the user to remove.
     * @return          True on success, false otherwise.
     */
    bool removeUser_(const QString& username) override {
        auto newEnd = std::remove_if(users_.begin(), users_.end(), [&](const User& user) {
            return user.username == username;
        });
        if (newEnd != users_.end()) {
            users_.erase(newEnd, users_.end());
            return true;
        } else {
            return false;
        }
    }

    // User list in memory.
    QVector<User> users_;
};

SIUserAuthorizer* ExampleUserAuthorizerDriver::createUserAuthorizerInstance(const QVariantMap& parameters) {
    return new ExampleUserAuthorizer();
}
