#include "CMessage.h"

CMessage::CMessage(void)
	:m_pObj(NULL),
	m_iMsgMode(eProcessing),
	m_iMsgType(0)
{
}

CMessage::CMessage( CMessage& msg )
{
	m_iMsgMode = msg.getMsgMode();
	m_iMsgType = msg.getMsgType();
	m_pObj = msg.getObj();
}

CMessage::~CMessage()
{
	m_pObj = NULL;
	delete m_pObj;
}

CMessage& CMessage::operator=( CMessage& msg )
{
	m_iMsgMode = msg.getMsgMode();
	m_iMsgType = msg.getMsgType();
	m_pObj = msg.getObj();
	return *this;
}
