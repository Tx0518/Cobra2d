#ifndef _CMESSAGE_H_
#define _CMESSAGE_H_

#include "CCobraObject.h"

enum eMsgMode
{
	eFree = 0,
	eProcessing,
};

/************************************************************************/
/*
	CMessage
*/
class CMessage : public CCobraObject
{
public:
	CMessage(void);
	CMessage(CMessage& msg);
	virtual ~CMessage(void);
	CMessage& operator=(CMessage& msg);
	COBRA_CREATE_PROPERTY(int,m_iMsgType,MsgType)
	COBRA_CREATE_PROPERTY(void*,m_pObj,Obj)
	COBRA_CREATE_PROPERTY(int,m_iMsgMode,MsgMode)
};

/************************************************************************/
#endif	//_CMESSAGE_H_