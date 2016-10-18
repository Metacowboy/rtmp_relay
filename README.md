# RTMP relay v0.1

[![Build Status](https://api.travis-ci.org/elnormous/rtmp_relay.svg?branch=master)](https://travis-ci.org/elnormous/rtmp_relay) [![Build Status](https://ci.appveyor.com/api/projects/status/9axwxwyf99dcr11d?svg=true)](https://ci.appveyor.com/project/elnormous/rtmp_relay)

Relays RTMP streams to multiple endpoints.

# Usage

RTMP relay uses cppsocket and yaml-cpp submodules. The following command has to be run after cloning the RTMP relay:

```
$ git submodule update --init
```

To compile the RTMP relay, just run "make" in the root directory. To launch it, run "./bin/rtmp_relay --config config.yaml". You can optionally pass "--daemon" to run it as a daemon or "--kill-daemon" to kill it.

# Configuration

RTMP relay configuration files are YAML-based. It must start with servers array. Each server has following attributes:

* *listen* – the address server is listening to
* *applications* – application object (can be multiple for each server)
 * *name* – name of the application (optional if server should route all applications)
 * *push* – array of push destinations
  * *overrideStreamName* – string to override the stream name with
  * *addresses* – list of addresses to push to
  * *video* – flag that indicates wether to forward video stream
  * *audio* – flag that indicates wether to forward audio stream
  * *data* – flag that indicates wether to forward data stream
  * *metaDataBlacklist* – list of metadata fields that should not be forwarded
  * *connectionTimeout* – how long should the attempt to connect last
  * *reconnectInterval* – the interval of reconnection
  * *reconnectCount* – amount of connect attempts

*overrideStream* name can have the following tokens:

* ${name} – name of the source stream
* ${applicationName} – name of the application
* ${address} – IP address of the destination
* ${port} – destination port

Example configuration:

    servers:
      - listen: "127.0.0.1:2200"
        applications:
          - name: "app/name"
            push:
              - overrideStreamName: "test_${name}"
                address: "10.0.1.1:1935"
                video: true
                audio: true
                connectionTimeout: 5.0
                reconnectInterval: 5.0
                reconnectCount: 3
          - name: "casino/roulette"
            push:
              - address: [ "10.0.1.2:1935", "10.0.1.3:1935" ]
                video: true
                audio: true
                connectionTimeout: 5.0
                reconnectInterval: 5.0
                reconnectCount: 3