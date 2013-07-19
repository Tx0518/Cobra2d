#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include <string>
#include "CPlatFormDefine.h"
#include "CMarcos.h"

class CIntent;
class CCobraObjectPool;
class CService;


class CApplication
{
public:
	CApplication(void);
	virtual ~CApplication(void);
	static CApplication* shareApplication();
public:
	virtual void onCreate();
	virtual void onFinish();
	virtual void didEnterApplication();
	virtual void didExitApplication();
	virtual void onMainLoop();
	bool isCreated();
private:
	static CApplication* m_Instance;
	bool m_bIsCreated;
};

#endif //_CAPPLICATION_H_