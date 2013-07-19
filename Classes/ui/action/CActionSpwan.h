#ifndef __C_ACTION_SPWAN_H__
#define __C_ACTION_SPWAN_H__
#include "CActionInterval.h"
/************************************************************************/
/* usage:
create a action1 and action2
then call initWidthActions(action1,action2);
!!YOU MUST pass these actions once to a target
these actions will be owned by the new  created CActionSpwan action
*/
/************************************************************************/
class CActionSpwan:public CActionInterval
{
public:
	static const int CMD_ID_ACTION_SPWAN = 0x2012;
	CActionSpwan(void);
	~CActionSpwan(void);
	//////////////////////////////////////////////////////////////////////////
	void initWidthActions(CActionInterval *pAction1,...);
	//////////////////////////////////////////////////////////////////////////
	void startWidthTarget(CBaseWidget* pTarget);
	void update(float time);
protected:
	std::vector<CActionInterval*> m_vcActions;
};

#endif//__C_ACTION_SPWAN_H__