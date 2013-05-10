#ifndef _CSOCKETADAPTER_H_
#define _CSOCKETADAPTER_H_

#include <string>

class CSocket;
class ISocket;

#define USE_NEW_SOCKET 1

class CSocketAdapter
{
	enum
	{
		kDataStreamBufferLen = 65536,
	};

public:
	CSocketAdapter(void);
	~CSocketAdapter(void);

	//连接成功
	virtual void connectionSucceed();
	//连接失败
	virtual void connectionFailed();
	//收到信息
	virtual void reciveMessage(const char* lpMsgBuf, int nLen);
	//请求失败
	//virtual void requestFailed(ERROR_RES errorRes);
	//远程连接断开
	virtual void onConnectionAbort();

	//连接
	bool Connect(std::string szServerIP,  int wPort);
	//发送函数
	bool sendData(char* buf, int nLen, bool bPushQueue = false);
	//关闭连接
	void closeSocket(bool bNotify = false);
	void addEventListener(ISocket* value);
	bool getIsConnect();

	void processNetMsg();
	bool StopThread();

private:
	void pushStream2Buffer(const char* pStream, int nLen);
	void popStreamFromBuffer(int nLen);
protected:
	ISocket* m_iSocketConnectEvent;

	//数据流缓冲
	char	m_dataStreamBuffer[kDataStreamBufferLen];
	//当前数据流长度
	int		m_nCurDataStreamLen;
private:
	CSocket* m_pSocket;
	bool			m_bReady;
	int				m_nConnectServerFlag;
};


#endif //_CSOCKETADAPTER_H_