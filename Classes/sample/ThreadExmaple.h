#ifndef _THREADEXMAPLE_H_
#define _THREADEXMAPLE_H_
#include "zthread/Thread.h"

#include "CCobraObject.h"

using namespace ZThread; 

class ThreadExample : public Runnable
{
public:
	ThreadExample(void)
		:m_bQuit(false),
		_id(0),
		_num(0)
	{
	}

	~ThreadExample(void)
	{
		m_bQuit = false;
	}

	virtual void run() 
	{
		LOG("ThreadExample============");
		_num = 1;  
		while(_num <= 3)  
		{  
			LOG("id===========%d",_num);
			_num++;  
			Thread::sleep(1000);  
		}
	}

	void quit()
	{
		m_bQuit = true;
	}

private:
	bool m_bQuit; 
	int _id;                  // 给任务一个识别id   
	int _num;                 // 计数器   
};

#endif //_THREADEXMAPLE_H_