/*
*******************************************************************************************************
*
* 文件名称 : mainwindow.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : GUI 主文件
* 
*******************************************************************************************************
*/

#include "gui_user.h"


#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  


lv_obj_t *label_btn1;
lv_obj_t *label_btn2;

lv_img_dsc_t tiaotu_logo80;

void lv_obj_btn_test(void);





/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_load_img_bin_from_file(&tiaotu_logo80,"0:/lvgl/tiaotu_logo80.bin");	/* 从文件加载 bin 格式的图片到图片变量 */
	
	lv_obj_btn_test();					/* 按钮控件测试 */
	
}




static void btn1_event_cb(lv_obj_t * obj, lv_event_t event)
{
	static uint8_t en=0;
	switch (event)
	{
	case LV_EVENT_RELEASED:
		lv_obj_set_drag(obj, (en=1-en));
		lv_label_set_text(label_btn1, (en ? "按钮可拖动":"按钮不可拖动" ));
		break;
	default:
		break;
	}
}


static void btn2_event_cb(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
		lv_label_set_text(label_btn2,"按钮按下");
		break;
	case LV_EVENT_RELEASED:
		lv_label_set_text(label_btn2, "按钮释放");
		break;
	case LV_EVENT_LONG_PRESSED:
		lv_label_set_text(label_btn2, "按钮长按");
		break;
	default:
		break;
	}
}

/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_btn_test(void)
{
	/* 新建个样式 */
	static lv_style_t style_desktop;

	lv_style_copy(&style_desktop,&lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);		/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);			/* 设置样式 */
		
	lv_obj_t *btn1 = lv_btn_create(scr, NULL);		/* 创建按钮 */
	label_btn1 = lv_label_create(btn1, NULL);		/* 创建label,作为按钮子对象 */
	lv_label_set_style(label_btn1, LV_LABEL_STYLE_MAIN, &style_cn_16);	/* 设置label的样式 */
	lv_label_set_text(label_btn1, "按钮可拖动");		/* 设置label文本 */
	lv_obj_set_width(btn1, 150);						/* 设置控件宽度 */
	lv_btn_set_ink_in_time(btn1, 500);					/* 按钮按下的动画 */
	lv_btn_set_ink_wait_time(btn1,100);
	lv_btn_set_ink_out_time(btn1,100);
	lv_obj_set_drag(btn1, true);						/* 允许拖动 */
	lv_obj_set_event_cb(btn1, btn1_event_cb);			/* 设置按钮事件回调函数 */

	lv_obj_t *btn2 = lv_btn_create(scr,NULL);			/* 创建按钮 */
	lv_obj_set_size(btn2, 100, 100);					/* 设置控件尺寸 */
	lv_btn_set_style(btn2, LV_BTN_STYLE_REL, &lv_style_transp);		/* 设置按钮释放时的样式,设置为透明 */
	lv_btn_set_style(btn2, LV_BTN_STYLE_PR, &lv_style_btn_ina);		/* 设置按钮按下时的样式,设置为透明带边框 */
	lv_obj_set_pos(btn2, 200, 0);						/* 设置控件绝对坐标 */
	lv_obj_t *image_btn2 = lv_img_create(btn2, NULL);	/* 创建一个图像控件 */
	lv_img_set_src(image_btn2, &tiaotu_logo80);			/* 设置图像的数据 */
	label_btn2 = lv_label_create(scr, NULL);			/* 创建label控件 */
	lv_label_set_style(label_btn2, LV_LABEL_STYLE_MAIN, &style_cn_16);	/* 设置label的样式 */
	lv_label_set_text(label_btn2, "图片按钮");			/* 设置文本 */
	lv_obj_align(label_btn2, btn2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);	/* 设置位置 */

	lv_obj_set_event_cb(btn2, btn2_event_cb);			/* 设置按钮事件回调函数 */

	
}






/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

