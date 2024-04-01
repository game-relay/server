/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_CONNECTIONS_H
#define RELAY_SERVER_CONNECTIONS_H

#include "connection.h"
#include <stdlib.h>

struct RelayServerConnection;
struct GuiseSclUserSession;
struct RelayListener;

typedef struct RelayServerConnections {
    struct RelayServerConnection* connections;
    size_t connectionCount;
    size_t capacityCount;
    Clog log;
} RelayServerConnections;

void relayServerConnectionsInit(RelayServerConnections* self, size_t maxCount, Clog log);
void relayServerConnectionsDestroy(RelayServerConnections* self);
struct RelayServerConnection* relayServerConnectionsFindConnection(RelayServerConnections* self,
                                                                   RelayServerConnectionId id);
struct RelayServerConnection* relayServerConnectionsFindOrCreateConnection(
    RelayServerConnections* self, const struct GuiseSclUserSession* initiatorUserSession,
    RelaySerializeUserId targetUserId, struct RelayListener* listener, RelaySerializeApplicationId applicationId,
    RelaySerializeChannelId channelId, RelaySerializeRequestId createFromRequestId);
#endif
