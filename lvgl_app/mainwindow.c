#include "gui_user.h"


/* 函数定义 */
static void btn_event_cb(lv_obj_t * btn, lv_event_t event);
static void slider_event_handler(lv_obj_t * slider, lv_event_t event);


/* 全局变量 */
lv_obj_t *bar1;


LV_IMG_DECLARE(wlan);

LV_IMG_DECLARE(tiaotu48);

static lv_img_dsc_t bg1_bin;
static lv_img_dsc_t bg0_bin;

static lv_obj_t *image2;


/**
  * @brief lvglC格式图片显示
  * @param None
  * @retval	None
  */
void lv_image_test(void)
{
	static lv_style_t style1;
	lv_style_copy(&style1, &lv_style_plain);
	style1.text.font = &gb2312_puhui32;
	style1.text.color = LV_COLOR_WHITE;
	
	lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/

	
	
	lv_load_bmp_from_file(&bg1_bin,"0:/lvgl/bg1_24.bin");
	lv_load_bmp_from_file(&bg0_bin,"0:/lvgl/bg0.bin");
	image2 = lv_img_create(scr,NULL);
	lv_img_set_src(image2,&bg1_bin);
	lv_obj_set_pos(image2,0,0);
	
    /*************************
     * IMAGE FROM SOURCE CODE
     *************************/

//    lv_obj_t * img_var = lv_img_create(scr, NULL); /*Crate an image object*/
//    lv_img_set_src(img_var, &wlan);  /*Set the created file as image (a red flower)*/
//    lv_obj_set_pos(img_var, 10, 10);      /*Set the positions*/
//    lv_obj_set_drag(img_var, true);
	
	
	
	lv_obj_t * img_btn = lv_imgbtn_create(scr,NULL);
	lv_imgbtn_set_src(img_btn,LV_BTN_STATE_REL,&wlan);
	lv_obj_set_pos(img_btn,50,50);
	
	
	lv_obj_t *label_wlan = lv_label_create(scr,NULL);
	lv_label_set_style(label_wlan, LV_LABEL_STYLE_MAIN, &style1);
	lv_label_set_text(label_wlan, "无线");
	lv_obj_align(label_wlan,img_btn,LV_ALIGN_OUT_BOTTOM_MID,0,10);
	
	lv_obj_t *btn1 = lv_btn_create(scr,NULL);
	lv_obj_set_size(btn1,80,80);
	lv_btn_set_style(btn1,LV_BTN_STYLE_REL,&lv_style_transp);
	lv_btn_set_style(btn1,LV_BTN_STYLE_PR,&lv_style_btn_ina);
	lv_obj_align(btn1,img_btn,LV_ALIGN_OUT_BOTTOM_MID,0,100);
	lv_obj_t * img_var = lv_img_create(btn1, NULL);
	lv_img_set_src(img_var, &wlan);
	lv_obj_t *label_btn1 = lv_label_create(scr,NULL);
	lv_label_set_style(label_btn1, LV_LABEL_STYLE_MAIN, &style1);
	lv_label_set_text(label_btn1, "连接");
	lv_obj_align(label_btn1,btn1,LV_ALIGN_OUT_BOTTOM_MID,0,10);
	
	
	lv_obj_t *image1 = lv_img_create(scr,NULL);
	lv_img_set_src(image1,&tiaotu48);
	lv_obj_set_pos(image1,200,100);
	
	

	
	
}




/**
  * @brief 任务回调函数
  * @param task-任务对象
  * @retval	None
  * @note 该函数由用户创建任务并设置回调,然后由系统调用
*/
static void my_task_cb(lv_task_t * task)
{

	static uint8_t i = 0;
	if(i)
	{
		i = 1 - i;
		lv_img_set_src(image2,&bg1_bin);
	}
	else
	{
		i = 1 - i;
		lv_img_set_src(image2,&bg0_bin);
	}
	printf("my_task called \n");

}





/**
  * @brief GUI主函数
  * @param None
  * @retval	None
  */
void lv_app_main(void)
{
	lv_load_user_font_from_file();	//加载中文字体
    //lv_tutorial_hello_world();
	//lv_test_theme_1(lv_theme_alien_init(210, NULL));
	//lv_tutorial_fonts();
	//lv_tutorial_image();
	//lv_font_cn_test();
	lv_image_test();
	
	/* 创建任务 */
	lv_task_t * task = lv_task_create(my_task_cb, 2000, LV_TASK_PRIO_MID, NULL);
}











