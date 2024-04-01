/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <relay-server/address.h>
#include <stdio.h>
#include <tiny-libc/tiny_libc.h>

#if defined TORNADO_OS_WINDOWS
#include <Ws2tcpip.h>
#endif

int relayAddressEqual(const RelayAddress* a, const RelayAddress* b)
{
    return (a->sin_addr.s_addr == b->sin_addr.s_addr && a->sin_port == b->sin_port);
}

const char* relayAddressToString(const RelayAddress* self, char* temp, size_t maxCount)
{
    const char* converted = inet_ntop(AF_INET, &self->sin_addr, temp, (socklen_t) maxCount - 6);

    size_t len = tc_strlen(converted);

    sprintf(&temp[len], ":%d", self->sin_port);

    return temp;
}
