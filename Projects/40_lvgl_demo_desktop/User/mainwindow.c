/*
* 文件名称 : mainwindow.c
* 版    本 : V1.0
* 作    者 : OpenRabbit
* 说    明 : MDK跟VS端兼容
*
* 背景利用图片填充，在图片上面的全屏控件设置为透明，避免遮挡背景
* 主页ICON加载方式，用结构体保存图像指针，文本指针，图像存储路径指针，app函数指针
* 用一个数组保存每个icon的结构体信息
* 上电从SD卡根据图像存储路径指针加载图像到图像指针
* 指定一个父对象，依次创建按钮往按钮添加图片和文字达到icon的效果，共3个页面
* 所有icon的事件回调函数公用一个，创建的按钮的返回对象利用链表保存，在事件回调函数中遍历链表找到索引
* 根据索引找到对应的结构体数组，执行相应的APP函数
* APP函数默认带有一个void*的形参，暂未使用
* 创建一个任务定时更新状态栏信息
* 用户添加APP只需要在对应页面的保存信息的数组中添加APP相关的参数即可（图像指针，文本，文件名，函数）
*
*/

 
/* 头文件 -----------------------------------------------------------*/
#include "gui_user.h"



/**
  * @brief APP空函数
  * @param user_data-自定义数据
  * @retval	None
  */
lv_obj_t * app_null(void *user_data)
{
	(void)user_data;
	printf("\napp1\n");
	return NULL;
}



/* 图像变量定义 */
lv_img_dsc_t img_desktop;
lv_img_dsc_t icon_led;
lv_img_dsc_t icon_qzone;
lv_img_dsc_t icon_qq;
lv_img_dsc_t icon_airbnb;
lv_img_dsc_t icon_amazon;
lv_img_dsc_t icon_wechat;
lv_img_dsc_t icon_google;
lv_img_dsc_t icon_windows;
lv_img_dsc_t icon_facebook;
lv_img_dsc_t icon_baidu;
lv_img_dsc_t icon_android;


/* ICON描述信息结构体 */
typedef struct
{
	lv_img_dsc_t *icon_img;
	const char *text_en;
	const char *text_cn;
	const char *icon_fname;
	lv_obj_t * (*app)(void *user_data);

}icon_item;

/* 桌面的ICON信息定义 */
static const icon_item icon_desktop_page1[] =
{
	{ &icon_led, "LED", "灯光", "0:/lvgl/led1.bin", app_led_create },
	{ &icon_qzone, "Qzone", "QQ空间 ", "0:/lvgl/qzone.bin", app_null },
	{ &icon_qq, "QQ", "QQ", "0:/lvgl/tencent_qq.bin", app_null },
	{ &icon_airbnb, "Airbnb", "爱彼 ", "0:/lvgl/airbnb.bin", app_null },
	{ &icon_amazon, "Amazon", "亚马 ", "0:/lvgl/amazon.bin", app_null },
	{ &icon_wechat, "Wechat", "微信 ", "0:/lvgl/wechat.bin", app_wechat_create },
	{ &icon_google, "Google", "谷歌 ", "0:/lvgl/google.bin", app_null },
	{ &icon_windows, "Windows", "窗口 ", "0:/lvgl/windows.bin", app_null },
	{ &icon_facebook, "Facebook", "脸书 ", "0:/lvgl/facebook.bin", app_null },
	{ &icon_baidu, "Baidu", "百度 ", "0:/lvgl/baidu.bin", app_null },
	{ &icon_android, "Android", "安卓 ", "0:/lvgl/android.bin", app_null },
};
static const icon_item icon_desktop_page2[] =
{
	{ &icon_qq, "QQ", "QQ", "0:/lvgl/tencent_qq.bin", app_null },
	{ &icon_wechat, "Wechat", "微信 ", "0:/lvgl/wechat.bin", app_null },
	{ &icon_google, "Google", "谷歌 ", "0:/lvgl/google.bin", app_null },
};
static const icon_item icon_desktop_page3[] =
{
	{ &icon_facebook, "Facebook", "脸书 ", "0:/lvgl/facebook.bin", app_null },
	{ &icon_baidu, "Baidu", "百度 ", "0:/lvgl/baidu.bin", app_null },
	{ &icon_android, "Android", "安卓 ", "0:/lvgl/android.bin", app_null },
};


/* 保存icon的对象的链表结构 */
typedef struct icon_obj
{
	lv_obj_t *obj;
	struct icon_obj *next;
}_icon_obj_list;
/* 链表表头定义 */
_icon_obj_list *icon_obj_list = NULL;



/* 全局对象指针定义 */
lv_obj_t *label_header_device_name;
lv_obj_t *label_header_time;
lv_obj_t *label_header_ele;





void lv_create_desktop(void);
void lv_load_icon_desktop(icon_item *item,uint16_t icon_num);
void lv_create_icon_desktop(lv_obj_t *parent, icon_item *item, uint16_t icon_num, lv_event_cb_t icon_event_cb);
static void update_header_time(lv_task_t *t);



/**
  * @brief 用户GUI主函数
  * @param None
  * @retval	None
  * @note 此函数一定要返回,禁止死循环
  */
void lv_app_main(void)
{

	lv_load_user_font_from_file();

	lv_font_cn_style_init();

	lv_load_img_bin_from_file(&img_desktop,"0:/lvgl/bg02.bin");

	lv_load_icon_desktop(icon_desktop_page1, sizeof(icon_desktop_page1)/sizeof(icon_desktop_page1[0]));
	lv_load_icon_desktop(icon_desktop_page1, sizeof(icon_desktop_page2) / sizeof(icon_desktop_page2[0]));
	lv_load_icon_desktop(icon_desktop_page1, sizeof(icon_desktop_page3) / sizeof(icon_desktop_page3[0]));

	lv_create_desktop();

	lv_task_create(update_header_time,1000,LV_TASK_PRIO_LOW,NULL);

}

/**
  * @brief ICON的事件回调函数
  * @param obj-触发事件的对象
  * @param event-事件类型
  * @retval	None
  * @note 根据对象找链表中的索引,根据索引执行APP
  */
static void icon_obj_event_cb(lv_obj_t * obj, lv_event_t event)
{
	if (event == LV_EVENT_RELEASED)
	{
		uint16_t index = 0;
		_icon_obj_list *p = icon_obj_list;
		while (p)
		{
			if (p->obj == obj)
			{
				break;
			}
			index++;
			p = p->next;
		}
		uint8_t icon_num_page1, icon_num_page2;
		icon_num_page1 = sizeof(icon_desktop_page1) / sizeof(icon_desktop_page1[0]);
		icon_num_page2 = sizeof(icon_desktop_page2) / sizeof(icon_desktop_page2[0]);
		if (index < icon_num_page1)
		{
			/* 第一个页面 */
			printf("page1\n");
			icon_desktop_page1[index].app(NULL);
		}
		else if ((index < icon_num_page1 + icon_num_page2))
		{
			/* 第二个页面 */
			printf("page2\n");
			icon_desktop_page2[index - icon_num_page1].app(NULL);
		}
		else
		{
			/* 第三个界面 */
			printf("page3\n");
			icon_desktop_page3[index - icon_num_page1 - icon_num_page2].app(NULL);
		}

		//printf("index:%d\r\n", index);
	}
}

/**
  * @brief 追加list
  * @param obj-list对象
  * @retval	None
  * @note 在链表结尾添加
  */
void icon_obj_list_append(lv_obj_t *obj)
{
	if (icon_obj_list == NULL)
	{
		icon_obj_list = (_icon_obj_list*)lv_mem_alloc(sizeof(_icon_obj_list));
		icon_obj_list->next = NULL;
		icon_obj_list->obj = obj;
	}
	else
	{
		_icon_obj_list *p = icon_obj_list;
		_icon_obj_list *node;
		node = (_icon_obj_list*)lv_mem_alloc(sizeof(_icon_obj_list));
		while (p)
		{
			if (p->next == NULL)
			{
				p->next = node;
				node->next = NULL;
				node->obj = obj;
			}

			p = p->next;
		}

	}
}


/**
  * @brief 更新顶部状态栏信息
  * @param t-任务指针
  * @retval	None
  */
static void update_header_time(lv_task_t *t)
{
	(void)t;
	if (label_header_time != NULL)
	{
		lv_label_set_text(label_header_time, "17:55");
	}
}



/**
  * @brief 创建桌面
  * @param Nnoe
  * @retval	None
  */
void lv_create_desktop(void)
{
	/* 新建个样式 */
	static lv_style_t style_desktop;
	static lv_style_t style_tabview;
	static lv_style_t style_label;
	static lv_style_t style_label_1;

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

	lv_theme_set_current(lv_theme_material_init(210, NULL));			/* 设置主题 */

	lv_obj_t *img_bg = lv_img_create(scr,NULL);
	lv_img_set_src(img_bg,&img_desktop);


	lv_obj_t *tabview = lv_tabview_create(scr, NULL);
	lv_tabview_set_btns_hidden(tabview, true);
	lv_style_copy(&style_tabview, lv_tabview_get_style(tabview, LV_TABVIEW_STYLE_BG));
	style_tabview.body.opa = 0;
	lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &style_tabview);
	lv_tabview_set_anim_time(tabview, 10);


	lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
	lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
	lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");


	lv_create_icon_desktop(tab1, icon_desktop_page1, sizeof(icon_desktop_page1) / sizeof(icon_desktop_page1[0]), icon_obj_event_cb);
	lv_create_icon_desktop(tab2, icon_desktop_page2, sizeof(icon_desktop_page2) / sizeof(icon_desktop_page2[0]), icon_obj_event_cb);
	lv_create_icon_desktop(tab3, icon_desktop_page3, sizeof(icon_desktop_page3) / sizeof(icon_desktop_page3[0]), icon_obj_event_cb);



	lv_style_copy(&style_label, &lv_style_pretty);
	style_label.text.font = style_cn_16.text.font;
	style_label.text.color = LV_COLOR_WHITE;
	style_label.body.opa = 150;
	style_label.body.border.width = 0;
	style_label.body.radius = 0;

	lv_obj_t *count = lv_cont_create(scr, NULL);
	lv_obj_set_size(count,LV_HOR_RES,32);
	lv_cont_set_style(count, LV_CONT_STYLE_MAIN, &style_label);

	label_header_device_name = lv_label_create(count, NULL);
	lv_label_set_style(label_header_device_name, LV_LABEL_STYLE_MAIN, &style_label);
	lv_label_set_text(label_header_device_name,"大野牛手持机");
	lv_obj_align(label_header_device_name, count, LV_ALIGN_IN_TOP_LEFT, 0, 0);

	label_header_time = lv_label_create(count, label_header_device_name);
	lv_label_set_text(label_header_time, "17:51");
	lv_obj_align(label_header_time, count, LV_ALIGN_IN_TOP_MID, 0, 0);

	lv_style_copy(&style_label_1, &style_label);
	style_label_1.text.font = &lv_font_roboto_28;
	label_header_ele = lv_label_create(count, label_header_device_name);
	lv_label_set_style(label_header_ele, LV_LABEL_STYLE_MAIN, &style_label_1);
	lv_label_set_text(label_header_ele, LV_SYMBOL_BATTERY_1);
	lv_obj_align(label_header_ele, count, LV_ALIGN_IN_TOP_RIGHT, -5, 2);


}


/**
  * @brief 加载ICON
  * @param item-保存ICON信息的数组
  * @param icon_num-数量
  * @retval	None
  */
void lv_load_icon_desktop(icon_item *item,uint16_t icon_num)
{
	uint16_t i=0;
	for ( i = 0; i < icon_num; ++i)
	{
		lv_load_img_bin_from_file(item[i].icon_img,item[i].icon_fname);
	}
}

/**
  * @brief 创建ICON
  * @param parent-父对象
  * @param item-保存ICON信息的数组
  * @param icon_num-数量
  * @param icon_event_cb-事件回调函数
  * @retval	None
  * @note 所有ICON公用一个事件回调函数
  */
void lv_create_icon_desktop(lv_obj_t *parent, icon_item *item, uint16_t icon_num, lv_event_cb_t icon_event_cb)
{

	uint16_t i=0;
	uint16_t x_pos=0,y_pos=0;

	static lv_style_t style_label;
	lv_style_copy(&style_label,&lv_style_pretty);
	style_label.text.font = style_cn_16.text.font;

	x_pos = 32;
	y_pos = 40;

	for ( i = 0; i < icon_num; ++i)
	{
		x_pos = ((i%4)*120)+10;
		y_pos = ((i/4)*120)+32;

		lv_obj_t *btn = lv_btn_create(parent, NULL);
		lv_obj_t *image = lv_img_create(btn,NULL);
		lv_obj_t *label = lv_label_create(btn,NULL);

		lv_obj_set_event_cb(btn, icon_event_cb);
		icon_obj_list_append(btn);

		lv_obj_set_pos(btn,x_pos,y_pos);
		lv_obj_set_size(btn,100,120);
		lv_btn_set_style(btn,LV_BTN_STYLE_REL,&lv_style_transp);
		lv_btn_set_style(btn,LV_BTN_STYLE_PR,&lv_style_btn_ina);


		lv_img_set_src(image,item[i].icon_img);

		//style_label.text.color = LV_COLOR_WHITE;
		//style_label.body.main_color = LV_COLOR_BLACK;
		//style_label.body.grad_color = LV_COLOR_BLACK;
		style_label.body.opa = 150;
		style_label.body.border.width = 0;

		lv_label_set_body_draw(label,true);

		lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style_label);
		lv_label_set_text(label,item[i].text_cn);
		lv_obj_align(label,btn,LV_ALIGN_IN_BOTTOM_MID,0,0);

	}

}

 
/***************************** 跳兔科技 www.whtiaotu.com (END OF FILE) *********************************/
