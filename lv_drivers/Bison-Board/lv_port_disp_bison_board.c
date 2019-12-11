/**
 * @file lv_port_disp_templ.c
 *
 */

 /*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp_bison_board.h"
#include "bsp.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
#if LV_USE_GPU
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa);
static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
                    const lv_area_t * fill_area, lv_color_t color);
#endif



/**********************
 *  STATIC VARIABLES
 **********************/
extern LTDC_HandleTypeDef hltdc;
DMA2D_HandleTypeDef  hdma2d;


static lv_disp_drv_t * my_disp_drv;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /* LittlevGL requires a buffer where it draws the objects. The buffer's has to be greater than 1 display row
     *
     * There are three buffering configurations:
     * 1. Create ONE buffer with some rows: 
     *      LittlevGL will draw the display's content here and writes it to your display
     * 
     * 2. Create TWO buffer with some rows: 
     *      LittlevGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LittlevGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     * 
     * 3. Create TWO screen-sized buffer: 
     *      Similar to 2) but the buffer have to be screen sized. When LittlevGL is ready it will give the
     *      whole frame to display. This way you only need to change the frame buffer's address instead of
     *      copying the pixels.
     * */

    /* Example for 1) */
    static lv_disp_buf_t disp_buf_1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * 100];                      /*A buffer for 10 rows*/
    lv_disp_buf_init(&disp_buf_1, buf1_1, NULL, LV_HOR_RES_MAX * 100);   /*Initialize the display buffer*/


    /* Example for 2) */
//    static lv_disp_buf_t disp_buf_2;
//    static lv_color_t buf2_1[LV_HOR_RES_MAX * 60];                        /*A buffer for 10 rows*/
//    static lv_color_t buf2_2[LV_HOR_RES_MAX * 60];                        /*An other buffer for 10 rows*/
//    lv_disp_buf_init(&disp_buf_2, buf2_1, buf2_2, LV_HOR_RES_MAX * 60);   /*Initialize the display buffer*/



//    /* Example for 3) */
//    static lv_disp_buf_t disp_buf_3;
//    static lv_color_t buf3_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*A screen sized buffer*/
//    static lv_color_t buf3_2[LV_HOR_RES_MAX * LV_VER_RES_MAX];            /*An other screen sized buffer*/
//    lv_disp_buf_init(&disp_buf_3, buf3_1, buf3_2, LV_HOR_RES_MAX * LV_VER_RES_MAX);   /*Initialize the display buffer*/


    /*-----------------------------------
     * Register the display in LittlevGL
     *----------------------------------*/

    lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.buffer = &disp_buf_1;
	
	
	__HAL_RCC_DMA2D_CLK_ENABLE();
	
	/* Set LTDC Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(DMA2D_IRQn, 15, 0);
  
	/* Enable LTDC Interrupt */
	HAL_NVIC_EnableIRQ(DMA2D_IRQn);
	

#if LV_USE_GPU
    /*Optionally add functions to access the GPU. (Only in buffered mode, LV_VDB_SIZE != 0)*/

    /*Blend two color array using opacity*/
    disp_drv.gpu_blend_cb = gpu_blend;

    /*Fill a memory array with a color*/
    disp_drv.gpu_fill_cb = gpu_fill;
#endif

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Initialize your display and the required peripherals. */
static void disp_init(void)
{
    /*You code here*/
}



/* Flush the content of the internal buffer the specific area on the display
 * You can use DMA or any hardware acceleration to do this operation in the background but
 * 'lv_disp_flush_ready()' has to be called when finished. */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
	uint32_t time_out;
	uint16_t offline;
	offline = LV_HOR_RES_MAX - (area->x2 - area->x1 + 1);
	DMA2D->CR      = 0x00000000UL;   //存储器到存储器模式
	/* Set up pointers */
	DMA2D->FGMAR   = (uint32_t)color_p;     //源地址              
	DMA2D->OMAR    = (uint32_t)hltdc.LayerCfg[0].FBStartAdress+2*(LV_HOR_RES_MAX*area->y1+area->x1);     //输出存储器地址                  
	DMA2D->FGOR	   = 0;					//前景层行偏移为0           
	DMA2D->OOR     = offline; 
	/* Set up pixel format */  
	DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_RGB565;  	//颜色格式为RGB565
	/*  Set up size */
	DMA2D->NLR     = (uint32_t)((area->x2 - area->x1 + 1) << 16) | (uint16_t)(area->y2 - area->y1 + 1); 

#if 1
	DMA2D->CR     |= (1 << 0);		//使能DMA2D
	/* Wait until transfer is done */
	while (DMA2D->CR & DMA2D_CR_START)
	{
		if(time_out++ >= 0XFFFFFFFF)break;
	}
    /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
#else
	DMA2D->CR     |= (1 << 0) | (1 << 9);		//使能DMA2D并且打开传输完成中断   
	my_disp_drv = disp_drv;
	
#endif
}

/**
  * @brief DMA2D中断函数
  * @param None
  * @retval	None
  */
void DMA2D_IRQHandler(void)
{
	if(DMA2D->ISR & (1<<1))	//传输完成中断
	{
		DMA2D->IFCR |= (1<<1);		//清楚传输完成中断
		/* Inform the graphics library that you are ready with the flushing */
		lv_disp_flush_ready(my_disp_drv);	
	}
	
	//printf("DMA2D_IRQHandler\r\n");
}



/*OPTIONAL: GPU INTERFACE*/
#if LV_USE_GPU

/* If your MCU has hardware accelerator (GPU) then you can use it to blend to memories using opacity
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void gpu_blend(lv_disp_drv_t * disp_drv, lv_color_t * dest, const lv_color_t * src, uint32_t length, lv_opa_t opa)
{
    /*It's an example code which should be done by your GPU*/
    uint32_t i;
    for(i = 0; i < length; i++) {
        dest[i] = lv_color_mix(dest[i], src[i], opa);
    }
	
}

/* If your MCU has hardware accelerator (GPU) then you can use it to fill a memory with a color
 * It can be used only in buffered mode (LV_VDB_SIZE != 0 in lv_conf.h)*/
static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
                    const lv_area_t * fill_area, lv_color_t color)
{
    /*It's an example code which should be done by your GPU*/
    uint32_t x, y;
    dest_buf += dest_width * fill_area->y1; /*Go to the first line*/

    for(y = fill_area->y1; y < fill_area->y2; y++) {
        for(x = fill_area->x1; x < fill_area->x2; x++) {
            dest_buf[x] = color;
        }
        dest_buf+=dest_width;    /*Go to the next line*/
    }
}

#endif  /*LV_USE_GPU*/

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
