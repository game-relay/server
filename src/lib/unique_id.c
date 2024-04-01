/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <relay-server/unique_id.h>
#include <stdlib.h>

RelayUniqueId relayGenerateUniqueIdFromIndex(size_t index)
{
    uint32_t upperPart = (unsigned int) rand() % 0xffffffff;

    RelayUniqueId uniqueIndex = ((uint64_t) upperPart << 32) | index;

    return uniqueIndex;
}

size_t relayUniqueIdGetIndex(RelayUniqueId uniqueIndex)
{
    return uniqueIndex & 0xffffffff;
}
