# openstuder driver examples

The openstuder gateway functionality can be extended using special plugins, so called drivers. There are three categories of drivers possible:

In order to be able to build any of these examples, you need first to **install a recent (0.3.0++) version of the gateway software**:

```
> sudo apt update
> sudo apt install ca-certificates
> curl -s --compressed "https://www.openstuder.io/ppa/KEY.gpg" | sudo apt-key add -
> sudo curl -s --compressed -o /etc/apt/sources.list.d/openstuder.list "https://www.openstuder.io/ppa/openstuder.list"
> sudo apt update
> sudo apt install openstuder-gateway
```

## device access drivers

Device access drivers allow to interact with real devices and provide self-describing properties for all devices supported by that device access driver. The Gateway
comes with two device access drivers, XCom485i which supports all devices connected to an XCom485i CAN to Modbus converter and the Demo  device access driver, which 
provides access to a virtual solar installation with PV, Battery and Inverter. You can extend the functionality of the gateway by implementing your own device access
drivers. An example of such a device access driver is provided in the folder `device-access`.

The example device access driver will present a single virtual device, that has only one "switch" property, that can be turned on and off. For more details have a look 
at the comments in the source code.

You can change into the example directory and build the driver:

```
> cd device-access
> cmake -B build .
> cmake --build build
```

If you want to install the driver, just build the software like above and do:

```
> sudo cmake --build build --target install
```

Now you need to stop the gateway, change the drivers configuration and start the gateway again in order the example device access driver is loaded:

*Stop the gateway software*:

```
> sudo systemctl stop sigatewayd 
```

*Change the configuration file (Add to the end)* **/etc/openstuder/drivers.conf**:

```
[example]
driver = ExampleDeviceAccess
```

*Start the gateway software*:

```
> sudo systemctl start sigatewayd 
```

Now there should be a device access registered under `example` with the device `example`, which has a boolean property with the id `42` (`example.example.42`).


## authorize drivers

Authorize drivers can be used to replace the build-in user management with another one. For example an LDAP client or something similar.

The example authorize driver will handle all user management in memory (thus not persistent) and has an initial user `admin` with password `admin` and access level `Expert`. The driver 
supports user management. For more details have a look at the comments in the source code.

You can change into the example directory and build the driver:

```
> cd authorize
> cmake -B build .
> cmake --build build
```

If you want to install the driver, just build the software like above and do:

```
> sudo cmake --build build --target install
```

Now you need to stop the gateway, change the gateway configuration and start the gateway again in order the example authorize driver is used instead of the default user management:

*Stop the gateway software*:

```
> sudo systemctl stop sigatewayd 
```

*Change the configuration file (only Authorize section is shown)* **/etc/openstuder/gateway.conf**:

```
[Authorize]
enabled = true
driver = ExampleAuthorize
guestAccessLevel = None
```

*Start the gateway software*:

```
> sudo systemctl start sigatewayd 
```

Now you should be able to log into the gateway using the username and password `admin`/`admin`.


## storage drivers

Storage drivers can be used to store the logged property values and received messages to another storage as the default SQLite database. This can be another database or even a cloud-based
IoT system.

The example storage driver will not store any property values for simplicity and store the device messages only in memory (non-persistent).

You can change into the example directory and build the driver:

```
> cd storage
> cmake -B build .
> cmake --build build
```

If you want to install the driver, just build the software like above and do:

```
> sudo cmake --build build --target install
```

Now you need to stop the gateway, change the gateway configuration and start the gateway again in order the example storage driver is used instead of the default SQLite one:

*Stop the gateway software*:

```
> sudo systemctl stop sigatewayd 
```

*Change the configuration file (only Authorize section is shown)* **/etc/openstuder/gateway.conf**:

```
[Storage]
driver = ExampleStorage
```

*Start the gateway software*:

```
> sudo systemctl start sigatewayd 
```

Now the new storage driver is active and only device messages are stored in memory.
