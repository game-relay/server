/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_TRANSPORT_H
#define RELAY_SERVER_TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

#include <relay-server/address.h>

typedef int (*relayServerSendFn)(void* self, const RelayAddress* address, const uint8_t* data, size_t size);
typedef struct RelayServerSendDatagram {
    relayServerSendFn send;
    void* self;
} RelayServerSendDatagram;

#endif
