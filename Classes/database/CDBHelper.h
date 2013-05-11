#ifndef __DB_HELPER_H__
#define __DB_HELPER_H__
#include "CMarcos.h"
#include "CDataBase.h"
/*
数据库帮助类，模拟安卓的实现
*/

class ContentValues
{
public:
	enum
	{
		VALUE_TYPE_BYTE,
		VALUE_TYPE_BOOL,
		VALUE_TYPE_SHORT,
		VALUE_TYPE_INT,
		VALUE_TYPE_BYTE_ARRAY,
		VALUE_TYPE_FLOAT,
		VALUE_TYPE_LONG,
		VALUE_TYPE_STRING,
		VALUE_TYPE_NULL
	};

	ContentValues();
	~ContentValues();
	//////////////////////////
	bool containsKey(std::string key);
	int  size(void);
	void clear(void);
	std::vector<std::pair<std::string,std::pair<std::string,int> > >* getContentMap(void);
	void put(std::string key, int value);
	void put(std::string key, short value);
	void put(std::string key, std::vector<char> value);
	void put(std::string key, unsigned char value);
	void put(std::string key, std::string value);
	void put(std::string key, long value);
	void put(std::string key, bool value);
	void put(std::string key, float value);
	void putNULL(std::string key); 

	std::string getAsString(std::string key);
	bool		getAsBool(std::string key);
	int			getAsInt(std::string key);
	short       getAsShort(std::string key);
	bool		getAsByteArray(std::string key,std::string& strByteBuffer);
	long        getAsLong(std::string key);
	float       getAsfloat(std::string key);
	unsigned char        getAsByte(std::string key);

	void remove(std::string key);
	//////////////////////////
private:
	std::pair<std::string,std::pair<std::string,int> >* findKey(std::string key);
	//std::map<std::string,std::pair<std::string,int> >* m_pValues;
	std::vector<std::pair<std::string,std::pair<std::string,int> > >* m_pValues;
};

//数据库默认加密的KEY
#define DEFAULT_KEY "xiaoruyu*$@"
class DBHelper
{
public:
	DBHelper(void);
	~DBHelper(void);
	bool init(const char* strDBName,std::string strKey =DEFAULT_KEY);
	bool createTable(const char* strTableName,ContentValues* pContentValues);
	//bReplace 是否使用replace 语句
	bool insert(const char* strTableName,ContentValues* pContentValues,bool bReplace = false);
	CDBEnumerator* query(const char* strTabName,std::string strCols,std::string strSeletion = std::string(""),std::string strOrderBy = std::string(""));
	bool update(const char* strTabeName,ContentValues* pContentValues,std::string strSeletion);
	bool del(const char* strTabName,std::string strSeletion = "");
	////////////////
	bool beginTransaction(void);
	bool endTransaction(void);
	bool rollBackTransaction(void);
	const CDataBase* getDataBase(void);
private:
	CDataBase* m_pDataBase;
};
#endif //__DB_HELPER_H__