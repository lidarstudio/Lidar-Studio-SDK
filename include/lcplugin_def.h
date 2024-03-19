////////////////////////////////////////////////////////////////////////////
//	File:		lcplugin_def.h
//	Author:		zhonghu
//	Description :	struct for sdk.
////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#pragma pack(push, 1)
struct LcIOPoint
{
	LcIOPoint():
		x(0),y(0),z(0),
		intensity(0), return_info(0), classification(0),
		scan_angle_rank(0), user_data(0), point_source_id(0), gps_time(0),
		r(0), g(0), b(0)
	{

	}

	double x, y, z;
	unsigned short intensity;
	unsigned char return_info; //return_number(bits 0,1,2); number of returns(bits 3,4,5); scan direction flag(bit 6);edge of flight line(bit 7)
	unsigned char classification;
	char scan_angle_rank;
	unsigned char user_data;
	unsigned short point_source_id;
	double gps_time;
	unsigned short r, g, b;
};
#pragma pack(pop)

struct LcDataInfo
{
	LcDataInfo():
		max_x(0), min_x(0), max_y(0), min_y(0), max_z(0), min_z(0),
		min_intensity(0), max_intensity(0), min_gps_time(0), max_gps_time(0),
		number_of_point_records(0), points_have_gps_time(false), points_have_rgb(false), m_wkt("")
	{
		memset(classification_statistics, 0, sizeof(unsigned long long) * 32);
		memset(number_of_points_by_return, 0, sizeof(unsigned long long) * 8);
	}
	double max_x;
	double min_x;
	double max_y;
	double min_y;
	double max_z;
	double min_z;

	unsigned short min_intensity;
	unsigned short max_intensity;

	double min_gps_time;
	double max_gps_time;

	unsigned long long number_of_point_records;
	unsigned long long classification_statistics[32];
	unsigned long long number_of_points_by_return[8];

	bool points_have_gps_time;
	bool points_have_rgb;

	std::string m_wkt;

};