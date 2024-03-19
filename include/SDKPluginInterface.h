////////////////////////////////////////////////////////////////////////////
//	File:		SDKPluginInterface.h
//	Author:		zhonghu
//	Description :	SDK PluginInterface.
////////////////////////////////////////////////////////////////////////////

#pragma once
//Qt
#include <QObject>
#include <QMenu>
#include "i_plugin_sdk.h"

class LCPLUGINSDK_DLL_API SDKPluginInterface
{

public:

	virtual ~SDKPluginInterface() = default;

	bool getSDKVersion(unsigned int& version_major, unsigned int& version_minor, unsigned int& version_patch);

	QString getKey();

	virtual QMenu* getMenu() = 0;

};

Q_DECLARE_METATYPE(const SDKPluginInterface *);

Q_DECLARE_INTERFACE(SDKPluginInterface, "Lidar Studio SDKPluginInterface")

