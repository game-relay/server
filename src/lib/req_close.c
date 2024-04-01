/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <relay-serialize/serialize.h>
#include <relay-server/connection.h>
#include <relay-server/req_close.h>
#include <relay-server/server.h>

/// Listener wants the connection to be closed
/// @param self server
/// @param userSession user session that wants to close the connection
/// @param inStream stream to read from
/// @param outStream response stream
/// @return negative on error
/// @note not implemented yet
int relayReqClose(RelayServer* self, const struct RelayUserSession* userSession, FldInStream* inStream,
                  FldOutStream* outStream)
{
    (void) userSession;
    (void) inStream;
    (void) outStream;
    (void) self;

    return 0;
}
