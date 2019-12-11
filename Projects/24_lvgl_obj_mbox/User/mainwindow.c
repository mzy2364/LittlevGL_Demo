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

lv_img_dsc_t file_img;
lv_img_dsc_t directory_img;
lv_img_dsc_t close_img;
lv_img_dsc_t edit_img;
lv_img_dsc_t save_img;


lv_obj_t *mbox,*info;

static const char * btns2[] = { "Ok", "Cancel", "" };

void lv_obj_mbox_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */

	lv_load_img_bin_from_file(&file_img,"0:/lvgl/file_img.bin");
	lv_load_img_bin_from_file(&directory_img, "0:/lvgl/directory_img.bin");
	lv_load_img_bin_from_file(&close_img, "0:/lvgl/close_img.bin");
	lv_load_img_bin_from_file(&edit_img, "0:/lvgl/edit_img.bin");
	lv_load_img_bin_from_file(&save_img, "0:/lvgl/save_img.bin");
	
	lv_obj_mbox_test();					/* 消息提示框控件测试 */
	
}

static void mbox_event_cb(lv_obj_t *obj, lv_event_t event)
{
	if (event == LV_EVENT_DELETE && obj == mbox) {
		/* 删除父窗口,去除模态化效果 */
		lv_obj_del_async(lv_obj_get_parent(mbox));
		mbox = NULL; /* happens before object is actually deleted! */

	}
	else if (event == LV_EVENT_VALUE_CHANGED) {
		/* 自动关闭 */
		lv_mbox_start_auto_close(mbox, 0);
		/* 获取用户按下的按钮的文本 */
		lv_label_set_text(info, lv_mbox_get_active_btn_text(mbox));

	}


}

static void btn1_event_cb(lv_obj_t *obj, lv_event_t event)
{
	static lv_style_t style_mbox;
	static lv_style_t style_modal;

	
	if (event == LV_EVENT_RELEASED)
	{

		/* 创建一个窗口用于模态化效果 */
		/* Create a full-screen background */
		lv_style_copy(&style_modal, &lv_style_plain_color);
		/* Set the background's style */
		style_modal.body.main_color = style_modal.body.grad_color = LV_COLOR_BLACK;
		style_modal.body.opa = LV_OPA_50;
		/* Create a base object for the modal background */
		lv_obj_t *obj = lv_obj_create(lv_scr_act(), NULL);
		lv_obj_set_style(obj, &style_modal);
		lv_obj_set_pos(obj, 0, 0);
		lv_obj_set_size(obj, LV_HOR_RES, LV_VER_RES);
		lv_obj_set_opa_scale_enable(obj, true); /* Enable opacity scaling for the animation */

		/* 创建消息提示框 */
		mbox = lv_mbox_create(obj, NULL);
		lv_style_copy(&style_mbox, lv_mbox_get_style(mbox, LV_MBOX_STYLE_BG));
		style_mbox.text.font = style_cn_16.text.font;
		lv_mbox_set_style(mbox, LV_MBOX_STYLE_BG, &style_mbox);
		lv_mbox_set_text(mbox, "消息提示框，想好了吗 ");
		lv_mbox_add_btns(mbox, btns2);
		lv_obj_align(mbox,obj,LV_ALIGN_IN_TOP_MID,0,150);
		lv_obj_set_event_cb(mbox,mbox_event_cb);

	}
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_mbox_test(void)
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


	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	lv_obj_set_style(scr, &style_desktop);					/* 设置样式 */

	/* 创建一个按钮,设置其事件为打开对话框 */
	lv_obj_t *btn1 = lv_btn_create(scr,NULL);
	lv_obj_set_width(btn1, 230);
	lv_btn_set_layout(btn1, LV_LAYOUT_ROW_M);
	lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

	/* 给按钮添加图标 */
	lv_obj_t *img_btn1 = lv_img_create(btn1, NULL);
	lv_img_set_src(img_btn1, &directory_img);

	/* 给按钮添加文字 */
	lv_obj_t *label_btn1 = lv_label_create(btn1,NULL);
	lv_label_set_style(label_btn1,LV_LABEL_STYLE_MAIN,&style_cn_16);
	lv_label_set_text(label_btn1,"打开一个消息框 ");

	/* 设置按钮的事件回调函数 */
	lv_obj_set_event_cb(btn1, btn1_event_cb);
	
	/* 创建用于展示对话框选择的文本 */
	info = lv_label_create(scr,NULL);
	lv_label_set_style(info,LV_LABEL_STYLE_MAIN,&style_cn_16);
	lv_label_set_text(info,"按下按钮打开一个消息提示框 ");
	lv_obj_align(info,btn1,LV_ALIGN_OUT_BOTTOM_MID,0,10);


}








/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

