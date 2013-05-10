#include "CMsgSubject.h"
#include "CNetMarcos.h"

CMsgSubject::CMsgSubject(void)
{
	m_bIsChange = false;
	m_MsgBuf_vector.clear();
}

CMsgSubject::~CMsgSubject(void)
{
}

void CMsgSubject::OnMessage(const char* bytes, int nLen)
{
// 	memset(m_msgBuffer, 0 , MAX_MESSAGE_BUF_LEN);
// 	memcpy(m_msgBuffer, bytes, static_cast<size_t>(nLen));
	m_bIsChange = true;
	OnDispatchMessage((SeqMsgHead*)(bytes));
}

void CMsgSubject::RegObserver(unsigned short type,  IMsgObserver* pObserver)
{
	std::map<unsigned short, vIMsgObserverBase>::iterator it = m_msgMap.find(type);
	if(it !=  m_msgMap.end())
	{
		vIMsgObserverBase& vIMsgArr = it->second;
		for(size_t i = 0; i < vIMsgArr.size(); ++i)
		{
			if(pObserver == vIMsgArr[i])
				return;
		}
	}
	m_msgMap[type].push_back(pObserver);
}

void CMsgSubject::DelObserver(unsigned short type, IMsgObserver* pObserver)
{
	if(m_msgMap.size()<1)
		return;
	std::map<unsigned short, vIMsgObserverBase>::iterator it = m_msgMap.find(type);
	if(m_msgMap.end() != it)
	{
		for (size_t i = 0; i < it->second.size(); ++i)
		{
			if (pObserver == m_msgMap[type][i])
			{
				m_msgMap[type].erase(m_msgMap[type].begin() + i);
			}
		}
		//m_msgMap.erase(it);
	}
}


void CMsgSubject::OnDispatchMessage(SeqMsgHead* pMsgHead)
{
	if (!m_bIsChange)
		return;		
	m_DispatchFlg = false;
	std::map<unsigned short, vIMsgObserverBase>::iterator it = m_msgMap.find(pMsgHead->usType);
	if(it != m_msgMap.end())
	{
		std::vector<IMsgObserver*>& observers = (*it).second;
		//IMessageObserverBase* pObserv;
		size_t obSvrCount = observers.size();
		for (unsigned short i = 0; i < obSvrCount; ++i) 
		{
			observers[i]->onUpdate(pMsgHead);
			m_DispatchFlg = true;
		}
	}
	if( !m_DispatchFlg )
	{
		printf("ERROR usType%d usSize:%d\n", pMsgHead->usType, pMsgHead->usSize);
	}

	m_bIsChange	= false;
}
