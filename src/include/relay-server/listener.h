/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_LISTENER_H
#define RELAY_LISTENER_H

struct GuiseSclUserSession;

#include <relay-serialize/types.h>

typedef struct RelayListener {
    const struct GuiseSclUserSession* providingUserSession;
    RelaySerializeListenerId id;
    RelaySerializeApplicationId applicationId;
    RelaySerializeChannelId channelId;
} RelayListener;

void relayListenerInit(RelayListener* self, const struct GuiseSclUserSession* providingUserSession,
                       RelaySerializeListenerId listenerId, RelaySerializeApplicationId applicationId,
                       RelaySerializeChannelId channelId);

#endif
