/*
*******************************************************************************************************
*
* 文件名称 : gui_user.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : GUI 与 RTOS 和硬件的交互文件，使用时注意区分 MCU 端和模拟器端
* 
*******************************************************************************************************
*/

/* 头文件 -----------------------------------------------------------*/
#include "gui_user.h"
#include <stdio.h>
#include <stdlib.h>

/* 定义中文字体样式 */
lv_style_t style_cn_12;
lv_style_t style_cn_16;
lv_style_t style_cn_24;
lv_style_t style_cn_32;


/**
  * @brief 初始化中文字体
  * @param None
  * @retval	0-加载成功 非0-加载失败
  */
void lv_font_cn_style_init(void)
{
	
	/* 复制style的属性 */
	lv_style_copy(&style_cn_12, &lv_style_pretty_color);
	lv_style_copy(&style_cn_16, &lv_style_pretty_color);
	lv_style_copy(&style_cn_24, &lv_style_pretty_color);
	lv_style_copy(&style_cn_32, &lv_style_pretty_color);
	
	style_cn_12.text.font = &gb2312_puhui12;
	style_cn_16.text.font = &gb2312_puhui16;	
	style_cn_24.text.font = &gb2312_puhui24;	
	style_cn_32.text.font = &gb2312_puhui32;	
	
}



/**
  * @brief 颜色转换函数
  * @param color-原颜色
  * @retval	EMWIN需要的颜色
  * @note 大小端转换
  */
uint32_t color_change(uint32_t color)
{
	uint32_t ret_color = 0;
	uint8_t r, g, b;
	b = color & 0X000000FF;
	g = (color & 0X0000FF00) >> 8;
	r = (color & 0X00FF0000) >> 16;


	ret_color |= b;
	ret_color <<= 8;

	ret_color |= g;
	ret_color <<= 8;

	ret_color |= r;

	return ret_color;
}




/**
  * @brief 从文件系统加载字体
  * @param None
  * @retval	0-加载成功 非0-加载失败
  */
uint8_t lv_load_user_font_from_file(void)
{
#if defined (__CC_ARM)
	uint8_t res;
	uint32_t br;
	uint8_t *pfont;
	pfont = (uint8_t *)LV_USER_FONT_ADDR;
	
	res = f_open(&SDFile,"0:/lvgl/gb2312_font.bin",FA_OPEN_EXISTING | FA_READ);
	if(res != FR_OK)
	{
		return 1;
	}
	
	if(SDFile.obj.objsize > LV_USER_FONT_MAX_SIZE)
	{
		/* 文件过大了 */
		f_close(&SDFile);
		return 2;
	}
	
	res = f_read(&SDFile,pfont,SDFile.obj.objsize,&br);
	if((res != FR_OK) || (br == 0))
	{
		f_close(&SDFile);
		return 3;
	}
	
	f_close(&SDFile);
	
	return 0;
#elif defined (_MSC_VER)
	return 0;
#endif
}



/**
  * @brief 从文件系统获取bmp图片
  * @param image-存储图片信息的指针
  * @param file_name-文件名
  * @retval	0-加载成功 非0-加载失败
  */
uint8_t lv_load_img_bin_from_file(lv_img_dsc_t *image, const char *file_name)
{
#if defined (__CC_ARM)
	uint8_t res;
	uint32_t br;
	uint8_t *pbuf;		//读取数据缓冲区
	uint8_t *pbmp;
	uint32_t i;
	uint32_t header;
	uint32_t file_size;
	
	if(image == NULL)
		return 1;
	if(file_name == NULL)
		return 1;
	
	res = f_open(&SDFile,(const TCHAR*)file_name,FA_OPEN_EXISTING | FA_READ);
	if(res != FR_OK)
	{
		return 1;
	}
	
	file_size = SDFile.obj.objsize;
	
	if(file_size > 1*1024*1024)
	{
		/* 文件过大了 */
		f_close(&SDFile);
		return 2;
	}
	
	/* 为图片申请内存,如果图片需要一直显示,内存不用释放 */
	pbuf = lv_mem_alloc(file_size);
	
	res = f_read(&SDFile,pbuf,file_size,&br);
	if((res != FR_OK) || (br == 0))
	{
		f_close(&SDFile);
		return 3;
	}
	

	/* 获取头 */
	header = (uint32_t)pbuf[3] << 24;
	header |= (uint32_t)pbuf[2] << 16;
	header |= (uint32_t)pbuf[1] << 8;
	header |= (uint32_t)pbuf[0];
	
	rt_kprintf("header:0X%X\r\n",header);
	rt_kprintf("width:%d height:%d\r\n", (uint16_t)(header >> 10), header >> 21);
	
	
	/* 获取图片数据流 */
	pbmp = (uint8_t *)pbuf+4;
	
	image->header.cf = pbuf[0];
	image->header.always_zero = 0;
	image->header.w = (uint16_t)(header >> 10);
	image->header.h = (uint16_t)(header >> 21);
	image->data_size = file_size - 4;		//去掉4字节的头,剩余的就是图片数据流长度
	image->data = pbmp;
	


	f_close(&SDFile);
	
	return 0;
#elif defined (_MSC_VER)


	uint8_t res;
	uint32_t br;
	uint8_t *pbuf;		//读取数据缓冲区
	uint8_t *pbmp;
	uint32_t i;
	uint32_t header;
	int file_size;
	uint8_t fname[256];
	
	if(image == NULL)
		return 1;
	if(file_name == NULL)
		return 1;

	sprintf(fname, "../../sd_add_file/%s", file_name+2);

	printf("fname:%s\n",fname);

	FILE *fp = NULL;

	fp = fopen(fname, "rb");
	if (fp == NULL)
	{
		printf("open file failed!\r\n");
		return 1;
	}

	//获取文件长度
	fseek(fp, 0, SEEK_END);		/* 定位到文件末 */
	file_size = ftell(fp);		/* 文件长度 */

	fseek(fp, 0, SEEK_SET);		/* 恢复到文件头 */

	if (file_size > 1 * 1024 * 1024)
	{
		/* 文件过大了 */
		fclose(fp);
		return 2;
	}


	pbuf = lv_mem_alloc(file_size);

	printf("file_size:%d\n",file_size);

	if (fread(pbuf, 1, file_size, fp) < file_size)
	{
		printf("read file failed!\r\n");
		fclose(fp);
		return 3;
	}

	printf("file:%x",pbuf[0]);

	/* 获取头 */
	header = (uint32_t)pbuf[3] << 24;
	header |= (uint32_t)pbuf[2] << 16;
	header |= (uint32_t)pbuf[1] << 8;
	header |= (uint32_t)pbuf[0];

	//printf("header:0X%X\r\n", header);
	//printf("width:%d height:%d\r\n", (uint16_t)(header >> 10), header >> 21);


	/* 获取图片数据流 */
	pbmp = (uint8_t *)pbuf + 4;

	image->header.cf = pbuf[0];
	image->header.always_zero = 0;
	image->header.w = (uint16_t)(header >> 10);
	image->header.h = (uint16_t)(header >> 21);
	image->data_size = file_size - 4;		//去掉4字节的头,剩余的就是图片数据流长度
	image->data = pbmp;


	fclose(fp);

	return 0;

#endif
	

	

	
}







/**
  * @brief LED变换
  * @param None
  * @retval	None
  */
void gui_hal_led_toggle(void)
{
#if defined (__CC_ARM)
	led_toggle();
#else
	
#endif
}




/**
  * @brief LED颜色设置
  * @param color-LED颜色,注意大小端
  * @retval	None
  */
void gui_hal_led_set_color(uint32_t color)
{
#if defined (__CC_ARM)
	led_color(color);
#else
	
#endif
}

/**
  * @brief LED获取颜色
  * @param None
  * @retval	None
  */
uint32_t gui_hal_led_get_current_color(void)
{
#if defined (__CC_ARM)
	return led_current_color();
#else
	return 0;
#endif

}


/**
  * @brief 背光调节
  * @param light-背光亮度
  * @retval	None
  */
void gui_hal_backlight(uint8_t light)
{
	
#if defined (__CC_ARM)
	if(light <= 5)
		light = 5;
	lcd_backlight(light);
#else
	
#endif
	
	
}


/**
  * @brief 获取光敏ADC的百分比值
  * @param light-背光亮度
  * @retval	None
  */
uint8_t gui_hal_adc_light_get_ratio(void)
{
	
#if defined (__CC_ARM)
	
	uint8_t res = 0;
	
	res = (float)adc_light_get()/4096*100;
	
	return res;
	
#else
	return rand() % 100;
#endif
	
	
}



/**
  * @brief 获取CPU利用率
  * @param light-背光亮度
  * @retval	None
  */
uint8_t gui_hal_cpuusage_get(void)
{
	
#if defined (__CC_ARM)
	
	static uint8_t cpu_major = 0;
	
	cpu_usage_get(&cpu_major,NULL);
	return cpu_major;
	
#else
	return rand() % 100;
#endif
	
	
}


/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/


