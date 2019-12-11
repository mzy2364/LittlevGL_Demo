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



lv_obj_t *label_arc1;
lv_obj_t *label_arc2;


void lv_obj_arc_test(void);



/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();		/* 加载中文字体 */
	
	lv_font_cn_style_init();			/* 初始化中文字体 */
	
	
	lv_obj_arc_test();					/* 图片测试 */
	
}


/**
  * @brief lvgl任务函数
  * @param t-任务参数
  * @retval	None
  */
static void arc1_loader(lv_task_t * t)
{
    static int16_t a = 0;
	uint8_t buf[4];

    a+=5;
    if(a >= 359) a = 359;

    if(a < 180)
	{
		lv_arc_set_angles(t->user_data, 180-a ,180);
		sprintf((char*)buf,"%d",(lv_arc_get_angle_end(t->user_data)-lv_arc_get_angle_start(t->user_data)));
	}
    else
	{		
		lv_arc_set_angles(t->user_data, 540-a ,180);
		sprintf((char*)buf,"%d",(lv_arc_get_angle_end(t->user_data)+(360-lv_arc_get_angle_start(t->user_data))));
	}

    if(a == 359) {
        a = 0;
    }


	lv_label_set_text(label_arc1,(const char*)buf);

}

/**
  * @brief lvgl任务函数
  * @param t-任务参数
  * @retval	None
  */
static void arc2_loader(lv_task_t * t)
{
    static int16_t a = 0;
	uint8_t buf[5];

    a+=5;
    if(a >= 359) a = 359;

    if(a < 180)
	{
		lv_arc_set_angles(t->user_data, 180-a ,180);
		sprintf((char*)buf,"%d%%",(int)((float)(lv_arc_get_angle_end(t->user_data)-lv_arc_get_angle_start(t->user_data))/360*100));
	}
    else
	{		
		lv_arc_set_angles(t->user_data, 540-a ,180);
		sprintf((char*)buf,"%d%%",(int)((float)(lv_arc_get_angle_end(t->user_data)+(360-lv_arc_get_angle_start(t->user_data)))/360*100));
	}

    if(a == 359) {
        a = 0;
    }


	lv_label_set_text(label_arc2,(const char*)buf);
}


/**
  * @brief 控件测试函数
  * @param None
  * @retval	None
  */
void lv_obj_arc_test(void)
{
	
	/* 新建样式 */
	static lv_style_t style1;
	static lv_style_t style2;

	lv_obj_t *scr = lv_disp_get_scr_act(NULL);				/* 获取当前屏幕 */
	
	/* 复制样式并设置新的参数 */
	lv_style_copy(&style1,&lv_style_scr);
	style1.line.color = LV_COLOR_BLUE;
	style1.line.width = 10;
	
	lv_style_copy(&style2,&lv_style_scr);
	style2.line.color = LV_COLOR_RED;
	style2.line.width = 20;
	

	lv_obj_t *arc1 = lv_arc_create(scr,NULL);			/* 创建 arc 控件 */
	lv_arc_set_angles(arc1,0,90);						/* 设置起始角度和终止角度 */
	lv_arc_set_style(arc1,LV_ARC_STYLE_MAIN,&style1);	/* 设置样式 */
	lv_obj_align(arc1,NULL,LV_ALIGN_IN_TOP_MID,0,0);	/* 设置位置 */
	
	label_arc1 = lv_label_create(arc1,NULL);			/* 创建 label 控件 */
	lv_obj_align(label_arc1,arc1,LV_ALIGN_CENTER,0,0);	/* 设置 label 位置 */
	lv_label_set_text(label_arc1,"0");					/* 设置文字 */
	
	lv_obj_t *arc2 = lv_arc_create(scr,NULL);			/* 创建 arc 控件 */
	lv_arc_set_angles(arc2,0,180);						/* 设置起始角度和终止角度 */
	lv_arc_set_style(arc2,LV_ARC_STYLE_MAIN,&style2);	/* 设置样式 */
	lv_obj_set_size(arc2,200,200);						/* 设置控件尺寸 */
	lv_obj_align(arc2,arc1,LV_ALIGN_OUT_BOTTOM_MID,0,50);/* 设置位置 */

	label_arc2 = lv_label_create(arc2,NULL);			/* 创建 label 控件 */
	lv_obj_align(label_arc2,arc2,LV_ALIGN_CENTER,0,0);	/* 设置 label 位置 */
	lv_label_set_text(label_arc2,"0");					/* 设置文字 */
	
	/* 创建两个 task 用于重设 arc 控件的起始角度和终止角度 */
	lv_task_create(arc1_loader, 100, LV_TASK_PRIO_LOWEST, arc1);
	lv_task_create(arc2_loader, 200, LV_TASK_PRIO_LOWEST, arc2);
	
}







/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/

