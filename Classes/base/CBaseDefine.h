#ifndef _CBASEDEFINE_H_
#define _CBASEDEFINE_H_

typedef enum
{
	COBRA_OBJECT,
	COBRA_EVENT,
	COBRA_ACTIVITY,
	COBRA_SERVICES,
	COBRA_OBSERVER,
	COBRA_RESPONSE,
	COBRA_INTENT,
	COBRA_BUNDLE,
	COBRA_COMMAND,
	COBRA_LOADER,
	COBRA_HTTP_REQUEST,
	COBRA_HTTP_RESPONSE,
	COBRA_CONTROLLER,
} cCobraObjType;


typedef enum
{
	kLanguageEnglish = 0,
	kLanguageChinese,
	kLanguageFrench,
	kLanguageItalian,
	kLanguageGerman,
	kLanguageSpanish,
	kLanguageRussian,
	kLanguageKorean,
	kLanguageJapanese,
	kLanguageHungarian,
	kLanguagePortuguese,
	kLanguageArabic
} cLanguageType;


typedef enum 
{
	kTargetWindows,
	kTargetLinux,
	kTargetMacOS,
	kTargetAndroid,
	kTargetIphone,
	kTargetIpad,
	kTargetBlackBerry,
	kTargetNaCl,
} cTargetPlatform;


typedef enum
{
	SERVICE_ACTIVITY,
	SERVICE_NOTIFICATION,
	SERVICE_NET,
	SERVICE_GUI,
	SERVICE_DATACLOUD,
	SERVICE_HTTP,
	SERVICE_EVENT,
} cServiceType;


typedef enum
{
	ERROR_FAIL = -1,
	ERROR_UNKNOW,
	ERROR_OK,
}cError;


#endif //_CBASEDEFINE_H_