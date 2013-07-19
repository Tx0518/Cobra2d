#include "CBaseContainer.h"
#include "CPanel.h"
#include "CSorllPanel.h"
//////////////////////////////////////////////////////////////////////////
const std::string CSorllPanel::SORLL_PANEL_TYPE = "CSorllPanel";
//////////////////////////////////////////////////////////////////////////
CSorllPanel::CSorllPanel(void)
{
	m_sorllType = E_SORLL_TYPE_VERTI;
	m_moveCursor   = 0;
	m_maxMoveCursor = 0;
	m_moveCursorHori    = 0;
	m_maxMoveCursorHori = 0;
	m_movebackInfo.m_iTimeSpan = 10;
	m_damp = 2500;
	m_bSorllAble = true;
	//////////////////////////////////////////////////////////////////////////
	m_handler.setSource(this);
	m_handler.addInterestCmdID(CMD_SP_MOVE_UP);
	m_handler.addInterestCmdID(CMD_SP_MOVE_DOWN);
	m_handler.addInterestCmdID(CMD_SP_MOVE_BK_UP);
	m_handler.addInterestCmdID(CMD_SP_MOVE_BK_DOWN);
	m_handler.addInterestCmdID(CMD_SP_MOVE_LEFT);
	m_handler.addInterestCmdID(CMD_SP_MOVE_RIGHT);
	m_handler.addInterestCmdID(CMD_SP_MOVE_BK_LEFT);
	m_handler.addInterestCmdID(CMD_SP_MOVE_BK_RIGHT);
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
	m_moveInfoHori = m_moveInfo;
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
	m_moveInfoHori = m_moveInfo;
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

void CSorllPanel::computeOffset(float& offset,float offsetLimit,float& currentMoveCursor,float maxMoveCursor)
{
	//already to the first line
	//and try to move down
	//do nothing 
	if (0 <= currentMoveCursor && offset > 0)
	{
		if (currentMoveCursor > offsetLimit)
		{
			offset = 0;
			currentMoveCursor = offsetLimit;
		}

		//modify offset if it to large
		if (currentMoveCursor + offset >= offsetLimit)
		{
			offset = offsetLimit - currentMoveCursor;
			currentMoveCursor = offsetLimit;
		}
	}
	//already move to the last line
	//and try to move up
	//do nothing
	if (coabs(currentMoveCursor) >= maxMoveCursor && offset < 0)
	{
		if (coabs(currentMoveCursor) > maxMoveCursor + offsetLimit)
		{
			offset = 0;
			currentMoveCursor = -1 * (maxMoveCursor + offsetLimit);
		}


		if (coabs(currentMoveCursor + offset) >= maxMoveCursor + offsetLimit)
		{
			offset = coabs(currentMoveCursor) -  (maxMoveCursor + offsetLimit);
			currentMoveCursor = -1 * (maxMoveCursor + offsetLimit);
		}
	}
}
void CSorllPanel::handlePenMove(CWidgetEvent& event)
{
	//if is moving do nothing
	if (m_moveInfo.m_bMoving || false == m_bSorllAble)
	{
		return;
	}

	if (NULL != m_pCurrentSelWidget)
	{
		//cancel this event and send a pen up event to the current selected widget
		event.setCanceled(true);
		m_pCurrentSelWidget->handlePenUp(event);
		m_pCurrentSelWidget = NULL;
	}

	CPoint ptMove = event.getPt();
	float offset = 0;
	float offsetX = 0;
	float offsetY = 0;
	
	if (m_sorllType & E_SORLL_TYPE_VERTI)
	{
		//>0 stands for move down
		//<0 stands for move up
		offsetY = ptMove.y - m_ptOldPos.y;
	}

	if (m_sorllType & E_SORLL_TYPE_HORI)
	{
		//>0 stands for move right
		//<0 stands for move left
		offsetX = ptMove.x - m_ptOldPos.x;
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
			this->computeOffset(offsetY,rc.size.height,m_moveCursor,m_maxMoveCursor);
			this->computeOffset(offsetX,rc.size.width,m_moveCursorHori,m_maxMoveCursorHori);
			if (0 != offsetX || 0 != offsetY)
			{
				//update all children's position
				this->updateChildPos(offsetX,offsetY);
				LOG("in move :m_moveCursor =[%f],m_moveCursorHori =[%f]",m_moveCursor,m_moveCursorHori);
			}

		} while (0);
	}
	event.setHandled(true);
}

void CSorllPanel::handlePenMoveOut(CWidgetEvent& event)
{
	CPanel::handlePenMoveOut(event);
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
		m_maxMoveCursor = comax(rcPre.origin.y + rcPre.size.height - this->getRect().size.height,m_maxMoveCursor);
	}

	//get the largest
	if (0 == m_maxMoveCursorHori)
	{
		rcPre = pWidget->getRect();
		m_maxMoveCursorHori = rcPre.origin.x + rcPre.size.width;
		if (m_maxMoveCursorHori - this->getRect().size.width <= 0)
		{
			m_maxMoveCursorHori = 0;
		}
		else
		{
			m_maxMoveCursorHori -= this->getRect().size.width; 
		}
	}
	else
	{
		rcPre = pWidget->getRect();
		m_maxMoveCursorHori = comax(rcPre.origin.x + rcPre.size.width - this->getRect().size.width,m_maxMoveCursorHori);
	}
}

void CSorllPanel::computeVelocity()
{
	clock_t deltaT = m_moveInfo.m_iPenUpTime - m_moveInfo.m_iPenDownTime;
	float   deltaSecond = (float)deltaT/CLOCKS_PER_SEC;
	if (deltaSecond < 0.5f)
	{
		float   delatDistance = 0;
		if (m_sorllType & E_SORLL_TYPE_VERTI)
		{
			//if velocity is larger than zero means move down
			//if velocity is smaller than zero means move up
			delatDistance = m_moveInfo.m_ptUp.y - m_moveInfo.m_ptDown.y;
			if (coabs(delatDistance) >= 20)
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
		}


		if (m_sorllType & E_SORLL_TYPE_HORI)
		{
			delatDistance = m_moveInfoHori.m_ptUp.x - m_moveInfoHori.m_ptDown.x;
			if (coabs(delatDistance) >= 20)
			{
				if (delatDistance > 0)
				{
					m_moveInfoHori.m_moveDir = MoveInfo::MOVE_INFO_DIR_RIGHT;
				}
				else
				{
					m_moveInfoHori.m_moveDir = MoveInfo::MOVE_INFO_DIR_LEFT;
				}
			}
		}

		if (MoveInfo::MOVE_INFO_DIR_UNKNOWN != m_moveInfo.m_moveDir)
		{
			m_moveInfo.m_iCurrentMoveSpeed =  MoveInfo::MOVE_INFO_SPEED_1;
			m_moveInfo.m_iTotalTimeSpan  =  coabs(delatDistance /deltaSecond)/100;
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

		if (MoveInfo::MOVE_INFO_DIR_UNKNOWN != m_moveInfoHori.m_moveDir)
		{
			m_moveInfoHori.m_iCurrentMoveSpeed =  MoveInfo::MOVE_INFO_SPEED_1;
			m_moveInfoHori.m_iTotalTimeSpan  =  coabs(delatDistance /deltaSecond)/100;
			m_moveInfoHori.m_iCurrentTimeSpan = m_moveInfoHori.m_iTotalTimeSpan;
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
	
	if (m_sorllType & E_SORLL_TYPE_VERTI)
	{
		CUICommand cmd;
		//check for move back
		if (m_moveCursor > 0
			|| coabs(m_moveCursor) >= m_maxMoveCursor)
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
			default:break;
			}
			m_moveInfo.m_bMoving = true;
			cmd.setSource(this);
			CCommandHandlerMgr::instance()->postCmd(cmd);
		}
	}

	if (m_sorllType & E_SORLL_TYPE_HORI)
	{
		CUICommand cmd;
		//check for move back
		if (m_moveCursorHori > 0
			|| coabs(m_moveCursorHori) >= m_maxMoveCursorHori)
		{
			LOG("try to move back in triggerMove");
			MoveInfo info;
			m_moveInfoHori  = info;
			this->triggerMoveBack();
			return;
		}
		if (MoveInfo::MOVE_INFO_DIR_UNKNOWN != m_moveInfoHori.m_moveDir)
		{
			//send cmd for move
			switch(m_moveInfoHori.m_moveDir)
			{
			case MoveInfo::MOVE_INFO_DIR_LEFT:
				{
					cmd.setCmdID(CMD_SP_MOVE_LEFT);
					break;
				}
			case MoveInfo::MOVE_INFO_DIR_RIGHT:
				{
					cmd.setCmdID(CMD_SP_MOVE_RIGHT);
					break;
				}
			default:break;
			}
			m_moveInfoHori.m_bMoving = true;
			cmd.setSource(this);
			CCommandHandlerMgr::instance()->postCmd(cmd);
		}
	}

}

void CSorllPanel::triggerMoveBack(void)
{
	ENTERFUNC();
	
	if (m_sorllType & E_SORLL_TYPE_VERTI)
	{	
		CUICommand cmd;
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
			else if(coabs(m_moveCursor) >= m_maxMoveCursor)
			{//start to move back down
				LOG("try to move back down");
				m_movebackInfo.m_bMovingBack = true;
				m_movebackInfo.m_fVelocity   = (coabs(m_moveCursor) - m_maxMoveCursor)/m_movebackInfo.m_iTimeSpan;
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
		cmd.setSource(this);
		if (0 != cmd.getCmdID())
		{
			CCommandHandlerMgr::instance()->postCmd(cmd);
		}
	}

	if (m_sorllType & E_SORLL_TYPE_HORI)
	{
		CUICommand cmd;
		if (!m_movebackInfoHori.m_bMovingBack)
		{//compute and set flag
			MoveBackInfo info;
			m_movebackInfoHori = info;
			//start to move back up
			//compute the init values
			if (m_moveCursorHori > 0)
			{
				LOG("try to move back left");
				m_movebackInfoHori.m_bMovingBack = true;
				m_movebackInfoHori.m_fVelocity   = -1 * m_moveCursorHori/m_movebackInfoHori.m_iTimeSpan;
				cmd.setCmdID(CMD_SP_MOVE_BK_LEFT);
			}
			else if(coabs(m_moveCursorHori) >= m_maxMoveCursorHori)
			{//start to move back down
				LOG("try to move back right");
				m_movebackInfoHori.m_bMovingBack = true;
				m_movebackInfoHori.m_fVelocity   = (coabs(m_moveCursorHori) - m_maxMoveCursorHori)/m_movebackInfoHori.m_iTimeSpan;
				cmd.setCmdID(CMD_SP_MOVE_BK_RIGHT);
			}
		}
		else
		{//already in moving back mode just set cmd id
			//TODO check for left and right
			if(m_movebackInfoHori.m_fVelocity < 0)
			{
				cmd.setCmdID(CMD_SP_MOVE_BK_LEFT);
			}
			else
			{
				cmd.setCmdID(CMD_SP_MOVE_BK_RIGHT);
			}
		}
		cmd.setSource(this);
		if (0 != cmd.getCmdID())
		{
			CCommandHandlerMgr::instance()->postCmd(cmd);
		}
	}
	LVFUNC();
}

void CSorllPanel::updateChildPos(float fDeltaX,float fDeltaY)
{
	WidgetListIter iter = m_pList->begin();
	CRectange rcTemp;
	if (0 != fDeltaX || 0 != fDeltaY)
	{
		//update all children's position
		while(iter != m_pList->end())
		{
			rcTemp = (*iter)->getRect();
			if (m_sorllType & E_SORLL_TYPE_VERTI)
			{
				rcTemp.origin.y += fDeltaY;
			}

			if (m_sorllType & E_SORLL_TYPE_HORI)
			{
				rcTemp.origin.x += fDeltaX;
			}
			(*iter)->setRect(rcTemp);
			iter++;
		}
		//update the move cursor
		m_moveCursor += fDeltaY;
		m_moveCursorHori += fDeltaX;
	}
}

void CSorllPanel::handleMoveInner(MoveInfo& moveInfo)
{
	if (MoveInfo::MOVE_INFO_DIR_UNKNOWN !=  moveInfo.m_moveDir )
	{
		if (-- moveInfo.m_iCurrentTimeSpan <= 0)
		{
			switch(moveInfo.m_iCurrentMoveSpeed)
			{
			case MoveInfo::MOVE_INFO_SPEED_1:
				{
					LOG("trans to speed 2");
					moveInfo.m_iCurrentMoveSpeed = MoveInfo::MOVE_INFO_SPEED_2;
					moveInfo.m_iCurrentTimeSpan  = m_moveInfo.m_iTotalTimeSpan/2;
					break;
				}
			case MoveInfo::MOVE_INFO_SPEED_2:
				{
					LOG("trans to speed 3");
					moveInfo.m_iCurrentMoveSpeed = MoveInfo::MOVE_INFO_SPEED_3;
					moveInfo.m_iCurrentTimeSpan  = m_moveInfo.m_iTotalTimeSpan/4;
					break;
				}
			case MoveInfo::MOVE_INFO_SPEED_3:
				{
					MoveInfo info;
					moveInfo = info;
					LOG("auto move over");
					break;
				}
			default:break;
			}
		}


		switch (moveInfo.m_moveDir)
		{
		case MoveInfo::MOVE_INFO_DIR_UP:
			{
				this->updateChildPos(0,-1 * moveInfo.m_iCurrentMoveSpeed);
				break;
			}
		case MoveInfo::MOVE_INFO_DIR_LEFT:
			{
				this->updateChildPos(-1 * moveInfo.m_iCurrentMoveSpeed,0);
				break;
			}
		case MoveInfo::MOVE_INFO_DIR_DOWN:
			{
				this->updateChildPos(0,moveInfo.m_iCurrentMoveSpeed);
				break;
			}
		case MoveInfo::MOVE_INFO_DIR_RIGHT:
			{
				this->updateChildPos(moveInfo.m_iCurrentMoveSpeed,0);
				break;
			}
		default:
			{
				break;
			}
		}
		this->triggerMove();
	}
	else
	{
#if 1
		//TODO check me
		LOG("here !!! may be should try to move back");
		if ((m_moveCursor > 0|| coabs(m_moveCursor) >= m_maxMoveCursor)
			||  (m_moveCursorHori > 0	|| coabs(m_moveCursorHori) >= m_maxMoveCursorHori))
		{
			LOG("try to move back top down in triggerMove");
			MoveInfo info;
			moveInfo  = info;
			this->triggerMoveBack();
		}
#endif
	}
}

 void CSorllPanel::handleMove(float dt)
 {
	 ENTERFUNC();
	 this->handleMoveInner(m_moveInfo);
	 this->handleMoveInner(m_moveInfoHori);
	 LVFUNC();
 }

 void CSorllPanel::handleMoveBack(float dt,int cmdID)
 {
	 ENTERFUNC();
	 LOG("m_movebackInfo.m_iTimeSpan = [%d]",m_movebackInfo.m_iTimeSpan);
	 if (m_movebackInfo.m_bMovingBack && --m_movebackInfo.m_iTimeSpan >= 0)
	 {
		 this->updateChildPos(0,m_movebackInfo.m_fVelocity);
		 LOG("m_moveCursor = [%f]",m_moveCursor);
		 this->triggerMoveBack();
	 }
	 else
	 {
		 LOG("move back done in handleMoveBack m_moveCursor = [%f]",m_moveCursor);
		 MoveBackInfo  info;
		 m_movebackInfo = info;
	 }

	 if (m_movebackInfoHori.m_bMovingBack && --m_movebackInfoHori.m_iTimeSpan >= 0)
	 {
		 this->updateChildPos(m_movebackInfoHori.m_fVelocity,0);
		 LOG("m_moveCursorHori = [%f]",m_moveCursorHori);
		 this->triggerMoveBack();
	 }
	 else
	 {
		 LOG("move back done in handleMoveBack m_moveCursorHori = [%f]",m_moveCursorHori);
		 MoveBackInfo  info;
		 m_movebackInfoHori = info;
	 }

	 LVFUNC();
 }


 void CSorllPanel::setMoveBackSpan(int timeSpan)
 {
	m_movebackInfo.m_iTimeSpan = timeSpan;
	m_movebackInfoHori.m_iTimeSpan = timeSpan;
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
	 if (cmd.getSource() == m_pSource)
	 {
		 switch(cmd.getCmdID())
		 {
			case CSorllPanel::CMD_SP_MOVE_UP:
			case CSorllPanel::CMD_SP_MOVE_DOWN:
			case CSorllPanel::CMD_SP_MOVE_LEFT:
			case CSorllPanel::CMD_SP_MOVE_RIGHT:
			 {
				 CSorllPanel* pSource = (CSorllPanel*)cmd.getSource();
				 pSource->handleMove(cmd.getdeltaT());
				 break;
			 }
			case CSorllPanel::CMD_SP_MOVE_BK_UP:
			case CSorllPanel::CMD_SP_MOVE_BK_DOWN:
			case CSorllPanel::CMD_SP_MOVE_BK_LEFT:
			case CSorllPanel::CMD_SP_MOVE_BK_RIGHT:
			 {
				 CSorllPanel* pSource = (CSorllPanel*)cmd.getSource();
				 pSource->handleMoveBack(cmd.getdeltaT(),cmd.getCmdID());
				 break;
			 }
		 default:break;
		 }
	 }

 }