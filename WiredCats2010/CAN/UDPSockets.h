#ifndef UDPSockets__h_
#define UDPSockets__h_

#include "Task.h"
#include "sockLib.h" 
#include "hostLib.h" 
#include "inetLib.h" 
#include "usrLib.h"
#include "sigLib.h"		// for signal
#include "errno.h"
#include "fioLib.h"
#include "hostLib.h" 
#include "signal.h"
#include <string>
#include "time.h"

class RxUDPSocket
{
	public:
		RxUDPSocket();
		~RxUDPSocket();
		unsigned long  Receive(char * data, unsigned long len);
		
	private:
		int	socketFile;
		struct in_addr remoteIP;
		Task m_obTask;
		SEM_ID m_ThrID;
		bool m_bPoked;
		
		char m_cData[2048];
		unsigned long m_ulLen;
		
		char m_cCachedData[2048];
		unsigned long m_ulCachedLen;

		static void InitTask(RxUDPSocket * pThis);
		void Run();
		int CreateRxSocket(void);
		void WaitForPoke();
};

class TxUDPSocket
{
	public:
		TxUDPSocket();
		~TxUDPSocket();
		
		void Send(char * data, unsigned long len);
		
	private:
		int	socketFile;
		struct in_addr remoteIP;
		Task m_obTask;
		SEM_ID m_ThrID;
		bool m_bPoked;
		
		char m_cData[2048];
		unsigned long m_ulLen;
		
		char m_cCachedData[2048];
		unsigned long m_ulCachedLen;

		static void InitTask(TxUDPSocket * pThis);
		void Run(void);
		int CreateTxSocket(void);
		void WaitForPoke();
};


#endif // UDPSockets__h_


