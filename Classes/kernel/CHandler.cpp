#include "CHandler.h"
#include "CEvent.h"
#include "CIntent.h"
#include "CMemoryCache.h"
#include "CService.h"
#include "CActivity.h"
#include "CMessage.h"

CHandler::CHandler( void )
	:m_eHandlerType(COMPLICATING)
{
}

CHandler::~CHandler( void )
{
}

void CHandler::postMessage( CMessage* msg )
{
	if(m_pMsgSet.size() < MAX_HANDLER_MESSAGE_COUNT)
	{
		m_pMsgSet.push_back(msg);
	}
	else
	{
		CMessage* freeMsg = getFreeMessage();
		COBRA_CHECK_NULL(msg);
		freeMsg = msg;
	}
	dispatchMessage();
}

void CHandler::handlerMessage( CMessage* msg )
{
	COBRA_CHECK_NULL(msg);
	COBRA_RETURN_IF(msg->getMsgMode() == eProcessing);
	msg->setMsgMode(eFree);
	//do something
}


static int sequenceId = 0; //记录顺序的编号ID

void CHandler::dispatchMessage()
{
	if(m_pMsgSet.empty()) return;
	if(m_eHandlerType == COMPLICATING) //并发处理消息队列
	{
		doComplicating();
	}
	else if(m_eHandlerType == SEQUENCE) //序列处理消息队列
	{
		doSequence();
	}
}


void CHandler::doComplicating()
{
	CMessage* msg = NULL;
	for( size_t i = 0; i < m_pMsgSet.size(); i++)
	{
		msg = m_pMsgSet[i];
		COBRA_CHECK_NULL(msg);
		if(msg->getMsgMode() == eProcessing)
		{
			handlerMessage(msg);
		}
	}
}

void CHandler::doSequence()
{
	CMessage* msg = NULL;
	if(sequenceId < m_pMsgSet.size())
	{
		msg = getMessageByIndex(sequenceId++);
		COBRA_CHECK_NULL(msg);
		if(msg->getMsgMode() == eProcessing)
		{
			handlerMessage(msg);
		}
		dispatchMessage();
	}
	else
	{
		sequenceId = 0; // reset
	}
}


bool CHandler::hasMessage( CMessage* msg )
{
	pMessageItor itor;
	for (itor = m_pMsgSet.begin();itor !=  m_pMsgSet.begin();itor++)
	{
		if(*itor == msg)
		{
			return true;
		}
	}
	return false;
}

bool CHandler::hasMessage( int msgType )
{
	pMessageItor itor;
	for (itor = m_pMsgSet.begin();itor !=  m_pMsgSet.begin();itor++)
	{
		if((*itor)->getMsgType() == msgType)
		{
			return true;
		}
	}
	return false;
}


void CHandler::onHandler( CEvent* evt )
{
	COBRA_CHECK_NULL(evt);
	onHandlerEvent(evt);
}

void CHandler::onHandler( CIntent* intent )
{
	COBRA_CHECK_NULL(intent);
	onHandlerIntent(intent);
}

void CHandler::onHandlerIntent( CIntent* intent )
{
	int srvId = intent->getServiceID();
	if(srvId == COBRA_UNKNOWN) return;
	CService* service = dynamic_cast<CService*>(MemoryCacheShare->getExtra(COBRA_SERVICES,srvId));
	COBRA_CHECK_NULL(service);
	service->onAcceptIntent(intent);
}

void CHandler::onHandlerEvent( CEvent* evt )
{
	//do something
	CService* service = dynamic_cast<CService*>(MemoryCacheShare->getExtra(COBRA_SERVICES,SERVICE_EVENT));
	COBRA_CHECK_NULL(service);
	CIntent intent(INTENT_HTTP_DOWNLOAD,evt);
	service->onAcceptIntent(&intent);
}

void CHandler::onRegisterEvent( CEvent* evt )
{
	//do something
}

void CHandler::clearMessage()
{
	pMessageItor itor;
	for (itor = m_pMsgSet.begin();itor !=  m_pMsgSet.begin();itor++)
	{
		m_pMsgSet.erase(itor);
		delete *itor;
	}
}

int CHandler::hasFreeMessage()
{
	pMessageItor itor;
	int index = 0;
	for (itor = m_pMsgSet.begin();itor !=  m_pMsgSet.begin();itor++)
	{
		if((*itor)->getMsgMode() == eFree)
		{
			break;
		}
		index++;
	}
	return index;
}


CMessage* CHandler::getFreeMessage()
{
	pMessageItor itor;
	for (itor = m_pMsgSet.begin();itor !=  m_pMsgSet.begin();itor++)
	{
		if((*itor)->getMsgMode() == eFree)
		{
			return (*itor);
		}
	}
	return NULL;
}


CMessage* CHandler::getMessageByIndex( int index )
{
	if(index < 0 || index > m_pMsgSet.size()) return NULL;
	return m_pMsgSet[index];
}


void CHandler::setHandlerMode( eHandlerMode mode )
{
	m_eHandlerType = mode;
}

CHandler::eHandlerMode CHandler::getHandlerMode()
{
	return m_eHandlerType;
}
