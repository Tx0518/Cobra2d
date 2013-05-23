#ifndef __SCROLL_PANEL_H__
#define __SCROLL_PANEL_H__
#include "CommandHandlerMgr.h"
//////////////////////////////////////////////////////////////////////////
class CHandlerScollPanel:public CCommandHandler
{
public:
	CHandlerScollPanel();
	~CHandlerScollPanel();
	void handleCmd(CUICommand& cmd);
};
//////////////////////////////////////////////////////////////////////////
class CPanel;
//////////////////////////////////////////////////////////////////////////
typedef struct _stMoveInfo
{
	enum
	{
		MOVE_INFO_DIR_UP,
		MOVE_INFO_DIR_DOWN,
		MOVE_INFO_DIR_LEFT,
		MOVE_INFO_DIR_RIGHT,
		MOVE_INFO_DIR_UNKNOWN
	};

	enum
	{
		MOVE_INFO_SPEED_1 = 30,
		MOVE_INFO_SPEED_2 = 15,
		MOVE_INFO_SPEED_3 = 10,
		MOVE_INFO_SPEED_UNKNOWN = 0
	};
	CPoint m_ptDown;
	CPoint m_ptUp;
	clock_t     m_iPenDownTime;
	clock_t     m_iPenUpTime;
	int    m_moveDir;
	char   m_iCurrentMoveSpeed;
	int	   m_iTotalTimeSpan;
	int    m_iCurrentTimeSpan;
	bool   m_bMoving;//flag for moving or not
	_stMoveInfo()
	{
		m_ptDown = PointZero;
		m_ptUp   = PointZero;
		m_iPenDownTime = 0;
		m_iPenUpTime   = 0;
		m_moveDir    = MOVE_INFO_DIR_UNKNOWN;
		m_iCurrentMoveSpeed = MOVE_INFO_SPEED_UNKNOWN;
		m_iTotalTimeSpan = 0;
		m_iCurrentTimeSpan = 0;
		m_bMoving      = false;
	}
}MoveInfo;


typedef struct _stMoveBackInfo
{
	int	  m_iTimeSpan;
	float m_fVelocity;
	bool  m_bMovingBack;
	_stMoveBackInfo()
	{
		m_iTimeSpan     = 10;
		m_fVelocity = 0;
		m_bMovingBack = false;
	}
}MoveBackInfo;


class CSorllPanel:public CPanel
{
public:
	enum
	{
		E_SORLL_TYPE_VERTI,
		E_SORLL_TYPE_HORI
	};
	//cmd id
	static const int CMD_SP_MOVE_UP   = 0x2000;
	static const int CMD_SP_MOVE_DOWN = 0x2001;
	static const int CMD_SP_MOVE_BK_UP = 0x2002;
	static const int CMD_SP_MOVE_BK_DOWN = 0x2003;
	CSorllPanel(void);
	~CSorllPanel(void);
	//////////////////////////////////////////////////////////////////////////
	void add(CBaseWidget* pWidget);
	void add(CBaseWidget* pWidget,int x,int y);
	//////////////////////////////////////////////////////////////////////////
	 void handlePenDown(CWidgetEvent& event);
	 void handlePenUp(CWidgetEvent& event);
	 void handlePenClick(CWidgetEvent& event);
	 void handlePenMoveIn(CWidgetEvent& event);
	 void handlePenMove(CWidgetEvent& event);
	 void handlePenMoveOut(CWidgetEvent& event);
	//////////////////////////////////////////////////////////////////////////
	 void handleMove(float dt);
	 void handleMoveBack(float dt,int cmdID);

	 void setMoveBackSpan(int iSpan);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY(int,m_sorllType,SorllType);
	COBRA_CREATE_PROPERTY(int,m_damp,Damp);
	
private:
	void updateCursor(CBaseWidget* pWidget);
	void updateChildPos(float fDelta);
	void computeVelocity(void);
	void triggerMoveBack(void);
	void triggerMove(void);
	//////////////////////////////////////////////////////////////////////////
	float m_moveCursor;
	float m_maxMoveCursor;
	int m_fTotleContentHeight;
	CPoint m_ptOldPos;
	//////////////////////////////////////////////////////////////////////////
	MoveInfo m_moveInfo;
	MoveBackInfo m_movebackInfo;
	//////////////////////////////////////////////////////////////////////////
	CHandlerScollPanel m_handler;
};
#endif //__SCROLL_PANEL_H__