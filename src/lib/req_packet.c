/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <clog/clog.h>
#include <flood/in_stream.h>
#include <flood/out_stream.h>
#include <guise-sessions-client/user_session.h>
#include <inttypes.h>
#include <relay-serialize/commands.h>
#include <relay-serialize/serialize.h>
#include <relay-serialize/server_out.h>
#include <relay-server/connection.h>
#include <relay-server/listener.h>
#include <relay-server/req_packet.h>
#include <relay-server/server.h>
#include <relay-server/utils.h>

/// A packet is requested to be sent to the remote for that connection
/// @param self server
/// @param userSession user session that wants to send a datagram
/// @param inStream stream with datagram
/// @param response the response
/// @return negative on error
int relayReqPacket(RelayServer* self, const GuiseSclUserSession* userSession, FldInStream* inStream,
                   RelayServerResponse* response)
{
    RelaySerializeConnectionId connectionId;
    relaySerializeReadConnectionId(inStream, &connectionId);

    RelayServerConnection* foundConnection = relayServerConnectionsFindConnection(&self->connections, connectionId);
    if (foundConnection == 0) {
        return -4;
    }

    const struct GuiseSclUserSession* target = 0;
    if (foundConnection->listener->providingUserSession == userSession) {
        // If listener is sending to an initiator and knows the connection handle, the listener has
        // implicitly accepted it
        target = foundConnection->initiatorUserSession;
        if (foundConnection->phase == RelayServerConnectionPhaseConnecting) {
            CLOG_C_DEBUG(&self->log, "listener sent a packet on connection, we can mark it as accepted")
            foundConnection->phase = RelayServerConnectionPhaseAcceptedByListener;
        }
    } else if (foundConnection->initiatorUserSession == userSession) {
        target = foundConnection->listener->providingUserSession;
        if (foundConnection->phase == RelayServerConnectionPhaseConnecting) {
            // listener has not accepted the connection, so send request
            CLOG_C_DEBUG(&self->log, "listener has not accepted this connection, so send it as a connection request")
            return relayServerSendConnectRequestToListener(foundConnection->listener, foundConnection, response);
        }
    } else {
        CLOG_C_NOTICE(&self->log, "not allowed to send packets on this connection")
    }

    uint16_t packetOctetCount;
    fldInStreamReadUInt16(inStream, &packetOctetCount);

    uint8_t buf[DATAGRAM_TRANSPORT_MAX_SIZE];

    FldOutStream outStream;
    fldOutStreamInit(&outStream, buf, DATAGRAM_TRANSPORT_MAX_SIZE);

    RelaySerializeServerPacketFromServerToClient packetHeader;
    packetHeader.packetOctetCount = packetOctetCount;
    packetHeader.connectionId = foundConnection->id;
    relaySerializeServerOutPacketToClientHeader(&outStream, packetHeader);

    fldOutStreamWriteOctets(&outStream, inStream->p, packetOctetCount);
    inStream->pos += packetOctetCount;
    inStream->p += packetOctetCount;

    RelayServerSendDatagram* sendDatagram = &response->sendDatagram;

    CLOG_C_VERBOSE(&self->log, "relay packet over the connection %" PRIX64, connectionId)
    sendDatagram->send(sendDatagram->self, &target->address, buf, outStream.pos);

    return 0;
}
