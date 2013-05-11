#ifndef __MSG_JNI_H__
#define __MSG_JNI_H__
#include "CSingleton.h"
#ifdef ANDROID
//send msg to java
extern void SendMessageToJava(int iD,std::map<std::string,std::string>& map);

//
//You must implement this method for your own route
class RecevieMsgFromJavaHandler
{
public:
	virtual ~RecevieMsgFromJavaHandler();
	virtual void OnReceiveMessageFromJava(int iD,std::map<std::string,std::string>& map);
	//if the ID exists do nothing
	void addInterestID(int ID);
	//if the ID does not exist do nothing
	void removeInterestID(int ID);
	//return true if it interests at the ID
	bool isInterestID(int ID);
private:
	std::vector<int> m_ObserverID;
};

class RecevieMsgFromJavaMgr :public  CSingleton<RecevieMsgFromJavaMgr>
{
public:
	//add 
	void addHandler(RecevieMsgFromJavaHandler* pHandler);
	//after use you must remove it yourself
	void removeHandler(RecevieMsgFromJavaHandler* pHandler);
	void distributeMsg(int id,std::map<std::string,std::string>& map);
private:
	friend class CSingleton<RecevieMsgFromJavaMgr>;
	RecevieMsgFromJavaMgr();
	~RecevieMsgFromJavaMgr();
private:
	std::vector<RecevieMsgFromJavaHandler*> m_veHandlers;
	bool hasHander(RecevieMsgFromJavaHandler* pHandler);
};


#endif
#endif //__MSG_JNI_H__