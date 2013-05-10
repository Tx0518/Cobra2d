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

//简单线程类
class CThread  
{
public:
	CThread();
	virtual ~CThread();

//////////////////////////////////////////////////////////////////////////
protected://属性
	//IThreadEvent& m_event;
	ThreadID m_nID;	
	CTask m_task;
	bool m_bRun;

	//线程退出控制属性
#ifdef WIN32
	HANDLE m_hHandle;
#else
	pthread_cond_t m_exit;
	pthread_mutex_t m_exitMutex;
	bool m_bStop;
#endif
	//End线程退出控制属性
	//////////////////////////////////////////////////////////////////////////
public://接口
	bool Run( MethodPointer method, void *pObj, void *pParam );//启动线程，使用类成员函数，pParam传递给线程函数的参数
	bool Run( FuntionPointer fun, void *pParam );//启动线程，使用全局函数，pParam传递给线程函数的参数
	/*
	 	停止
	 */
	void Stop(long lMillSecond = 0);
	/*
	 	等待线程停止
		注：linux下一旦返回，之后再调用WaitStop()与Stop();将不再等待，直接返回
		因为WaitStop();返回前会发送1次线程结束信号，通知其它可能存在等待的线程
	 */
	void WaitStop();
	ThreadID GetID();//取得线程ID

protected:
	bool Run( void *pParam );//启动线程，pParam传递给线程函数的参数
	static void* TMain(void*);
	void* Main();
};

#endif //_CTHREAD_H_