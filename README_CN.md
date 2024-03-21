
[English Version](README.md)

[知乎](https://zhuanlan.zhihu.com/p/504083964)

[视频教程](https://www.bilibili.com/video/BV1bC411h7rL/?spm_id_from=333.337.search-card.all.click&vd_source=0f3856461d10e6a4d57fd99cf05a7fca)

# 简介
Lidar Studio SDK 是为Lidar Studio点云处理与分析软件[https://github.com/lidarstudio/Lidar-Studio](https://github.com/lidarstudio/Lidar-Studio)设计的软件开发套件。它基于 C/C++ 语言开发，并为用户提供了易用的 C 语言风格的接口。通过 Lidar Studio SDK，用户可以快速地基于Lidar Studio平台进行二次开发。

## 开发环境
* Windows 7/10/11, Visual Studio 2015 Update3/2017/2019/2022
* C++11 编译器
* Lidar Studio v1.7及更高版本
* [Qt5.13.0](https://download.qt.io/archive/qt/5.13/5.13.0/)


# 使用
## 安装Lidar Studio
软件、用户手册、教程视频下载地址（百度网盘）
```
	链接：https://pan.baidu.com/s/1GgvWMf8kNGyYG7l12w9Wtg 
	提取码：69uh
```

## 配置CMake
设置QT_ROOT与SDK_ROOT，参考

    QT_ROOT  D:\Qt\Qt5.13.0\5.13.0\msvc2015_64
	SDK_ROOT D:\Lidar-Studio-SDK

## 编译
选择Release，编译结果输出至bin文件夹，作为平台的插件

## 拷贝插件
拷贝编译好的插件至目录`{Lidar Studio install root}/plugins/custom_plugins`

## 拷贝插件使用的三方库
拷贝插件依赖的三方库至目录`{Lidar Studio install root}/plugins/custom_plugins/custom_thirdparty`

# 关于我们
武汉空间智测科技有限公司：创始人拥有武大遥感、北航教育背景，专注于移动测量系统的软硬件研发工作，研发成果包括各种载体的移动测量系统（机载、车载等）以及专业的点云处理软件Lidar Studio，我们旨在推动点云行业高质量发展。





