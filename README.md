# Relay Server Lib

Relay server for datagrams

> **Note** Only for testing, not production ready

Uses [Relay Serialize](https://github.com/piot/relay-serialize-c)

## Connection Flow

* A listener tells the server that the user wants to receive incoming connect requests for a certain application and channel (to allow multiple listeners for each application). The channel is usually zero.
* An initiator tries to connect to the listener using the listener userId, application and channel. The request is assigned a unique connection Id.
* The listener receives the connection request that has the unique connection Id included. The listener can now send datagrams on that connection to the initiator.
* The initiator receives a datagram for that connectionId and then knows that the connection is accepted.
