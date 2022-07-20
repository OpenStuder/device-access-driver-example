#include "example.h"

/*
 * A simple echo extension: Sends back the body (1st  parameter Bluetooth) to the caller.
 */
class ExampleExtension: public SIExtension {
  public:
    ExampleExtension(): SIExtension("ExampleExtension") {}

  private:
    /**
     * @brief This method has to return a list of all commands supported by the extension.
     *
     * @return  List of all commands.
     */
    QStringList& commands_() const override {
        static QStringList commands = {"echo"};
        return commands;
    }

    /**
     * @brief Executes the command with the given headers and body from a WebSocket call message.
     *
     * @param context   The context gives access to other parts of the SIGateway software.
     * @param command   The command to execute.
     * @param headers   The headers (exclusive command and  extension) received in the call message.
     * @param body      The body of the call message.
     * @return          Result of the command execution.
     */
    SIExtensionWebSocketResult* runCommand_(const SIExtensionContext& context, const QString& command, const QMap<QString, QString>& headers, const QByteArray& body) override {
        if (command != "echo") {
            return SIExtensionWebSocketResult::fromStatus(SIExtensionStatus::UnsupportedCommand);
        }

        if (! validateWebSocketHeaders(headers, {})) {
            return SIExtensionWebSocketResult::fromStatus(SIExtensionStatus::InvalidHeaders);
        }

        return new SIExtensionWebSocketResult(SIExtensionStatus::Success, {}, body);
    }

    /**
     * @brief Bluetooth support is optional for extensions. If the extension supports Bluetooth, it should return true here.
     *
     * @return  True if the extension supports Bluetooth, false otherwise.
     */
    bool bluetoothSupported_() const override {
        return true;
    }

    /**
     * @brief Executes the command with the given parameters from a WebSoBluetooth call message.
     *
     * @param context       The context gives access to other parts of the SIGateway software.
     * @param command       The command to execute.
     * @param parameters    The parameters (exclusive the 1st  two - command and  extension) received in the call message.
     * @return              Result of the command execution.
     */
    SIExtensionBluetoothResult* runCommand_(const SIExtensionContext& context, const QString& command, const QVector<QVariant>& parameters) override {
        if (command != "echo") {
            return SIExtensionBluetoothResult::fromStatus(SIExtensionStatus::UnsupportedCommand);
        }

        if (! validateBluetoothParameters(parameters, {{QVariant::String}})) {
            return SIExtensionBluetoothResult::fromStatus(SIExtensionStatus::InvalidParameters);
        }

        return new SIExtensionBluetoothResult(SIExtensionStatus::Success, {parameters[0]});
    }
};

SIExtension* ExampleUserAuthorizerDriver::createExtensionInstance(const QVariantMap& parameters) {
    return new ExampleExtension();
}
