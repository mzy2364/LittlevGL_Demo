<h1 align="center">LittlevGL应用笔记</h1>
# 对象 Object

在 LittlevGL 中，用户界面的基本构建块是对象 object，也可以称为 widget 或者控件、小部件，比如按钮、label 或者图像。

## 对象属性

### 基本属性

所有的对象都有一些独立于对象本身的基本属性：

- 位置
- 大小
- 父类
- 是否可拖动
- 是否可点击
- ...

可以使用 `` lv_obj_set_xx()`` 和 ``lv_obj_get_xx()`` 来设置和获取这些属性，例如：

```c
lv_obj_set_pos(btn, 10, 10);			/* 设置控件的位置 */
lv_obj_set_size(btn, 100, 100);			/* 设置控件的大小 */
lv_obj_set_event_cb(btn, my_event_cb);	/* 设置控件的事件回调函数 */
```

### 专有属性

对象也有专有属性，基本每个控件都有自己一些特殊的属性，比如一个 btn 控件，就有独有的属性：

- **state** 状态，按下或者释放 LV_BTN_STATE_REL/LV_BTN_STATE_PR 等
- **toggle** 切换状态
- **fit** 四周边框的绘制策略

对于这些特有的属性，每个控件都有独立的API来对属性进行设置，比如：

```c
lv_btn_set_state(btn,LV_BTN_STATE_PR);
lv_btn_set_toggle(btn,true);
lv_btn_set_fit(btn, LV_FIT_NONE);
```

## 对象工作机制

### 父子结构

父对象可以视为其子对象的容器。 每个对象只有一个父对象（屏幕除外），但是一个父对象可以有无限多个子对象。 父对象的类型没有限制，但是有典型的父对象（例如，按钮）和典型的子对象（例如，标签）。

### 一起移动

如果更改了父对象的位置，则子对象将与父对象一起移动。 因此，所有位置都相对于父对象。

(0,0) 坐标表示对象的位置会保持在他们各自父对象的左上角

![1574700669308](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574700669308.png)

```c
lv_obj_t *par = lv_obj_create(scr, NULL);	/* 创建一个父对象 */
lv_obj_set_size(par, 200, 200);				/* 设置父对象的尺寸 */

lv_obj_t *btn = lv_btn_create(par, NULL);	/* 创建一个子对象 */
lv_obj_set_pos(btn, 50, 50);				/* 设置子对象的位置 */
```

修改父对象的位置

![1574700762106](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574700762106.png)

```c
lv_obj_set_pos(par, 100, 100);				/* 设置父对象的位置 */
```

父对象的位置修改后，子对象随着父对象一起移动

### 只可显示在父对象上

如果子对象的外框超过了父对象的大小，那么在父对象以外的区域，子对象是无法被显示出来的

![1574700993601](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574700993601.png)

```c
lv_obj_set_pos(btn, -10, 50);				/* 设置子对象的位置 */
```

### 创建删除对象

在 LittlevGL 中，可以在运行时动态创建和删除对象。 这意味着仅当前创建的对象消耗 RAM。 例如，如果需要图表，则可以在需要时创建它，并在不可见或不必要时将其删除。

每个对象类型都有自己的带有统一原型的创建功能。 它需要两个参数：

- 指向父对象的指针。 要创建一个屏幕，请将NULL作为父级
- （可选）用于复制具有相同类型的对象的指针。 该复制对象可以为NULL，以避免复制操作

使用 ``lv_obj_t`` 指针作为句柄在 C 代码中引用所有对象。 以后可以使用此指针设置或获取对象的属性。

创建函数

```c
lv_obj_t * lv_xxx_create(lv_obj_t * parent, const lv_obj_t * copy);
```

 有一个所有对象类型通用的删除函数，它会删除一个对象和该对象的所有子对象 

```c
void lv_obj_del(lv_obj_t * obj);
```

``lv_obj_del`` 将立即删除该对象。 如果出于某种原因不能立即删除该对象，则可以使``lv_obj_del_async(obj)``。 例如要删除子级的LV_EVENT_DELETE信号中对象的父级。

可以使用 ``lv_obj_clean`` 删除对象的所有子对象(但不能删除对象本身)：

```c
void lv_obj_clean(lv_obj_t * obj);
```

### 屏幕对象

屏幕对象是库初始化的时候就会存在的一个特殊对象，可以理解为顶级父对象，所有控件在创建的时候都可以作为其子对象，在创建控件的时候，往往会先获取当前屏幕，然后将屏幕作为其父对象，例如：

```c
lv_obj_t *scr = lv_disp_get_scr_act(NULL);		/* 获取当前屏幕 */
lv_obj_t *label = lv_label_create(scr, NULL);	/* 创建label */
```



# 图层 Layer

## 创建顺序

默认情况下，先创建的对象会显示在底层，后创建的对象会显示在顶层。

例如我们先创建一个名为 back 的按钮，然后创建一个名为 front 的按钮，就会发现后面创建的名为 front 的按钮在两个按钮重叠部分会遮挡前面创建的按钮

![1574772659417](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574772659417.png)

```c
	/* 创建一个名为 back 的按钮控件 */
	lv_obj_t *btn1 = lv_btn_create(scr, NULL);		/* 创建 btn 控件 */
	lv_obj_t *label1 = lv_label_create(btn1, NULL);	/* 创建 label 控件 */
	lv_label_set_text(label1, "back");				/* 设置文字 */
	lv_obj_set_pos(btn1, 200, 10);					/* 设置坐标 */

	/* 创建一个名为 front 的按钮控件 */
	lv_obj_t *btn2 = lv_btn_create(scr, NULL);		/* 创建 btn 控件 */
	lv_obj_t *label2 = lv_label_create(btn2, NULL);	/* 创建 label 控件 */
	lv_label_set_text(label2,"front");				/* 设置文字 */
	lv_obj_set_pos(btn2,260,50);					/* 设置坐标 */
```

## 成为前台

如果要让前面创建的对象置于前景显示，有以下方法：

- 使用 ``lv_obj_set_top(obj,true)`` 函数，如果对象或者其子对象被点击，库会将改对象置于前景层，工作方式类似与 windows 
- 使用 ``	lv_obj_move_foreground(obj) `` 告诉库将对象置于前台或者使用 ``lv_obj_move_background(obj)`` 将对象置于后台
- 当使用 ``lv_obj_set_parent(obj, new_parent)`` 时，``obj`` 将位于 ``new_parent`` 的前台

![1574773763640](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574773763640.png)

```c
lv_obj_set_top(btn1,true);
```

![1574773808295](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574773808295.png)

```c
lv_obj_move_foreground(btn1);
```

## 顶层和系统层

LittlevGL 使用两个名为 ``layer_top`` 和 ``layer_sys`` 的特殊层，两者在显示器的所有屏幕上都是 可见且通用的。但是，他们不会在多个物理显示器之间共享。``layer_top`` 始终位于默认屏幕 ``(lv_scr_act()) `` 的顶部，``layer_sys`` 则位于 ``layer_top`` 的顶部。

用户可以使用 ``layer_top`` 来创建一些随处可见的内容，例如，菜单栏，对话框。如果启动了 ``click`` 属性，``layer_top`` 将吸收所用用户的点击并将其模态化。

```c
lv_obj_set_click(lv_layer_top(), true); /* 启用后除了 lv_layer_top 上的控件会响应输入设备，其他层的控件不会响应 */
```



![1574774640244](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574774640244.png)

```c
/* 创建一个父对象为 lv_layer_top 的按钮 */
lv_obj_t *btn3 = lv_btn_create(lv_layer_top(),NULL);
lv_obj_t *label3 = lv_label_create(btn3,NULL);
lv_label_set_text(label3,"btn on top");
lv_obj_set_pos(btn3,180,40);
```

# 事件 Event

当控件被点击或者发生其他与控件相关的事项时，事件将会被触发。例如拖动和修改控件的属性等。

用户可以为对象设置回调函数，然后查看这些事件，例如一个滑动控件 ``slider`` 

![1574776784564](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574776784564.png)

```c
lv_obj_t *slider1 = lv_slider_create(scr, NULL);		/* 创建一个 slider 滑动控件 */
lv_obj_set_event_cb(slider1, my_event_cb);				/* 为控件设置事件的回调函数 */

...
    
/**
  * @brief 控件的事件回调函数
  * @param obj-控件对象
  * @param event-事件类型
  * @retval	None
  * @note 该函数由用户注册,然后由系统调用
*/
static void my_event_cb(lv_obj_t * obj, lv_event_t event)
{
	switch (event)
	{
	case LV_EVENT_PRESSED:
		printf("pressed value:%d\n", lv_slider_get_value(obj));
		break;
	case LV_EVENT_VALUE_CHANGED:
		printf("change value:%d\n", lv_slider_get_value(obj));
		break;
	case LV_EVENT_RELEASED:
		printf("release value:%d\n", lv_slider_get_value(obj));
		break;
	default:
		break;
	}
}
```

## 事件类型

跟对象的属性一样，对象有一些通用的事件类型，某些对象也有一些特殊的事件类型

从源码中摘取的所有事件枚举

```c
enum {
    LV_EVENT_PRESSED,             /**< The object has been pressed*/
    LV_EVENT_PRESSING,            /**< The object is being pressed (called continuously while pressing)*/
    LV_EVENT_PRESS_LOST,          /**< User is still pressing but slid cursor/finger off of the object */
    LV_EVENT_SHORT_CLICKED,       /**< User pressed object for a short period of time, then released it. Not called if dragged. */
    LV_EVENT_LONG_PRESSED,        /**< Object has been pressed for at least `LV_INDEV_LONG_PRESS_TIME`.  Not called if dragged.*/
    LV_EVENT_LONG_PRESSED_REPEAT, /**< Called after `LV_INDEV_LONG_PRESS_TIME` in every
                                       `LV_INDEV_LONG_PRESS_REP_TIME` ms.  Not called if dragged.*/
    LV_EVENT_CLICKED,             /**< Called on release if not dragged (regardless to long press)*/
    LV_EVENT_RELEASED,            /**< Called in every cases when the object has been released*/                                    
    LV_EVENT_DRAG_BEGIN,		  
    LV_EVENT_DRAG_END,
    LV_EVENT_DRAG_THROW_BEGIN,
    LV_EVENT_KEY,
    LV_EVENT_FOCUSED,
    LV_EVENT_DEFOCUSED,
    LV_EVENT_VALUE_CHANGED,		 /**< The object's value has changed (i.e. slider moved) */
    LV_EVENT_INSERT,
    LV_EVENT_REFRESH,
    LV_EVENT_APPLY,  /**< "Ok", "Apply" or similar specific button has clicked*/
    LV_EVENT_CANCEL, /**< "Close", "Cancel" or similar specific button has clicked*/
    LV_EVENT_DELETE, /**< Object is being deleted */
};
```

### 一般事件

所有对象都存在的事件

### 与输入设备有关的事件

当用户点击或者释放控件的时候，会触发这些事件。触摸、鼠标、键盘、按键等输入设备都可以触发这些事件

**LV_EVENT_PRESSED** 对象被按下

**LV_EVENT_PRESSING** 对象被按下（长按的时候连续发送）

**LV_EVENT_PRESS_LOST** 输入设备仍处于按下状态，但不在对象上，例如鼠标点击按钮后将光标移至按钮外

**LV_EVENT_SHORT_CLICKED** 用户在短时间内按下对象然后释放，拖动不会触发

**LV_EVENT_LONG_PRESSED** 长按超过 ``LV_INDEV_DEF_LONG_PRESS_TIME`` (**注释不是这个宏但实际使用的是这个宏**)并释放，拖动不会触发

**LV_EVENT_LONG_PRESSED_REPEAT** 长按后的连续汇报事件，拖动则不触发，在长按超过  ``LV_INDEV_DEF_LONG_PRESS_TIME`` 后每隔这个时间调用一次

**LV_EVENT_CLICKED** 如果没有拖动且释放了就触发（无论是否长按）

**LV_EVENT_RELEASED** 任何情况下对象释放了就触发

### 与指针相关

这类事件仅由指针输入设备调用，例如鼠标和触摸屏

以下事件需要使能拖动后才会被触发 ``lv_obj_set_drag(obj,true)`` 和 ``lv_obj_set_drag_throw(obj,true)``

**LV_EVENT_DRAG_BEGIN** 开始拖动对象

**LV_EVENT_DRAG_END** 结束拖动对象（包括惯性拖动）

**LV_EVENT_DRAG_THROW_BEGIN** 开始控件的惯性拖动（就是使能 drag_throw 后，拖动控件然后松开鼠标，控件还会向前移动一段距离）

### 跟键盘和按键相关的事件

**LV_EVENT_KEY** 将键值发送到对象

**LV_EVENT_FOCUSED** 聚焦

**LV_EVENT_FOCUSED** 聚焦释放

### 特殊事件

这类事件往往属于某个特殊的控件

**LV_EVENT_VALUE_CHANGED** 对象的值改变

**LV_EVENT_INSERT** 往对象中插入内容（例如 label 控件）

**LV_EVENT_REFRESH** 查询以刷新对象，这个事件不会由库触发，用户可以使用

**LV_EVENT_APPLY** 单击“确定”或类似特殊按钮。（通常来自键盘）

**LV_EVENT_CANCEL** 单击“取消”等特殊按钮。（通常来自键盘）

### 一般事件

**LV_EVENT_DELETE** 控件删除时发送，可以用于释放资源

### 事件的自定义数据

某些事件可能包含一些数据，例如 ``LV_EVENT_VALUE_CHANGED`` 会高速对象有一个新值，可以在回调函数中使用 ``lv_event_get_data()`` 函数获取自定义数据

自定义的数据类型取决于发送对象，如果时数值那么类型是 ``uint32_t *`` 或者 ``int32_t *``  ,如果是文本那么类型是 ``char *`` 或者 ``const char *`` 

**``slider`` 控件的 ``LV_EVENT_VALUE_CHANGED `` 事件没有自定义数据。**

![1574782363508](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574782363508.png)

```c
lv_obj_t *btnm1 = lv_btnm_create(scr,NULL);
lv_obj_set_event_cb(btnm1, my_event_btnm_cb);

...
    
/**
  * @brief 控件的事件回调函数
  * @param obj-控件对象
  * @param event-事件类型
  * @retval	None
  * @note 该函数由用户注册,然后由系统调用
*/
static void my_event_btnm_cb(lv_obj_t * obj, lv_event_t event)
{
	static int *value;
	switch (event)
    {
	case LV_EVENT_VALUE_CHANGED:
		value = lv_event_get_data();
		if (value != NULL)
			printf("change value:%d\n", (int)*value);
		break;
	default:
		break;
	}
}

```


### 用户发送事件

要将事件发送到对象，可以使用 ``lv_event_send(lv_obj_t * obj, lv_event_t event, const void * data)`` 

嵌入式设备中，我们往往可以RTOS获取按钮的数据然后以事件的方式发送到 LittlevGL。也可以在一个对象的事件回调函数中发事件消息到另一个对象实现同步的目的。

也可以执行刷新

```c
lv_event_send(label, LV_EVENT_REFRESH, NULL);
```



# 样式 Style

样式用于设置对象的外观。 样式是一种具有颜色，填充，不透明度，字体等属性的结构。使用样式可以定制个性化的控件外观。

对象仅存储指向样式的指针，因此样式不能是在函数退出后销毁的局部变量。 创建样式的时候应该定义为静态变量或者全局变量。

## 样式结构体源码

```c	
typedef struct
{
    uint8_t glass : 1; /**< 1: Do not inherit this style*/

    /** Object background. */
    struct
    {
        lv_color_t main_color; /**< Object's main background color. */
        lv_color_t grad_color; /**< Second color. If not equal to `main_color` a gradient will be drawn for the background. */
        lv_coord_t radius; /**< Object's corner radius. You can use #LV_RADIUS_CIRCLE if you want to draw a circle. */
        lv_opa_t opa; /**< Object's opacity (0-255). */

        struct
        {
            lv_color_t color; /**< Border color */
            lv_coord_t width; /**< Border width */
            lv_border_part_t part; /**< Which borders to draw */
            lv_opa_t opa; /**< Border opacity. */
        } border;

        
        struct
        {
            lv_color_t color;
            lv_coord_t width;
            lv_shadow_type_t type; /**< Which parts of the shadow to draw */
        } shadow;

        struct
        {
            lv_coord_t top;
            lv_coord_t bottom;
            lv_coord_t left;
            lv_coord_t right;
            lv_coord_t inner;
        } padding;
    } body;

    /** Style for text drawn by this object. */
    struct
    {
        lv_color_t color; /**< Text color */
        lv_color_t sel_color; /**< Text selection background color. */
        const lv_font_t * font;
        lv_coord_t letter_space; /**< Space between letters */
        lv_coord_t line_space; /**< Space between lines (vertical) */
        lv_opa_t opa; /**< Text opacity */
    } text;

    /**< Style of images. */
    struct
    {
        lv_color_t color; /**< Color to recolor the image with */
        lv_opa_t intense; /**< Opacity of recoloring (0 means no recoloring) */
        lv_opa_t opa; /**< Opacity of whole image */
    } image;

    /**< Style of lines (not borders). */
    struct
    {
        lv_color_t color;
        lv_coord_t width;
        lv_opa_t opa;
        uint8_t rounded : 1; /**< 1: rounded line endings*/
    } line;
} lv_style_t;
```



## 样式的属性

### 共同属性

**glass**:不继承这种风格(为1的时候对象的子类不会继承这种风格，以为着自类需要重新设置风格)

### body 属性

**body.main_color**:主要颜色

**body.grad_color**:渐变色（底色）

**body.radius**:角半径

**body.opa**:不透明度（0-255）

**border**:边框

**body.border.color**：边框颜色

**body.border.width**：边框宽度

**body.border.part**：边框部分（选择哪一部分边框， *LV_BORDER_LEFT/RIGHT/TOP/BOTTOM/FULL* 或者 ‘OR’ed 的值）

**body.border.opa**：边框不透明度（0-255）

**shadow**:阴影

**body.shadow.color**:阴影颜色

**body.shadow.width**:阴影宽度

**body.shadow.type**:阴影类型（LV_SHADOW_FULL/LV_SHADOW_BOTTOM）

**padding**:填充

**body.padding.top**:顶部填充

**body.padding.bottom**:底部填充

**body.padding.left**:左边部分填充

**body.padding.right**:右边部分填充

**body.padding.inner**:内部填充（在内容元素或子元素之间）



### text 文字属性

**text.color**:文字颜色

**text.sel_color**:所选文字颜色

**text.font**:字体

**text.letter_space**:字母之间的间隔

**text.line_space**:线间距（垂直）

**text.opa**:不透明度



### image 图片属性

**image.color**:颜色，使用颜色重新着色图像

**image.intense**:重新着色的不透明度（0表示不重新着色）

**image.opa**:整个图像不透明度



### line 线条属性

**line.color**:线条颜色

**line.width**:线条宽度

**line.opa**:线条透明度

**line:rounded**:圆角线尾



## lvgl 内置的样式

<img src="C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574688898051.png" alt="1574688898051" style="zoom:150%;" />

:warning:注意

透明的内置样式默认情况下将 ``glass = 1``，这些样式（例如其颜色）将不会被子类继承。子类需要重新定义样式。



对于内置的样式，可以直接设置控件的样式

```c
lv_label_set_style(label1,LV_LABEL_STYLE_MAIN,&lv_style_transp);
```

如果控件有多种状态，例如btn，可以对不同状态设置不同的样式

```c
lv_btn_set_style(btn,LV_BTN_STYLE_PR,&lv_style_transp);		/* 设置btn释放时的样式 */
lv_btn_set_style(btn,LV_BTN_STYLE_REL,&lv_style_btn_rel);	/* 设置btn按下时的样式 */
```



## 如何使用自定义的样式

内置的样式虽然丰富，但是很多时候我们往往要自己定义样式，例如中文字体的显示，用内置的样式是无法实现的，需要我们重新定义样式的字体。这个时候我们可以修改他原有的样式或者重新定义样式，我们尽量不去修改源码，所以需要自己定义样式。

下面的代码段演示了自定义样式的使用，我们在自定义样式后，可以复制内置的样式，这样就不需要我们重新定义每一个属性，仅仅需要修改我们改变的一部分属性，比如下面代码中修改字体和文字颜色。

```c
static lv_style_t style_cn_24;		/* 定义一个新的样式,注意使用static */
lv_style_copy(&style_cn_24, &lv_style_pretty_color);	/* 复制style的属性 */
style_cn_24.text.font = &gb2312_puhui24;		/* 重新设置style的字体 */
style_cn_24.text.color = LV_COLOR_BLUE;			/* 重新设置style的文字颜色 */

lv_obj_t *label4 = lv_label_create(scr,NULL);	/* 创建label控件 */
lv_obj_set_style(label4,&style_cn_24);			/* 为控件设置新的style */
lv_obj_set_pos(label4,0,100);					/* 设置控件的坐标 */
lv_label_set_text(label4,"这是一个蓝色的中文字体的label控件");	/* 设置文字 */
```



## 主题

前面介绍了样式，我们可以使用内置的样式或者自定义的样式，但是创建一些优美的样式需要我们对库有深入的了解并且具备设计能力，创建样式也会耗费开发者的时间。

鉴于以上考虑，LittlevGL 的作者为了简化开发流程，坚持以更少的代码写出更优美的界面，为我们引入了主题的概念，相信主题大家也都很熟悉，就是一系列控件美化的集合，包含了所有控件的样式。

如果不是定制化要求较高的场合，内置的8种主题就能满足我们的需求。需要在 ``lv_conf.h`` 里面开启对应的宏

### 主题使用方法

![1574693284041](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574693284041.png)

```c
/* 创建主题 */
lv_theme_t *theme1 = lv_theme_alien_init(10, NULL);
lv_theme_t *theme2 = lv_theme_night_init(10, NULL);

/* 创建按钮并设置主题 */
lv_obj_t *btn1 = lv_btn_create(scr, NULL);	
lv_obj_t *label_btn1 = lv_label_create(btn1,NULL);
lv_label_set_text(label_btn1,"theme_alien");
lv_obj_set_pos(btn1, 10, 10);
lv_btn_set_style(btn1, LV_BTN_STYLE_REL,theme1->style.btn.rel);
lv_btn_set_style(btn1, LV_BTN_STYLE_PR, theme1->style.btn.pr);

lv_obj_t *btn2 = lv_btn_create(scr, NULL);
lv_obj_t *label_btn2 = lv_label_create(btn2, NULL);
lv_label_set_text(label_btn2, "theme_night");
lv_obj_set_pos(btn2, 10, 100);
lv_btn_set_style(btn2, LV_BTN_STYLE_REL, theme2->style.btn.rel);
lv_btn_set_style(btn2, LV_BTN_STYLE_PR, theme2->style.btn.pr);
```



以上方法需要为每个控件设置主题，如果我们的应用或者某一部分控件使用同样的主题时，可以定义当前的主题，这样后面再创建控件的时候默认使用这个主题，例如：

![1574693341385](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574693341385.png)

```c
	/* 创建主题 */
	lv_theme_t *theme1 = lv_theme_alien_init(10, NULL);

	/* 设置当前主题 */
	lv_theme_set_current(theme1);

	/* 创建按钮 */
	lv_obj_t *btn1 = lv_btn_create(scr, NULL);	
	lv_obj_t *label_btn1 = lv_label_create(btn1,NULL);
	lv_label_set_text(label_btn1,"theme_alien");
	lv_obj_set_pos(btn1, 10, 10);

	lv_obj_t *btn2 = lv_btn_create(scr, NULL);
	lv_obj_t *label_btn2 = lv_label_create(btn2, NULL);
	lv_label_set_text(label_btn2, "theme_night");
	lv_obj_set_pos(btn2, 10, 100);
```



### 主题的实时更新

LittlevGL 允许我们在程序运行时更新主题。在默认情况下，如果再次调用 ``lv_theme_set_current(theme)`` 不会刷新已经创建的控件的样式，需要在 ``lv_conf.h`` 中开启 ``LV_THEME_LIVE_UPDATE`` 宏定义以实现实时刷新。

实时更新只会更新主题创建样式不变的对象，即，第一次调用 ``lv_theme_set_current(theme)`` 之后创建的控件或者手动应用了主题样式的控件。





# 字体 Font

在 LittlevGL 中。字体是文字的位图和其他信息的集合。字体存储在 ``lv_font_t`` 变量中，并且可以在样式的字段中设置，例如

![1574786323610](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574786323610.png)

```c
	/* 创建一个新字体的 style */
	static lv_style_t style2;
	lv_style_copy(&style2, &lv_style_plain);
	style2.text.font = &gb2312_puhui32;

	/* 创建一个新字体的 label */
	lv_obj_t * label = lv_label_create(scr, NULL);
	lv_obj_set_pos(label, 100, 200);
	lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style2);
	lv_label_set_text(label, "你好世界");  
```

字体具有bpp（每像素位数）属性，他表示用于描述字体中像素的位数，bpp越高，字体就会越平滑，抗锯齿的效果就会越好，高性能的显示带来的就是字库的存储空间变大。

## Unicode 支持

LittlevGL 支持 UTF-8 编码的 Unicode 字符，在使用时需要确保文件的保存格式为 UTF-8 

### 中文字体

LittlevGL 官网有在线的字体转换工具，可以将 ttf 的字体文件转换为 LittlevGL 支持的字体文件，字体可以保存在内部数组，也可以保存在外部 flash 或者文件系统。显示中文的 c 文件必须使用 UTF8 编码。

## 内置字体

LittlevGL 内置了几种 ASCII 字体，可以在 ``lv_conf.h`` 中启用

- LV_FONT_ROBOTO_12
- LV_FONT_ROBOTO_16
- LV_FONT_ROBOTO_22
- LV_FONT_ROBOTO_28

内置字体是全局变量，使用时只需调用即可，内部字体是 4bpp 

除了 ASCII 范围的字体，内置字体还支持符号字体，例如

![1574787017263](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574787017263.png)

符号字体可以直接使用

```C
lv_label_set_text(label,LV_SYMBOL_AUDIO);
```

也可以配合字符串一起使用

```c
lv_label_set_text(label,LV_SYMBOL_AUDIO "AUDIO");
```

或者两个符号一起使用

```c
lv_label_set_text(label,LV_SYMBOL_AUDIO LV_SYMBOL_BELL);
```

## 添加新字体

有几种方法可以向项目中添加新字体以及本地化的字体

- 利用官方提供的 [在线字体转换](https://littlevgl.com/ttf-font-to-c-array) ，可以在浏览器上传您的 ttf 字体文件并可以选择范围和文字，然后生成 c 字体文件并添加到项目中（这种方法对于国内用户往往较慢）
- 利用论坛网友  [【阿里】](  https://whycan.cn/t_1350.html  )  提供的免费字体转换软件，该软件可以将中文转化为 C 数组文件或者 XBF 的 bin 文件存储在外部 Flash 或者文件系统。

要使用汉字，需要将文件保存为 UTF-8 格式，然后将字体文件加入到工程，在需要显示中文的文件里面声明新字体 ``LV_FONT_DECLARE(gb2312_puhui32)`` 

# 图像 Image

图像可以是存储位图本身和一些元数据的文件或变量。

## 存储图像

可以将图像存储在两个位置

- 内部 flash 或者 ram中的变量
- 外部 flash 或者文件系统

### 变量方式存储

存储在内部变量的图像由 ``lv_img_dsc_t`` 结构体保存，该结构体具有以下内容：

- **cf** 颜色格式
- **always_zero** 始终为0
- **reserved** 保留
- **w** 图像宽度（<=2048）
- **h** 图像高度（<=2048）
- **data_size** 数据长度
- **data** 图像数据的指针

### 文件方式存储

要使用文件的方式处理图片，需要注册 LittlevGL 的文件接口，实现打开、读取、关闭等功能。

## 颜色格式

LittlevGL 内置多种颜色格式：

- **LV_IMG_CF_TRUE_COLOR** 
- **LV_IMG_CF_TRUE_COLOR_ALPHA** 
- **LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED **
- **LV_IMG_CF_INDEXED_1/2/4/8BIT** 
- **LV_IMG_CF_ALPHA_12/4/8BIT** 

除了内置的颜色格式外，用户可以使用 Raw 格式存储，这种颜色格式需要使用外部图像解码器来解码图像

- **LV_IMG_CF_RAW**
- **LV_IMG_CF_RAW_ALPHA**
- **LV_IMG_CF_RAW_CHROMA_KEYED**

## 如何使用图像

用户可以通过两种方式将图像添加到 LittlevGL :

- 使用图像转换器（在线图像转换或者离线图像转换工具）
- 手动创建图像

### 图像转换器

可以使用在线图像转换： https://littlevgl.com/image-to-c-array 

也可以使用论坛网友提供的图像转换工具：   https://github.com/zhangjingxun12/Lvgl_image_convert_tool 

可以将图像转换成 c 格式的数组存储在内部 Flash，也可以转换为 bin 文件存储在外部 Flash 或者文件系统。

### 如何使用图像

在创建图像后将 c 文件添加到工程或者将 bin 文件复制到文件系统，然后使用以下方法显示图像

![1574858720562](C:\Users\Admin\AppData\Roaming\Typora\typora-user-images\1574858720562.png)

```c
LV_IMG_DECLARE(tiaotu)	/* 声明一个全局图像变量 */
    
...
    
lv_obj_t *img1 = lv_img_create(scr, NULL);	/* 创建 img 控件 */
lv_img_set_src(img1, &tiaotu);				/* 设置 img 的数据 */
lv_obj_align(img1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);	/* 设置位置 */
```

如果实现了文件系统接口并且把图像以 bin 文件格式存储在了外部，则应该使用这种方式显示图像

```c
lv_img_set_src(img1, "P:/lv_examples/tiaotu.bin");
```

# 文件系统 File system

LittlevGL 具有文件系统抽象模块，用户可以附加任何类型的文件系统，只需要注册对应的接口即可。文件系统由驱动器的 ``letter`` 标识。例如，如果 SD 卡与字母关联，则可以用 `` 'S' `` 访问文件，例如 ``"S:/ui/tiaotu.bin"`` 

## 添加驱动程序

如果要添加文件系统接口，就必须要定义一个 ``lv_fs_drv_t`` 的变量，实现文件操作功能的接口函数，并将这个变量注册到库的驱动里面

``lv_fs_drv_t`` 结构体源码

```c
typedef struct _lv_fs_drv_t
{
    char letter;
    uint16_t file_size;
    uint16_t rddir_size;
    bool (*ready_cb)(struct _lv_fs_drv_t * drv);

    lv_fs_res_t (*open_cb)(struct _lv_fs_drv_t * drv, void * file_p, const char * path, lv_fs_mode_t mode);
    lv_fs_res_t (*close_cb)(struct _lv_fs_drv_t * drv, void * file_p);
    lv_fs_res_t (*remove_cb)(struct _lv_fs_drv_t * drv, const char * fn);
    lv_fs_res_t (*read_cb)(struct _lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
    lv_fs_res_t (*write_cb)(struct _lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
    lv_fs_res_t (*seek_cb)(struct _lv_fs_drv_t * drv, void * file_p, uint32_t pos);
    lv_fs_res_t (*tell_cb)(struct _lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);
    lv_fs_res_t (*trunc_cb)(struct _lv_fs_drv_t * drv, void * file_p);
    lv_fs_res_t (*size_cb)(struct _lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
    lv_fs_res_t (*rename_cb)(struct _lv_fs_drv_t * drv, const char * oldname, const char * newname);
    lv_fs_res_t (*free_space_cb)(struct _lv_fs_drv_t * drv, uint32_t * total_p, uint32_t * free_p);

    lv_fs_res_t (*dir_open_cb)(struct _lv_fs_drv_t * drv, void * rddir_p, const char * path);
    lv_fs_res_t (*dir_read_cb)(struct _lv_fs_drv_t * drv, void * rddir_p, char * fn);
    lv_fs_res_t (*dir_close_cb)(struct _lv_fs_drv_t * drv, void * rddir_p);

#if LV_USE_USER_DATA
    lv_fs_drv_user_data_t user_data; /**< Custom file user data */
#endif
} lv_fs_drv_t;
```

实现一个文件驱动的注册

```c
lv_fs_drv_t my_fs_drv;							/* 定义一个文件驱动 */
lv_fs_drv_init(&my_fs_drv);						/* 初始化 */

my_fs_drv.letter = 'S';							/* 驱动器标识 */
my_fs_drv.file_size = sizeof(my_file_obj);		/* 文件对象大小 */
my_fs_drv.file_size = sizeof(my_dir_obj);		/* 目录对象大小 */
my_fs_drv.ready_cb = my_fs_ready_cb;			/* 文件是否准备就绪 */
my_fs_drv.open_cb = my_fs_open_cb_cb;			/* 打开文件 */
my_fs_drv.close_cb = my_fs_close_cb;			/* 关闭文件 */
my_fs_drv.remove_cb = my_fs_remove_cb;			/* 删除文件 */
my_fs_drv.read_cb = my_fs_read_cb;				/* 读取文件 */
my_fs_drv.write_cb = my_fs_write_cb;			/* 写入文件 */
my_fs_drv.seek_cb = my_fs_seek_cb;				/* 移动读写指针 */
my_fs_drv.tell_cb = my_fs_tell_cb;				/* 汇报读写指针位置 */
my_fs_drv.trunc_cb = my_fs_trunc_cb;			/* 从读写指针处删除文件 */
my_fs_drv.size_cb = my_fs_size_cb;				/* 获取文件大小 */
my_fs_drv.rename_cb = my_fs_rename_cb;			/* 重命名文件 */
my_fs_drv.free_space_cb = my_fs_free_space_cb;	/* 获取可用空间 */
my_fs_drv.dir_open_cb = my_fs_dir_open_cb;		/* 打开目录 */
my_fs_drv.dir_read_cb = my_fs_dir_read_cb;		/* 读取目录 */
my_fs_drv.dir_close_cb = my_fs_dir_close_cb;	/* 离开目录 */

my_fs_drv.user_data = my_fs_user_data;			/* 用户数据 */

lv_fs_drv_register(&pcfs_drv);					/* 注册一个文件驱动 */
```

以上回调函数并不是每一个都需要实现的，根据用户的需求，把用户暂时没有使用的回调函数赋值为 ``NULL`` 即可

如果我们需要打开一个文件，可以用以下方式

```c
lv_fs_open(&file, "S:/ui/font.bin", LV_FS_MODE_RD);
```

其中路径以驱动器标识 'S' 开头

## 文件系统使用示例

```c
lv_fs_file_t f;
lv_fs_res_t res;
uint32_t read_num;
uint8_t buf[8];
res = lv_fs_open(&f, "S:ui/tiaotu.txt", LV_FS_MODE_RD);
if(res != LV_FS_RES_OK) 
    my_error_handling();

res = lv_fs_read(&f, buf, 8, &read_num);
if(res != LV_FS_RES_OK || read_num != 8) 
    my_error_handling();

lv_fs_close(&f);
```



# 动画 Animation

用户可以使用动画在开始值和结束值之间自动更改变量的值，动画将定期调用带有相应 vale 参数的函数来生成

该函数原型如下

```c
void func(void *var, lv_anim_value_t value);
```

### 创建动画

要创建动画，必须初始化 ``lv_anim_t`` 类型的变量并使用 ``lv_anim_set_xxx()`` 函数进行配置

```c
lv_anim_t a;
lv_anim_set_exec_cb(&a, btn1, lv_obj_set_x);    /* 设置回调函数 */
lv_anim_set_time(&a, duration, delay);			/* 设置动画的持续时间和延迟 */
lv_anim_set_values(&a, start, end);             /* 设置动画的开始和结束值 */
lv_anim_set_path_cb(&a, lv_anim_path_linear);   /* 通过 lv_anim_path_xxx()函数或者自定义设置动画的路径(曲线) */
lv_anim_set_ready_cb(&a, ready_cb);             /* 动画已就绪的回调 */
lv_anim_set_playback(&a, wait_time);            /* 启用具有 wait_time 延迟的动画播放 */
lv_anim_set_repeat(&a, wait_time);              /* 以 wait_time 延迟启用动画的重复。 可以通过回放进行编译 */

lv_anim_create(&a);                             /* 创建动画 */
```
可以同时在同一变量上应用多个不同的动画。 例如，用 ``lv_obj_set_x`` 和 ``lv_obj_set_y`` 设置x和y坐标的动画。 但是，只有一个具有给定变量和函数对的动画。 因此，``lv_anim_create()`` 将删除已经存在的可变函数动画。

### 动画路径

动画的路径是可以确定的，动画一般是线性的，意味着开始和结束之间的当前值是线性变化的。路径是一项功能，可根据动画的当前状态计算下一个要设置的值。 LittlevGL 内置了以下路径：

- **lv_anim_path_linear **线性动画
- **lv_anim_path_step** 最后一步更改
- **lv_anim_path_ease_in** 开头缓慢
- **lv_anim_path_ease_out ** 最后慢
- **lv_anim_path_ease_in_out **在开始和结束时也很慢
- **lv_anim_path_overshoot** 超出最终值
- **lv_anim_path_bounce **从最终值反弹一点（碰撞边缘后回弹）

## 速度 VS 时间

动画的时间默认是可以设置的，在某些情况下，**动画速度**更加实用

``lv_anim_speed_to_time(speed, start, end)`` 函数计算从具有给定速度的起始值到达结束值所需的时间（以毫秒为单位）。 速度单位/秒。 例如， ``anim_speed_to_time(20, 0, 100)`` 将给出 5000 毫秒  

### 删除动画

可以通过 ``lv_anim_del(var, func)`` 删除动画，方法是提供动画变量及其动画函数

# 任务 Task

LittlevGL 内置任务系统，可以注册一个函数以使其被定期调用。任务是在 ``lv_task_handler()`` 中进行处理

任务是非抢占式的，意味这一个任务无法中断另一个任务，因此可以在任务中安全调用 LittlevGL 相关功能

## 创建任务

要创建新任务，请使用

```c
lv_task_create(task_cb,period,LV_TASK_PRIO_OFF/LOWEST/LOW/MID/HIGH/HIGHEST,user_data)
```

此函数会创建一个 ``lv_task_t *`` 的变量，用于保存和修改任务的参数。也可以使用 ``lv_task_create_basic()`` 函数创建一个无需任何参数的空任务。

任务回调函数原型

```c
void (*lv_task_cb_t)(lv_task_t *);
```

例如：

```c
/**
  * @brief 任务回调函数
  * @param task-任务对象
  * @retval	None
  * @note 该函数由用户创建任务并设置回调,然后由系统调用
*/
static void my_task_cb(lv_task_t * task)
{

	printf("my_task called \n");

}

...
    
/* 创建任务 */
lv_task_t * task = lv_task_create(my_task_cb, 500, LV_TASK_PRIO_MID, NULL);    
```

## 准备和复位

``lv_task_ready(task)`` 使任务在下一次调用 ``lv_task_handler()`` 的时候运行。

``lv_task_reset(task)`` 重置任务的周期，在任务周期过后，它将会被再次调用。

## 设置参数

在创建任务后可以修改任务的参数，创建空任务后可以为空任务设置参数，其他任务也可以在创建后修改参数，使用以下函数进行设置：

```
lv_task_set_cb(task,new_cb);
lv_task_set_period(task,new_period);
lv_task_set_proi(task,new_prio);
```
## 一次性任务

使用 ``lv_task_once(task)`` 可以使任务仅运行一次，然后自动删除。

## 测量空闲时间

可以使用 ``lv_task_get_idle()`` 获得空闲百分比时间，他仅仅标识 LittlevGL 的空闲，并非整个系统。

## 异步调用

在某些情况下我们不能直接执行某下操作。例如，我们需要在本次任务执行完毕以后删除某个对象。可以使用 ``lv_async_call(func,data_p)`` 使 ``func`` 函数在下一次任务调用的时候执行，``data_p`` 作为形参。

如果只想删除一个对象，而无需清理 ``my_screen_cleanup`` 中的任何内容，则可以使用 ``lv_obj_del_async``，它将在下次调用 ``lv_task_handler`` 时删除该对象。

# 绘图 Drawing

使用 LittlevGL，用户无需手动绘制任何内容。 只需创建对象（如按钮和标签）并更改它们，LittlevGL 就会刷新并重新绘制所需的内容。

LittlevGL 使用缓冲区，先将内容绘制到内部缓冲区，然后由硬件将内容绘制到显示屏或者显存上面，使用这种绘制方式由以下优点：

- 避免闪烁，以位图的形式绘制到显示屏将会降低闪烁
- 以缓存的方式将内容送到液晶屏，可以有效提升速度，例如 SPI 屏可以仅仅发送一次起始地址然后进行内容填充

## 缓冲类型

共有三种缓冲配置

- **一个缓冲区**：LittlevGL 将内容绘制到缓冲区，然后由硬件送到显示器。在这种情况下，较大的区域分多次绘制。如果只有很小的区域发生变化（例如按下按钮），则只会刷新那一部分区域。
- **两个小缓冲区**：LittlevGL 首先将内容绘制到某一个缓冲区，然后由 DMA 或者其他硬件加速器将这个缓冲区的内容在后台送到显示器，而 CPU 可以同时对另一个缓冲区进行绘制，这样使得显存的填充和内存缓存的绘制变得并行，加快速度。 如果缓冲区小于要刷新的区域，LittlevGL 将以类似于单缓冲区的块形式绘制显示内容。 
-  **两个屏幕大小的缓冲区** ：与两个小缓冲区相反，LittlevGL 将始终提供整个屏幕的内容，而不仅仅是块。这样，驱动程序可以简单地将帧缓冲区的地址更改为从 LittlevGL 接收的缓冲区。因此，当 MCU 具有 LCD / TFT 接口且帧缓冲区只是RAM中的一个位置时，此方法最有效。 但是这种方法需要的 RAM 非常大，在嵌入式系统中不一定可取。

## 刷新机制

GUI 有内容更新，需要重绘。例如，按下了按钮，滑动了滑块等。

LittlevGL 将更改后的对象的新旧区域保存到缓冲区中，称为无效区域缓冲区。为了优化，在某些情况下，对象不添加到缓冲区:

- 不添加隐藏对象
- 不添加完全超出其父对象的对象
- 父类之外的区域被裁剪到父类的区域
- 不添加其他屏幕上的对象

在每个 ``LV_DISP_DEF_REFR_PERIOD`` 中

- LittlevGL 检查无效区域并连接相邻区域或交叉区域
- 获取第一个连接区域（如果小于显示缓冲区），则将该区域的内容绘制到显示缓冲区。如果大于缓冲区，绘制尽可能多的内容
- 绘制区域后，从显示驱动程序调用 ``flush_cb`` 回调函数刷新到显示器
- 如果该区域大于缓冲区，重新绘制其余部分
- 对所有连接的区域执行相同的操作

三种绘制缓冲区之间的区别

1. 单缓冲 LittlevGL 需要等待当前绘制完成，也就是等待 ``lv_disp_flush_ready`` 后才能绘制下一部分。
2. 两个小缓冲 LittlevGL 在绘制第一个缓冲区的时候，可以调用硬件的 DMA 或者其他加速器在后台进行绘制，库同时进行填充缓冲区的操作，DMA 绘制完成后调用  ``lv_disp_flush_ready`` 如果此时填充缓冲区完成，再进行下一次的绘制
3. 两个屏幕大小的缓冲区 在调用第一个缓冲区 ``flush_cb`` 之后，如果显示为帧缓冲区的话。它的内容被复制到第二个缓冲区，所有的更改都被绘制在上面。



# 笔记

## 模态化

lvgl 没有将一个窗口或者控件模态化的 API，我们要处理模态化的过程是新建一个屏幕大小的对象，将其设置为半透明，然后将需要模态化的对象作为其子对象。在需要退出模态化的时候，也需要删除刚刚的父对象。

## 坐标

控件可以设置为相对坐标和绝对坐标。

