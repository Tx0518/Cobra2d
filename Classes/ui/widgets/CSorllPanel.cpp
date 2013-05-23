#include "CBaseContainer.h"
#include "CPanel.h"
#include "CSorllPanel.h"


CSorllPanel::CSorllPanel(void)
{
	m_sorllType = E_SORLL_TYPE_VERTI;
	m_moveCursor   = 0;
	m_maxMoveCursor = 0;
	m_movebackInfo.m_iTimeSpan = 10;
	m_damp = 2500;
	//////////////////////////////////////////////////////////////////////////
	m_handler.addInterestCmdID(CMD_SP_MOVE_UP);
	m_handler.addInterestCmdID(CMD_SP_MOVE_DOWN);
	m_handler.addInterestCmdID(CMD_SP_MOVE_BK_UP);
	m_handler.addInterestCmdID(CMD_SP_MOVE_BK_DOWN);
	CCommandHandlerMgr::instance()->addCmdHander(&m_handler);
}


CSorllPanel::~CSorllPanel(void)
{

}
//////////////////////////////////////////////////////////////////////////
void CSorllPanel::add(CBaseWidget* pWidget)
{
	CBaseContainer::add(pWidget);
	this->updateCursor(pWidget);
}

void CSorllPanel::add(CBaseWidget* pWidget,int x,int y)
{
	CBaseContainer::add(pWidget,x,y);
	this->updateCursor(pWidget);
}

void CSorllPanel::setDamp(int var)
{
	m_damp = var;
}

int CSorllPanel::getDamp()
{
	return m_damp;
}
//////////////////////////////////////////////////////////////////////////
void CSorllPanel::handlePenDown(CWidgetEvent& event)
{
	//if in moving back mode do nothing
	if (m_movebackInfo.m_bMovingBack )
	{
		return;
	}
	m_ptOldPos = event.getPt();
	//reset move info,this will stop move
	MoveInfo info;
	m_moveInfo = info;
	m_moveInfo.m_ptDown = m_ptOldPos;
	m_moveInfo.m_iPenDownTime = clock();
	CPanel::handlePenDown(event);
	event.setHandled(true);
}

void CSorllPanel::handlePenUp(CWidgetEvent& event)
{
	//if is moving do nothing
	if (m_moveInfo.m_bMoving)
	{
		return;
	}
	//save it
	m_moveInfo.m_ptUp = event.getPt();
	m_moveInfo.m_iPenUpTime = clock();

	this->computeVelocity();
	CPanel::handlePenUp(event);
}

void CSorllPanel::handlePenClick(CWidgetEvent& event)
{
	CPanel::handlePenClick(event);
}

void CSorllPanel::handlePenMoveIn(CWidgetEvent& event)
{
	CPanel::handlePenMoveIn(event);
}

void CSorllPanel::handlePenMove(CWidgetEvent& event)
{
	//if is moving do nothing
	if (m_moveInfo.m_bMoving)
	{
		return;
	}

	if (NULL != m_pCurrentSelWidget)
	{
		m_pCurrentSelWidget->handlePenUp(event);
		m_pCurrentSelWidget = NULL;
	}

	CPoint ptMove = event.getPt();
	float offset = 0;
	switch(m_sorllType)
	{
	case E_SORLL_TYPE_VERTI:
		{//>0 stands for move down
		 //<0 stands for move up
			offset = ptMove.y - m_ptOldPos.y;
			break;
		}
	case E_SORLL_TYPE_HORI:
		{//>0 stands for move right
		 //<0 stands for move left
			offset = ptMove.x - m_ptOldPos.x;
			break;
		}
	default:break;
	}
	m_ptOldPos = ptMove;
	//////////////////////////////////////////////////////////////////////////
	//offset larger  than zero means we move down
	//else we move up
	if (!m_pList->empty())
	{
		do 
		{
			CRectange rc = this->getRect();
			//already to the first line
			//and try to move down
			//do nothing 
			if (0 <= m_moveCursor && offset > 0)
			{
				if (m_moveCursor > rc.size.height)
				{
					offset = 0;
					m_moveCursor = rc.size.height;
				}

				//modify offset if it to large
				if (m_moveCursor + offset >= rc.size.height)
				{
					offset = rc.size.height - m_moveCursor;
					m_moveCursor = rc.size.height;
				}
			}
			//already move to the last line
			//and try to move up
			//do nothing
			if (cabs(m_moveCursor) >= m_maxMoveCursor && offset < 0)
			{
				if (cabs(m_moveCursor) > m_maxMoveCursor + rc.size.height)
				{
					offset = 0;
					m_moveCursor = -1 * (m_maxMoveCursor + rc.size.height);
				}
				

				if (cabs(m_moveCursor + offset) >= m_maxMoveCursor + rc.size.height)
				{
					offset = cabs(m_moveCursor) -  (m_maxMoveCursor + rc.size.height);
					m_moveCursor = -1 * (m_maxMoveCursor + rc.size.height);
				}
			}
			if (0 != offset)
			{
				//update all children's position
				this->updateChildPos(offset);
				LOG("in move :m_moveCursor =[%f]",m_moveCursor);
			}

		} while (0);
	}
	event.setHandled(true);
}

void CSorllPanel::handlePenMoveOut(CWidgetEvent& event)
{
	CPanel::handlePenMoveOut(event);
}

void CSorllPanel::setSorllType(int var)
{
	m_sorllType = var;
}

int CSorllPanel::getSorllType()
{
	return m_sorllType;
}
//////////////////////////////////////////////////////////////////////////
void CSorllPanel::updateCursor(CBaseWidget* pWidget)
{
	//update
	WidgetListIter iter = m_pList->begin();
	CRectange rcPre;
	//get the largest 
	if (0 == m_maxMoveCursor)
	{
		rcPre = pWidget->getRect();
		m_maxMoveCursor = rcPre.origin.y + rcPre.size.height;
		if (m_maxMoveCursor - this->getRect().size.height <= 0)
		{
			m_maxMoveCursor = 0;
		}
		else
		{
			m_maxMoveCursor -= this->getRect().size.height; 
		}
	}
	else
	{
		rcPre = pWidget->getRect();
		m_maxMoveCursor = cmax(rcPre.origin.y + rcPre.size.height - this->getRect().size.height,m_maxMoveCursor);
	}
}

void CSorllPanel::computeVelocity(void)
{
	clock_t deltaT = m_moveInfo.m_iPenUpTime - m_moveInfo.m_iPenDownTime;
	float   deltaSecond = (float)deltaT/CLOCKS_PER_SEC;
	if (deltaSecond < 0.5f)
	{
		float   delatDistance = 0;
		switch(m_sorllType)
		{
		case E_SORLL_TYPE_VERTI:
			{
				//if velocity is larger than zero means move down
				//if velocity is smaller than zero means move up
				delatDistance = m_moveInfo.m_ptUp.y - m_moveInfo.m_ptDown.y;
				if (cabs(delatDistance) >= 20)
				{
					if (delatDistance > 0)
					{
						m_moveInfo.m_moveDir = MoveInfo::MOVE_INFO_DIR_DOWN;
					}
					else
					{
						m_moveInfo.m_moveDir = MoveInfo::MOVE_INFO_DIR_UP;
					}
				}
				break;
			}
		case E_SORLL_TYPE_HORI:
			{
				delatDistance = m_moveInfo.m_ptUp.x - m_moveInfo.m_ptDown.x;
				if (cabs(delatDistance) >= 20)
				{
					if (delatDistance > 0)
					{
						m_moveInfo.m_moveDir = MoveInfo::MOVE_INFO_DIR_RIGHT;
					}
					else
					{
						m_moveInfo.m_moveDir = MoveInfo::MOVE_INFO_DIR_LEFT;
					}
				}
				break;
			}
		}

		if (MoveInfo::MOVE_INFO_DIR_UNKNOWN != m_moveInfo.m_moveDir)
		{
			m_moveInfo.m_iCurrentMoveSpeed =  MoveInfo::MOVE_INFO_SPEED_1;
			m_moveInfo.m_iTotalTimeSpan  =  cabs(delatDistance /deltaSecond)/100;
			m_moveInfo.m_iCurrentTimeSpan = m_moveInfo.m_iTotalTimeSpan;
			this->triggerMove();
		}
		else
		{
			//check for move back
			//if there is no moving mode is not detected
			LOG("check for move back if there is no moving mode is not detected");
			this->triggerMoveBack();
		}
	}
	else
	{	//check for move back
		//if time is too large
		LOG("check for move back if time is too large");
		this->triggerMoveBack();
	}
}

void CSorllPanel::triggerMove(void)
{
	CUICommand cmd;
	switch(m_sorllType)
	{
	case E_SORLL_TYPE_VERTI:
		{
			//check for move back
			if (m_moveCursor > 0
				|| cabs(m_moveCursor) >= m_maxMoveCursor)
			{
				LOG("try to move back in triggerMove");
				MoveInfo info;
				m_moveInfo  = info;
				this->triggerMoveBack();
				return;
			}
			if (MoveInfo::MOVE_INFO_DIR_UNKNOWN != m_moveInfo.m_moveDir)
			{
				//send cmd for move
				switch(m_moveInfo.m_moveDir)
				{
				case MoveInfo::MOVE_INFO_DIR_UP:
					{
						cmd.setCmdID(CMD_SP_MOVE_UP);
						break;
					}
				case MoveInfo::MOVE_INFO_DIR_DOWN:
					{
						cmd.setCmdID(CMD_SP_MOVE_DOWN);
						break;
					}
				case MoveInfo::MOVE_INFO_DIR_LEFT:
					{
						;//TODO
						break;
					}
				case MoveInfo::MOVE_INFO_DIR_RIGHT:
					{
						;//TODO
						break;
					}
				default:break;
				}
				m_moveInfo.m_bMoving = true;
			}
			break;
		}
	case E_SORLL_TYPE_HORI:
		{
			;//TODO
			break;
		}
	}
	cmd.setSource(this);
	CCommandHandlerMgr::instance()->postCmd(cmd);
}

void CSorllPanel::triggerMoveBack(void)
{
	ENTERFUNC();
	CUICommand cmd;
	switch(m_sorllType)
	{
	case E_SORLL_TYPE_VERTI:
		{
			
			if (!m_movebackInfo.m_bMovingBack)
			{//compute and set flag
				MoveBackInfo info;
				m_movebackInfo = info;
				//start to move back up
				//compute the init values
				if (m_moveCursor > 0)
				{
					LOG("try to move back up");
					m_movebackInfo.m_bMovingBack = true;
					m_movebackInfo.m_fVelocity   = -1 * m_moveCursor/m_movebackInfo.m_iTimeSpan;
					cmd.setCmdID(CMD_SP_MOVE_BK_UP);
				}
				else if(cabs(m_moveCursor) >= m_maxMoveCursor)
				{//start to move back down
					LOG("try to move back down");
					m_movebackInfo.m_bMovingBack = true;
					m_movebackInfo.m_fVelocity   = (cabs(m_moveCursor) - m_maxMoveCursor)/m_movebackInfo.m_iTimeSpan;
					cmd.setCmdID(CMD_SP_MOVE_BK_DOWN);
				}
			}
			else
			{//already in moving back mode just set cmd id
				//TODO check for left and right
				if(m_movebackInfo.m_fVelocity < 0)
				{
					cmd.setCmdID(CMD_SP_MOVE_BK_UP);
				}
				else
				{
					cmd.setCmdID(CMD_SP_MOVE_BK_DOWN);
				}
			}
			break;
		}
	case E_SORLL_TYPE_HORI:
		{
			;//TODO
			break;
		}
	}
	cmd.setSource(this);
	CCommandHandlerMgr::instance()->postCmd(cmd);
	LVFUNC();
}

void CSorllPanel::updateChildPos(float fDelta)
{
	WidgetListIter iter = m_pList->begin();
	CRectange rcTemp;
	if (0 != fDelta)
	{
		//update all children's position
		while(iter != m_pList->end())
		{
			rcTemp = (*iter)->getRect();
			switch(m_sorllType)
			{
			case E_SORLL_TYPE_VERTI:
				{
					rcTemp.origin.y += fDelta;
					break;
				}
			case E_SORLL_TYPE_HORI:
				{
					rcTemp.origin.x += fDelta;
					break;
				}
			default:break;
			}
			(*iter)->setRect(rcTemp);
			iter++;
		}
		//update the move cursor
		m_moveCursor += fDelta;
	}
}

 void CSorllPanel::handleMove(float dt)
 {
	 ENTERFUNC();
	 if (MoveInfo::MOVE_INFO_DIR_UNKNOWN !=  m_moveInfo.m_moveDir )
	 {
		 if (-- m_moveInfo.m_iCurrentTimeSpan <= 0)
		 {
			 switch(m_moveInfo.m_iCurrentMoveSpeed)
			 {
			 case MoveInfo::MOVE_INFO_SPEED_1:
				 {
					LOG("trans to speed 2");
					m_moveInfo.m_iCurrentMoveSpeed = MoveInfo::MOVE_INFO_SPEED_2;
					m_moveInfo.m_iCurrentTimeSpan  = m_moveInfo.m_iTotalTimeSpan/2;
					break;
				 }
			 case MoveInfo::MOVE_INFO_SPEED_2:
				 {
					 LOG("trans to speed 3");
					 m_moveInfo.m_iCurrentMoveSpeed = MoveInfo::MOVE_INFO_SPEED_3;
					 m_moveInfo.m_iCurrentTimeSpan  = m_moveInfo.m_iTotalTimeSpan/4;
					break;
				 }
			 case MoveInfo::MOVE_INFO_SPEED_3:
				 {
					 MoveInfo info;
					 m_moveInfo = info;
					 LOG("auto move over");
					 break;
				 }
			 default:break;
			 }
		 }


		 switch (m_moveInfo.m_moveDir)
		 {
		 case MoveInfo::MOVE_INFO_DIR_UP:
		 case MoveInfo::MOVE_INFO_DIR_LEFT:
			 {
				 this->updateChildPos(-1 * m_moveInfo.m_iCurrentMoveSpeed);
				 break;
			 }
		 case MoveInfo::MOVE_INFO_DIR_DOWN:
		 case MoveInfo::MOVE_INFO_DIR_RIGHT:
			 {
				 this->updateChildPos(m_moveInfo.m_iCurrentMoveSpeed);
				 break;
			 }
		 }
		 this->triggerMove();
	 }
	 else
	 {
		 //TODO check me
		 LOG("here !!! may be should try to move back");
		 if (m_moveCursor > 0
			 || cabs(m_moveCursor) >= m_maxMoveCursor)
		 {
			 LOG("try to move back in triggerMove");
			 MoveInfo info;
			 m_moveInfo  = info;
			 this->triggerMoveBack();
			 return;
		 }
	 }
	 LVFUNC();
 }

 void CSorllPanel::handleMoveBack(float dt,int cmdID)
 {
	 ENTERFUNC();
	 LOG("m_movebackInfo.m_iTimeSpan = [%d]",m_movebackInfo.m_iTimeSpan);
	 if (--m_movebackInfo.m_iTimeSpan >= 0)
	 {
		 this->updateChildPos(m_movebackInfo.m_fVelocity);
		 LOG("m_moveCursor = [%f]",m_moveCursor);
		 this->triggerMoveBack();
	 }
	 else
	 {
		 LOG("move back done in handleMoveBack m_moveCursor = [%f]",m_moveCursor);
		 MoveBackInfo  info;
		 m_movebackInfo = info;
	 }
	 LVFUNC();
 }


 void CSorllPanel::setMoveBackSpan(int timeSpan)
 {
	m_movebackInfo.m_iTimeSpan = timeSpan;
 }

 //////////////////////////////////////////////////////////////////////////
 //command handler
 CHandlerScollPanel::CHandlerScollPanel()
 {

 }

 CHandlerScollPanel::~CHandlerScollPanel()
 {

 }

 void CHandlerScollPanel::handleCmd(CUICommand& cmd)
 {
	 switch(cmd.getCmdID())
	 {
	 case CSorllPanel::CMD_SP_MOVE_UP:
	 case CSorllPanel::CMD_SP_MOVE_DOWN:
		 {
			CSorllPanel* pSource = (CSorllPanel*)cmd.getSource();
			pSource->handleMove(cmd.getdeltaT());
			break;
		 }
	 case CSorllPanel::CMD_SP_MOVE_BK_UP:
	 case CSorllPanel::CMD_SP_MOVE_BK_DOWN:
		 {
			 CSorllPanel* pSource = (CSorllPanel*)cmd.getSource();
			 pSource->handleMoveBack(cmd.getdeltaT(),cmd.getCmdID());
			break;
		 }
	 default:break;
	 }
 }
