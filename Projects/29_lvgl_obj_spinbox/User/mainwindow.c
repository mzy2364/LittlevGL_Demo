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

lv_obj_t * spinbox;
lv_obj_t * label;

const char *btnm_map[] = {LV_SYMBOL_PLUS,LV_SYMBOL_PREV,"\n",LV_SYMBOL_MINUS,LV_SYMBOL_NEXT,""};

void lv_obj_spinbox_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_spinbox_test();				/* 控件测试 */
	
}


static void btnm_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED) 
	{
		static uint8_t spinbox_value[16];
		uint8_t btnm_value = lv_btnm_get_active_btn(obj);
		switch (btnm_value)
		{
		case 0:
			lv_spinbox_increment(spinbox);		/* 当前数字加1 */
			break;
		case 1:
			lv_spinbox_step_prev(spinbox);		/* 编辑的数字左移 */
			break;
		case 2:
			lv_spinbox_decrement(spinbox);		/* 当前数字减1 */
			break;
		case 3:
			lv_spinbox_step_next(spinbox);		/* 编辑的数字右移 */
			break;
		default:
			break;
		}
		sprintf(spinbox_value, "Value: %.2f\n", (float)lv_spinbox_get_value(spinbox) / 100.00f);
		lv_label_set_text(label, spinbox_value);
		lv_obj_align(label, spinbox, LV_ALIGN_OUT_TOP_MID, -10, 10);
		//printf("Value: %.2f\n", (float)lv_spinbox_get_value(spinbox)/100.00f);
	}

}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_spinbox_test(void)
{

	/* 新建个样式 */
	static lv_style_t style_desktop;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_WHITE;		/* 设置底色 */
	style_desktop.body.grad_color = LV_COLOR_WHITE;		/* 设置渐变色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;


	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */


	
	spinbox = lv_spinbox_create(scr, NULL);						/* 创建spinbox控件 */
	lv_spinbox_set_digit_format(spinbox, 5, 3);					/* 设置数字格式,小数点前3位,总位数5位 */
	lv_spinbox_step_prev(spinbox);								/* 编辑的位号左移动一位 */
	lv_spinbox_set_padding_left(spinbox, 0);
	lv_obj_set_width(spinbox, 100);								/* 设置控件宽度 */
	lv_spinbox_set_range(spinbox, -100, 100);					/* 设置范围,这里要注意上面动了小数点 */
	lv_obj_align(spinbox, NULL, LV_ALIGN_IN_TOP_MID, 0, 50);
	lv_spinbox_set_step(spinbox, 1);							/* 设置增量为1 */


	/* 创建btnm控件用于控制spinbox */
	lv_obj_t *btnm = lv_btnm_create(scr, NULL);
	lv_btnm_set_map(btnm, btnm_map);
	lv_obj_set_size(btnm, 100, 100);
	lv_obj_align(btnm, spinbox, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
	lv_obj_set_event_cb(btnm, btnm_event_cb);

	/* 创建label控件显示数字 */
	label = lv_label_create(scr, NULL);
	lv_label_set_text(label,"");
	lv_obj_align(label, spinbox, LV_ALIGN_OUT_TOP_MID, 0, 0);
}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

