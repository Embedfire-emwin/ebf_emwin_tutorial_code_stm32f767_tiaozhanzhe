#ifndef __BSP_LCD_H
#define	__BSP_LCD_H


/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx.h"
#include "./sdram/bsp_sdram.h"
#include "./fonts/fonts.h"

/*����Һ�������ֲ�Ĳ�������*/
#define HBP  46		//HSYNC�����Ч����
#define VBP  23		//VSYNC�����Ч����

#define HSW   1		//HSYNC���
#define VSW   1		//VSYNC���

#define HFP  22		//HSYNCǰ����Ч����
#define VFP  22		//VSYNCǰ����Ч����

/* LCD Size (Width and Height) */
#define  LCD_PIXEL_WIDTH          ((uint16_t)800)
#define  LCD_PIXEL_HEIGHT         ((uint16_t)480)  

/** 
  * @brief  LCD FB_StartAddress  
  */
#define LCD_FB_START_ADDRESS       ((uint32_t)0xD0000000)

/** 
  * @brief  LCD status structure definition  
  */     
#define LCD_OK                 ((uint8_t)0x00)
#define LCD_ERROR              ((uint8_t)0x01)
#define LCD_TIMEOUT            ((uint8_t)0x02)



//��ɫ������
#define LTDC_R0_GPIO_PORT        	GPIOH
#define LTDC_R0_GPIO_CLK_ENABLE()   __GPIOH_CLK_ENABLE()
#define LTDC_R0_GPIO_PIN         	GPIO_PIN_2
#define LTDC_R0_AF			        GPIO_AF14_LTDC

#define LTDC_R1_GPIO_PORT        	GPIOH
#define LTDC_R1_GPIO_CLK_ENABLE()   __GPIOH_CLK_ENABLE()
#define LTDC_R1_GPIO_PIN         	GPIO_PIN_3
#define LTDC_R1_AF			        GPIO_AF14_LTDC

#define LTDC_R2_GPIO_PORT        	GPIOH
#define LTDC_R2_GPIO_CLK_ENABLE()	__GPIOH_CLK_ENABLE()
#define LTDC_R2_GPIO_PIN         	GPIO_PIN_8
#define LTDC_R2_AF			        GPIO_AF14_LTDC

#define LTDC_R3_GPIO_PORT        	GPIOB
#define LTDC_R3_GPIO_CLK_ENABLE()	__GPIOB_CLK_ENABLE()
#define LTDC_R3_GPIO_PIN         	GPIO_PIN_0
#define LTDC_R3_AF			        GPIO_AF9_LTDC

#define LTDC_R4_GPIO_PORT        	GPIOA
#define LTDC_R4_GPIO_CLK_ENABLE()	__GPIOA_CLK_ENABLE()
#define LTDC_R4_GPIO_PIN         	GPIO_PIN_11
#define LTDC_R4_AF			        GPIO_AF14_LTDC

#define LTDC_R5_GPIO_PORT        	GPIOA
#define LTDC_R5_GPIO_CLK_ENABLE()	__GPIOA_CLK_ENABLE()
#define LTDC_R5_GPIO_PIN         	GPIO_PIN_12
#define LTDC_R5_AF			        GPIO_AF14_LTDC

#define LTDC_R6_GPIO_PORT        	GPIOB
#define LTDC_R6_GPIO_CLK_ENABLE()	__GPIOB_CLK_ENABLE()
#define LTDC_R6_GPIO_PIN         	GPIO_PIN_1
#define LTDC_R6_AF			        GPIO_AF9_LTDC

#define LTDC_R7_GPIO_PORT        	GPIOG
#define LTDC_R7_GPIO_CLK_ENABLE()	__GPIOG_CLK_ENABLE()
#define LTDC_R7_GPIO_PIN         	GPIO_PIN_6
#define LTDC_R7_AF			        GPIO_AF14_LTDC
//��ɫ������
#define LTDC_G0_GPIO_PORT        	GPIOE
#define LTDC_G0_GPIO_CLK_ENABLE()	__GPIOE_CLK_ENABLE()
#define LTDC_G0_GPIO_PIN         	GPIO_PIN_5
#define LTDC_G0_AF			        GPIO_AF14_LTDC

#define LTDC_G1_GPIO_PORT        	GPIOE
#define LTDC_G1_GPIO_CLK_ENABLE()	__GPIOE_CLK_ENABLE()
#define LTDC_G1_GPIO_PIN         	GPIO_PIN_6
#define LTDC_G1_AF			        GPIO_AF14_LTDC

#define LTDC_G2_GPIO_PORT        	GPIOH
#define LTDC_G2_GPIO_CLK_ENABLE() 	__GPIOH_CLK_ENABLE()
#define LTDC_G2_GPIO_PIN         	GPIO_PIN_13
#define LTDC_G2_AF			        GPIO_AF14_LTDC

#define LTDC_G3_GPIO_PORT        	GPIOG
#define LTDC_G3_GPIO_CLK_ENABLE()	__GPIOG_CLK_ENABLE()
#define LTDC_G3_GPIO_PIN         	GPIO_PIN_10
#define LTDC_G3_AF			        GPIO_AF9_LTDC

#define LTDC_G4_GPIO_PORT        	GPIOH
#define LTDC_G4_GPIO_CLK_ENABLE()	__GPIOH_CLK_ENABLE()
#define LTDC_G4_GPIO_PIN         	GPIO_PIN_15
#define LTDC_G4_AF			        GPIO_AF14_LTDC

#define LTDC_G5_GPIO_PORT        	GPIOI
#define LTDC_G5_GPIO_CLK_ENABLE()	__GPIOI_CLK_ENABLE()
#define LTDC_G5_GPIO_PIN         	GPIO_PIN_0
#define LTDC_G5_AF			        GPIO_AF14_LTDC

#define LTDC_G6_GPIO_PORT        	GPIOC
#define LTDC_G6_GPIO_CLK_ENABLE()	__GPIOC_CLK_ENABLE()
#define LTDC_G6_GPIO_PIN         	GPIO_PIN_7
#define LTDC_G6_AF			        GPIO_AF14_LTDC

#define LTDC_G7_GPIO_PORT        	GPIOI
#define LTDC_G7_GPIO_CLK_ENABLE() 	__GPIOI_CLK_ENABLE()
#define LTDC_G7_GPIO_PIN         	GPIO_PIN_2
#define LTDC_G7_AF			        GPIO_AF14_LTDC

//��ɫ������
#define LTDC_B0_GPIO_PORT        	GPIOE
#define LTDC_B0_GPIO_CLK_ENABLE()  	__GPIOE_CLK_ENABLE()
#define LTDC_B0_GPIO_PIN         	GPIO_PIN_4
#define LTDC_B0_AF			        GPIO_AF14_LTDC

#define LTDC_B1_GPIO_PORT        	GPIOG
#define LTDC_B1_GPIO_CLK_ENABLE() 	__GPIOG_CLK_ENABLE()
#define LTDC_B1_GPIO_PIN         	GPIO_PIN_12
#define LTDC_B1_AF			        GPIO_AF14_LTDC

#define LTDC_B2_GPIO_PORT        	GPIOD
#define LTDC_B2_GPIO_CLK_ENABLE()  	__GPIOD_CLK_ENABLE()
#define LTDC_B2_GPIO_PIN         	GPIO_PIN_6
#define LTDC_B2_AF			        GPIO_AF14_LTDC

#define LTDC_B3_GPIO_PORT        	GPIOG
#define LTDC_B3_GPIO_CLK_ENABLE() 	__GPIOD_CLK_ENABLE()
#define LTDC_B3_GPIO_PIN         	GPIO_PIN_11
#define LTDC_B3_AF			        GPIO_AF14_LTDC

#define LTDC_B4_GPIO_PORT        	GPIOI
#define LTDC_B4_GPIO_CLK_ENABLE() 	__GPIOI_CLK_ENABLE()
#define LTDC_B4_GPIO_PIN         	GPIO_PIN_4
#define LTDC_B4_AF			        GPIO_AF14_LTDC

#define LTDC_B5_GPIO_PORT        	GPIOA
#define LTDC_B5_GPIO_CLK_ENABLE()	__GPIOA_CLK_ENABLE()
#define LTDC_B5_GPIO_PIN         	GPIO_PIN_3
#define LTDC_B5_AF			        GPIO_AF14_LTDC

#define LTDC_B6_GPIO_PORT        	GPIOB
#define LTDC_B6_GPIO_CLK_ENABLE() 	__GPIOB_CLK_ENABLE()
#define LTDC_B6_GPIO_PIN         	GPIO_PIN_8
#define LTDC_B6_AF			        GPIO_AF14_LTDC

#define LTDC_B7_GPIO_PORT        	GPIOB
#define LTDC_B7_GPIO_CLK_ENABLE() 	__GPIOB_CLK_ENABLE()
#define LTDC_B7_GPIO_PIN         	GPIO_PIN_9
#define LTDC_B7_AF			        GPIO_AF14_LTDC

//�����ź���
/*����ʱ��CLK*/
#define LTDC_CLK_GPIO_PORT              GPIOG
#define LTDC_CLK_GPIO_CLK_ENABLE()      __GPIOG_CLK_ENABLE()
#define LTDC_CLK_GPIO_PIN               GPIO_PIN_7
#define LTDC_CLK_AF			            GPIO_AF14_LTDC
/*ˮƽͬ���ź�HSYNC*/
#define LTDC_HSYNC_GPIO_PORT            GPIOI
#define LTDC_HSYNC_GPIO_CLK_ENABLE()    __GPIOI_CLK_ENABLE()
#define LTDC_HSYNC_GPIO_PIN             GPIO_PIN_10
#define LTDC_HSYNC_AF			        GPIO_AF14_LTDC
/*��ֱͬ���ź�VSYNC*/
#define LTDC_VSYNC_GPIO_PORT            GPIOI
#define LTDC_VSYNC_GPIO_CLK_ENABLE()    __GPIOI_CLK_ENABLE()
#define LTDC_VSYNC_GPIO_PIN             GPIO_PIN_9
#define LTDC_VSYNC_AF			        GPIO_AF14_LTDC

/*����ʹ���ź�DE*/
#define LTDC_DE_GPIO_PORT               GPIOF
#define LTDC_DE_GPIO_CLK_ENABLE()       __GPIOF_CLK_ENABLE()
#define LTDC_DE_GPIO_PIN                GPIO_PIN_10
#define LTDC_DE_AF			            GPIO_AF14_LTDC
/*Һ����ʹ���ź�DISP���ߵ�ƽʹ��*/
#define LTDC_DISP_GPIO_PORT             GPIOD
#define LTDC_DISP_GPIO_CLK_ENABLE()     __GPIOD_CLK_ENABLE()
#define LTDC_DISP_GPIO_PIN              GPIO_PIN_4
/*Һ���������źţ��ߵ�ƽʹ��*/
#define LTDC_BL_GPIO_PORT               GPIOD
#define LTDC_BL_GPIO_CLK_ENABLE()       __GPIOD_CLK_ENABLE()
#define LTDC_BL_GPIO_PIN                GPIO_PIN_7

void LCD_Init(void);
void LCD_LayerInit(uint16_t LayerIndex, uint32_t FB_Address,uint32_t PixelFormat);

#endif /* __BSP_LCD_H */
