/*
*******************************************************************************************************
*
* �ļ����� : gui_user.c
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : GUI �� RTOS ��Ӳ���Ľ����ļ���ʹ��ʱע������ MCU �˺�ģ������
* 
*******************************************************************************************************
*/

/* ͷ�ļ� -----------------------------------------------------------*/
#include "gui_user.h"
#include <stdio.h>
#include <stdlib.h>

/* ��������������ʽ */
lv_style_t style_cn_12;
lv_style_t style_cn_16;
lv_style_t style_cn_24;
lv_style_t style_cn_32;


/**
  * @brief ��ʼ����������
  * @param None
  * @retval	0-���سɹ� ��0-����ʧ��
  */
void lv_font_cn_style_init(void)
{
	
	/* ����style������ */
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
  * @brief ��ɫת������
  * @param color-ԭ��ɫ
  * @retval	EMWIN��Ҫ����ɫ
  * @note ��С��ת��
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
  * @brief ���ļ�ϵͳ��������
  * @param None
  * @retval	0-���سɹ� ��0-����ʧ��
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
		/* �ļ������� */
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
  * @brief ���ļ�ϵͳ��ȡbmpͼƬ
  * @param image-�洢ͼƬ��Ϣ��ָ��
  * @param file_name-�ļ���
  * @retval	0-���سɹ� ��0-����ʧ��
  */
uint8_t lv_load_img_bin_from_file(lv_img_dsc_t *image, const char *file_name)
{
#if defined (__CC_ARM)
	uint8_t res;
	uint32_t br;
	uint8_t *pbuf;		//��ȡ���ݻ�����
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
		/* �ļ������� */
		f_close(&SDFile);
		return 2;
	}
	
	/* ΪͼƬ�����ڴ�,���ͼƬ��Ҫһֱ��ʾ,�ڴ治���ͷ� */
	pbuf = lv_mem_alloc(file_size);
	
	res = f_read(&SDFile,pbuf,file_size,&br);
	if((res != FR_OK) || (br == 0))
	{
		f_close(&SDFile);
		return 3;
	}
	

	/* ��ȡͷ */
	header = (uint32_t)pbuf[3] << 24;
	header |= (uint32_t)pbuf[2] << 16;
	header |= (uint32_t)pbuf[1] << 8;
	header |= (uint32_t)pbuf[0];
	
	rt_kprintf("header:0X%X\r\n",header);
	rt_kprintf("width:%d height:%d\r\n", (uint16_t)(header >> 10), header >> 21);
	
	
	/* ��ȡͼƬ������ */
	pbmp = (uint8_t *)pbuf+4;
	
	image->header.cf = pbuf[0];
	image->header.always_zero = 0;
	image->header.w = (uint16_t)(header >> 10);
	image->header.h = (uint16_t)(header >> 21);
	image->data_size = file_size - 4;		//ȥ��4�ֽڵ�ͷ,ʣ��ľ���ͼƬ����������
	image->data = pbmp;
	


	f_close(&SDFile);
	
	return 0;
#elif defined (_MSC_VER)


	uint8_t res;
	uint32_t br;
	uint8_t *pbuf;		//��ȡ���ݻ�����
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

	//��ȡ�ļ�����
	fseek(fp, 0, SEEK_END);		/* ��λ���ļ�ĩ */
	file_size = ftell(fp);		/* �ļ����� */

	fseek(fp, 0, SEEK_SET);		/* �ָ����ļ�ͷ */

	if (file_size > 1 * 1024 * 1024)
	{
		/* �ļ������� */
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

	/* ��ȡͷ */
	header = (uint32_t)pbuf[3] << 24;
	header |= (uint32_t)pbuf[2] << 16;
	header |= (uint32_t)pbuf[1] << 8;
	header |= (uint32_t)pbuf[0];

	//printf("header:0X%X\r\n", header);
	//printf("width:%d height:%d\r\n", (uint16_t)(header >> 10), header >> 21);


	/* ��ȡͼƬ������ */
	pbmp = (uint8_t *)pbuf + 4;

	image->header.cf = pbuf[0];
	image->header.always_zero = 0;
	image->header.w = (uint16_t)(header >> 10);
	image->header.h = (uint16_t)(header >> 21);
	image->data_size = file_size - 4;		//ȥ��4�ֽڵ�ͷ,ʣ��ľ���ͼƬ����������
	image->data = pbmp;


	fclose(fp);

	return 0;

#endif
	

	

	
}







/**
  * @brief LED�任
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
  * @brief LED��ɫ����
  * @param color-LED��ɫ,ע���С��
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
  * @brief LED��ȡ��ɫ
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
  * @brief �������
  * @param light-��������
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
  * @brief ��ȡ����ADC�İٷֱ�ֵ
  * @param light-��������
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
  * @brief ��ȡCPU������
  * @param light-��������
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


/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/


