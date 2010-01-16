#ifndef TOUCANDATAOBJECTS__H_
#define TOUCANDATAOBJECTS__H_

#pragma pack(push,2)


typedef unsigned long int32;
typedef unsigned short int16;
typedef unsigned char int8;

#define MAX_NUM_JAGS	(8)

#define JAG_PARAM_SIZE_BYTES		90
#define JAG_SIZE_BYTES				50
#define JAG_MGR_PARAM_SIZE_BYTES	16
//#define PACKET_SIZE_BYTES			(1518 - 18 - 40 - 512) // 1410 = MAX Ether Frame - mac header & crc - max ip header - max udp header - 50 for good measure
#define PACKET_SIZE_BYTES			(1024) // 1410 = MAX Ether Frame - mac header & crc - max ip header - max udp header - 50 for good measure
#define JAG_NAME_CAPACITY			10

#define MIN_OUT_PACKET_SIZE		(MAX_NUM_JAGS*(JAG_SIZE_BYTES+JAG_NAME_CAPACITY)+ 8)
#define MIN_IN_PACKET_SIZE		(MAX_NUM_JAGS*JAG_PARAM_SIZE_BYTES + JAG_MGR_PARAM_SIZE_BYTES + 8)

#if MIN_OUT_PACKET_SIZE > PACKET_SIZE_BYTES
	#error MIN_OUT_PACKET_SIZE TOO LARGE
#endif
#if MIN_IN_PACKET_SIZE > PACKET_SIZE_BYTES
	#error MIN_IN_PACKET_SIZE TOO LARGE
#endif


#define REMAINING_IN_PACKET_SIZE_BYTES	 (PACKET_SIZE_BYTES - MIN_IN_PACKET_SIZE)
#define REMAINING_OUT_PACKET_SIZE_BYTES	 (PACKET_SIZE_BYTES - MIN_OUT_PACKET_SIZE)
#define REMAINING_JAGPARAM_PACKET_SIZE_BYTES	 (sizeof(SJagParameters) - sizeof(SJagParametersTight))
#define REMAINING_JAG_PACKET_SIZE_BYTES	 		(sizeof(SJag) - sizeof(SJagTight))





// ----------- Signatures for each packet type
#define SIG_JAG_INPUT_PACKET	(0xAAAA)
#define SIG_JAG_OUTPUT_PACKET	(0xBBBB)
#define SIG_CAN_INPUT_PACKET	(0xCCCC)	//TODO
#define SIG_CAN_OUTPUT_PACKET	(0xDDDD)	//TODO

#define SIG_UPDATE_JAG_PACKET	(0xAAA0)


typedef union _STo2CAN_UpdateJagPacket
{
	struct
	{
		int16 iSig;
		int16 iByteLen;

		int16 uiMode[20];
		int16 uiSetVoltage[20];
	};
	struct
	{
		int16 Words[511];
		int16 iCRC;
	};
}STo2CAN_UpdateJagPacket;




#define JAG_MODE_VOLTAGE	(0)
#define JAG_MODE_CURRENT	(1)
#define JAG_MODE_SPEED		(2)
#define JAG_MODE_POSITION	(3)
#define JAG_MODE_OFF		(0xFF)

typedef struct _S32BitFixedPoint
{
	int16 iFrac;	
	int16 iWhole;
}S32BitFixedPoint;


//System Control APIs
#define JAG_OPTION1_SYTEM_CNTRL_HALT		(0x0001)
#define JAG_OPTION1_SYTEM_CNTRL_RESET		(0x0002)
#define JAG_OPTION1_SYTEM_CNTRL_GETFIRMVER	(0x0004)
//Status
#define JAG_OPTION1_STATUS_GETVOLTOUT		(0x0008)
#define JAG_OPTION1_STATUS_GETVOLTBUS		(0x0010)
#define JAG_OPTION1_STATUS_GETCURRENT		(0x0020)
#define JAG_OPTION1_STATUS_GETTEMP			(0x0040)
#define JAG_OPTION1_STATUS_GETFAULT			(0x0080)
//Motor Control
#define JAG_OPTION1_MC_GETBRUSHES			(0x0100)
#define JAG_OPTION1_MC_GETENC				(0x0200)
#define JAG_OPTION1_MC_GETPOT				(0x0400)
//voltage
#define JAG_OPTION1_MC_SETMODE				(0x0800)
#define JAG_OPTION1_MC_SETVOLTAGE			(0x1000)
#define JAG_OPTION1_MC_SETVOLTAGERAMP		(0x2000)
//speed
#define JAG_OPTION1_MC_SETSETSPEED			(0x4000)
#define JAG_OPTION1_MC_SETSPEEDP			(0x8000)
#define JAG_OPTION2_MC_SETSPEEDI			(0x0001)
#define JAG_OPTION2_MC_SETSPEEDD			(0x0002)
#define JAG_OPTION2_MC_SETSPEEDREF			(0x0004)
//pos
#define JAG_OPTION2_MC_SETSETPOS			(0x0008)
#define JAG_OPTION2_MC_SETPOSP				(0x0010)
#define JAG_OPTION2_MC_SETPOSI				(0x0020)
#define JAG_OPTION2_MC_SETPOSD				(0x0040)
#define JAG_OPTION2_MC_SETPOSREF			(0x0080)
//current
#define JAG_OPTION2_MC_SETSETCUR			(0x0100)
#define JAG_OPTION2_MC_SETCURP				(0x0200)
#define JAG_OPTION2_MC_SETCURI				(0x0400)
#define JAG_OPTION2_MC_SETCURD				(0x0800)

#define JAG_OPTION2_MC_SEBRKCST				(0x1000)
#define JAG_OPTION2_MC_SETSOFTLIMIT			(0x2000)
#define JAG_OPTION2_MC_SETFORLIM			(0x4000)
#define JAG_OPTION2_MC_SETREVLIM			(0x8000)
#define JAG_OPTION2_MC_SETMAX_VOLT			(0x0001)
				
#define JAG_STATUS1_CURRENT_FAULT			(0x0001)
#define JAG_STATUS1_TEMP_FAULT				(0x0002)
#define JAG_STATUS1_UNDERVOLTAGE_FAULT		(0x0004)	
				
				
#define JAGMGR_OPTION1_SET_ID				(0x0001)
#define JAGMGR_OPTION1_ENUM					(0x0002)

typedef union _SJagParameters
{
	struct
	{
		int16 iDeviceType;
		
		//System Control APIs
		int16 iFirmwareHigh;
		int16 iFirmwareLow;
		
		int16 iMode;
		
		//Voltage Mode
		int16 iSetVoltage;
		int16 iSetVoltageRamp;
		
		//Speed Mode - not supported in 3330
		S32BitFixedPoint iSetSpeed;
		S32BitFixedPoint iSpeedP;
		S32BitFixedPoint iSpeedI;
		S32BitFixedPoint iSpeedD;
		int16 iSpeedRef;
		
		//Position Mode - not supported in 3330
		S32BitFixedPoint iSetPosition;
		S32BitFixedPoint iPositionP;
		S32BitFixedPoint iPositionI;
		S32BitFixedPoint iPositionD;
		int16 iPositionRef;
		
		//Current Mode - not supported in 3330
		int16 iSetCurrent;
		S32BitFixedPoint iCurrentP;
		S32BitFixedPoint iCurrentI;
		S32BitFixedPoint iCurrentD;
		
		//Motor Control
		int16 iBreakCoast;
		int16 iSoftLimit;
		int16 iForwardSwitch1;
		int16 iForwardSwitch2;
		int16 iReverseSwitch1;
		int16 iReverseSwitch2;
		int16 iMaxVoltage;
		
		int16 iOptions1;
		int16 iOptions2;
		int16 iOptions3;
		int16 iOptions4;
	};
	int16 Words[JAG_PARAM_SIZE_BYTES/2];
}SJagParameters;

#define ENUM_STATUS_MARK	(0)
#define ENUM_STATUS_SUCCESS	(1)
#define ENUM_STATUS_FAILED	(2)
	
#define ENUM_STATUS_TIMEOUT_MS	(10)

typedef union _SJag
{
	struct
	{
		int16 iDeviceType;
		int16 iID;
		
		//System Control APIs
		int16 iFirmwareHigh;
		int16 iFirmwareLow;
		
		int16 iMode;
		
		int16 iVoltageOut;
		int16 iVoltageBus;
		int16 iCurrent;
		int16 iTemp;
		int16 iTimeoutMs;
		
		int16 iRxState;
		int16 iRxTimeoutMs;
		int16 iEnumState;
		int16 iEnumStateTimeoutMs;
		
		int16 iStatus1;
		int16 iStatus2;
		int16 iStatus3;
		int16 iStatus4;
	};
	int16 Words[JAG_SIZE_BYTES/2];
}SJag;
typedef struct _SJagMgrParameters
		{
			struct
			{
		int16 iOptions1;
		int16 iOptions2;
		int16 iOptions3;
		int16 iOptions4;
				
		int16 iSetID;
		};
		
	int16 Words[JAG_MGR_PARAM_SIZE_BYTES/2];
}SJagMgrParameters;


typedef union _SOutputPacket
{
	struct
	{
		int16 iSig;
		int16 iByteLen;
		int16 iJagCount;
		SJag obJags[MAX_NUM_JAGS];
		char sJags[MAX_NUM_JAGS][10];
		int16 iCRC;
	};
	int16 Words[PACKET_SIZE_BYTES/2];
}SOutputPacket;

typedef union _SInputPacket
{
	struct
	{
		int16 iSig;
		int16 iByteLen;
		int16 iJagCount;
		SJagParameters obJagParams[MAX_NUM_JAGS];
		SJagMgrParameters obJagMgrParam;
		int16 iCRC;
	};
	int16 Words[PACKET_SIZE_BYTES/2];
}SInputPacket;


#pragma pack(pop)

#endif // TOUCANDATAOBJECTS__H_


