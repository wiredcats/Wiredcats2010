#include "2CAN.H"

#include "2CANDataObjects.H"

#include "Timer.h"
#include "Synchronized.h"

void Swap(int16 & var)
{
	union
	{
		int16 u16;
		char bytes[2];
	} b;
	b.u16 = var;
	char cSwap = b.bytes[1];
	b.bytes[1] = b.bytes[0];
	b.bytes[0] = cSwap;
	var = b.u16;
}

/**
 * C2CAN contructor.
 * 
 * This is only called once the first time GetInstance() is called
 */
C2CAN::C2CAN()  : m_obTask("C2CAN",(FUNCPTR)InitTask)
{
	m_bDie = false;
	m_dWatchdogTick = 0;
	
	memset(&obInPacketRaw,0,sizeof(obInPacketRaw));
	memset(&obInPacket,0,sizeof(obInPacket));
	memset(&obTo2CAN_UpdateJagPacket,0,sizeof(obTo2CAN_UpdateJagPacket));
	memset(&obTo2CAN_UpdateJagPacket.uiMode,0xff,sizeof(obTo2CAN_UpdateJagPacket.uiMode));

	
	
	
	memset(&obJagPars,0,sizeof(obJagPars));
	
	obTo2CAN_UpdateJagPacket.iSig = SIG_UPDATE_JAG_PACKET;
	obInPacket.iSig = SIG_JAG_OUTPUT_PACKET;
	obTo2CAN_UpdateJagPacket.iByteLen = sizeof(obTo2CAN_UpdateJagPacket);
	obInPacket.iByteLen = sizeof(obInPacket);

	obInPacketRaw.iSig = SIG_JAG_OUTPUT_PACKET;
	obInPacketRaw.iByteLen = sizeof(obInPacketRaw);

	m_ThrID = semMCreate(SEM_Q_PRIORITY);

	if (!m_obTask.Start((INT32)this))
	{
		//wpi_fatal(DriverStationTaskError);
	}
}

C2CAN::~C2CAN()
{
	//m_pInstance = NULL;
	
	Discard();
}
/**
 * Return a pointer to the singleton C2CAN.
 */
C2CAN* C2CAN::GetInstance()
{
	static C2CAN* m_pInstance = NULL;
	if (m_pInstance == NULL)
		m_pInstance = new C2CAN();
	return m_pInstance;
}

void C2CAN::InitTask(C2CAN * pThis)
{
	pThis->Run();
}
void C2CAN::Swap(STo2CAN_UpdateJagPacket & Packet)
{
	for(unsigned int i=0;i<sizeof(Packet)/2;++i)
		::Swap(Packet.Words[i]);
}
void C2CAN::Swap(SOutputPacket & Packet)
{
	for(unsigned int i=0;i<sizeof(Packet)/2;++i)
		::Swap(Packet.Words[i]);
}	
void C2CAN::Swap(SInputPacket & Packet)
{
	for(unsigned int i=0;i<sizeof(Packet)/2;++i)
		::Swap(Packet.Words[i]);
}

unsigned short C2CAN::CheckSum(unsigned short * data,
											unsigned long byte_len)
{
	unsigned int i=0;
	unsigned short c=0;
	
	c = 0;
	for(;i<byte_len/2;++i)
	{
		c += data[i];
	}

	return ~c + 1;
}
void C2CAN::Discard()
{
	CRITICAL_REGION(m_ThrID);
	m_bDie = true;
	END_REGION;
	
	m_obTask.Stop();
}
void C2CAN::FeedWatchDog()
{
	CRITICAL_REGION(m_ThrID);
	m_dWatchdogTick = GetTime();
	END_REGION;
}
void C2CAN::Run()
{
	bool bDie = false;
	
	unsigned long len;

	RxUDPSocket obRx;
	TxUDPSocket obTx;
	
	while(bDie == false)
	{
		len = sizeof(obInPacket);
		len = obRx.Receive((char*)&obInPacketRaw,len);
		if(len)
		{
			Swap(obInPacketRaw);
			unsigned short chk = CheckSum((unsigned short*)&obInPacketRaw,sizeof(obInPacketRaw));
			if(chk == 0)
			{
				obInPacket = obInPacketRaw;
			}
		}

//		mapJagParams_t::iterator i = m_mapJagParams.begin();
//		obOutPacket.iJagCount = 0;
//		for(;i!= m_mapJagParams.end();++i)
//		{
//			obOutPacket.obJagParams[ obOutPacket.iJagCount++ ] = i->second;
//			
//			if(obOutPacket.iJagCount == MAX_NUM_JAGS)
//				break;
//				
//		}


		bool bTx = false;
		
		CRITICAL_REGION(m_ThrID);
		if( m_dWatchdogTick)
		{
			if( (GetTime() - m_dWatchdogTick) < .2) 
			{	
				bTx = true;
			}
			else
				m_dWatchdogTick = 0;
		}
		END_REGION;
		
		if( bTx)
		{
			//obOutPacket.iJagCount = MAX_NUM_JAGS;
			//obOutPacketRaw = obOutPacket;
			obTo2CAN_UpdateJagPacketRaw = obTo2CAN_UpdateJagPacket;
			obTo2CAN_UpdateJagPacketRaw.iCRC = 0;
			obTo2CAN_UpdateJagPacketRaw.iCRC = CheckSum((unsigned short*)&obTo2CAN_UpdateJagPacket,sizeof(obTo2CAN_UpdateJagPacket));
			Swap(obTo2CAN_UpdateJagPacketRaw);
			obTx.Send((char*)&obTo2CAN_UpdateJagPacketRaw, sizeof(obTo2CAN_UpdateJagPacketRaw));
		}
		
		taskDelay(10);
		
		CRITICAL_REGION(m_ThrID);
		bDie = m_bDie;
		END_REGION;
	}
}

C2CAN_Error_t C2CAN::SetVoltage(JagID_t id,float fVoltage)
{
	if((id-1) >= MAX_NUM_JAGS)
		return iC2CAN_ErrorInvalidID;
	
	if(fVoltage > 12)
		fVoltage = 12;
	else if(fVoltage < -12)
		fVoltage = -12;
	
	signed short ss = (signed short)(fVoltage/12.0f * 32767);

	obTo2CAN_UpdateJagPacket.uiMode[id-1] = JAG_MODE_VOLTAGE;
	obTo2CAN_UpdateJagPacket.uiSetVoltage[id-1] = ss;
	
	return 0;
}

