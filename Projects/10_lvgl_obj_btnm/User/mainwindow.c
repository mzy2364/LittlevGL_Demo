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

lv_obj_t *label_btnm1;
uint8_t label_buf[100];



/* 定义btnm控件的map,注意使用全局定义或者static */
static const uint8_t *btnm_map[] = { "1", "2", "3", "\n",
									"4", "5", "6", "\n",
									"7", "8", "9", "\n",
									"*", "0", "#", "\n",
									"OK", "Space", "Cancel", "" };

void lv_obj_btnm_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_btnm_test();					/* 按钮阵列控件测试 */
	
}




static void btnm1_event_cb(lv_obj_t * obj, lv_event_t event)
{
	static uint16_t count = 0;
	switch (event)
	{
	case LV_EVENT_RELEASED:
		if (lv_btnm_get_active_btn(obj) == 14)
		{
			memset(label_buf,0,sizeof(label_buf));
		}
		else
		{
			if (strlen(label_buf) <= (sizeof(label_buf)-10))
			{
				strcat(label_buf, lv_btnm_get_active_btn_text(obj));
			}
		}
		
		lv_label_set_text(label_btnm1,label_buf);
		//printf("%d\n", lv_btnm_get_active_btn(obj));
		//printf("%s\n",lv_btnm_get_active_btn_text(obj));
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
void lv_obj_btnm_test(void)
{

	/* 新建个样式 */
	static lv_style_t style_desktop;

	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);		/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);			/* 设置样式 */

	lv_obj_t *btnm1 = lv_btnm_create(scr, NULL);		/* 创建btnm控件 */
	lv_btnm_set_map(btnm1, btnm_map);					/* 设置btnm控件的map,控件会根据map设置按钮的分布 */
	lv_obj_set_size(btnm1, LV_HOR_RES, LV_VER_RES / 2);	/* 设置控件的尺寸 */
	lv_obj_align(btnm1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);	/* 设置控件位置 */

	lv_obj_set_event_cb(btnm1, btnm1_event_cb);			/* 设置控件事件回调函数 */

	label_btnm1 = lv_label_create(scr, NULL);			/* 创建label控件 */
	lv_label_set_text(label_btnm1, label_buf);			/* 设置label文本 */
	lv_label_set_long_mode(label_btnm1, LV_LABEL_LONG_BREAK);	/* 设置长文本模式为自动换行 */
	lv_obj_set_width(label_btnm1, LV_HOR_RES);			/* 设置控件宽度 */
	lv_obj_set_style(label_btnm1, &style_cn_32);		/* 设置中文字体的样式 */
	lv_obj_align(label_btnm1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);	/* 设置位置 */

}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

