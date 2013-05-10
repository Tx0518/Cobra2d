#include "CObserver.h"
#include "CNetMarcos.h"
/************************************************************************/
/* 
	CCommand
*/
CCommand::CCommand( CCobraObject* target )
	:m_pTarget(target)
{
}

CCommand::~CCommand( void )
{
	COBRA_SAFE_DELETE(m_pTarget);
}

/************************************************************************/


/************************************************************************/
/*
	CObserver
*/
CObserver::CObserver( void )
{
}


CObserver::~CObserver( void )
{
}

void CObserver::addCommand( CCommand* command )
{
	if(command == NULL) return;
	m_pCommandSet[command->getObjectID()] = command;
}

void CObserver::removeCommand( CCommand* command )
{
	if(command == NULL) return;
	std::map<int,CCommand*>::iterator itor = m_pCommandSet.find(command->getObjectID());
	if(itor != m_pCommandSet.end())
	{
		m_pCommandSet.erase(itor);
	}
}

void CObserver::dispatchCommand( int cmdKey )
{
	if(m_pCommandSet.empty()) return;
	std::map<int,CCommand*>::iterator itor = m_pCommandSet.find(cmdKey);
	if(itor != m_pCommandSet.end())
		itor->second->execute();
}

void CObserver::onHandlerDataStream( void* pMsg )
{
	SeqMsgHead* msg = (SeqMsgHead*) pMsg;
	dispatchCommand(msg->usType);
}

/************************************************************************/

