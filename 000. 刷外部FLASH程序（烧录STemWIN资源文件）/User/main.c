/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2017-xx-xx
  * @brief   GPIO���--ʹ�ù̼������LED��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32F767 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f7xx.h"
#include "main.h"
#include "./led/bsp_led.h"
#include "./key/bsp_key.h" 
#include "./sdmmc/bsp_sdmmc_sd.h"
#include "./usart/bsp_debug_usart.h"
#include "./flash/bsp_qspi_flash.h"
/* FatFs includes component */
#include "./FATFS/ff.h"
#include "./FATFS/ff_gen_drv.h"
#include "./FATFS/sd_diskio.h"
#include "./res_mgr/RES_MGR.h"

/**
  ******************************************************************************
  *                              �������
  ******************************************************************************
  */
char SDPath[4]; /* SD�߼�������·�� */
extern FATFS sd_fs;	
FRESULT res_sd;                /* �ļ�������� */
extern char src_dir[];

extern FATFS flash_fs;
extern Diskio_drvTypeDef  SD_Driver;

/**
  * @brief AP6181_PDN_INIT
  * @note ��ֹWIFIģ��
  * @param ��
  * @retval ��
  */
static void WIFI_PDN_INIT(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStruct;
	/*ʹ������ʱ��*/	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*ѡ��Ҫ���Ƶ�GPIO����*/															   
	GPIO_InitStruct.Pin = GPIO_PIN_13;	
	/*�������ŵ��������Ϊ�������*/
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;      
	/*��������Ϊ����ģʽ*/
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	/*������������Ϊ���� */   
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST; 
	/*���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO*/
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);	
	/*����WiFiģ��*/
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);  
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{ 
  /* ϵͳʱ�ӳ�ʼ����216 MHz */
  SystemClock_Config();

  /* LED �˿ڳ�ʼ�� */
  LED_GPIO_Config();
  
  /* ����WiFiģ�� */
  WIFI_PDN_INIT();
  
  /* ��ʼ��USART1 ����ģʽΪ 115200 8-N-1 */
  DEBUG_USART_Config();	
  
  BSP_QSPI_Init();
  
  Key_GPIO_Config();
  
  QSPI_FLASH_Init();
  
  //�����������������̷�
  FATFS_LinkDriver(&SD_Driver, SDPath);
  //���ⲿSD�������ļ�ϵͳ���ļ�ϵͳ����ʱ���SD����ʼ��
  res_sd = f_mount(&sd_fs,"0:",1);  

  if(res_sd != FR_OK)
  {
    printf("f_mount ERROR!������������SD��Ȼ�����¸�λ������!");
    LED_RED;
    while(1);
  }    
    
  printf("\r\n ��һ��KEY1��ʼ��д�ֿⲢ�����ļ���FLASH�� \r\n"); 
  printf("\r\n ע��ò������FLASH��ԭ���ݻᱻɾ������ \r\n"); 

  while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0);
  while(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1); 
  printf("\r\n ���ڽ�����Ƭ������ʱ��ܳ��������ĵȺ�...\r\n"); 
  
  BSP_QSPI_Erase_Chip();
  
  /* ������¼Ŀ¼��Ϣ�ļ� */
  Make_Catalog(src_dir,0);

  /* ��¼ Ŀ¼��Ϣ��FLASH*/
  Burn_Catalog();
   /* ���� Ŀ¼ ��¼������FLASH*/
  Burn_Content();
  /* У����¼������ */
  Check_Resource();    
  /* ������ɣ�ͣ�� */
  while(1)
  {
  } 
}

/**
  * @brief  System Clock ����
  *         system Clock �������� : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  ��
  * @retval ��
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* ʹ��HSE������HSEΪPLL��ʱ��Դ������PLL�ĸ��ַ�Ƶ����M N P Q 
	 * PLLCLK = HSE/M*N/P = 25M / 25 *432 / 2 = 216M
	 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* ���� OverDrive ģʽ�Դﵽ216MƵ��  */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* ѡ��PLLCLK��ΪSYSCLK�������� HCLK, PCLK1 and PCLK2 ��ʱ�ӷ�Ƶ���� 
	 * SYSCLK = PLLCLK     = 216M
	 * HCLK   = SYSCLK / 1 = 216M
	 * PCLK2  = SYSCLK / 2 = 108M
	 * PCLK1  = SYSCLK / 4 = 54M
	 */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
	/* ��HAL_RCC_ClockConfig��������ͬʱ��ʼ������ϵͳ��ʱ��systick������Ϊ1ms�ж�һ�� */
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }  
}

/*********************************************END OF FILE**********************/

