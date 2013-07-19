#ifndef _CSTLHELPER_H_
#define _CSTLHELPER_H_

#include <map>
#include <vector>
#include <list>

#define COBRA_MAP_FORECH_FOR_METHOD(refMap,refKey,refClass,refFunc)\
	for (std::map<refKey, refClass>::iterator iter = refMap.begin();iter != refMap.end();iter ++) {\
		refClass value = iter->second; \
	if (value != NULL) { \
		value->refFunc(); \
	} \
}\


namespace stl_helper
{

	template<class TKey,class TClass> 
	inline void clearMap(std::map<TKey,TClass*>& refMap)
	{
		typename std::map<TKey,TClass*>::iterator itor;
		for (itor = refMap.begin();itor!=refMap.end();itor++)
		{
			delete itor->second;
			refMap.erase(itor);
		}
		refMap.clear();
	}

	template <class ForwardIterator>
	void STLDeleteContainerPairPointers(ForwardIterator begin,ForwardIterator end)
	{
		while (begin != end)
		{
			ForwardIterator temp = begin;
			++begin;
			delete temp->first;
			delete temp->second;
		}
	}

	template <class ForwardIterator>
	inline void STLDeleteContainerPairFirstPointers(ForwardIterator begin,ForwardIterator end) 
	{
		while (begin != end) 
		{
			ForwardIterator temp = begin;
			++begin;
			delete temp->first;
		}
	}

	template <class ForwardIterator>
	void STLDeleteContainerPairSecondPointers(ForwardIterator begin,ForwardIterator end) 
	{
		while (begin != end) 
		{
			ForwardIterator temp = begin;
			++begin;
			delete temp->second;
		}
	}

	template<class TClass> 
	inline void clearVector(std::vector<TClass*>& refVector)
	{
		typename std::vector<TClass*>::iterator itor;
		for (itor = refVector.begin();itor!=refVector.end();itor++)
		{
			delete *itor;
			refVector.erase(itor);
		}
		//refVector.clear();
	}

	template<class TClass> 
	inline void clearList(std::list<TClass*>& refList)
	{
		typename std::list<TClass*>::iterator itor;
		for(itor = refList.begin();itor!=refList.end();itor++)
			delete *itor;
		refList.clear();
	}


	template<class TClass> 
	inline unsigned int getCapacityOfVector(std::vector<TClass*>& refList)
	{
		return refList.size();
	}


	template<class T> 
	inline void STLClearObject(T* obj)
	{
		T tmp;
		tmp.swap(*obj);
		obj->reserve(0);
	}


	template<class T>
	inline T* vector_as_array(std::vector<T>* v) 
	{
		return v->empty() ? NULL : &*v->begin();
	}

	template<class T>
	inline const T* vector_as_array(const std::vector<T>* v)
	{
		return v->empty() ? NULL : &*v->begin();
	}

	template <typename Collection, typename Key>
	bool ContainsKey(const Collection& collection, const Key& key) 
	{
		return collection.find(key) != collection.end();
	}

}

#endif	//_CSTLHELPER_H_