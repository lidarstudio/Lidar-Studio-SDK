////////////////////////////////////////////////////////////////////////////
//	File:		i_plugin_sdk.h
//	Author:		zhonghu
//	Description :	api for sdk. if a api return false, there are errors
////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include "lcplugin_def.h"
#include <QStringList>
#include <QWidget>

#ifdef LCPLUGINSDK_DLL_EXPORTS
#define LCPLUGINSDK_DLL_API __declspec(dllexport)
#else
#define LCPLUGINSDK_DLL_API __declspec(dllimport)
#endif

namespace lc_sdk {
	/** Get sdk version information.*/
	LCPLUGINSDK_DLL_API bool get_version(unsigned int& version_major, unsigned int& version_minor, unsigned int& version_patch);

	/** Get layout widget, set as your widget's parent.*/
	LCPLUGINSDK_DLL_API QWidget* get_layout_widget();

	/** output standard log to platform.*/
	LCPLUGINSDK_DLL_API bool log_print(std::string message, std::string module);

	/** output warning log to platform.*/
	LCPLUGINSDK_DLL_API bool log_warning(std::string message, std::string module);

	/** output error log to platform.*/
	LCPLUGINSDK_DLL_API bool log_error(std::string message, std::string module);

	/** init progress bar in platform.*/
	LCPLUGINSDK_DLL_API bool progress_init();

	/** set progress bar value in platform.[0, 100]*/
	LCPLUGINSDK_DLL_API bool progress_set(int nProgress);

	/** finish progress bar in platform.*/
	LCPLUGINSDK_DLL_API bool progress_finish();

	/** get whether progress bar is canceled by platform GUI.*/
	LCPLUGINSDK_DLL_API bool progress_is_canceled();

	/** notify platform that task is start.*/
	LCPLUGINSDK_DLL_API void notify_start_task();

	/** notify platform that task is finish.*/
	LCPLUGINSDK_DLL_API void notify_finish_task();

	/** notify platform to load result files.*/
	LCPLUGINSDK_DLL_API bool process_result(QStringList files);

	/** get objects(point cloud¡¢raster...) in platform, return the path and visible info.*/
	LCPLUGINSDK_DLL_API std::vector<std::pair<std::string, bool>> get_objects();

	/** get point cloud objects in platform, return the path and visible info.*/
	LCPLUGINSDK_DLL_API std::vector<std::pair<std::string, bool>> get_point_cloud_objs();

	/** get raster objects in platform, return the path and visible information.*/
	LCPLUGINSDK_DLL_API std::vector<std::pair<std::string, bool>> get_raster_objs();

	/** get point cloud file information.*/
	LCPLUGINSDK_DLL_API bool get_file_info(std::string strPath, LcDataInfo& info);

	/** start to read point cloud file.*/
	LCPLUGINSDK_DLL_API bool read_start(std::string strPath);

	/** finish read point cloud file.*/
	LCPLUGINSDK_DLL_API bool read_finish(std::string strPath);

	/** read points from point cloud file in range [start_x, end_x) and [start_y, end_y).*/
	LCPLUGINSDK_DLL_API bool read_points(std::string strPath, std::vector<LcIOPoint>& vecPoints,
		double start_x, double start_y, double end_x, double end_y);
	
	/** start to edit point cloud file.*/
	LCPLUGINSDK_DLL_API bool edit_start(std::string strPath);

	/** read points from point cloud file in range [start_x, end_x) and [start_y, end_y).*/
	LCPLUGINSDK_DLL_API bool edit_read(std::string strPath, std::vector<LcIOPoint>& vecPoints,
		double start_x, double start_y, double end_x, double end_y);

	/** write points to point cloud file in range [start_x, end_x) and [start_y, end_y). Attention:vecPoints must from edit_read and only medify classification attribute*/
	LCPLUGINSDK_DLL_API bool edit_save(std::string strPath, std::vector<LcIOPoint>& vecPoints,
		double start_x, double start_y, double end_x, double end_y);

	/** finish edit point cloud file.*/
	LCPLUGINSDK_DLL_API bool edit_finish(std::string strPath);

	/** start to create point cloud file strPath and write points to it.*/
	LCPLUGINSDK_DLL_API bool write_start(std::string strPath, std::string wkt = "", std::vector<double> save_precision = { 0.001, 0.001, 0.001 });

	/** write points to point cloud file.*/
	LCPLUGINSDK_DLL_API bool write_points(std::string strPath, std::vector<LcIOPoint>& vecPoints);

	/** finish write points to point cloud file.*/
	LCPLUGINSDK_DLL_API bool write_finish(std::string strPath);
}