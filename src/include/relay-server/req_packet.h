/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_REQ_PACKET_H
#define RELAY_SERVER_REQ_PACKET_H

#include <stddef.h>
#include <stdint.h>

struct RelayServer;
struct FldOutStream;
struct FldInStream;
struct GuiseSclUserSession;
struct RelayServerResponse;

int relayReqPacket(struct RelayServer* self, const struct GuiseSclUserSession* userSession, struct FldInStream* inStream,
                 struct RelayServerResponse* response);

#endif
