# LittlevGL_Demo

## 介绍

基于野牛开发板的 lvgl 6.0 例程，包括控件例程和应用例程

视频介绍：https://www.bilibili.com/video/av78916927

<p><img src="http://www.whtiaotu.com/picture/LittlevGL_Demo/lvgl_desktop.png"><p>


## 编译器

模拟器使用 Visual Studio，单片机编译器使用 MDK

## 特点

上电从内存卡加载 bin 格式的字库到 SDRAM ，后续从 SDRAM 读取字库

上电从内存卡加载 bin 格式的图片到 SDRAM，可以显示各种大型图片

GUI 与硬件隔离，用户只需关心 gui_user.c 的兼容性问题，如果硬件不支持对应的接口，把对应的函数定义为空即可

## 使用方法

模拟器直接打开 VS 工程，默认只有一个 mainwindow 文件，需要使用哪个演示就将 Project 对应文件夹的 mainwindow 添加到工程即可

单片机演示直接打开 Project 对应文件夹的工程

## 使用注意事项

所有工程的运行请确保 BootLoader 正常，如何查看 BootLoader 是否正常，按住左键再开机，屏幕显示 boot 的信息就可确保 BootLoader 正常，如果丢失，请使用 link 烧写。

 VS 模拟器端的 UI 程序跟 MCU 端的程序兼容，两个平台运行无需修改任何代码，用户在添加的时候注意考虑二者兼容性。

需要显示中文的地方请使用 utf8 编码，VS 上面的中文支持可能不是太好，如果有错误，可以尝试使用偶数长度的中文

## 文件夹解释

**Drivers** STM32 的 HAL 库，里面包含一个编译好的 .lib ，例程中使用这个 lib

**FatFs** fatfs 库文件

**image** 原始 UI 图片文件存放区

**lv_drivers** MCU端程序的 lvgl 的驱动文件

**lv_examples** lvgl 官方的演示文件

**lvgl** lvgl 库文件

**lvgl_app** 用户 UI_APP 文件，里面的文件要考虑 VS 模拟器和 MCU 程序的兼容

**Project** 每个单独的例程的 UI 源码已经 MDK 工程文件夹

**rt-thread-4.0.0** RT-Thread 源码

**sd_add_file** 需要存放在内存卡根目录的文件,模拟器用的图片和字库也来自这个文件夹

**sim** VS 模拟器文件夹，由官方示例复制过来，里面包含了 lvgl 的库和驱动文件，只有 APP 从外部文件夹添加

**User** MCU 端程序的用户文件夹，包括 bsp

**Software** PC 小工具,包括字库转换软件和图片转换软件,论坛的网友制作的,非官方,官方只有网页版

##  下载源码

~~~c
git clone https://github.com/mzy2364/LittlevGL_Demo
~~~

## 支持我们

官网：www.whtiaotu.com

淘宝店：www.whtiaotu.com/mall_taobao.html

QQ交流群：909796874

