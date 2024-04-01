/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_REQ_CONNECT_H
#define RELAY_SERVER_REQ_CONNECT_H

#include <relay-server/address.h>

struct RelayServer;
struct FldOutStream;
struct FldInStream;
struct RelayServerResponse;
struct GuiseSclUserSession;

int relayReqConnect(struct RelayServer* self, const struct GuiseSclUserSession* userSession, struct FldInStream* inStream,
                    struct FldOutStream* outStream, struct RelayServerResponse* response);
#endif
