/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_CONNECTION_H
#define RELAY_SERVER_CONNECTION_H

#include "unique_id.h"
#include <relay-serialize/types.h>

struct GuiseSclUserSession;
struct RelayListener;

typedef enum RelayServerConnectionPhase {
    RelayServerConnectionPhaseConnecting,
    RelayServerConnectionPhaseAcceptedByListener,
    RelayServerConnectionPhaseClosedByListener,
} RelayServerConnectionPhase;

typedef RelayUniqueId RelayServerConnectionId;

typedef struct RelayServerConnection {
    RelayServerConnectionId id;
    RelaySerializeApplicationId applicationId;
    RelaySerializeChannelId channelId;
    RelaySerializeRequestId createdFromRequestId;
    const struct GuiseSclUserSession* initiatorUserSession;
    const struct RelayListener* listener;
    RelayServerConnectionPhase phase;
} RelayServerConnection;

#endif
