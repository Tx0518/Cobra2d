#ifndef _CACTIVITY_H_
#define _CACTIVITY_H_

#include "CCobraObject.h"
#include "CBaseDefine.h"
#include "CMsgSubject.h"

class CIntent;
class CResponse;
class CObserver;
class CService;
class CGui;

class CActivity : public CCobraObject,public IMsgObserver
{
public:
	CActivity(void);
	virtual ~CActivity(void);
	/*
		对象创建入口
		@return void
	*/
	virtual void onCreate();
	/*
		对象销毁
		@return void
	*/
	virtual void onFinish();
	/*
		请求打开其他Activity函数
		@param intent		请求意图信息对象
		@return void
	*/
	virtual void startActivity(CIntent* intent);
	/*
		服务反馈回调函数
		@param reponse		服务器应答信息
		@return void
	*/
	virtual void onResponseHandler(CResponse* reponse);
	/*
		消息处理入口函数
		@param pMsgHead	消息Buff数组
		@return void
	*/
	virtual void onUpdate( void* pMsgHead );
protected:
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bisActive,Active)
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bHasObserver,hasObserver)
	COBRA_CREATE_PROPERTY_BY_BOOL(m_bHasService,hasService)
	COBRA_CREATE_PROPERTY(CObserver*,m_Observer,Observer)
	COBRA_CREATE_PROPERTY(CService*,m_Service,Service)
	COBRA_CREATE_PROPERTY(CGui*,m_pGui,GUI)
};

#endif //_CACTIVITY_H_