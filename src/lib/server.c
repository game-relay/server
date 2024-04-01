/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <guise-serialize/serialize.h>
#include <guise-serialize/types.h>
#include <guise-sessions-client/user_session.h>
#include <guise-sessions-client/user_sessions.h>
#include <imprint/allocator.h>
#include <relay-serialize/commands.h>
#include <relay-serialize/debug.h>
#include <relay-server/address.h>
#include <relay-server/req_connect.h>
#include <relay-server/req_listen.h>
#include <relay-server/req_packet.h>
#include <relay-server/server.h>
#include <relay-server/utils.h>

static int readAndLookupUserSession(GuiseSclClient* client, const GuiseSclAddress* address, FldInStream* inStream,
                                    const GuiseSclUserSession** out)
{
    GuiseSerializeUserSessionId userSessionId;
    int err = guiseSerializeReadUserSessionId(inStream, &userSessionId);
    if (err < 0) {
        *out = 0;
        return err;
    }

    err = guiseSclClientLookup(client, address, userSessionId, out);
    if (err < 0) {
        *out = 0;
        return err;
    }

    return 0;
}

/// Handle incoming datagrams
/// @param self server
/// @param address network address of request
/// @param data payload
/// @param len octet size of data
/// @param response response
/// @return negative on error
int relayServerFeed(RelayServer* self, const RelayAddress* address, const uint8_t* data, size_t len,
                    RelayServerResponse* response)
{
    CLOG_C_VERBOSE(&self->log, "relayServerFeed: feed: %s octetCount: %zu", relaySerializeCmdToString(data[0]), len)
    static uint8_t buf[DATAGRAM_TRANSPORT_MAX_SIZE];
    FldOutStream outStream;
    fldOutStreamInit(&outStream, buf, DATAGRAM_TRANSPORT_MAX_SIZE);
    int result = -1;
    FldInStream inStream;
    fldInStreamInit(&inStream, data + 1, len - 1);
    const GuiseSclUserSession* foundUserSession;
    int err = readAndLookupUserSession(&self->guiseSclClient, address, &inStream, &foundUserSession);
    if (err < 0) {
        if (err == -1) {
            return 0;
        }
        return err;
    }

    switch (data[0]) {
        case relaySerializeCmdPacket:
            return relayReqPacket(self, foundUserSession, &inStream, response);
        case relaySerializeCmdConnectRequestToServer:
            result = relayReqConnect(self, foundUserSession, &inStream, &outStream, response);
            break;
        case relaySerializeCmdListenRequestToServer:
            result = relayReqListen(self, foundUserSession, &inStream, &outStream);
            break;
        default:
            CLOG_C_SOFT_ERROR(&self->log, "relayServerFeed: unknown command %02X", data[0])
            return 0;
    }

    if (result < 0) {
        return result;
    }

    if (outStream.pos == 0) {
        return result;
    }

    return response->sendDatagram.send(response->sendDatagram.self, address, outStream.octets, outStream.pos);
}

/// Initialize the relay server
/// Must already have a transport to a Guise Server and be logged in.
/// @param self server
/// @param memory allocator
/// @param log target log
/// @return negative on error
int relayServerInit(RelayServer* self, struct ImprintAllocator* memory,
                    GuiseSerializeUserSessionId assignedSessionIdForThisRelayServer,
                    DatagramTransport transportToGuiseServer, Clog log)
{
    (void) assignedSessionIdForThisRelayServer;

    self->log = log;

    Clog subLog;
    subLog.config = log.config;

    guiseSclClientInit(&self->guiseSclClient, transportToGuiseServer, assignedSessionIdForThisRelayServer, subLog);

    relayServerConnectionsInit(&self->connections, 128, subLog);
    relayListenersInit(&self->listeners, memory, 128, subLog);

    return 0;
}

void relayServerUpdate(RelayServer* self)
{
    guiseSclClientUpdate(&self->guiseSclClient);
}

void relayServerReset(RelayServer* self)
{
    (void) self;
}

void relayServerDestroy(RelayServer* self)
{
    (void) self;
}
