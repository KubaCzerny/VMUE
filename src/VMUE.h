#ifndef VMUE_h
#define VMUE_h
#endif

#include "MiniMB.h"

class VMUE 
{


public:

	VMUE(unsigned char RS485_address, MiniMB *COMM)	;
	
	unsigned char RS485_address;
	
	int DataStatus;
	
	long getVoltage();	//ok
	long getCurrent();	//ok
	long getPower();	//ok	
	long getkWh();		//ok
	
	int	 getAlarm();	//ok

	bool SetPassword(unsigned int password);
	bool SetAlarmOutput(int alarm);										
	bool SetAlarmType(int type);
	bool SetPointA(int type);
	bool SetPointB(int type);	
	bool SetAlarmDelay(int delay);
	bool SetAlarmDisableDelay(int delay);
	bool SetCurrentInputType(bool type);		
	bool SetRS485Address (unsigned char address);		//save to ARDUUINO EEPROM MEMORY
	bool SetRS485Bound (int bound);
	bool Resetmeasurement(int type);
	
	
	
private:
	
	MMB_INT32 int32reg[5];
	MMB_UINT16 uint16reg[12];
	MMB_INT16 int16reg[1];
	
	MiniMB *RS485_COMM;
	
};
