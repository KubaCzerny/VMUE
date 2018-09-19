#include "VMUE.h"

#define MAX_NUM_ATTEMPS 3


VMUE::VMUE(unsigned char address, MiniMB *COMM){	

	this->int32reg[0].address =300001;		//VOLTAGE
	this->int32reg[1].address =300003;		//CURRENT
	this->int32reg[2].address =300007;		// POWER
	this->int32reg[3].address =300025;		// kWh
	
	this->int16reg[0].address =300027;		// ALARM
	
	this->uint16reg[0].address =304097;		// PASSWORD
	this->uint16reg[1].address =304099;		// ALARM OUTPUT
	this->uint16reg[2].address =304100;		// ALARM TYPE
	this->uint16reg[3].address =304101;		// SETPOINT A
	this->uint16reg[4].address =304102;		// SETPOINT B
	this->uint16reg[5].address =304103;		// ALARM DELAY
	this->uint16reg[6].address =304104;		// ALARM DISABLE DELAY
	this->uint16reg[7].address =304105;		// CURRENT INPUT TYPE
	this->uint16reg[8].address =304108;		// INSTRUMENT ADDRESS
	this->uint16reg[9].address =304109;		// RS485 BOUND RATE;
	this->uint16reg[10].address =312289;	// RESET

	this->RS485_COMM = COMM;		
	this->RS485_address = address;	//set address		

	this->SetCurrentInputType(0);	//set direct current measerument
	this->SetAlarmOutput(1);		//set alarm type to ALARM

}


/*
--------------------------------------------------------------------------
---------------------------------INT32------------------------------------
*/

long VMUE::getVoltage(){
	
	int weight = 10;
	this->DataStatus = 1;
	
	for (int i=0;i<MAX_NUM_ATTEMPS;i++){
		this->RS485_COMM->GetData(this->RS485_address, &this->int32reg[0]);
		if (this->int32reg[0].status)	return (this->int32reg[0].value)/weight;
	}
	this->DataStatus = this->int32reg[0].status;
	return 0;
}	

long VMUE::getCurrent(){
	
	int weight = 100;
	this->DataStatus = 1;	
	
	for (int i=0;i<MAX_NUM_ATTEMPS;i++){
		this->RS485_COMM->GetData(this->RS485_address, &this->int32reg[1]);
		if (this->int32reg[1].status)	return (this->int32reg[1].value)/weight;
	}
	this->DataStatus = this->int32reg[1].status;
	return 0;
}

long VMUE::getPower(){
	
	int weight = 100;
	this->DataStatus = 1;
	
	for (int i=0;i<MAX_NUM_ATTEMPS;i++){
		this->RS485_COMM->GetData(this->RS485_address, &this->int32reg[2]);
		if (this->int32reg[2].status)	return (this->int32reg[2].value)/weight;
	}
	this->DataStatus = this->int32reg[2].status;
	return 0;
}


long VMUE::getkWh(){
	
	int weight = 10;
	this->DataStatus = 1;
	
	for (int i=0;i<MAX_NUM_ATTEMPS;i++){
		this->RS485_COMM->GetData(this->RS485_address, &this->int32reg[3]);
		if (this->int32reg[3].status)	return (this->int32reg[3].value)/weight;
	}
	this->DataStatus = this->int32reg[3].status;
	return 0;
}

/*
--------------------------------------------------------------------------
---------------------------------INT16------------------------------------
*/

int VMUE::getAlarm(){
	
	this->DataStatus = 1;
	
	for (int i=0;i<MAX_NUM_ATTEMPS;i++){
		this->RS485_COMM->GetData(this->RS485_address, &this->int16reg[4]);
		if (this->int16reg[4].status)	return (this->int16reg[4].value);
	}
	this->DataStatus = this->int16reg[4].status;
	return 0;
}

/*
---------------------------------------------------------------------------
---------------------------------UINT16------------------------------------
	this->uint16reg[0].address =304097;		// PASSWORD
	this->uint16reg[1].address =304099;		// ALARM OUTPUT
	this->uint16reg[2].address =304100;		// ALARM TYPE
	this->uint16reg[3].address =304101;		// SETPOINT A
	this->uint16reg[4].address =304102;		// SETPOINT B
	this->uint16reg[5].address =304103;		// ALARM DELAY
	this->uint16reg[6].address =304104;		// ALARM DISABLE DELAY
	this->uint16reg[7].address =304105;		// CURRENT INPUT TYPE
	this->uint16reg[8].address =304108;		// INSTRUMENT ADDRESS
	this->uint16reg[9].address =304109;		// RS485 BOUND RATE;
	this->uint16reg[10].address =312289;	// RESET
*/


bool VMUE::SetPassword(unsigned int password){
	
	MMB_UINT16 tempData;
	tempData = uint16reg[0];
	
	if (password <0 | password > 9999) return 0;
	tempData.value = password;
	
	for (int i=0;i<MAX_NUM_ATTEMPS;i++){
		this->RS485_COMM->SetData(this->RS485_address, &tempData);
		if (tempData.status) {
			uint16reg[0].value = tempData.value;
			uint16reg[0].status = 1;
			return 1;
		}
	}
	uint16reg[0].status = tempData.status;
	return 0;
}


