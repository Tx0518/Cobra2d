#ifndef __C_ACTION_MOVE_BY_H__
#define __C_ACTION_MOVE_BY_H__
#include "CGeometry.h"
#include "CActionInterval.h"

class CActionMoveBy : public CActionInterval
{
public:
	static const int CMD_ID_ACTION_MOVE_BY = 0x2010;
	CActionMoveBy(void);
	~CActionMoveBy(void);
	void init(float dt,CPoint& ptDelta);
	void update(float time);
	void startWidthTarget(CBaseWidget* pTarget);
protected:
	CPoint m_ptDelta;
	CPoint m_ptStart;
	CPoint m_ptPre;
};
#endif //__C_ACTION_MOVE_BY_H__
