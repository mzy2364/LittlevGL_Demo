#include "lvgl.h"

lv_obj_set_width(obj, new_width);   //设置对象的宽度
lv_obj_set_height(obj, new_height); //设置对象的高度
lv_obj_set_size(obj, new_width, new_height);  //设置对象的高宽


lv_obj_set_x(obj, new_x);   //设置对象的X轴坐标
lv_obj_set_y(obj, new_y);   //设置对象的Y轴坐标
lv_obj_set_pos(obj, new_x, new_y);//设置对象的坐标

/* 设置对象的对齐,相对坐标 */
lv_obj_align(obj, base, LV_ALIGN_..., x_mod, y_mod);

lv_obj_align(label,btn,LV_ALIGN_IN_BOTTOM_MID,0,0);
lv_obj_align_origo(btn, image, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
lv_obj_t * child;
child = lv_obj_get_child(parent, NULL);
while(child) 
{
    /* 遍历子代 */
    child = lv_obj_get_child(parent, child);
}






















