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

static const uint8_t *btnm_map[] = { "LV_LAYOUT_OFF", "LV_LAYOUT_CENTER", "\n",
" LV_LAYOUT_COL_L", "LV_LAYOUT_COL_M", "LV_LAYOUT_COL_R", "\n",
"LV_LAYOUT_ROW_T", "LV_LAYOUT_ROW_M", " LV_LAYOUT_ROW_B", "\n",
"LV_LAYOUT_PRETTY", " LV_LAYOUT_GRID", "" };

void lv_obj_cont_test(void);

static lv_obj_t *cont2;


/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	lv_obj_cont_test();					/* 容器控件测试 */
	
}

static void btn_event_cb(lv_obj_t *obj, lv_event_t event)
{
	if (event == LV_EVENT_RELEASED)
	{
		/* 按一次按钮往容器添加一个label */
		lv_obj_t *label1 = lv_label_create(lv_obj_get_user_data(obj), NULL);
		lv_label_set_text(label1, "new text");
	}
}


static void btnm_event_cb(lv_obj_t *obj, lv_event_t event)
{
	if (event == LV_EVENT_VALUE_CHANGED)
	{
		//lv_btnm_get_active_btn();
		lv_cont_set_layout(cont2, lv_btnm_get_active_btn(obj));
		lv_btnm_clear_btn_ctrl_all(obj, LV_BTNM_CTRL_TGL_STATE);
		lv_btnm_set_btn_ctrl(obj, lv_btnm_get_active_btn(obj), LV_BTNM_CTRL_TGL_STATE);
	}
}





/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_cont_test(void)
{


	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_cont;


	lv_style_copy(&style_desktop, &lv_style_scr);
	style_desktop.body.main_color = LV_COLOR_BLUE;		/* 设置底色 */

	/* 设置样式的字体颜色 */
	style_cn_12.text.color = LV_COLOR_WHITE;
	style_cn_16.text.color = LV_COLOR_WHITE;
	style_cn_24.text.color = LV_COLOR_WHITE;
	style_cn_32.text.color = LV_COLOR_WHITE;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	lv_obj_t *cont1 = lv_cont_create(scr, NULL);				/* 创建cont控件 */
	lv_cont_set_fit(cont1, LV_FIT_TIGHT);						/* 设置自动调整模式 */
	lv_obj_align(cont1, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);		/* 设置位置 */
	lv_cont_set_layout(cont1, LV_LAYOUT_COL_M);					/* 设置容器布局为居中对齐 */

	lv_obj_t *label1 = lv_label_create(cont1, NULL);			/* 创建位于cont上的label */
	lv_label_set_text(label1, "text1");							/* 设置文本 */

	lv_obj_t *label2 = lv_label_create(cont1, NULL);			/* 创建位于cont上的label */
	lv_label_set_text(label2, "It is a long text");				/* 设置文本 */

	lv_obj_t *btn = lv_btn_create(cont1, NULL);					/* 创建位于cont上的btn */
	lv_obj_t *label_btn = lv_label_create(btn, NULL);			/* 创建btn上面的label */
	lv_label_set_text(label_btn, "add text");					/* 设置文字 */
	lv_obj_set_event_cb(btn, btn_event_cb);						/* 设置对象的事件回调函数 */
	lv_obj_set_user_data(btn, cont1);							/* 设置对象的用户数据 */



	cont2 = lv_cont_create(scr, NULL);				/* 创建cont控件 */

	/* 复制样式 */
	lv_style_copy(&style_cont, lv_cont_get_style(cont2, LV_CONT_STYLE_MAIN));
	/* 修改样式属性 */
	style_cont.body.padding.top = 10;
	style_cont.body.padding.bottom = style_cont.body.padding.top;
	style_cont.body.padding.left = style_cont.body.padding.top;
	style_cont.body.padding.right = style_cont.body.padding.top;
	style_cont.body.padding.inner = style_cont.body.padding.top;
	/* 设置样式 */
	lv_cont_set_style(cont2, LV_CONT_STYLE_MAIN, &style_cont);

	lv_obj_set_size(cont2, lv_obj_get_width(lv_scr_act()), 400);	/* 设置控件尺寸 */
	lv_cont_set_fit(cont2, LV_FIT_NONE);						/* 设置自动调整模式 */
	lv_obj_align(cont2, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);		/* 设置位置 */
	lv_cont_set_layout(cont2, LV_LAYOUT_OFF);					/* 设置容器布局 */

	uint8_t buf[8] = {0};
	for (size_t i = 0; i < 6; i++)
	{
		lv_obj_t *btn2 = lv_btn_create(cont2, NULL);					/* 创建位于cont上的btn */
		lv_obj_t *label_btn2 = lv_label_create(btn2, NULL);			/* 创建btn上面的label */
		sprintf(buf,"btn%d",i);
		lv_label_set_text(label_btn2, buf);					/* 设置文字 */
	}


	/* 创建一个btnm控制cont的布局 */
	lv_obj_t *btnm = lv_btnm_create(scr,NULL);
	lv_btnm_set_map(btnm,btnm_map);
	lv_obj_set_width(btnm,lv_obj_get_width(scr));
	lv_obj_align(btnm,NULL,LV_ALIGN_IN_BOTTOM_MID,0,0);
	lv_obj_set_event_cb(btnm, btnm_event_cb);


}





/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

