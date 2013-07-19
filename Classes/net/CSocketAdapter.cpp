#include "CSocketAdapter.h"
#include "CMsgSubject.h"
#include "CSocket.h"

CSocketAdapter::CSocketAdapter(void)
	:m_iSocketConnectEvent(NULL),
	m_nCurDataStreamLen(0),
	m_bReady(false),
	m_pSocket(NULL),
	m_nConnectServerFlag(0)
{
	memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
}


CSocketAdapter::~CSocketAdapter(void)
{
	if(NULL != m_pSocket)
	{
		closeSocket(false);
	}
}

//连接
bool CSocketAdapter::Connect(std::string szServerIP, int wPort)
{
#if USE_NEW_SOCKET
	if(szServerIP.empty() || wPort<0)
		return false;
	if(m_pSocket == NULL)
		m_pSocket = new CSocket();
	if (!m_pSocket) 
		return false;
	if( !m_pSocket->Check())
	{
		if(m_pSocket->create(szServerIP.c_str(), wPort, 30)) 
		{
			this->m_bReady	=true;
			connectionSucceed();
			return true;
		}
		else
		{
			this->m_bReady	=false;
			connectionFailed();
			return false;
		}
	}
#else
	m_Socket.setCallBack(this);
	bool bFlag = m_Socket.connect(szServerIP.c_str(), wPort);
	return bFlag;
#endif
	return false;
}

//发送函数
bool CSocketAdapter::sendData(char* buf, int nLen, bool bPushQueue /*= false*/)
{
#if USE_NEW_SOCKET
	if(!m_bReady || !buf) {
		return false;
	}

	bool bSucSend;
	try {
		//bSucSend	=::ClientSocketSendMsg(pbufMsg, dwSize);
		if (m_pSocket) {
			bSucSend = m_pSocket->sendMsg(buf, nLen);
		}
	}
	catch(...)
	{
		//LogMsg("catch error in send msg.");		
	}
#else
	m_Socket.sendMessage(buf, nLen, bPushQueue);
#endif
	return true;
}
//关闭连接
void CSocketAdapter::closeSocket(bool bNotify)
{
	if(NULL != m_iSocketConnectEvent && bNotify)
	{
		m_iSocketConnectEvent->closeSocket();
	}

#if USE_NEW_SOCKET
	if (m_bReady && m_pSocket)
	{
		// ::ClientSocketDestroy();
		m_pSocket->Flush();
		m_pSocket->Destroy();
		m_bReady	=false;
	}

	delete m_pSocket;
	m_pSocket = NULL;
#else
	m_Socket.close();
#endif
}

void CSocketAdapter::addEventListener(ISocket* value)
{
	m_iSocketConnectEvent = value;
}


void CSocketAdapter::pushStream2Buffer(const char* pStream, int nLen)
{
	if(m_nCurDataStreamLen + nLen >= kDataStreamBufferLen)
	{
		//		CCLOG("<<<<<<<<<<<<<<<< ERROR: data stream buffer is full! >>>>>>>>>>>>>>>>>>");
		return;
	}

	memcpy(m_dataStreamBuffer+m_nCurDataStreamLen, pStream, nLen);
	m_nCurDataStreamLen += nLen;
}

void CSocketAdapter::popStreamFromBuffer(int nLen)
{
	if(m_nCurDataStreamLen - nLen <= 0)
	{
		m_nCurDataStreamLen = 0;
		memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);

		//       CCLOG(">>>>>>>>>>>>>>>>>>>>>>>  ClientSocket::popStreamFromBuffer popBufLen:%d Message Buffer stream is null!", nLen);

		return;
	}

	int nResidueLen = m_nCurDataStreamLen - nLen;

	//   CCLOG(">>>>>>>>>>>>>>>>>>>>>>>  ClientSocket::popStreamFromBuffer curBufLen:%d popBufLen:%d residueBufLen:%d ",
	//          m_nCurDataStreamLen, nLen, nResidueLen);

	//#ifndef _UNUSE_MEMPOOL_
	//	char *pTmpBuf = static_cast<char*>(CMemPool::getInstance().GetMemory(nResidueLen));
	//#else
	char *pTmpBuf = new char[nResidueLen];
	//#endif

	memset(pTmpBuf, 0, nResidueLen);
	memcpy(pTmpBuf, m_dataStreamBuffer + nLen, nResidueLen);
	memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
	memcpy(m_dataStreamBuffer, pTmpBuf, nResidueLen);
	m_nCurDataStreamLen = nResidueLen;

	//	CMemPool::getInstance().FreeMemory(pTmpBuf, nResidueLen);
	if(NULL != pTmpBuf)
	{
		delete[] pTmpBuf;
		pTmpBuf = NULL;
	}
	//if(m_nCurDataStreamLen - nLen >= 0)
	//	m_nCurDataStreamLen -= nLen;
	//else
	//	m_nCurDataStreamLen = 0;
}

void CSocketAdapter::processNetMsg()
{
#if USE_NEW_SOCKET
	if (!m_pSocket) {
		return;
	}

	if (!m_pSocket->Check()) {
		m_pSocket = NULL;
		// 掉线了
		onConnectionAbort();
		return;
	}

	// 发送数据（向服务器发送消息）
	//m_pSocket->Flush();

	// 接收数据（取得缓冲区中的所有消息，直到缓冲区为空）
	while (true)
	{
		char buffer[_MAX_MSGSIZE] = { 0 };
		int nSize = sizeof(buffer);
		char* pbufMsg = buffer;
		if(m_pSocket == NULL)
		{
			break;
		}
		if (!m_pSocket->receiveMsg(pbufMsg, nSize)) {
			break;
		}

		while (true)
		{
			SeqMsgHead* pReceiveMsg = (SeqMsgHead*)(pbufMsg);
			UINT16	dwCurMsgSize = pReceiveMsg->usSize;
			//CCLOG("msgsize: %d  msgtype:%d", dwCurMsgSize,pReceiveMsg->usType);

			if((int)dwCurMsgSize > nSize || dwCurMsgSize <= 0) 
			{	
				break;
			}
			CMsgSubject::getInstance()->OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);
			pbufMsg	+= dwCurMsgSize;
			nSize	-= dwCurMsgSize;
			if(nSize <= 0)
			{
				break;
			}
		}
	}
#else
	//	while (true) {
	m_Socket.processNetMsg();
	if(m_nCurDataStreamLen <= 0)
		return;
	SeqMsgHead* pReceiveMsg = (SeqMsgHead*)(m_dataStreamBuffer);
	if(m_nCurDataStreamLen < pReceiveMsg->usSize)
		return;

	CMsgSubject::getInstance()->OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);
	popStreamFromBuffer(pReceiveMsg->usSize);
	//	}
#endif
}

//连接成功
void CSocketAdapter::connectionSucceed()
{
	if(NULL != m_iSocketConnectEvent)
	{
		m_iSocketConnectEvent->onHandlerConnected();
	}

}
//连接失败
void CSocketAdapter::connectionFailed()
{
	// CCMessageBox("连接服务器失败!", "Error!");
	/*CLoginModule::getInstance().connectFaild();*/
	//LoginManager::getInstance().onConnectFaild();
	m_bReady = false;
	if(NULL != m_iSocketConnectEvent)
	{
		m_iSocketConnectEvent->onConnectFaild();
	}
}
//收到信息
void CSocketAdapter::reciveMessage(const char* lpMsgBuf, int nLen)
{
	//MessageSubject::instance().OnMessage(lpMsgBuf, nLen);
	// CC_SAFE_DELETE(buf);

	//CCLOG("ClientSocket::reciveMessage dataStramSize:%d", nLen);

	pushStream2Buffer(lpMsgBuf, nLen);
}
//请求失败
/*void GClientSocket::requestFailed(ERROR_RES errorRes)
{

}*/
//远程连接断开
void CSocketAdapter::onConnectionAbort()
{
	std::string strMessageInfo = "与服务器连接中断!";
	//CCMessageBox("与服务器连接中断!", "ERROR!!");
	m_bReady = false;
	if(NULL != m_iSocketConnectEvent)
	{
		m_iSocketConnectEvent->onConnectionAbort();
	}
}


bool CSocketAdapter::getIsConnect()
{
	return m_bReady;
}

bool CSocketAdapter::StopThread()
{
	if (!m_pSocket) {
		return true;
	}
	if (!m_pSocket->Check()) {
		m_pSocket = NULL;
		// 掉线了
		onConnectionAbort();
		return true;
	}
	return false;
}

