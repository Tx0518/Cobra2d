#ifndef _CTASK_H
#define _CTASK_H

#include "CExecutor.h"
/**
	������
	ʹ�÷���
	void* g_fun(void*)
	{
		return NULL;
	}
	class A
	{
	...
	void* RemoteCall fun(void*);
	}
	A a;

	mdk::Task t;
	//linux�±���&A::fun��windows�¿�ʹ��A::fun
	//Ϊ����ֲ�ԣ����鴫��&A::fun��Bind()
	t.Accept( mdk::Executor::Bind(&A::fun), &a, (void*)param );
	t.Execute();

	t.Accept( g_fun, (void*)param );
	t.Execute();
*/
class CTask
{
public:
	CTask(int i);
	CTask();
	virtual ~CTask();
	//��������
	//methodΪ����Ϊvoid* fun(void*)�ĳ�Ա����
	void Accept( MethodPointer method, void *pObj, void *pParam );
	//��������
	//funΪ����Ϊvoid* fun(void*)�ĺ���
	void Accept( FuntionPointer fun, void *pParam );
	//ִ������
	void* Execute();
	
private:
	void *m_pParam;
	MethodPointer m_method;
	void *m_pObj;
	FuntionPointer m_fun;
};

#endif //_CTASK_H
