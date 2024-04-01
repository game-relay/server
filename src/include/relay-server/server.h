/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef CONCLAVE_SERVER_SERVER_H
#define CONCLAVE_SERVER_SERVER_H

#include <clog/clog.h>
#include <guise-sessions-client/address.h>
#include <guise-sessions-client/client.h>
#include <relay-serialize/types.h>
#include <relay-server/address.h>
#include <relay-server/connections.h>
#include <relay-server/listeners.h>
#include <relay-server/transport.h>
#include <stdarg.h>

struct ImprintAllocator;
struct RelayServerResponse;

typedef struct RelayServer {
    GuiseSclClient guiseSclClient;
    RelayServerConnections connections;
    RelayListeners listeners;
    Clog log;
} RelayServer;

int relayServerInit(RelayServer* self, struct ImprintAllocator* memory, GuiseSerializeUserSessionId loginForThisServer,
                    DatagramTransport transportToGuiseServer, Clog log);
void relayServerDestroy(RelayServer* self);
void relayServerReset(RelayServer* self);
int relayServerFeed(RelayServer* self, const RelayAddress* address, const uint8_t* data, size_t len,
                    struct RelayServerResponse* response);
void relayServerUpdate(RelayServer* self);

#endif
