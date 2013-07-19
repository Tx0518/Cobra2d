#ifndef _CXMLUTILS_H_
#define _CXMLUTILS_H_

#include "CPlusInclude.h"
#include <string>

namespace Xml_Helper
{	
	/*
		从Xml节点中获取文本
		@param node 当前节点
		@return string
	*/
	std::string getElementText(const pugi::xml_node node);		

	/*
		从Xml节点中获取文本
		@param 当前节点
		@return Int
	*/
	int getElementInt(const pugi::xml_node node);

	/*
		从Xml节点中获取文本
		@param 当前节点
		@return float
	*/
	float getElementFloat(const pugi::xml_node node);
	
	/*
		从Xml节点中获取子节点文本
		@param node 当前节点
		@param szTag 子节点名称
		@return string
	*/
	std::string getChildrenElementText(const pugi::xml_node node,const char* szTag);

	/*
		从Xml节点中获取子节点文本
		@param node 当前节点
		@param szTag 子节点名称
		@return int
	*/
	int getChildrenElementInt(const pugi::xml_node node,const char* szTag );
	
	/*
		从Xml节点属性中获取文本
		@param 当前节点
		@param 属性名字
		@return string
	*/
	std::string getAttributeText(const pugi::xml_node node,const char* attrName);

	/*
		从Xml节点属性中获取文本
		@param 当前节点
		@param 属性名字
		@return Int
	*/
	int getAttributeInt(const pugi::xml_node node,const char* attrName);

	/*
		从Xml节点属性中获取文本
		@param 当前节点
		@param 属性名字
		@return Float
	*/
	float getAttributeFloat(const pugi::xml_node node,const char* attrName);
}

#endif //_CXMLUTILS_H_