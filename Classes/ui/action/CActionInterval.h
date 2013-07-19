#ifndef __C_ACTION_INTERVAL_H__
#define __C_ACTION_INTERVAL_H__
class CBaseWidget;
class CCommandHandler;
class CActionSpwan;
class CActionInterval:public CCommandHandler
{
public:
	CActionInterval(void);
	virtual ~CActionInterval(void);
	void init(float dt);
	int getCMD(void);
	virtual void step(float dt);
	virtual void update(float time);

	////////////////////////////////
	bool isDone(void);
	void handleCmd(CUICommand& cmd);
	virtual void startWidthTarget(CBaseWidget* pTarget);
	//////////////////////////////////////////////////////////////////////////
	COBRA_CREATE_PROPERTY(float,m_duration,Duration);
	//////////////////////////////////////////////////////////////////////////
protected:
	CBaseWidget* m_pTarget;
	float m_elapsed;
	bool  m_bFirstTick;
	int   m_iCmdID;
};

#endif //__C_ACTION_INTERVAL_H__