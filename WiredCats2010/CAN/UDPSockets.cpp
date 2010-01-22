#include "UDPSockets.h"

#include "Synchronized.h"



RxUDPSocket::RxUDPSocket() : m_obTask("2CAN Rx",(FUNCPTR)InitTask)
{
	m_bPoked = false;
	socketFile = -1	;
	m_ThrID = semMCreate(SEM_Q_PRIORITY);
	m_ulLen = 0;
	int ret = m_obTask.Start((INT32)this); 
	if (!ret)
	{
		//wpi_fatal(UDPTaskError);
	}
}

RxUDPSocket::~RxUDPSocket()
{
	if(socketFile != -1)
		close(socketFile);
	socketFile = -1;
	
	m_obTask.Stop();
}

void RxUDPSocket::InitTask(RxUDPSocket * pThis)
{
	pThis->Run();
}
void RxUDPSocket::Run()
{
	struct sockaddr_in      serverSockAddr;
	int						bytes;
	int				sin_len;
	char					remoteIPString[20];

	sprintf(remoteIPString, "10.%02u.%02u.10", 2, 17);

	if (!inet_aton(remoteIPString, &remoteIP))
	{
		//return ;
	}

	if (CreateRxSocket())
		return ;

	while (1)
	{
		sin_len = sizeof(serverSockAddr);

		
		bytes = recvfrom(socketFile, m_cCachedData, 1024, 0,
			(struct sockaddr*)&serverSockAddr, &sin_len);

		if (serverSockAddr.sin_addr.s_addr == remoteIP.s_addr)
			if (bytes > 0)
			{
				m_ulCachedLen = bytes;
				CRITICAL_REGION(m_ThrID);
				memcpy(m_cData,m_cCachedData,m_ulLen = m_ulCachedLen);
				END_REGION;
	
				WaitForPoke();
			}

	}
}
int RxUDPSocket::CreateRxSocket(void)
{
	struct sockaddr_in	sin;

	if ((socketFile = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return (errno);
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(1141);
	sin.sin_addr.s_addr = INADDR_ANY;

	if (bind(socketFile, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		close(socketFile);
		socketFile = -1;
		return (errno);
	}

	return (0);
}
unsigned long RxUDPSocket::Receive(char * data, unsigned long len)
{
	CRITICAL_REGION(m_ThrID);
	if(len > m_ulLen)
		len = m_ulLen;
	memcpy(data,m_cData,len);
	m_bPoked = true;
	m_ulLen = 0;
	END_REGION;
	
	return len;
}

void RxUDPSocket::WaitForPoke()
{
	bool bPoked = false;
	while(!bPoked)
	{
		CRITICAL_REGION(m_ThrID);
		bPoked = m_bPoked;
		END_REGION;

		taskDelay(10);
	}
	CRITICAL_REGION(m_ThrID);
	m_bPoked = false;
	END_REGION;
}






TxUDPSocket::TxUDPSocket() : m_obTask("2CAN Tx",(FUNCPTR)InitTask)
{
	m_bPoked = false;
	socketFile = -1;
	m_ThrID = semMCreate(SEM_Q_PRIORITY);
	m_ulLen = 0;
	if (!m_obTask.Start((INT32)this))
	{
		//wpi_fatal(UDPTaskError);
	}
}

TxUDPSocket::~TxUDPSocket()
{
	if(socketFile != -1)
		close(socketFile);
	socketFile = -1;
	
	m_obTask.Stop();
}

void TxUDPSocket::InitTask(TxUDPSocket * pThis)
{
	pThis->Run();
}

void TxUDPSocket::WaitForPoke()
{
	bool bPoked = false;
	while(!bPoked)
	{
		CRITICAL_REGION(m_ThrID);
		bPoked = m_bPoked;
		END_REGION;

		taskDelay(10);
	}
	CRITICAL_REGION(m_ThrID);
	m_bPoked = false;
	END_REGION;
}
void TxUDPSocket::Send(char * data, unsigned long len)
{
	CRITICAL_REGION(m_ThrID);
	m_bPoked = true;
	memcpy(m_cData,data,len);
	m_ulLen = len;
	END_REGION;
}
void TxUDPSocket::Run(void)
{
	struct sockaddr_in      serverSockAddr;
	int						bytes;
	char					remoteIPString[20];

	sprintf(remoteIPString, "10.%02u.%02u.10", 2, 17);

	if (!inet_aton(remoteIPString, &remoteIP))
	{
		//return ;
	}

	if (CreateTxSocket())
		return ;

	while (1)
	{
		WaitForPoke();
		CRITICAL_REGION(m_ThrID);
		memcpy(m_cCachedData,m_cData,m_ulCachedLen = m_ulLen);
		END_REGION;
		
		memset(&serverSockAddr, 0, sizeof(serverSockAddr));

		serverSockAddr.sin_family = AF_INET;
		serverSockAddr.sin_addr.s_addr = remoteIP.s_addr;
		serverSockAddr.sin_port = htons(1217);

		bytes = sendto(socketFile, m_cData, m_ulCachedLen, 0,
			(struct sockaddr*)&serverSockAddr, sizeof(serverSockAddr));

	}
}

int TxUDPSocket::CreateTxSocket(void)
{
	struct sockaddr_in	sin;

	if ((socketFile = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return (errno);
	}

	sin.sin_family = AF_INET;
	sin.sin_port = htons(1217);
	sin.sin_addr.s_addr = INADDR_ANY;

	if (bind(socketFile, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		close(socketFile);
		socketFile = -1;
		return (errno);
	}

	return (0);
}




