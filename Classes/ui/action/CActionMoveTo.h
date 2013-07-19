
#ifndef __C_ACTION_MOVE_TO_H__
#define __C_ACTION_MOVE_TO_H__
class CActionMoveTo : public CActionMoveBy
{
public:
	CActionMoveTo(void);
	~CActionMoveTo(void);
	void init(float dt,CPoint& ptDest);
	void startWidthTarget(CBaseWidget* pTarget);
protected:
	CPoint m_ptDest;
};
#endif //__C_ACTION_MOVE_TO_H__
