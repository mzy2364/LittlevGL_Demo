工程名:lvgl_font_cn
硬件:野牛开发板
作用:lvgl_font_cn
作者:OpenRabbit
修改记录:2019-11-29 第一次编写


中文字库存储在外部文件系统，上电加载到SDRAM，文字从SDRAM加载


SDRAM地址分配


说明                起始地址                大小
                    0xC0000000              32M
LTDC层0             0xC0000000              1M
LTDC层1             0xC0100000              1M
lvgl内存            0xC0200000              10M
字体内存            0xC0C00000              10M
未使用              0xC1600000              10M	