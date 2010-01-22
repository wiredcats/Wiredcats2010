#ifndef C2CAN__H_
#define TOUCAN__H_

#if 1

#include "UDPSockets.h"
#include "2CANDataObjects.h"
#include "SpeedController.h"

#define iC2CAN_OK					(0)
#define iC2CAN_ErrorTooManyJags	(1)
#define iC2CAN_ErrorInvalidID		(2)
#define iC2CAN_ErrorNoComm			(3)

typedef unsigned int C2CAN_Error_t;
typedef unsigned int JagID_t;


class C2CAN
{
	public:
		C2CAN();
		~C2CAN();
		
		static C2CAN* C2CAN::GetInstance();

		
		C2CAN_Error_t SetVoltage(JagID_t id,		float fVoltage);
		C2CAN_Error_t SetVoltageRamp(JagID_t id,	float fVperMs);

		C2CAN_Error_t GetOutputVoltage(JagID_t id,	float &fVoltage);
		C2CAN_Error_t GetBusVoltage(JagID_t id,	float &fVoltage);
		C2CAN_Error_t GetTemperature(JagID_t id,	float &fTemp);
		
		void Discard();
		void FeedWatchDog();
	private:

		static void InitTask(C2CAN * pThis);
		void Run(void);
		
		unsigned short CheckSum(unsigned short * data,unsigned long len);

		void Swap(STo2CAN_UpdateJagPacket & Packet);
		void Swap(SOutputPacket & Packet);
		void Swap(SInputPacket & Packet);

		Task m_obTask;


		STo2CAN_UpdateJagPacket obTo2CAN_UpdateJagPacket;
		STo2CAN_UpdateJagPacket obTo2CAN_UpdateJagPacketRaw;
		
		SOutputPacket obInPacketRaw;
		SOutputPacket obInPacket;
		//SInputPacket obOutPacketRaw;
		//SInputPacket obOutPacket;

		SEM_ID m_ThrID;
		bool m_bDie;
		double m_dWatchdogTick;
		
		SJag obJags[MAX_NUM_JAGS];
		
		SJagParameters obJagPars[MAX_NUM_JAGS];
};


class JaguarOverCAN : public SpeedController
{
	public:
		JaguarOverCAN(unsigned int iID)
		{
			m_iID = iID;
			m_pC2CAN = C2CAN::GetInstance();
		}
		
		virtual ~JaguarOverCAN()
		{
		}
		
		virtual void Set(float speed)
		{
			if(speed > 1)
				speed = 1;
			else if(speed < -1)
				speed = -1;
			m_fSpeed = speed;
			float fVoltage = 12 * speed;
			m_pC2CAN->SetVoltage(m_iID,fVoltage);
		}

		virtual float Get()
		{
			return m_fSpeed;
		}
	private:
		unsigned int m_iID;
		float m_fSpeed;
		C2CAN * m_pC2CAN;
};

#endif
#endif // C2CAN__H_


