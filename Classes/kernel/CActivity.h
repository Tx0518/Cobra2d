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
		���󴴽����
		@return void
	*/
	virtual void onCreate();
	/*
		��������
		@return void
	*/
	virtual void onFinish();
	/*
		���������Activity����
		@param intent		������ͼ��Ϣ����
		@return void
	*/
	virtual void startActivity(CIntent* intent);
	/*
		�������ص�����
		@param reponse		������Ӧ����Ϣ
		@return void
	*/
	virtual void onResponseHandler(CResponse* reponse);
	/*
		��Ϣ������ں���
		@param pMsgHead	��ϢBuff����
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