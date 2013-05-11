#include "CDataBase.h"

#include <stdio.h>
//////////////////////////////////////////////////////////////////////////
CDBEnumerator::CDBEnumerator(void)
{
	m_currentLine = -1;
	m_iTotalLine  = 0;
}

CDBEnumerator::~CDBEnumerator(void)
{
	//do clear
	int index = 0;
	int count = m_iTotalLine;
	std::vector<std::string>* pVc = NULL;
	for (;index < count;index++)
	{
		pVc = this->m_colValues.at(index);
		if (pVc)
		{
			delete pVc;
			pVc = NULL;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
bool CDBEnumerator::moveNext(void)
{
	bool ret = false;
	int totalLine = m_iTotalLine;
	if (totalLine)
	{
		if (++m_currentLine < totalLine)
		{
			ret = true;
		}
		else
		{
			//!!最后一行
			m_currentLine = totalLine - 1;
		}
	}
	return ret;
}

bool CDBEnumerator::getIntAt(int col,int& value)
{
	bool ret = false;
	std::vector<std::string>* pVc = NULL;
	std::string tempStr;
	if (0 <= col && col < m_colCount)
	{
		pVc = this->m_colValues.at(m_currentLine);
		tempStr = pVc->at(col);
		/*std::*/sscanf(tempStr.c_str(),"%d", &value);
		ret = true;
	}
	return ret;
}

bool CDBEnumerator::getDoubleAt(int col,double& value)
{
	bool ret = false;
	std::vector<std::string>* pVc = NULL;
	std::string tempStr;
	if (0 <= col && col < m_colCount)
	{
		pVc = this->m_colValues.at(m_currentLine);
		tempStr = pVc->at(col);
		/*std::*/sscanf(tempStr.c_str(), "%lf", &value);
		ret = true;
	}
	return ret;
}

bool CDBEnumerator::getStringAt(int col,std::string& str)
{
	bool ret = false;
	std::vector<std::string>* pVc = NULL;
	if (0 <= col && col < m_colCount)
	{
		pVc = this->m_colValues.at(m_currentLine);
		std::string& strTemp = pVc->at(col);
		str.assign(strTemp.begin(),strTemp.end());
		ret = true;
	}
	return ret;
}

int  CDBEnumerator::getTotalLineCount(void)
{
	return this->m_iTotalLine;
}
//////////////////////////////////////////////////////////////////////////
CDBStatement::CDBStatement(void)
{
	m_pstmt = NULL;
}
CDBStatement::~CDBStatement(void)
{
	if (m_pstmt)
	{
		sqlite3_finalize(m_pstmt);
		m_pstmt = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
bool CDBStatement::bindInt(int colIndex,int value)
{
	bool ret = false;
	if (m_pstmt)
	{
		if (SQLITE_OK == sqlite3_bind_int(m_pstmt,colIndex + 1,value))
		{
			ret = true;
		}	
	}
	return ret;
}

bool CDBStatement::bindDouble(int colIndex,double value)
{
	bool ret = false;
	if (m_pstmt)
	{
		if (SQLITE_OK == sqlite3_bind_double(m_pstmt,colIndex + 1,value))
		{
			ret = true;
		}
	}
	return ret;
}

bool CDBStatement::bindString(int colIndex,std::string& str)
{
	bool ret = false;
	if (m_pstmt)
	{
		if(SQLITE_OK == sqlite3_bind_text(m_pstmt,colIndex + 1,str.c_str(),str.length(),NULL))
		{
			ret = true;
		}
	}
	return ret;
}

bool CDBStatement::bindNull(int colIndex)
{
	bool ret = false;
	if (m_pstmt)
	{
		if(SQLITE_OK == sqlite3_bind_null(m_pstmt,colIndex + 1))
		{
			ret = true;
		}
	}
	return ret;
}

bool CDBStatement::bindBytes(int colIndex,const void* pBuffer,int size)
{
	bool ret = false;
	if (m_pstmt)
	{
		if(SQLITE_OK == sqlite3_bind_blob(m_pstmt,colIndex + 1,pBuffer,size,NULL))
		{
			ret = true;
		}
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////
CDataBase::CDataBase(void)
{
	m_sqlHandle = NULL;
}

CDataBase::~CDataBase(void)
{
	if (NULL != m_sqlHandle)
	{
		sqlite3_close(m_sqlHandle);
		m_sqlHandle = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
int dataBase_callback(void* pin,int colCount,char** colvalues, char** colsNames)
{//unused now
#if 0
	int ret = 0;
#if 1
	int index = 0;
	CDBEnumerator* pEnumerator = (CDBEnumerator*)pin;
	char** ppTempValues	= NULL;
	char*  pTempValues  = NULL;
	int   strValueLength = 0;
	pEnumerator->m_colCounts.push_back(colCount);
	ppTempValues = new char*[colCount];
	for (;index < colCount;index++)
	{
		//utf8编码，这里获得其字节长度
		strValueLength = strlen(colvalues[index]) + 1;
		pTempValues = new char[strValueLength];
		memcpy(pTempValues,colvalues[index],strValueLength);
		ppTempValues[index] = pTempValues;
		pTempValues = NULL;
	}
	pEnumerator->m_colValues.push_back(ppTempValues);
#else
	int i;
	for(i=0; i<colCount; i++)
	{
		LOG("%s = %s\n", colsNames[i], colvalues[i] ? colvalues[i] : "NULL");
	}
#endif
#endif
	return 0;
}
//////////////////////////////////////////////////////////////////////////
bool CDataBase::openDB(const char* strdbName,const std::string& key)
{
	bool ret = false;
	if (strdbName && NULL == m_sqlHandle)
	{
		if ( SQLITE_OK  == sqlite3_open(strdbName,&m_sqlHandle))
		{
			if (key.length())
			{
				sqlite3_key(m_sqlHandle,key.c_str(),key.length());
			}
			ret = true;
		}
		else
		{
			sqlite3_close(m_sqlHandle);
			m_sqlHandle = NULL;
			LOG("openDB failed");//;
		}		
	}
	return ret;
}

bool CDataBase::executeSql(const char* strSql)
{
	bool ret = false;
	if (strSql && NULL != m_sqlHandle)
	{
		if (SQLITE_OK == sqlite3_exec(m_sqlHandle,strSql,NULL,NULL,NULL))
		{
			ret = true;
		}
		else
		{
			LOG("executeSql failed");//;
		}
	}
	return ret;
}


CDBEnumerator* CDataBase::query(const char* strSql)
{
	CDBEnumerator* ret = NULL;
	if (strSql && NULL != m_sqlHandle)
	{
		ret = new CDBEnumerator();
		if (ret)
		{
			//sqlite3_exec(m_sqlHandle,strSql,dataBase_callback,ret,NULL);
			int rc = SQLITE_OK;         /* Return code */
			const char *zLeftover = NULL;      /* Tail of unprocessed SQL */
			sqlite3_stmt *pStmt = NULL;    /* The current SQL statement */
			rc = sqlite3_prepare(m_sqlHandle, strSql, -1, &pStmt, &zLeftover);
			if (rc == SQLITE_OK && pStmt)
			{
				int index = 0;
				int nCol = sqlite3_column_count(pStmt);
				int iBytes = 0;
				const char* pStr = NULL;
				std::string strTemp;
				ret->m_colCount = nCol;
				while (true)
				{
					rc = sqlite3_step(pStmt);
					if (SQLITE_ROW == rc)
					{
						std::vector<std::string>* pVc = new std::vector<std::string>;
						//TODO check me:考虑sqlite3_column_blob,sqlite3_column_text函数调用失败的情况
						for(index =0; index<nCol; index++)
						{
							pStr = NULL;
							if (SQLITE_BLOB == sqlite3_column_type(pStmt,index))
							{
								iBytes  = sqlite3_column_bytes(pStmt,index);
								pStr    = (const char*)sqlite3_column_blob(pStmt,index);
								strTemp.assign(pStr,iBytes);
							}	
							else if (SQLITE_NULL == sqlite3_column_type(pStmt,index))
							{
								strTemp = "";
							}
							else
							{
								pStr  = (char *)sqlite3_column_text(pStmt,index);
								strTemp = pStr;
							}
							pVc->push_back(strTemp);	
						}
						ret->m_colValues.push_back(pVc);
						ret->m_iTotalLine++;
					}
					else
					{
						break;
					}
				}
				sqlite3_finalize(pStmt);
			}
		}
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
bool CDataBase::beginTransaction(void)
{
	bool ret = false;
	if (NULL != m_sqlHandle)
	{
		ret = this->executeSql("begin;");
	}
	return ret;
}

bool CDataBase::endTransaction(void)
{
	bool ret = false;
	if (NULL != m_sqlHandle)
	{
		ret = this->executeSql("commit;");
	}
	return ret;
}

bool CDataBase::rollBackTransaction(void)
{
	bool ret = false;
	if (NULL != m_sqlHandle)
	{
		ret = this->executeSql("rollback");
	}
	return ret;
}
//////////////////////////////////////////////////////////////////////////
CDBStatement* CDataBase::createStatement(const char* strSql)
{
	CDBStatement* ret = NULL;
	sqlite3_stmt* stmt = NULL;
	if (strSql && NULL != m_sqlHandle)
	{
		//tail is null so you must pass only one sql once a time
		int iSqlRet = sqlite3_prepare(m_sqlHandle,strSql,-1,&stmt,NULL);
		if (SQLITE_OK == iSqlRet)
		{
			ret = new CDBStatement();
			if (ret)
			{
				ret->m_pstmt = stmt;
			}
		}
	}
	return ret;
}

bool CDataBase::executeStatement(CDBStatement* pStmt)
{
	bool ret = false;
	if (NULL != m_sqlHandle && pStmt)
	{
		if (SQLITE_DONE == sqlite3_step(pStmt->m_pstmt))
		{
			//reset it after execution
			sqlite3_reset(pStmt->m_pstmt);
			ret = true;
		}
		else
		{
			LOG("executeStatement failed");//
		}
	}
	return ret;
}