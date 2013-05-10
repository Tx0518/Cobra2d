#ifndef _BBTHREAD_H_
#define _BBTHREAD_H_

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

#ifdef WIN32
typedef DWORD ThreadID;
#else
typedef pthread_t ThreadID;
#endif


#include "CTask.h"

//���߳���
class CThread  
{
public:
	CThread();
	virtual ~CThread();

//////////////////////////////////////////////////////////////////////////
protected://����
	//IThreadEvent& m_event;
	ThreadID m_nID;	
	CTask m_task;
	bool m_bRun;

	//�߳��˳���������
#ifdef WIN32
	HANDLE m_hHandle;
#else
	pthread_cond_t m_exit;
	pthread_mutex_t m_exitMutex;
	bool m_bStop;
#endif
	//End�߳��˳���������
	//////////////////////////////////////////////////////////////////////////
public://�ӿ�
	bool Run( MethodPointer method, void *pObj, void *pParam );//�����̣߳�ʹ�����Ա������pParam���ݸ��̺߳����Ĳ���
	bool Run( FuntionPointer fun, void *pParam );//�����̣߳�ʹ��ȫ�ֺ�����pParam���ݸ��̺߳����Ĳ���
	/*
	 	ֹͣ
	 */
	void Stop(long lMillSecond = 0);
	/*
	 	�ȴ��߳�ֹͣ
		ע��linux��һ�����أ�֮���ٵ���WaitStop()��Stop();�����ٵȴ���ֱ�ӷ���
		��ΪWaitStop();����ǰ�ᷢ��1���߳̽����źţ�֪ͨ�������ܴ��ڵȴ����߳�
	 */
	void WaitStop();
	ThreadID GetID();//ȡ���߳�ID

protected:
	bool Run( void *pParam );//�����̣߳�pParam���ݸ��̺߳����Ĳ���
	static void* TMain(void*);
	void* Main();
};

#endif //_CTHREAD_H_