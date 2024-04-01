/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_UNIQUE_ID_H
#define RELAY_SERVER_UNIQUE_ID_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t RelayUniqueId;

RelayUniqueId relayGenerateUniqueIdFromIndex(size_t index);
size_t relayUniqueIdGetIndex(RelayUniqueId uniqueIndex);

#endif
