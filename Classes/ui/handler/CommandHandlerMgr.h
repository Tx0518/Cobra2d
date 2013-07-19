#ifndef __COMMAND_HANDLER_MGR_H__
#define __COMMAND_HANDLER_MGR_H__
#include "CMarcos.h"

#include "thread/zthread/Singleton.h"
#include <deque>
/************************************************************************/
/* this file  is used for handle UI command triggered by user interact
*/
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
class CBaseWidget;
class CBundle;
class CUICommand
{
public:
	CUICommand();
	virtual ~CUICommand();
	COBRA_CREATE_PROPERTY(CBaseWidget*,m_pSource,Source)
	COBRA_CREATE_PROPERTY(int,m_iCommandID,CmdID)
	COBRA_CREATE_PROPERTY(float,m_dt,deltaT)
	//m_pExtraData will be deep copied
//	COBRA_CREATE_PROPERTY(CBundle*,m_pExtraData,ExtraData);
};


class CCommandHandler
{
public:
	CCommandHandler();
	virtual ~CCommandHandler();
	//////////////////////////////////////////////////////////////////////////
	void addInterestCmdID(int id);
	void removeInterestCmdID(int id);
	void clearAll(void);
	bool isInterestedCmd(int id);
	//////////////////////////////////////////////////////////////////////////
	virtual void handleCmd(CUICommand& cmd);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY(bool,m_bDiscard,Discard)
	//if flag owndata equals true the CCommandHandlerMgr will take care the life circle of CCommandHandler
	//default value is true
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bOwnData,OwnData)

private:
	std::vector<int> m_vcInterestCmdID;
};


////////////////////////////////////////////////////////////////////////
 class CCommandHandlerMgr:public ZThread::Singleton<CCommandHandlerMgr>
 {
 public:
 	CCommandHandlerMgr(void);
 	~CCommandHandlerMgr(void);
 	//////////////////////////////////////////////////////////////////////////
 	void postCmd(CUICommand& cmd);
	//////////////////////////////////////////////////////////////////////////
	void addCmdHander(CCommandHandler* pcmdHander);
	void removeCmdHandler(CCommandHandler* pcmdHander);
 	//////////////////////////////////////////////////////////////////////////
	void handleCmd(float dt);
	//////////////////////////////////////////////////////////////////////////
 private:
	 //////////////////////////////////////////////////////////////////////////

	 //////////////////////////////////////////////////////////////////////////
	 //cache a cmd for next tick to execute
	 std::deque<CUICommand>  m_commandQueueCache;
	//hold cmd obj to be handled
	 std::deque<CUICommand> m_commandQueue;
	//hold ptr of cmd handler
 	std::list<CCommandHandler*> m_listCmdHandler;
 };

#endif //__COMMAND_HANDLER_MGR_H__