#ifndef __C_ACTION_SCALE_TO_H__
#define __C_ACTION_SCALE_TO_H__
#include "CActionInterval.h"
class CActionScaleTo : public CActionInterval
{
public:
	static const int CMD_ID_ACTION_SCALE_TO = 0x2012;
	CActionScaleTo(void);
	~CActionScaleTo(void);
	void init(float dt,float fScale);
	void update(float time);
	void startWidthTarget(CBaseWidget* pTarget);
protected:
	float m_fOriginalScale;
	float m_fScale;
	float m_fDeltaScale;
};

#endif //__C_ACTION_SCALE_TO_H__