# Agent usage

1. Go in the root folder (./product/)

2. Stay in the root folder and compile the Agent project as follow :

```
make -C manager/agent/
```

3. The program takes a json configuration file :

```
{
    "id": 1,
    "protobuf_port": 2424,
    "protobuf_host": "127.0.0.1",
    "netconfServer.port": 4242,
    "netconfServer.address": "0.0.0.0",
    "netconfServer.schemasPath": "/home/airbus/workspace/product/etc/netconf/schemas",
    "netconfServer.keyRsa": "/home/airbus/workspace/product/etc/netconf/data/key_rsa",
    "netconfServer.keyDsa": "/home/airbus/workspace/product/etc/netconf/data/key_dsa",
    "netconfServer.acceptTimeout": 35,
    "netconfServer.pollTimeout": 100,
    "netconfServer.sshClients":[
        {
            "username":"local",
            "publicKeyPath":"/home/airbus/workspace/product/etc/netconf/data/key_rsa.pub"
        }
    ],
    "programPath": [
        {
            "capture":"/home/airbus/workspace/product/bin/capture-debug",
            "vision":"/home/airbus/workspace/product/bin/vision-debug"
        }
    ]
}
```

4. Excecute the program __as root__ like below :
```
sudo ./bin/agent-debug "`cat ./agentNetworkConfig.json`"
```

5. In an other terminal, launch the netconfClient with its xml configuration file :

xml configuration file example (exampleLocalManagerToAgent.xml)

```
<magellan-agent xmlns="magellan-agent">
<module>
    <id>2</id>
    <name>capture</name>
    <parameters>{
        "id": 2,
        "interface": "lo",
        "filter": "ip",
        "timeout": 50,
        "promiscMode": 1,
        "tstampType": 0,
        "immediateMode": 1,
        "sharedDataSize": 10000,
        "sharedSize": 300
    }</parameters>
</module>
<module>
    <id>3</id>
    <name>vision</name>
    <parameters>{
        "id": 2,
        "idCapture": 2,
        "sendingTick": 5,
        "filter": "",
        "collectorReceiverHost": "127.0.0.1",
        "collectorReceiverPort": 2424
    }</parameters>
</module>
<module>
    <id>4</id>
    <name>vision</name>
    <parameters>{
        "id": 2,
        "idCapture": 1,
        "sendingTick": 5,
        "filter": "",
        "collectorReceiverHost": "127.0.0.1",
        "collectorReceiverPort": 2424
    }</parameters>
</module>
</magellan-agent>
```

	
5.1. clone the toolkit repository

5.2. checkout in branch netconfClient

5.3. compile, then run as follow
	
## __Warnings !!!__
	
__The [toolkit] program takes 2 configurations files (__ key_rsa __&__ key_rsa.pub __) that are present in the [product] repository !!!__

__The following files :__ *key_rsa* __and__ *key_rsa.pub* __, has to be the same between the repositories "product/etc/ and toolkit (branch netconClient)"__

```
./bin/plugClientNetconf-debug "local" "127.0.0.1" 4242 "/home/airbus/workspace/product/etc/netconf/data/key_rsa.pub" "/home/airbus/workspace/product/etc/netconf/data/key_rsa" exampleLocalManagerToAgentMod1.2.xml
```

compiler le programme et executer

./bin/plugClientNetconf-debug "local" "127.0.0.1" 4242 "absolutePathToProduct/etc/netconf/data/key_rsa.pub" "absolutePathToProduct/etc/netconf/data/key_rsa" ../config/exampleLocalManagerToAgentMod2.3.xml

# Changelog
## 2019-05-27 - version 0.0.0
The agent takes its configuration through a json file as program argument.
During its running the program can read an xml configuration file sent through the network protocol _netconf_

Then, it launch the modules present in the received configuration.

When a new configuration is received after a first one, the launched module will be stopped.