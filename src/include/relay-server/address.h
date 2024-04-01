/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_ADDRESS_H
#define RELAY_SERVER_ADDRESS_H

#if defined TORNADO_OS_WINDOWS
#include <WinSock2.h>
#include <Windows.h>
#else
#include <netinet/in.h>
#endif

typedef struct sockaddr_in RelayAddress;
int relayAddressEqual(const RelayAddress* a, const RelayAddress* b);
const char* relayAddressToString(const RelayAddress* self, char* temp, size_t maxCount);

#endif
