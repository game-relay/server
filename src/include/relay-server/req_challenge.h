/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_SERVER_REQ_CHALLENGE_H
#define RELAY_SERVER_REQ_CHALLENGE_H

#include <relay-server/address.h>

struct RelayServer;
struct FldOutStream;

int relayReqChallenge(struct RelayServer* self, const RelayAddress* address, const uint8_t* data, size_t len,
                      struct FldOutStream* outStream);

#endif
