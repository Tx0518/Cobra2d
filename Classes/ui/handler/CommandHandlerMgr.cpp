#include "CGeometry.h"
#include "CBaseWidget.h"
#include "CBundle.h"
#include "CommandHandlerMgr.h"

#include <algorithm>
///////////////////////////////////////////////////////////////////////////
//class CUICommand
CUICommand::CUICommand()
{
	m_pSource    = 0;
	m_iCommandID = 0;
	m_dt       = 0;
//	m_pExtraData = NULL;
}

CUICommand::~CUICommand()
{
//	COBRA_SAFE_DELETE(m_pExtraData);
}


// void CUICommand::setExtraData(CBundle* var)
// {
// 	COBRA_SAFE_DELETE(m_pExtraData);
// 	m_pExtraData = new CBundle();
// 	m_pExtraData = var;
// }
// 
// CBundle* CUICommand::getExtraData()
// {
// 	return m_pExtraData;
// }
//////////////////////////////////////////////////////////////////////////
CCommandHandler::CCommandHandler()
{
	m_bDiscard = false;
	m_bOwnData = true;
}

CCommandHandler::~CCommandHandler()
{

}

void CCommandHandler::addInterestCmdID(int id)
{
	std::vector<int>::iterator iter = std::find(m_vcInterestCmdID.begin(),m_vcInterestCmdID.end(),id);
	if (iter == m_vcInterestCmdID.end())
	{
		m_vcInterestCmdID.push_back(id);
	}
}

void CCommandHandler::removeInterestCmdID(int id)
{
	std::vector<int>::iterator iter = std::find(m_vcInterestCmdID.begin(),m_vcInterestCmdID.end(),id);
	if (iter != m_vcInterestCmdID.end())
	{
		m_vcInterestCmdID.erase(iter);
	}
	else
	{
		LOG("do not find the cmd id = [%d]");
	}
}

void CCommandHandler::clearAll(void)
{
	m_vcInterestCmdID.clear();
}

bool CCommandHandler::isInterestedCmd(int id)
{
	bool ret = false;
	std::vector<int>::iterator iter = std::find(m_vcInterestCmdID.begin(),m_vcInterestCmdID.end(),id);
	if (iter != m_vcInterestCmdID.end())
	{
		ret = true;
	}
	return ret;
}

void CCommandHandler::handleCmd(CUICommand& cmd)
{
	//default implement do nothing here
	ENTERFUNC();
	LVFUNC();
}
//////////////////////////////////////////////////////////////////////////
CCommandHandlerMgr::CCommandHandlerMgr(void)
{
}


CCommandHandlerMgr::~CCommandHandlerMgr(void)
{

}

void CCommandHandlerMgr::postCmd(CUICommand& cmd)
{	//just add to the quene
	m_commandQueueCache.push_back(cmd);
}


void CCommandHandlerMgr::addCmdHander(CCommandHandler* pcmdHander)
{
	std::list<CCommandHandler*>::iterator iter = std::find(m_listCmdHandler.begin(),m_listCmdHandler.end(),pcmdHander);
	if (iter == m_listCmdHandler.end())
	{
		m_listCmdHandler.push_back(pcmdHander);
	}
	else
	{
		LOG("try to add an already existed handler do nothing here");
	}
}

void CCommandHandlerMgr::removeCmdHandler(CCommandHandler* pcmdHander)
{
	std::list<CCommandHandler*>::iterator iter = std::find(m_listCmdHandler.begin(),m_listCmdHandler.end(),pcmdHander);
	if (iter != m_listCmdHandler.end())
	{
		//only set a flag
		(*iter)->setDiscard(true);
	}
}

void CCommandHandlerMgr::handleCmd(float dt)
{
	while(!m_commandQueue.empty())
	{
		CUICommand cmd = m_commandQueue.front();
		cmd.setdeltaT(dt);
		std::list<CCommandHandler*>::iterator iter = m_listCmdHandler.begin();
		CCommandHandler* pCmdHandler = NULL;
		while(iter != m_listCmdHandler.end())
		{//send cmd to handler if this handler interests in this id handle it
		 //else do nothing just looping
			pCmdHandler = *iter;
			if(pCmdHandler->getDiscard())
			{
				iter = m_listCmdHandler.erase(iter);
				if (pCmdHandler->isOwnData())
				{
					delete pCmdHandler;
				}
			}
			else
			{
				if (pCmdHandler->isInterestedCmd(cmd.getCmdID()))
				{
					pCmdHandler->handleCmd(cmd);
				}	
				iter++;
			}
		}
		m_commandQueue.pop_front();
	}
	//////////////////////////////////////////////////////////////////////////
	//syn m_commandQueueCache to m_commandQueue
	if(!m_commandQueueCache.empty())
	{
		m_commandQueue = m_commandQueueCache;
		m_commandQueueCache.clear();
	}
}
//////////////////////////////////////////////////////////////////////////