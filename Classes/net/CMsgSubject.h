#ifndef _CMSGSUBOBJECT_H_
#define _CMSGSUBOBJECT_H_

#include "CSingleton.h"
#include <map>
#include <queue>
#include <vector>
#include <string>
#include "CNetMarcos.h"
#include "CHandler.h"

class IMsgObserver;
struct SeqMsgHead;

//////////////////////////////////////////////////////////////////////////
//CMsgMsgSubjectHandler
class CMsgMsgSubjectHandler : public CHandler
{
public:
	CMsgMsgSubjectHandler(void){}
	virtual ~CMsgMsgSubjectHandler(void){}
	void handlerMessage( CMessage* msg );
};


class CMsgSubject : public CSingleton<CMsgSubject>
{
protected:
	friend class CSingleton<CMsgSubject>;
	CMsgSubject(void);
	~CMsgSubject(void);

public:
	virtual void OnMessage(const char* bytes, int nLen);
	virtual void RegObserver(unsigned short type,  IMsgObserver* pObserver);
	virtual void DelObserver(unsigned short type, IMsgObserver* pObserver);
	
	void OnDispatchMessage(SeqMsgHead* pMsgHead);

private:
	bool m_bIsChange;
	bool m_DispatchFlg;
	typedef std::vector<IMsgObserver*> vIMsgObserverBase;
	std::map<unsigned short, vIMsgObserverBase> m_msgMap;
	std::queue<SeqMsgHead*> m_MsgBuf_vector;
	CMsgMsgSubjectHandler* mHandler;
};

#define CMsgSubjectShared CMsgSubject::getInstance()

class IMessage
{
private:
	union 
	{
		char	bufMsg[2048];
		struct 
		{
			unsigned short usMsgSize;
			unsigned short usMsgType;
		};
	};
public:
	IMessage(void);
	IMessage(const void* buf)
	{	
		memset(bufMsg,0, sizeof(bufMsg));
		if (buf)
		{
			unsigned short size = *((unsigned short*) buf);
			if (size <= 2048)
				memcpy(bufMsg, buf, size);
		}

	}
	IMessage(int size, int type, const void* buf); 
	IMessage(const IMessage& rhs)
	{
		memset(bufMsg,0, sizeof(bufMsg));
		memcpy(bufMsg, rhs.bufMsg, sizeof(bufMsg));
	}; 

	int			Release	(void)	{ delete this; return 0;};

	int			GetSize	(void) const	{ return usMsgSize; }
	int			GetType	(void) const	{ return usMsgType; }
	const void*		GetBuf	(void) const	{ return bufMsg; }
};

#endif //_CMSGSUBOBJECT_H_