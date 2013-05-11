#include "CMsgJNI.h"
#ifdef ANDROID
#include <jni.h>
#include "JniHelper.h" //TODO

RecevieMsgFromJavaHandler::~RecevieMsgFromJavaHandler()
{
	;//do nothing here
}
void RecevieMsgFromJavaHandler::OnReceiveMessageFromJava(int iD,std::map<std::string,std::string>& map)
{
	;//do nothing here
}

void RecevieMsgFromJavaHandler::addInterestID(int ID)
{
	std::vector<int>::iterator iter = m_ObserverID.begin();
	while (iter != m_ObserverID.end())
	{
		if (ID == *iter)
		{
			break;
		}
		iter++;
	}

	if (iter == m_ObserverID.end())
	{
		m_ObserverID.push_back(ID);
	}
}

void RecevieMsgFromJavaHandler::removeInterestID(int ID)
{
	std::vector<int>::iterator iter = m_ObserverID.begin();
	while (iter != m_ObserverID.end())
	{
		if (ID == *iter)
		{
			m_ObserverID.erase(iter);
			break;
		}
		iter++;
	}
}

bool RecevieMsgFromJavaHandler::isInterestID(int ID)
{
	bool ret = false;
	std::vector<int>::iterator iter = m_ObserverID.begin();
	while (iter != m_ObserverID.end())
	{
		if (ID == *iter)
		{
			ret = true;
			break;
		}
		iter++;
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////
RecevieMsgFromJavaMgr::RecevieMsgFromJavaMgr()
{

}

RecevieMsgFromJavaMgr::~RecevieMsgFromJavaMgr()
{

}

void RecevieMsgFromJavaMgr::addHandler(RecevieMsgFromJavaHandler* pHandler)
{
	if (!this->hasHander(pHandler))
	{
		m_veHandlers.push_back(pHandler);
	}
}

void RecevieMsgFromJavaMgr::removeHandler(RecevieMsgFromJavaHandler* pHandler)
{
	if (this->hasHander(pHandler))
	{
		std::vector<RecevieMsgFromJavaHandler*>::iterator iter = m_veHandlers.begin();
		while (iter != m_veHandlers.end())
		{
			if (pHandler == *iter)
			{
				m_veHandlers.erase(iter);
				break;
			}
			iter++;
		}
	}
}


bool RecevieMsgFromJavaMgr::hasHander(RecevieMsgFromJavaHandler* pHandler)
{
	bool ret = false;
	std::vector<RecevieMsgFromJavaHandler*>::iterator iter = m_veHandlers.begin();
	while (iter != m_veHandlers.end())
	{
		if (pHandler == *iter)
		{
			ret = true;
			break;
		}
		iter++;
	}
	return ret;
}

void RecevieMsgFromJavaMgr::distributeMsg(int id,std::map<std::string,std::string>& map)
{
	std::vector<RecevieMsgFromJavaHandler*>::iterator iter = m_veHandlers.begin();
	RecevieMsgFromJavaHandler* pTemp  = NULL;
	while (iter != m_veHandlers.end())
	{
		pTemp = *iter;
		if (pTemp->isInterestID(id))
		{
			pTemp->OnReceiveMessageFromJava(id,map);
		}
		iter++;
	}
}
//////////////////////////////////////////////////////////////////////////
//send msg to java
void SendMessageToJava(int iD,std::map<std::string,std::string>& map)
{
	ENTERFUNC();
	JniMethodInfo methodInfo;
	if(JniHelper::getStaticMethodInfo(methodInfo, "com/zlz/warrior/warrior", "ReceiveMessage", 
		"(ILjava/util/Hashtable;)V"))
	{
		jclass class_Hashtable= methodInfo.env->FindClass("java/util/Hashtable"); 
		jmethodID construct_method= methodInfo.env->GetMethodID( class_Hashtable, "<init>","()V"); 
		jobject obj_Map =methodInfo.env->NewObject( class_Hashtable, construct_method, ""); 
		jmethodID add_method= methodInfo.env->GetMethodID(class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"); 
		//convert map to hashtable

		jstring jstrKey;
		jstring jstrValue;
		std::map<std::string,std::string>::iterator iter = map.begin();
		while (iter != map.end())
		{
			jstrKey   = methodInfo.env->NewStringUTF(iter->first.c_str());
			jstrValue = methodInfo.env->NewStringUTF(iter->second.c_str());
			//add it to hashtable
			methodInfo.env->CallObjectMethod(obj_Map,add_method,jstrKey,jstrValue); 
			methodInfo.env->DeleteLocalRef(jstrKey);
			methodInfo.env->DeleteLocalRef(jstrValue);
			iter++;
		}
		//
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, iD,obj_Map);
		methodInfo.env->DeleteLocalRef(obj_Map);
	}
	LVFUNC();
}

extern "C"
{
	void  Java_com_zlz_warrior_warrior_nativeReceiveMessage(JNIEnv*  env,jobject thiz,jint id,jobject jhashtable)
	{
		ENTERFUNC();
		JniMethodInfo methodInfo;
		if(JniHelper::getStaticMethodInfo(methodInfo, "com/zlz/warrior/warrior", "ReceiveMessage", 
			"(ILjava/util/Hashtable;)V"))
		{
			std::map<std::string,std::string> map;
			jclass class_Hashtable   = methodInfo.env->FindClass("java/util/Hashtable"); 
			jclass class_Enumeration = methodInfo.env->FindClass("java/util/Enumeration"); 
			///////////////////////////////////////////////////////////////////////////////////
			jmethodID keys_method = methodInfo.env->GetMethodID(class_Hashtable,"keys","()Ljava/util/Enumeration;"); 
			jmethodID get_method  = methodInfo.env->GetMethodID(class_Hashtable,"get","(Ljava/lang/Object;)Ljava/lang/Object;"); 
			//////////////////////////////////////////////////////////////////////////////////////////
			jobject  keyEnumeration = methodInfo.env->CallObjectMethod(jhashtable,keys_method);
			jmethodID nextElement_method = methodInfo.env->GetMethodID(class_Enumeration,"nextElement","()Ljava/lang/Object;"); 
			jmethodID hasMoreElements_method = methodInfo.env->GetMethodID(class_Enumeration,"hasMoreElements","()Z"); 
			while (methodInfo.env->CallBooleanMethod(keyEnumeration,hasMoreElements_method))
			{
				jstring jstrKey   = static_cast<jstring>(methodInfo.env->CallObjectMethod(keyEnumeration,nextElement_method));
				jstring jstrValue = static_cast<jstring>(methodInfo.env->CallObjectMethod(jhashtable,get_method,jstrKey));
				std::string strKey = JniHelper::jstring2string(jstrKey);
				std::string strValue = JniHelper::jstring2string(jstrValue);
				map[strKey] = strValue;
			}
			//now send the msg to handler
			RecevieMsgFromJavaMgr::getInstance()->distributeMsg(id,map);
		}
		LVFUNC();
	}

};



#endif