////////////////////////////////////////////////////////////////////////////
//	File:		SamplePluginInterface.h
//	Author:		zhonghu
//	Description : SamplePluginInterface inherit from SDKPluginInterface,then this plugin can be identified by platform
//				this sample give 3 examples:how to read data from lcdata¡¢how to edit lcdata and how to create a lcdata from scratch
////////////////////////////////////////////////////////////////////////////

#pragma once
#include <QObject>
#include "SDKPluginInterface.h"

class SamplePluginInterface : public QObject, public SDKPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(SDKPluginInterface)
	Q_PLUGIN_METADATA(IID "lidarstudio.plugin.sample")

public:
	SamplePluginInterface(QObject* parent = nullptr);

	virtual ~SamplePluginInterface() {};

	virtual QMenu* getMenu();

protected slots:

	void slotReadSample();

	void slotEditSample();

	void slotWriteSample();
};