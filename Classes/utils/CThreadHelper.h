#ifndef _CTHREADHELPER_H_
#define _CTHREADHELPER_H_

#include "zthread/ZThread.h"

namespace thread_helper
{
#if 0
	static void newThread(ZThread::Runnable* runnable)
	{
		try
		{
			ZThread::Thread th(runnable);
		}
		catch(ZThread::Synchronization_Exception& e)
		{
			//error
		}
	}

	static void executeThread(ZThread::Runnable* runnable)
	{
		try
		{
			ZThread::ThreadedExecutor execute(runnable);
		}
		catch (ZThread::Synchronization_Exception& e)
		{
			//error
		}
	}

	static void executeThreadPool(int num,ZThread::Runnable* runnable)
	{
		try
		{
			ZThread::PoolExecutor executor(num);
			for(int i = 0;i < num;i++)
				executer.execute(runnable);
		}
		catch (ZThread::Synchronization_Exception& e)
		{
			//error
		}
	}

	static void executeThreadConcurrent(int num,ZThread::Runnable* runnable)
	{
		try
		{
			ZThread::ConcurrentExecutor executer;
			for(int i = 0;i < num;i++)
				executer.execute(runnable);
		}
		catch (Synchronization_Exception& e)
		{
			//error
		}
	}

	static void executeThreadSynchronous(ZThread::Runnable* runnable)
	{
		try
		{
			ZThread::SynchronousExecutor executor();
			executor.execute(runnable);
		}
		catch (ZThread::Synchronization_Exception& e)
		{

		}//error
	}
		

	static void executeSleep(unsigned long sleepTime)
	{
		ZThread::Thread::sleep(sleepTime);
	}

#endif
}

#endif  //_CTHREADHELPER_H_