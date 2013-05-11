#ifndef __DATA_BASE_H__
#define __DATA_BASE_H__
#include "sqlite3.h"
#include <string>
#include <vector>
#include "CMarcos.h"
//!!需要使用sqlite库
class dataBase;

class CDBEnumerator
{
public:
	CDBEnumerator(void);
	~CDBEnumerator(void);
	//////////////////////////////////////////////////////////////////////////
	bool moveNext(void);
	//colIndex start from 0
	bool getIntAt(int col,int& value);
	bool getDoubleAt(int col,double& value);
	bool getStringAt(int col,std::string& str);

	int  getTotalLineCount(void);
public://read only
	int  m_iTotalLine;
	int  m_colCount;
	std::vector< std::vector<std::string>* > m_colValues;
	//////////////////////////////////////////////////////////////////////////
	int m_currentLine;
};

//////////////////////////////////////////////////////////////////////////
class CDBStatement
{
public:
	CDBStatement(void);
	~CDBStatement(void);
	//////////////////////////////////////////////////////////////////////////
	//you can bind different values
	//colIndex start from 0
	bool bindInt(int colIndex,int value);
	bool bindDouble(int colIndex,double value);
	bool bindString(int colIndex,std::string& str);
	bool bindNull(int colIndex);
	bool bindBytes(int colIndex,const void* pBuffer,int size);
private:
	friend class CDataBase;
	sqlite3_stmt*	m_pstmt;
};
//////////////////////////////////////////////////////////////////////////
class CDataBase
{
public:
	CDataBase(void);
	virtual ~CDataBase(void);
	//////////////////////////////////////////////////////////////////////////
	//open a db
	//utf-8 encoding
	bool openDB(const char* strdbName,const std::string& strkey);
	//execute sql
	bool executeSql(const char* strSql);
	//query
	CDBEnumerator* query(const char* strSql);
	//transaction
	bool beginTransaction(void);
	bool endTransaction(void);
	bool rollBackTransaction(void);
	//create and execute statement
	CDBStatement* createStatement(const char* strSql);
	bool executeStatement(CDBStatement* pStmt);
private:
	sqlite3* m_sqlHandle;
	//////////////////////////////////////////////////////////////////////////
};

#endif //__DATA_BASE_H__
