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

	//ע��Socket����
	void addEventListener(ISocket* value);
	//Socket����
	bool connect(const char* szServerIP, int wPort);
	//Socket����
	void reConnect(const char* szServerIP, int wPort);
	//��������
	void sendData(MsgHead* pMsgHead, bool bPushQueue = false);
	//�ر�Socket
	void closeSocket(bool bNotify = false);
	//�Ƿ�������״̬
	bool getIsConnect();
	//���ݼ����¼�
	void* RemoteCall processNetMsg(void *pParam);	
	//����SeqId����
	void setActiveSeqFlag( bool ActiveFlg );
	//��ȡSeqId���
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
	//��֤SeqId;
	int m_iSeqId;
	//�Ƿ�����SeqId;
	bool m_bActiveSeqIdFlg;
	CSocketAdapter m_clientSocket;
};

#endif	//_CNETSERVICE_H_