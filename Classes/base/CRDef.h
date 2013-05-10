#ifndef _CRDEF_H_
#define _CRDEF_H_

#include <string>

typedef enum
{
	SERVICE_ACTIVITY_GUID,
	SERVICE_NOTIFICATION_GUID,
	SERVICE_DATACLOUD_GUID,
	SERVICE_NET_GUID,
} R;

#define SERVICE_NOTIFICATION		"CNotificationService"
#define SERVICE_ACTIVITY				"CActivtyService"
#define SERVICE_DATACLOUD			"CDataCloudService"
#define SERVICE_NET						"CNetService"


#endif //_CRDEF_H_