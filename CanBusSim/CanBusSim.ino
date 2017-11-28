/*
 Name:		CanBusSim.ino
 Created:	2017-11-25
 Authors:	ericdes
 Note:		Most of the code has been taken from CAN-BUS Shiel (demo / send data). Link: http://wiki.seeed.cc/CAN-BUS_Shield_V1.2/
*/
 
#include <mcp_can.h>
#include <SPI.h>

#define COOLANT_TEMPERATURE	0x05
#define RPM         		0x0C
#define SPEED	     	 	0x0D
#define MAF_SENSOR          0x10
#define O2_VOLTAGE         	0x14
#define THROTTLE_POSITION	0x11

MCP_CAN CAN(10); // Set CS to pin 10


void setup()
{
	Serial.begin(115200);

START_INIT:

	if (CAN.begin(CAN_500KBPS) == CAN_OK) // init can bus : baudrate = 500k
	{
		Serial.println("CAN BUS Shield init ok!");
	}
	else
	{
		Serial.println("CAN BUS Shield init fail");
		Serial.println("Init CAN BUS Shield again");
		delay(100);
		goto START_INIT;
	}
}


void loop()
{
	// CAN.sendMsgBuf(INT8U id, INT8U ext, INT8U len, data_buf);
	// - id represents where the data comes from.
	// - ext represents the status of the frame.‘0’ means standard frame.‘1’ means extended frame.
	// - len represents the length of this frame.
	// - data_buf is the content of this message.

	INT8U txMsg[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }; // Message we're sending
	CAN.sendMsgBuf(0x00, 0, 8, txMsg);
	delay(100); // Send message every 100ms
}
