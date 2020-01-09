/*
*******************************************************************************************************
*
* �ļ����� : gui_user.h
* ��    �� : V1.0
* ��    �� : OpenRabbit
* ˵    �� : GUI �� RTOS ��Ӳ���Ľ����ļ���ʹ��ʱע������ MCU �˺�ģ������
* 
*******************************************************************************************************
*/

#ifndef _GUI_USER_H
#define _GUI_USER_H

/* ͷ�ļ� -----------------------------------------------------------*/
#include "lvgl.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#if defined (__CC_ARM)
#include "bsp.h"
#include "task.h"
#endif

/* �궨�� -----------------------------------------------------------*/



/* ICON������Ϣ�ṹ�� */
typedef struct
{
	lv_img_dsc_t *icon_img;
	const char *text_en;
	const char *text_cn;
	const char *icon_fname;
	lv_obj_t * (*app)(void *user_data);

}icon_item;


/* ȫ�ֱ��� ----------------------------------------------------------*/

/* ����������ʽ���� */
extern lv_style_t style_cn_12;
extern lv_style_t style_cn_16;
extern lv_style_t style_cn_24;
extern lv_style_t style_cn_32;

/* ����ȫ�ֱ��� */
LV_FONT_DECLARE(gb2312_puhui12)
LV_FONT_DECLARE(gb2312_puhui16)
LV_FONT_DECLARE(gb2312_puhui24)
LV_FONT_DECLARE(gb2312_puhui32)

/* ͼƬȫ�ֱ��� */

/* ����ͼƬ�������� */
extern lv_img_dsc_t img_desktop;
extern lv_img_dsc_t icon_led;
extern lv_img_dsc_t icon_key;
extern lv_img_dsc_t icon_beep;
extern lv_img_dsc_t icon_album;
extern lv_img_dsc_t icon_wireless;
extern lv_img_dsc_t icon_wifi;
extern lv_img_dsc_t icon_wechat;
extern lv_img_dsc_t icon_weather;
extern lv_img_dsc_t icon_temp;
extern lv_img_dsc_t icon_set;
extern lv_img_dsc_t icon_note;
extern lv_img_dsc_t icon_mall;
extern lv_img_dsc_t icon_light;
extern lv_img_dsc_t icon_ir;
extern lv_img_dsc_t icon_folder;
extern lv_img_dsc_t icon_tiaotu;
extern lv_img_dsc_t icon_triaxial;


/* ΢��ͼƬ */
/* ΢�� */
extern lv_img_dsc_t wechat_aliyun;
extern lv_img_dsc_t wechat_armfly;
extern lv_img_dsc_t wechat_ebf;
extern lv_img_dsc_t wechat_esp;
extern lv_img_dsc_t wechat_huxiaozhi;
extern lv_img_dsc_t wechat_mi;
extern lv_img_dsc_t wechat_myir;
extern lv_img_dsc_t wechat_nuclei;
extern lv_img_dsc_t wechat_onenet;
extern lv_img_dsc_t wechat_quectel;
extern lv_img_dsc_t wechat_rtt;
extern lv_img_dsc_t wechat_st;
extern lv_img_dsc_t wechat_tiaotu;
extern lv_img_dsc_t wechat_asus;
extern lv_img_dsc_t wechat_21ic;
extern lv_img_dsc_t wechat_jingdong;
extern lv_img_dsc_t wechat_grouphelp;
extern lv_img_dsc_t wechat_shunfeng;
extern lv_img_dsc_t wechat_exmail;
extern lv_img_dsc_t wechat_lcsc;
/* ͨѶ¼ */
extern lv_img_dsc_t wechat_newfriend;
extern lv_img_dsc_t wechat_groupchat;
extern lv_img_dsc_t wechat_label;
extern lv_img_dsc_t wechat_public;
/* ���� */
extern lv_img_dsc_t wechat_moments;
extern lv_img_dsc_t wechat_scan;
extern lv_img_dsc_t wechat_shake;
extern lv_img_dsc_t wechat_top_stories;
extern lv_img_dsc_t wechat_search;
extern lv_img_dsc_t wechat_people_nearby;
extern lv_img_dsc_t wechat_games;
extern lv_img_dsc_t wechat_mini_programs;
/* �� */
extern lv_img_dsc_t wechat_id;
extern lv_img_dsc_t wechat_pay;
extern lv_img_dsc_t wechat_favorites;
extern lv_img_dsc_t wechat_my_posts;
extern lv_img_dsc_t wechat_cards_offers;
extern lv_img_dsc_t wechat_sticker_gallery;
extern lv_img_dsc_t wechat_settings;
/* ������ */
extern lv_img_dsc_t wechat_chats0;
extern lv_img_dsc_t wechat_contacts0;
extern lv_img_dsc_t wechat_discover0;
extern lv_img_dsc_t wechat_me0;
extern lv_img_dsc_t wechat_chats1;
extern lv_img_dsc_t wechat_contacts1;
extern lv_img_dsc_t wechat_discover1;
extern lv_img_dsc_t wechat_me1;

/* ������APP */
extern lv_img_dsc_t beep_open;

/* ����APP */
extern lv_img_dsc_t set_backlight;
extern lv_img_dsc_t set_calendar;
extern lv_img_dsc_t set_theme;
extern lv_img_dsc_t set_wallpaper;

/* ͼƬ���ݽṹ�� */
extern icon_item icon_wechat_page_chats[20];
extern icon_item icon_wechat_page_contacts[4];
extern icon_item icon_wechat_page_discover[8];
extern icon_item icon_wechat_page_me[7];
extern icon_item icon_wechat_header[8];
extern icon_item icon_beep_app[1];
extern icon_item icon_set_list[4];

/* �������� ----------------------------------------------------------*/


/* APP�������� */
lv_obj_t * lv_app_common_int(lv_obj_t *parent, const char *title);
extern lv_obj_t * app_led_create(void *user_data);
extern lv_obj_t * app_wechat_create(void *user_data);
extern lv_obj_t * app_beep_create(void *user_data);
extern lv_obj_t * app_wlan_create(void *user_data);
extern lv_obj_t * message_box(lv_obj_t *parent, const char *title);
extern lv_obj_t * app_set_create(void *user_data);

void lv_app_main(void);

uint32_t color_change(uint32_t color);

uint8_t lv_load_user_font_from_file(void);	//��������
lv_img_dsc_t *lv_load_image_from_file(const char *file_name);
uint8_t lv_load_img_bin_from_file(lv_img_dsc_t *image, const char *file_name);
void lv_font_cn_style_init(void);

/* Ӳ��������غ��� */
void gui_hal_led_toggle(void);
void gui_hal_backlight(uint8_t light);
void gui_hal_led_set_color(uint32_t color);
uint32_t gui_hal_led_get_current_color(void);
uint8_t gui_hal_adc_light_get_ratio(void);
uint8_t gui_hal_cpuusage_get(void);






#endif



/***************************** ���ÿƼ� www.whtiaotu.com (END OF FILE) *********************************/

