#ifndef _CHANDLER_H_
#define _CHANDLER_H_

#include <vector>

const int MAX_HANDLER_MESSAGE_COUNT = 20; //����������޵���Ϣ����������ɸ���ʵ���������

class CIntent;
class CEvent;
class CMessage;
/************************************************************************/
/* 
	CHandler
	TODO:�������������������W��ͼ���¼���)
*/
class CHandler
{
public:
	static void onHandler(CEvent* evt);
	static void onRegisterEvent(CEvent* evt);
	static void onHandler(CIntent* intent);

public:
	typedef enum _HANDLER_TYPE
	{
		COMPLICATING = 0, //����
		SEQUENCE,		  //����
	}eHandlerMode;

	CHandler(void);
	virtual ~CHandler(void);

	void postMessage(CMessage* msg);
	bool hasMessage(CMessage* msg);
	bool hasMessage(int msgType);
	void clearMessage();
	int hasFreeMessage();
	void setHandlerMode(eHandlerMode mode);
	eHandlerMode getHandlerMode();
	CMessage* getFreeMessage();
	CMessage* getMessageByIndex(int index);
	void dispatchMessage();
	virtual void handlerMessage(CMessage* msg);
protected:
	static void onHandlerIntent(CIntent* intent);
	static void onHandlerEvent(CEvent* evt);

	void doComplicating();
	void doSequence();
protected:
	std::vector<CMessage*> m_pMsgSet;  
	typedef std::vector<CMessage*>::iterator pMessageItor;
	eHandlerMode m_eHandlerType;
};

#endif //_CHANDLER_H_