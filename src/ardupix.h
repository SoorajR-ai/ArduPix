#ifndef ARDUMAV_H
#define ARDUMAV_H

#include "mavlink.h"
#include "Arduino.h"

class Ardumav
{
  private:
    unsigned long mavTimestamp;
    unsigned long mavHeartbeatTimestamp;
    unsigned long mavStatTimestap;

    mavlink_message_t mvlTxMessage;
    mavlink_message_t mvlRxMessage;
    mavlink_status_t  mvlRxStatus;

    const uint8_t mvlCompId  = 1;
    const uint8_t mvlSysId   = 1;
    const uint8_t mvlChannel = MAVLINK_COMM_1;

    uint8_t mvlArmed          = 0;
    uint8_t mvlPacketReceived = 0;

    float GPS_Got_Lat=0;
    float GPS_Got_Lon = 0;
    float GPS_Got_Hdng = 0;
    bool GPS_Got_Updated=false;

    Stream *stream;

    virtual void transmitMessage(mavlink_message_t *mvlMsgPtr);

    virtual void CommandLongHandler(mavlink_message_t *mvlMsgPtr);
    virtual void ParamRequestListHandler(mavlink_message_t *mvlMsgPtr);

    virtual void heartbeat();
    virtual void process_msg();
    virtual void ProcessGps();
    virtual void SendStatus();

  public:
    Ardumav(Stream *str = NULL);

    virtual void run();

    virtual uint8_t GetArmStatus();
    virtual void SetPosition(bool update,float lat, float lon, float hdng);
};

#endif 
