#ifndef _CNETMARCOS_H_
#define _CNETMARCOS_H_

class IMsgObserver
{
public:
	//接收数据通知
	virtual void onUpdate(void* pMsgHead) = 0;
};

class ISocket
{
public:
	// 关闭连接回调
	virtual void closeSocket() = 0;	
	// 连接成功回调
	virtual void onHandlerConnected() = 0;	
	//远程断开连接
	virtual void onConnectionAbort() = 0;
	//连接失败
	virtual void onConnectFaild() = 0;
};

struct  MsgHead
{
	unsigned int usSize;
	unsigned int usType;
};

struct SeqMsgHead : public MsgHead
{
	unsigned __int64 UserId;		 //用户ID
	int	    SeqId;						 //序列号 C-G之间用
};

#endif //_BBNETMARCOS_H_