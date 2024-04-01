/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_LISTENERS_H
#define RELAY_SERVER_LISTENERS_H

#include <clog/clog.h>
#include <stddef.h>
#include <stdlib.h>

struct RelayListener;
struct GuiseSclUserSession;
struct RelayAddress;
struct ImprintAllocator;

typedef struct RelayListeners {
    struct RelayListener* listeners;

    size_t connectionCount;
    size_t capacityCount;
    RelaySerializeChannelId channelId;
    RelaySerializeApplicationId applicationId;
    Clog log;
} RelayListeners;

void relayListenersInit(RelayListeners* self, struct ImprintAllocator* allocator, size_t maxCount, Clog log);
// void relayListenersDestroy(RelayListeners* self);
int relayListenersFind(const RelayListeners* self, RelaySerializeListenerId uniqueId,
                       struct RelayListener** outSession);
int relayListenersCreate(RelayListeners* sessions, const struct GuiseSclUserSession* userSession,
                         RelaySerializeApplicationId applicationId, RelaySerializeChannelId channelId,
                         struct RelayListener** outSession);
struct RelayListener* relayListenersFindUsingUserId(const RelayListeners* self,
                                                    RelaySerializeApplicationId applicationId,
                                                    RelaySerializeChannelId channelId, RelaySerializeUserId userId);

struct RelayListener* relayListenersFindOrCreate(RelayListeners* self, const struct GuiseSclUserSession* userSession,
                                                 RelaySerializeApplicationId applicationId,
                                                 RelaySerializeChannelId channelId);
void relayListenersReset(RelayListeners* self);
void relayListenersDestroy(RelayListeners* self);

#endif
