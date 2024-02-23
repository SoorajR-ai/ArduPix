
#include "ardumav.h"

Ardumav::Ardumav(Stream *stream)
{
    this->stream = stream;
}

void Ardumav::run()
{
    mavTimestamp = millis();

    while (stream->available()) {
        uint8_t rxByte    = stream->read();
        mvlPacketReceived = mavlink_parse_char(mvlChannel, rxByte, &mvlRxMessage, &mvlRxStatus);
        if (mvlPacketReceived) {
            process_msg();
            break;
        }
    }

    if ((mavTimestamp - mavHeartbeatTimestamp > 1000)) {
        heartbeat();
    }

    if(mavTimestamp-mavStatTimestap>100){
        mavStatTimestap=mavTimestamp;
        SendStatus();
    }
}
void Ardumav::SendStatus(){
    ProcessGps();
}
void Ardumav::transmitMessage(mavlink_message_t *mvlMsgPtr)
{
    uint8_t txByteBuffer[512] = {0};

    uint16_t txBufLen = mavlink_msg_to_send_buffer(txByteBuffer, mvlMsgPtr);

    stream->write(txByteBuffer, txBufLen);
}

void Ardumav::heartbeat()
{
    mavlink_heartbeat_t mvlHb;
    mvlHb.type          = MAV_TYPE_GENERIC;
    mvlHb.autopilot     = MAV_AUTOPILOT_GENERIC;
    mvlHb.system_status = MAV_STATE_ACTIVE;

    if (mvlArmed) {
        mvlHb.base_mode = MAV_MODE_MANUAL_ARMED;
    } else {
        mvlHb.base_mode = MAV_MODE_MANUAL_DISARMED;
    }

    mvlHb.base_mode |= MAV_MODE_FLAG_MANUAL_INPUT_ENABLED;

    mavlink_msg_heartbeat_encode_chan(mvlSysId, mvlCompId, mvlChannel, &mvlTxMessage, &mvlHb);
    transmitMessage(&mvlTxMessage);

    mavHeartbeatTimestamp = millis();
}

void Ardumav::process_msg()
{
    mvlPacketReceived = 0;

    switch (mvlRxMessage.msgid) {
    case MAVLINK_MSG_ID_COMMAND_LONG: {
        CommandLongHandler(&mvlRxMessage);
        break;
    }
    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
        ParamRequestListHandler(&mvlRxMessage);
        break;
    }
    default: {
    }
    }
}

void Ardumav::CommandLongHandler(mavlink_message_t *mvlMsgPtr)
{

    mavlink_command_long_t mvlCmd;
    mavlink_msg_command_long_decode(mvlMsgPtr, &mvlCmd);
    switch (mvlCmd.command) {
    case (MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES): {
        if (mvlCmd.param1 == 0) {
            mavlink_autopilot_version_t mvl_apv;
            mvl_apv.flight_sw_version     = 2;
            mvl_apv.middleware_sw_version = 1;
            mvl_apv.board_version         = 1;
            mvl_apv.vendor_id             = 10101;
            mvl_apv.product_id            = 20202;
            mvl_apv.uid                   = 0;
            mvl_apv.capabilities          = 0;
            mvl_apv.capabilities |= MAV_PROTOCOL_CAPABILITY_SET_ATTITUDE_TARGET;
            mvl_apv.capabilities |= MAV_PROTOCOL_CAPABILITY_MAVLINK2;
            mavlink_msg_autopilot_version_encode_chan(mvlSysId, mvlCompId, mvlChannel, &mvlTxMessage, &mvl_apv);
            transmitMessage(&mvlTxMessage);
        }
        break;
    }
    case (MAV_CMD_COMPONENT_ARM_DISARM): {
        mvlArmed = (1 == mvlCmd.param1) ? 1 : 0;
        mavlink_command_ack_t mvlAck;
        mvlAck.command = MAV_CMD_COMPONENT_ARM_DISARM;
        mvlAck.result  = MAV_RESULT_ACCEPTED;
        mavlink_msg_command_ack_encode_chan(mvlSysId, mvlCompId, mvlChannel, &mvlTxMessage, &mvlAck);
        transmitMessage(&mvlTxMessage);
    }
    default: {
    }
    }
}

void Ardumav::ParamRequestListHandler(mavlink_message_t *mvlMsgPtr)
{
    mavlink_param_value_t mvl_param;
    mvl_param.param_count = 0;
    mvl_param.param_index = 0;
    mavlink_msg_param_value_encode_chan(mvlSysId, mvlCompId, mvlChannel,
                                        &mvlTxMessage, &mvl_param);
    transmitMessage(&mvlTxMessage);
}

uint8_t Ardumav::GetArmStatus()
{
    return mvlArmed;
}

void Ardumav::ProcessGps(){
    if(GPS_Got_Updated){
    mavlink_global_position_int_t pos;
    GPS_Got_Updated=false;
    pos.time_boot_ms=0;
    pos.lat = GPS_Got_Lat;
    pos.lon = GPS_Got_Lon;
    pos.hdg = GPS_Got_Hdng;
    mavlink_msg_global_position_int_encode(mvlSysId,mvlCompId, &mvlTxMessage,&pos);
    transmitMessage(&mvlTxMessage);
    }
}

void Ardumav::SetPosition(bool update = false,float lat=0, float lon=0, float hdng=0){
    GPS_Got_Updated=update;
    GPS_Got_Lat = lat*1E7;
    GPS_Got_Lon = lon*1E7;
    GPS_Got_Hdng = hdng;
}