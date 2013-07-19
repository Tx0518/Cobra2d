#ifndef _CNETSERVICE_H_
#define _CNETSERVICE_H_

#include "CService.h"
#include "CSingleton.h"
#include "CSocketAdapter.h"
#include "CThread.h"
#include "CNetMarcos.h"

#include "zthread/Thread.h"

using namespace ZThread;

// #define SEQID()					CNetService::getInstance()->getSeqId();
// #define SENDMSG(msg)		CNetService::getInstance()->sendData(msg);

class CSocketThread : public Runnable
{
public:
	CSocketThread(void){}
	virtual ~CSocketThread(void){}
	virtual void run();
};


class CNetService : public CService
{
public:
	CNetService(void);
	virtual ~CNetService(void);

	//注册Socket监听
	void addEventListener(ISocket* value);
	//Socket连接
	bool connect(const char* szServerIP, int wPort);
	//Socket重连
	void reConnect(const char* szServerIP, int wPort);
	//发送数据
	void sendData(MsgHead* pMsgHead, bool bPushQueue = false);
	//关闭Socket
	void closeSocket(bool bNotify = false);
	//是否处于连接状态
	bool getIsConnect();
	//数据监听事件
	void* RemoteCall processNetMsg(void *pParam);	
	//启用SeqId开关
	void setActiveSeqFlag( bool ActiveFlg );
	//获取SeqId序号
	int getSeqId();
	bool isActiveSeqIdFlg();

public:
	virtual void onStart();
	virtual void onAcceptIntent(CIntent* intent);
	virtual void onSynchResponse(CResponse* response);
	virtual void onFinish();
private:
	CThread m_SocketThread;
	//CSocketThread m_SocketThread;
	//验证SeqId;
	int m_iSeqId;
	//是否启用SeqId;
	bool m_bActiveSeqIdFlg;
	CSocketAdapter m_clientSocket;
};

#endif	//_CNETSERVICE_H_