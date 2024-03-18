
[中文版本](README_CN.md)

[知乎](https://zhuanlan.zhihu.com/p/504083964)

[Video tutorial](https://www.bilibili.com/video/BV1bC411h7rL/?spm_id_from=333.337.search-card.all.click&vd_source=0f3856461d10e6a4d57fd99cf05a7fca)

# Intro
Lidar Studio SDK is the software development kit designed for Lidar Studio point cloud processing and analysis software。It is developed based on C/C++，and provides easy-to-use C style API. With Lidar Studio SDK, users can quickly carry out secondary development based on Lidar Studio platform.

## Prerequisites
* Windows 7/10/11, Visual Studio 2015 Update3/2017/2019/2022
* C++11 compiler
* [Qt5.13.0](https://download.qt.io/archive/qt/5.13/5.13.0/)


# How to use
## Config CMake
config QT_ROOT与SDK_ROOT，refer to

    QT_ROOT  D:\Qt\Qt5.13.0\5.13.0\msvc2015_64
	SDK_ROOT D:\Lidar-Studio-SDK

## Compile
The compilation result is output to the bin folder as a plugin of the platform.

## Copy plugin
Copy the compiled plugin to the directory.`{Lidar Studio install root}/plugins/custom_plugins`

## Copy the third-party library used by the plugin
Copy the third-party libraries that plugins depend on to the directory.`{Lidar Studio install root}/plugins/custom_plugins/custom_thirdparty`

# About us
武汉空间智测科技有限公司: The founder has education background in Wuhan university remote sensing and Beihang University,focus on the research and development of the hardware and software of mobile measurement systems. The research and development results include mobile measurement systems of various carriers (airborne, vehicular, etc.) and professional point cloud processing software Lidar Studio. We aim to promote the high-quality development of the point cloud industry.






