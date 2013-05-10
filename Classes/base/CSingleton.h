#ifndef _CSINGLETON_H_
#define _CSINGLETON_H_

template <typename T>
class CSingleton
{
private:
	CSingleton(const CSingleton<T>&){};
	CSingleton& operator=(const CSingleton<T>&){};

protected:
	virtual ~CSingleton(){_mInstance = 0;}
	CSingleton(){};
	static T* _mInstance;
public:
	static void pugerSingleton() { if (_mInstance) delete _mInstance;}
	static T* getInstance()
	{
		if(_mInstance == 0)
			_mInstance = new T();
		return _mInstance;
	}
};

template <typename T> 
T* CSingleton<T>::_mInstance = 0;

#endif	//_CSINGLETON_H_