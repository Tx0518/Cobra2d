#include "CNetService.h"

#ifndef MAXINT32
#define MAXINT32 2147483647
#endif

CNetService::CNetService( void )
	:m_bActiveSeqIdFlg(false),
	m_iSeqId(0)
{

}

CNetService::~CNetService( void )
{

}

void CNetService::onStart()
{

}

void CNetService::onAcceptIntent( CIntent* intent )
{

}

void CNetService::onSynchResponse( CResponse* response )
{

}

void CNetService::onFinish()
{
	m_clientSocket.addEventListener(NULL);
	closeSocket(false);
}

void CNetService::addEventListener( ISocket* value )
{
	m_clientSocket.addEventListener(value);
}

bool CNetService::connect( const char* szServerIP, int wPort )
{
	setActiveSeqFlag(false);
	bool m_Connected = m_clientSocket.Connect(szServerIP, wPort);
	if( m_Connected ) 
	{
		//Start Receiving News Thread
		m_SocketThread.Run(CExecutor::Bind(&CNetService::processNetMsg),this,NULL);
	}
	return m_Connected;
}

void CNetService::reConnect( const char* szServerIP, int wPort )
{
	m_clientSocket.closeSocket(true);
	connect(szServerIP, wPort);
}

void CNetService::sendData( MsgHead* pMsgHead, bool bPushQueue /*= false*/ )
{
	m_clientSocket.sendData((char*)pMsgHead, pMsgHead->usSize, bPushQueue);
}

void CNetService::closeSocket( bool bNotify /*= false*/ )
{
	setActiveSeqFlag(false);
	m_clientSocket.closeSocket(bNotify);
}

bool CNetService::getIsConnect()
{
	return m_clientSocket.getIsConnect();
}

void* RemoteCall CNetService::processNetMsg( void *pParam )
{
		//线程模式
		while(1)
		{
			if( m_clientSocket.StopThread() ) return 0;
			m_clientSocket.processNetMsg();
#ifdef WIN32
			Sleep(1000);
#else 
			usleep(10000); //todo
#endif
		}

		//主线程驱动模式
 		//if( m_clientSocket.StopThread() ) return 0;
 		//m_clientSocket.processNetMsg();
		
		return 0;
}

void CNetService::setActiveSeqFlag( bool ActiveFlg )
{
	m_bActiveSeqIdFlg = ActiveFlg; 
	if( !m_bActiveSeqIdFlg ) m_iSeqId = 0; 
}

int CNetService::getSeqId()
{
	if ( m_bActiveSeqIdFlg )
	{
		if( m_iSeqId > MAXINT32 ) m_iSeqId = 0;
		return ++m_iSeqId;
	}
	return 0;
}

bool CNetService::isActiveSeqIdFlg()
{
	return m_bActiveSeqIdFlg;
}
