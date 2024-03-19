////////////////////////////////////////////////////////////////////////////
//	File:		SamplePluginInterface.cpp
//	Author:		zhonghu
//	Description : SamplePluginInterface inherit from SDKPluginInterface,then this plugin can be identified by platform
//				this sample give 3 examples:how to read data from lcdata¡¢how to edit lcdata and how to create a lcdata from scratch
////////////////////////////////////////////////////////////////////////////

#pragma once
#include <thread>
#include "SamplePluginInterface.h"
#include "i_plugin_sdk.h"
//Qt
#include <QWidget>
#include <QActionGroup>
#include <QMenu>
#include <QMessageBox>
#include <QDialog>
#include <QtCore/QTime>
#include <QtCore/QFileInfo>

SamplePluginInterface::SamplePluginInterface(QObject* parent /*= nullptr*/)
	: QObject(parent)
{

}


QMenu* SamplePluginInterface::getMenu()
{
	QMenu *menu = new QMenu(tr("Sample"));

	{
		QAction* action = new QAction(tr("Read Sample"), this);
		connect(action, SIGNAL(triggered()), this, SLOT(slotReadSample()));
		menu->addAction(action);
	}

	{
		QAction* action = new QAction(tr("Edit Sample"), this);
		connect(action, SIGNAL(triggered()), this, SLOT(slotEditSample()));
		menu->addAction(action);
	}

	{
		QAction* action = new QAction(tr("Write Sample"), this);
		connect(action, SIGNAL(triggered()), this, SLOT(slotWriteSample()));
		menu->addAction(action);
	}

	return menu;
}

void ReadSampleImp(std::vector<std::string> vecFiles, std::string strModuleName)
{
	lc_sdk::notify_start_task();
	float blocksize = 100.0;
	for (auto path : vecFiles)
	{
		lc_sdk::log_print("Start Processing " + path, strModuleName);
		unsigned long long point_number(0);
		double stats_min[3] = {INT_MAX, INT_MAX, INT_MAX};
		double stats_max[3] = { -INT_MAX, -INT_MAX, -INT_MAX };
		double stats_time[2] = {INT_MAX, -INT_MAX};

		LcDataInfo info;
		lc_sdk::get_file_info(path, info);
		
		double x_range = info.max_x - info.min_x;
		double y_range = info.max_y - info.min_y;

		int x_block = ceil(x_range / blocksize);
		int y_block = ceil(y_range / blocksize);
		int nblock = x_block * y_block;

		lc_sdk::progress_init();
		lc_sdk::read_start(path);
		for (int x = 0; x < x_block; x++)
		{
			for (int y = 0; y < y_block; y++)
			{
				int nProgress = x * y_block + y;
				std::vector<LcIOPoint> pts;
				lc_sdk::read_points(path, pts,
					info.min_x + x * blocksize, info.min_y + y * blocksize, info.min_x + (x + 1) * blocksize, info.min_y + (y + 1) * blocksize);

				lc_sdk::progress_set(100.0 * nProgress / nblock);
				if (pts.empty())
				{
					continue;
				}
				point_number += pts.size();
				for (auto& pt : pts)
				{
					if (pt.x < stats_min[0])
					{
						stats_min[0] = pt.x;
					}
					if (pt.y < stats_min[1])
					{
						stats_min[1] = pt.y;
					}
					if (pt.z < stats_min[2])
					{
						stats_min[2] = pt.z;
					}
					if (pt.x > stats_max[0])
					{
						stats_max[0] = pt.x;
					}
					if (pt.y > stats_max[1])
					{
						stats_max[1] = pt.y;
					}
					if (pt.z > stats_max[2])
					{
						stats_max[2] = pt.z;
					}

					if (pt.gps_time < stats_time[0])
					{
						stats_time[0] = pt.gps_time;
					}
					if (pt.gps_time > stats_time[1])
					{
						stats_time[1] = pt.gps_time;
					}
				}

				if (lc_sdk::progress_is_canceled())
				{
					lc_sdk::read_finish(path);
					lc_sdk::log_print("Cancelled successfully", strModuleName);
					lc_sdk::notify_finish_task();
					return;
				}
			}
		}
		lc_sdk::read_finish(path);
		lc_sdk::progress_finish();

		char text[128] = { 0 };
		sprintf(text, "min: %.3lf, %.3lf,%.3lf", stats_min[0], stats_min[1], stats_min[2]);
		lc_sdk::log_print(std::string(text), strModuleName);
		sprintf(text, "max: %.3lf, %.3lf,%.3lf", stats_max[0], stats_max[1], stats_max[2]);
		lc_sdk::log_print(std::string(text), strModuleName);

		sprintf(text, "points number: %d", point_number);
		lc_sdk::log_print(std::string(text), strModuleName);

		sprintf(text, "gpstime range: %.3lf---%.3lf", stats_time[0], stats_time[1]);
		lc_sdk::log_print(std::string(text), strModuleName);

		lc_sdk::log_print(path + " Process finished", strModuleName);

	}
	lc_sdk::notify_finish_task();
}

void SamplePluginInterface::slotReadSample()
{
	std::string strModuleName("ReadSample");
	std::vector<std::pair<std::string, bool>> objs = lc_sdk::get_point_cloud_objs();
	if (objs.empty())
	{
		lc_sdk::log_warning("No Point Cloud Data", strModuleName);
		return;
	}

	QDialog dlg(lc_sdk::get_layout_widget());
	if (dlg.exec() != QDialog::Accepted)
	{
		//return;
	}

	std::vector<std::string> vecFiles;
	{
		for (auto& e : objs) {
			if (e.second)
			{
				vecFiles.push_back(e.first);
			}
			
		}
	}

	std::thread t(&ReadSampleImp, vecFiles, strModuleName);
	t.detach();
}

void EditSampleImp(std::vector<std::string> vecFiles, std::string strModuleName)
{
	lc_sdk::notify_start_task();
	float blocksize = 100.0;
	for (auto path : vecFiles)
	{
		lc_sdk::log_print("Start Processing " + path, strModuleName);
		unsigned long long point_number(0);
		double stats_min[3] = { INT_MAX, INT_MAX, INT_MAX };
		double stats_max[3] = { -INT_MAX, -INT_MAX, -INT_MAX };
		double stats_time[2] = { INT_MAX, -INT_MAX };

		LcDataInfo info;
		lc_sdk::get_file_info(path, info);

		double x_range = info.max_x - info.min_x;
		double y_range = info.max_y - info.min_y;

		int x_block = ceil(x_range / blocksize);
		int y_block = ceil(y_range / blocksize);
		int nblock = x_block * y_block;

		unsigned int toClass(2);

		lc_sdk::progress_init();
		lc_sdk::edit_start(path);
		for (int x = 0; x < x_block; x++)
		{
			for (int y = 0; y < y_block; y++)
			{
				int nProgress = x * y_block + y;
				std::vector<LcIOPoint> pts;
				lc_sdk::edit_read(path, pts,
					info.min_x + x * blocksize, info.min_y + y * blocksize, info.min_x + (x + 1) * blocksize, info.min_y + (y + 1) * blocksize);

				lc_sdk::progress_set(100.0 * nProgress / nblock);
				if (pts.empty())
				{
					continue;
				}
				point_number += pts.size();
				for (auto& pt : pts)
				{
					pt.classification = toClass % 32;
					if (pt.x < stats_min[0])
					{
						stats_min[0] = pt.x;
					}
					if (pt.y < stats_min[1])
					{
						stats_min[1] = pt.y;
					}
					if (pt.z < stats_min[2])
					{
						stats_min[2] = pt.z;
					}
					if (pt.x > stats_max[0])
					{
						stats_max[0] = pt.x;
					}
					if (pt.y > stats_max[1])
					{
						stats_max[1] = pt.y;
					}
					if (pt.z > stats_max[2])
					{
						stats_max[2] = pt.z;
					}

					if (pt.gps_time < stats_time[0])
					{
						stats_time[0] = pt.gps_time;
					}
					if (pt.gps_time > stats_time[1])
					{
						stats_time[1] = pt.gps_time;
					}
				}

				lc_sdk::edit_save(path, pts,
					info.min_x + x * blocksize, info.min_y + y * blocksize, info.min_x + (x + 1) * blocksize, info.min_y + (y + 1) * blocksize);

				if (lc_sdk::progress_is_canceled())
				{
					lc_sdk::edit_finish(path);
					lc_sdk::log_print("Cancelled successfully", strModuleName);
					lc_sdk::notify_finish_task();
					return;
				}

				toClass++;
			}
		}
		lc_sdk::edit_finish(path);
		lc_sdk::progress_finish();

		char text[128] = { 0 };
		sprintf(text, "min: %.3lf, %.3lf,%.3lf", stats_min[0], stats_min[1], stats_min[2]);
		lc_sdk::log_print(std::string(text), strModuleName);
		sprintf(text, "max: %.3lf, %.3lf,%.3lf", stats_max[0], stats_max[1], stats_max[2]);
		lc_sdk::log_print(std::string(text), strModuleName);

		sprintf(text, "points number: %d", point_number);
		lc_sdk::log_print(std::string(text), strModuleName);

		sprintf(text, "gpstime range: %.3lf---%.3lf", stats_time[0], stats_time[1]);
		lc_sdk::log_print(std::string(text), strModuleName);

		lc_sdk::log_print(path + " Process finished", strModuleName);

	}
	lc_sdk::notify_finish_task();
}

void SamplePluginInterface::slotEditSample()
{
	std::string strModuleName("EditSample");
	std::vector<std::pair<std::string, bool>> objs = lc_sdk::get_point_cloud_objs();
	if (objs.empty())
	{
		lc_sdk::log_warning("No Point Cloud Data", strModuleName);
		return;
	}

	QDialog dlg(lc_sdk::get_layout_widget());
	if (dlg.exec() != QDialog::Accepted)
	{
		//return;
	}

	std::vector<std::string> vecFiles;
	{
		for (auto& e : objs) {
			if (e.second)
			{
				vecFiles.push_back(e.first);
			}

		}
	}

	std::thread t(&EditSampleImp, vecFiles, strModuleName);
	t.detach();
}

void WriteSampleImp(std::vector<std::string> vecFiles, std::string strModuleName)
{
	std::vector<unsigned short> g_colors[6] = {
		{ 255, 0, 0 },
		{ 0, 255, 0 },
		{ 0, 0, 255 },
		{ 255, 255, 0 },
		{ 0, 255, 255 },
		{ 255, 0, 255 },
	};

	lc_sdk::notify_start_task();
	QStringList results;
	float blocksize = 100.0;
	for (auto path : vecFiles)
	{
		lc_sdk::log_print("Start Processing " + path, strModuleName);
		LcDataInfo info;
		lc_sdk::get_file_info(path, info);

		std::string out_file = path.substr(0, path.rfind('.')) + "_out" + ".lcdata";
		lc_sdk::write_start(out_file, info.m_wkt);	

		double x_range = info.max_x - info.min_x;
		double y_range = info.max_y - info.min_y;

		int x_block = ceil(x_range / blocksize);
		int y_block = ceil(y_range / blocksize);
		int nblock = x_block * y_block;

		lc_sdk::progress_init();
		lc_sdk::read_start(path);
		for (int x = 0; x < x_block; x++)
		{
			for (int y = 0; y < y_block; y++)
			{
				int nProgress = x * y_block + y;
				std::vector<LcIOPoint> pts;
				lc_sdk::read_points(path, pts,
					info.min_x + x * blocksize, info.min_y + y * blocksize, info.min_x + (x + 1) * blocksize, info.min_y + (y + 1) * blocksize);

				lc_sdk::progress_set(80.0 * nProgress / nblock);
				if (pts.empty())
				{
					continue;
				}

				std::vector<unsigned short> cur_color = g_colors[nProgress % 6];
				for (auto& pt : pts)
				{
					pt.x += 10000;
					pt.y += 10000;
					pt.z += 1000;

					pt.r = cur_color[0];
					pt.g = cur_color[1];
					pt.b = cur_color[2];
				}
				lc_sdk::write_points(out_file, pts);

				if (lc_sdk::progress_is_canceled())
				{
					lc_sdk::read_finish(path);
					lc_sdk::write_finish(out_file);
					lc_sdk::log_print("Cancelled successfully", strModuleName);
					lc_sdk::notify_finish_task();
					return;
				}
			}
		}

		lc_sdk::progress_set(80);
		lc_sdk::read_finish(path);
		lc_sdk::write_finish(out_file);
		if (lc_sdk::progress_is_canceled()) {
			lc_sdk::log_print("Cancelled successfully", strModuleName);
			lc_sdk::notify_finish_task();
			return;
		}

		lc_sdk::progress_finish();
		lc_sdk::log_print(path + " Process finished", strModuleName);
		results.push_back(QString::fromLocal8Bit(out_file.c_str()));
	}
	lc_sdk::notify_finish_task();
	lc_sdk::process_result(results);
}

void SamplePluginInterface::slotWriteSample()
{
	std::string strModuleName("WriteSample");
	std::vector<std::pair<std::string, bool>> objs = lc_sdk::get_point_cloud_objs();
	if (objs.empty())
	{
		lc_sdk::log_warning("No Point Cloud Data", strModuleName);
		return;
	}

	QDialog dlg(lc_sdk::get_layout_widget());
	if (dlg.exec() != QDialog::Accepted)
	{
		//return;
	}

	std::vector<std::string> vecFiles;
	{
		for (auto& e : objs) {
			if (e.second)
			{
				vecFiles.push_back(e.first);
			}

		}
	}

	std::thread t(&WriteSampleImp, vecFiles, strModuleName);
	t.detach();
}

