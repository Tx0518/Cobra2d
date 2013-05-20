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
//	m_pExtraData = NULL;
}

CUICommand::~CUICommand()
{
//	COBRA_SAFE_DELETE(m_pExtraData);
}

void CUICommand::setSource(CBaseWidget* pSrc)
{
	m_pSource = pSrc;
}

CBaseWidget* CUICommand::getSource()
{
	return m_pSource;
}

void CUICommand::setCmdID(int var)
{
	m_iCommandID = var;
}

int CUICommand::getCmdID()
{
	return m_iCommandID;
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
	m_commandQueue.push_back(cmd);
}


void CCommandHandlerMgr::addCmdHander(CCommandHandler* pcmdHander)
{
	m_listCmdHandler.push_back(pcmdHander);
}

void CCommandHandlerMgr::removeCmdHandler(CCommandHandler* pcmdHander)
{
	std::list<CCommandHandler*>::iterator iter = std::find(m_listCmdHandler.begin(),m_listCmdHandler.end(),pcmdHander);
	if (iter != m_listCmdHandler.end())
	{
		m_listCmdHandler.erase(iter);
	}
}

void CCommandHandlerMgr::handleCmd(void)
{
	while(!m_commandQueue.empty())
	{
		CUICommand& cmd = m_commandQueue.front();
		std::list<CCommandHandler*>::iterator iter = m_listCmdHandler.begin();
		while(iter != m_listCmdHandler.end())
		{//send cmd to handler if this handler interests in this id handle it
		 //else do nothing just looping
			(*iter)->handleCmd(cmd);
			iter++;
		}
		m_commandQueue.pop_front();
	}
}
//////////////////////////////////////////////////////////////////////////