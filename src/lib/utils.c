/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/game-relay/server
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <flood/out_stream.h>
#include <guise-sessions-client/user_session.h>
#include <relay-serialize/server_out.h>
#include <relay-server/connection.h>
#include <relay-server/listener.h>
#include <relay-server/utils.h>

/// Send a connect request from an initiator to a listener
/// @param foundConnection connection
/// @param response response
/// @return negative on error
int relayServerSendConnectRequestToListener(const RelayListener* listener, RelayServerConnection* foundConnection,
                                            RelayServerResponse* response)
{
    FldOutStream outStream;
    uint8_t buf[512];
    fldOutStreamInit(&outStream, buf, 512);

    RelaySerializeConnectRequestFromServerToListener data;
    data.debugRequestId = foundConnection->createdFromRequestId;
    data.fromUserId = foundConnection->initiatorUserSession->userId;
    data.listenerId = listener->id;
    data.connectionId = foundConnection->id;

    int err = relaySerializeServerOutConnectRequestToListener(&outStream, data);
    if (err < 0) {
        return err;
    }
    return response->sendDatagram.send(response->sendDatagram.self,
                                       &foundConnection->listener->providingUserSession->address, buf, outStream.pos);
}
