#include "CTask.h"


CTask::CTask()
{
	m_pParam = NULL;
	m_method = 0;
	m_pObj = NULL;
	m_fun = NULL;
}

CTask::CTask(int i)
{
	m_method = i;
}

CTask::~CTask()
{
	if ( 0 != m_method ) 
	{
		m_method = 0;
	}
}

//��������
//methodΪ����Ϊvoid* fun(void*)�ĳ�Ա����
void CTask::Accept( MethodPointer method, void *pObj, void *pParam )
{
	m_pParam = pParam;
	m_method = method;
	m_pObj = pObj;
	m_fun = NULL;
}

//��������
//methodΪ����Ϊvoid* fun(void*)�ĺ���
void CTask::Accept( FuntionPointer fun, void *pParam )
{
	m_pParam = pParam;
	m_method = 0;
	m_pObj = NULL;
	m_fun = fun;
}

//ִ������
void* CTask::Execute()
{
	if ( NULL == m_pObj && NULL == m_fun ) return NULL;
	if ( NULL == m_pObj )
	{
		return m_fun(m_pParam);
	}
	else
	{
		return CExecutor::CallMethod(m_method, m_pObj, m_pParam);
	}
}
