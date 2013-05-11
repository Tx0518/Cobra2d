#include "CDBHelper.h"
#include "CPropertyHelper.h"
///////////////////////////////////////////////////////////////////////
ContentValues::ContentValues()
{
	m_pValues = new std::vector<std::pair<std::string,std::pair<std::string,int> > >;
}

ContentValues::~ContentValues()
{
	delete m_pValues;
	m_pValues = NULL;
}

bool ContentValues::containsKey(std::string key)
{
	bool ret = false;
	std::vector<std::pair<std::string,std::pair<std::string,int> > >::iterator iter = m_pValues->begin();
	while (iter != m_pValues->end())
	{
		if (iter->first == key)
		{
			ret = true;
			break;
		}
		iter++;
	}
	return ret;
}

int  ContentValues::size(void)
{
	return m_pValues->size	();
}

void ContentValues::clear(void)
{
	m_pValues->clear();
}

std::vector<std::pair<std::string,std::pair<std::string,int> > >*  ContentValues::getContentMap(void)
{
	return m_pValues;
}


///////////////////////////////////////////////////////////////////////
void ContentValues::put(std::string key, int value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = CPropertyHelper::intToString(value);
		pair.second.second = VALUE_TYPE_INT; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, short value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = CPropertyHelper::intToString(value);
		pair.second.second = VALUE_TYPE_SHORT; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, std::vector<char> value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;

		std::string str;
		str.assign(value.begin(),value.end());
		pair.second.first  = str;
		pair.second.second = VALUE_TYPE_BYTE_ARRAY; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, unsigned char value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;

		std::string str;
		str.append(1,value);
		pair.second.first  = str;
		pair.second.second = VALUE_TYPE_BYTE; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, std::string value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = value;
		pair.second.second = VALUE_TYPE_STRING; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, long value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = CPropertyHelper::longToString(value);
		pair.second.second = VALUE_TYPE_LONG; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, bool value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = CPropertyHelper::boolToString(value);
		pair.second.second = VALUE_TYPE_BOOL; 
		m_pValues->push_back(pair);
	}
}

void ContentValues::put(std::string key, float value)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = CPropertyHelper::floatToString(value);
		pair.second.second = VALUE_TYPE_FLOAT; 
		m_pValues->push_back(pair);
	}

}


void ContentValues::putNULL(std::string key)
{
	if (!containsKey(key))
	{
		std::pair<std::string,std::pair<std::string,int> > pair;
		pair.first  = key;
		pair.second.first  = "";
		pair.second.second = VALUE_TYPE_NULL; 
		m_pValues->push_back(pair);
	}
}


std::pair<std::string,std::pair<std::string,int> >* ContentValues::findKey(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* ret = NULL;
	std::vector<std::pair<std::string,std::pair<std::string,int> > >::iterator iter = m_pValues->begin();
	while (iter != m_pValues->end())
	{
		if (iter->first == key)
		{
			ret = &(*iter);
			break;
		}
		iter++;
	}
	return ret;
}

std::string  ContentValues::getAsString(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		return pValue->second.first;
	}
	return "";
}

bool		 ContentValues::getAsBool(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		return CPropertyHelper::stringToBool(str);
	}	
	return false;
}

int			 ContentValues::getAsInt(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		return CPropertyHelper::stringToInt(str);
	}
	return 0;
}

short        ContentValues::getAsShort(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		return CPropertyHelper::stringToInt(str);
	}
	return 0;
}

bool		 ContentValues::getAsByteArray(std::string key,std::string& strOut)
{
	bool ret = false;
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		if(str.length())
		{
			strOut.assign(str.begin(),str.end());
			ret = true;
		}
	}
	return ret;
}

long         ContentValues::getAsLong(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		return CPropertyHelper::stringToLong(str);
	}
	return 0;
}

float        ContentValues::getAsfloat(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		return CPropertyHelper::stringToFloat(str);
	}
	return 0;
}



unsigned char         ContentValues::getAsByte(std::string key)
{
	std::pair<std::string,std::pair<std::string,int> >* pValue = this->findKey(key);
	if (pValue)
	{
		std::string str = pValue->second.first;
		return CPropertyHelper::stringToUnsignedChar(str);
	}
	return 0;
}


void ContentValues::remove(std::string key)
{
	std::vector<std::pair<std::string,std::pair<std::string,int> > >::iterator iter = m_pValues->begin();
	while (iter != m_pValues->end())
	{
		if (iter->first == key)
		{
			m_pValues->erase(iter);
			break;
		}
		iter++;
	}
}
///////////////////////////////////////////////////////////////////////
DBHelper::DBHelper(void)
{
	m_pDataBase = NULL;
}

DBHelper::~DBHelper(void)
{
	if(m_pDataBase)
	{
		delete m_pDataBase;
		m_pDataBase = NULL;
	}
}


bool DBHelper::init(const char* strDBName,std::string strKey)
{
	bool ret = false;
	COBRA_ASSERT(m_pDataBase == NULL,"DBHelper can only be inited once");
#if 0//TODO check me
	if(strDBName)
	{
		m_pDataBase = new CDataBase();
		std::string strPath = CCFileUtils::getWriteablePath();
		strPath += strDBName;
		LOG("try to init db = [%s]",strPath.c_str());
		ret = m_pDataBase->openDB(strPath.c_str(),strKey);
	}
#endif
	return ret;
}

bool DBHelper::createTable(const char* strTableName,ContentValues* pContentValues)
{
	bool ret = false;
	COBRA_ASSERT(m_pDataBase != NULL,"DBHelper must be inited first");
	if(strTableName && pContentValues)
	{
		std::string str = "CREATE TABLE IF NOT EXISTS ";
		str += strTableName;
		str += " ( ";
		std::vector<std::pair<std::string,std::pair<std::string,int> > >* pMap = pContentValues->getContentMap();
		std::vector<std::pair<std::string,std::pair<std::string,int> > >::iterator  iter = pMap->begin();
		while (iter != pMap->end())
		{
			//key 
			str += iter->first;
			str += " ";
			//value
			str += iter->second.first;
			iter++;
			if(iter != pMap->end())
			{
				str += ", ";	
			}
		}
		str += " )";
		LOG("create sql = [%s]",str.c_str());
		ret = m_pDataBase->executeSql(str.c_str());
	}
	return ret;
}

bool DBHelper::insert(const char* strTableName,ContentValues* pContentValues,bool bReplace)
{
	bool ret = false;
	COBRA_ASSERT(m_pDataBase != NULL,"DBHelper must be inited first");
	if(strTableName && pContentValues)
	{
		std::string sql;
		if (bReplace)
		{//replace
			sql = "REPLACE INTO ";
		}
		else
		{
			sql = "INSERT INTO ";
		}
		
		sql += strTableName;
		sql += " (";
		std::vector<std::pair<std::string,std::pair<std::string,int> > >* pMap = pContentValues->getContentMap();
		std::vector<std::pair<std::string,std::pair<std::string,int> > >::iterator  iter = pMap->begin();
		while (iter != pMap->end())
		{
			//key
			sql += iter->first;	
			iter++;
			if (iter != pMap->end())
			{
				sql += ",";
			}
			else
			{
				sql += ") ";
			}
		}
		sql += "VALUES (";
		iter = pMap->begin();
		while (iter != pMap->end())
		{
			//value placeholder
			iter++;
			if (iter != pMap->end())
			{
				sql += "?,";
			}
			else
			{
				sql += "?)";
			}
		}
		//bind values
		LOG("inser sql =[%s]",sql.c_str());
		CDBStatement* pStatement = m_pDataBase->createStatement(sql.c_str());
		if(pStatement)
		{
			iter = pMap->begin();
			int iColIndex = 0;
			std::vector<std::string*> vcStrTemp;
			while (iter != pMap->end())
			{
				switch (iter->second.second)
				{
				case ContentValues::VALUE_TYPE_BOOL:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsBool(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_BYTE:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsByte(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_SHORT:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsShort(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_INT:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsInt(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_LONG:
					{
						pStatement->bindDouble(iColIndex,pContentValues->getAsLong(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_FLOAT:
					{
						//
						pStatement->bindDouble(iColIndex,pContentValues->getAsfloat(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_BYTE_ARRAY:
					{
						//
						std::string* pstrTemp = new std::string();
						vcStrTemp.push_back(pstrTemp);
						pContentValues->getAsByteArray(iter->first,*pstrTemp);
						pStatement->bindBytes(iColIndex,pstrTemp->c_str(),pstrTemp->length());
						break;
					}
				case ContentValues::VALUE_TYPE_STRING:
					{
						std::string* pstrTemp = new std::string();
						*pstrTemp = pContentValues->getAsString(iter->first);
						vcStrTemp.push_back(pstrTemp);
						pStatement->bindString(iColIndex,*pstrTemp);
						break;
					}
				case ContentValues::VALUE_TYPE_NULL:
					{
						pStatement->bindNull(iColIndex);
						break;
					}
				default:
					{
						LOG("insert unknown ContentValues type =[%d]",iter->second.second);
						break;
					}
				}
				iColIndex++;
				iter++;
			}

			ret = m_pDataBase->executeStatement(pStatement);
			delete pStatement;
			pStatement = NULL;

			std::vector<std::string*>::iterator iterVcStr = vcStrTemp.begin();
			std::string* pTemp = NULL;
			while (iterVcStr != vcStrTemp.end())
			{
				pTemp = *iterVcStr;
				if (pTemp)
				{
					delete pTemp;
					pTemp = NULL;
				}
				iterVcStr++;
			}
		}
		else
		{
			LOG("m_pDataBase->createStatement failed may be sql string is invalid");
		}
		

	}
	else
	{
		LOG("DBHelper::insert parameter error");
	}
	return ret;
}


CDBEnumerator* DBHelper::query(const char* strTabName,std::string strCols,std::string strSeletion,std::string strOrderBy)
{
	CDBEnumerator* ret = NULL;
	///
	if (strTabName && 0 < strCols.length())
	{
		std::string sql = "SELECT ";
		sql += strCols;
		sql += " FROM ";
		sql += strTabName;
		
		///
		if (0 < strSeletion.length())
		{
			sql += " WHERE ";
			sql.append(strSeletion.begin(),strSeletion.end());
		}
		
		if (0 < strOrderBy.length())
		{
			sql += " ORDER BY ";
			sql += strOrderBy;
		}

		LOG("query sql = [%s]",sql.c_str());
		ret = m_pDataBase->query(sql.c_str());
	}
	else
	{
		LOG("DBHelper::query parameter error");
	}
	return ret;
}


bool DBHelper::update(const char* strTabeName,ContentValues* pContentValues,std::string strSeletion)
{
	bool ret = false;
	if (strTabeName && pContentValues)
	{
		std::string sql = "UPDATE ";
		sql += strTabeName;
		sql += " ";
		sql += "SET ";
		std::vector<std::pair<std::string,std::pair<std::string,int> > >* pMap = pContentValues->getContentMap();
		std::vector<std::pair<std::string,std::pair<std::string,int> > >::iterator  iter = pMap->begin();
		while (iter != pMap->end())
		{
			//key
			sql += iter->first;	
			iter++;
			if (iter != pMap->end())
			{
				sql += "=?,";
			}
			else
			{
				sql += "=? ";
			}
		}

		if (0 < strSeletion.length())
		{
			sql += " WHERE ";
			sql.append(strSeletion.begin(),strSeletion.end());
		}
		LOG("update sql = [%s]",sql.c_str());
		//bind values
		CDBStatement* pStatement = m_pDataBase->createStatement(sql.c_str());
		if (pStatement)
		{
			iter = pMap->begin();
			int iColIndex = 0;
			std::vector<std::string*> vcStrTemp;
			while (iter != pMap->end())
			{
				switch (iter->second.second)
				{
				case ContentValues::VALUE_TYPE_BOOL:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsBool(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_BYTE:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsByte(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_SHORT:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsShort(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_INT:
					{
						pStatement->bindInt(iColIndex,pContentValues->getAsInt(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_LONG:
					{
						pStatement->bindDouble(iColIndex,pContentValues->getAsLong(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_FLOAT:
					{
						//
						pStatement->bindDouble(iColIndex,pContentValues->getAsfloat(iter->first));
						break;
					}
				case ContentValues::VALUE_TYPE_BYTE_ARRAY:
					{
						//
						std::string* pstrTemp = new std::string();
						vcStrTemp.push_back(pstrTemp);
						pContentValues->getAsByteArray(iter->first,*pstrTemp);
						pStatement->bindBytes(iColIndex,pstrTemp->c_str(),pstrTemp->length());
						break;
					}
				case ContentValues::VALUE_TYPE_STRING:
					{
						std::string* pstrTemp = new std::string();
						*pstrTemp = pContentValues->getAsString(iter->first);
						vcStrTemp.push_back(pstrTemp);
						pStatement->bindString(iColIndex,*pstrTemp);
						break;
					}
				case ContentValues::VALUE_TYPE_NULL:
					{
						pStatement->bindNull(iColIndex);
						break;
					}
				default:
					{
						LOG("insert unknow ContentValues type =[%d]",iter->second.second);
						break;
					}
				}
				iColIndex++;
				iter++;
			}

			ret = m_pDataBase->executeStatement(pStatement);
			delete pStatement;
			pStatement = NULL;


			std::vector<std::string*>::iterator iterVcStr = vcStrTemp.begin();
			std::string* pTemp = NULL;
			while (iterVcStr != vcStrTemp.end())
			{
				pTemp = *iterVcStr;
				if (pTemp)
				{
					delete pTemp;
					pTemp = NULL;
				}
				iterVcStr++;
			}
		}
		else
		{
			LOG("m_pDataBase->createStatement failed may be sql string is invalid");
		}
	}
	else
	{
		LOG("DBHelper::update parameter error");
	}
	return ret;
}

bool DBHelper::del(const char* strTabName,std::string strSeletion)
{
	bool ret = false;
	if (strTabName)
	{
		std::string sql = "DELETE FROM ";
		sql += strTabName;
		//如果有选择限制
		if (strSeletion.length())
		{
			sql += " WHERE ";
			sql.append(strSeletion.begin(),strSeletion.end());
		}
		LOG("del sql =[%s]",sql.c_str());
		ret = m_pDataBase->executeSql(sql.c_str());
	}
	else
	{
		LOG("DBHelper::del parameter error");
	}
	return ret;
}


bool DBHelper::beginTransaction(void)
{
	return m_pDataBase->beginTransaction();
}

bool DBHelper::endTransaction(void)
{
	return m_pDataBase->endTransaction();
}

bool DBHelper::rollBackTransaction(void)
{
	return m_pDataBase->rollBackTransaction();
}

const CDataBase* DBHelper::getDataBase(void)
{
	return this->m_pDataBase;
}