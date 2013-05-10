#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include <string>
#include <map>
#include "CSingleton.h"
#include "CPlatFormDefine.h"
#include "CMarcos.h"

class CIntent;
class CCobraObjectPool;
class CService;

class CApplication : public CSingleton<CApplication>
{
public:
	void onCreate();
	void onFinish();
	virtual void bindService(CIntent* intent);
	virtual void unBindService(CIntent* intent);
	CCobraObjectPool* getAppPool();
	CService* getServiceById(int id);
	bool isServiceRunnable(int serviceID);
protected:
	void loadCobraConfig(const char* xmlPath);
	bool isInit();
private:
	friend class CSingleton<CApplication>;
	CApplication(void);
	~CApplication(void);
private:
	/*
		ÓÐ´ýÓÅ»¯
	*/
	CCobraObjectPool* m_CobraPool;
	bool m_bInit;
};

#endif //_CAPPLICATION_H_