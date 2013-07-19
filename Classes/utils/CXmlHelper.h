#ifndef _CXMLUTILS_H_
#define _CXMLUTILS_H_

#include "CPlusInclude.h"
#include <string>

namespace Xml_Helper
{	
	/*
		��Xml�ڵ��л�ȡ�ı�
		@param node ��ǰ�ڵ�
		@return string
	*/
	std::string getElementText(const pugi::xml_node node);		

	/*
		��Xml�ڵ��л�ȡ�ı�
		@param ��ǰ�ڵ�
		@return Int
	*/
	int getElementInt(const pugi::xml_node node);

	/*
		��Xml�ڵ��л�ȡ�ı�
		@param ��ǰ�ڵ�
		@return float
	*/
	float getElementFloat(const pugi::xml_node node);
	
	/*
		��Xml�ڵ��л�ȡ�ӽڵ��ı�
		@param node ��ǰ�ڵ�
		@param szTag �ӽڵ�����
		@return string
	*/
	std::string getChildrenElementText(const pugi::xml_node node,const char* szTag);

	/*
		��Xml�ڵ��л�ȡ�ӽڵ��ı�
		@param node ��ǰ�ڵ�
		@param szTag �ӽڵ�����
		@return int
	*/
	int getChildrenElementInt(const pugi::xml_node node,const char* szTag );
	
	/*
		��Xml�ڵ������л�ȡ�ı�
		@param ��ǰ�ڵ�
		@param ��������
		@return string
	*/
	std::string getAttributeText(const pugi::xml_node node,const char* attrName);

	/*
		��Xml�ڵ������л�ȡ�ı�
		@param ��ǰ�ڵ�
		@param ��������
		@return Int
	*/
	int getAttributeInt(const pugi::xml_node node,const char* attrName);

	/*
		��Xml�ڵ������л�ȡ�ı�
		@param ��ǰ�ڵ�
		@param ��������
		@return Float
	*/
	float getAttributeFloat(const pugi::xml_node node,const char* attrName);
}

#endif //_CXMLUTILS_H_