/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.44                          *
*        Compiled Nov 10 2017, 08:53:57                              *
*        (c) 2017 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/
/* FreeRTOS头文件 */
#include "FreeRTOS.h"
#include "task.h"
/* STemWIN头文件 */
#include "ScreenShot.h"
#include "MainTask.h"
#include "./usart/bsp_debug_usart.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

/*********************************************************************
*
*       Types
*
**********************************************************************
*/


/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
char *_acbuffer = NULL;

UINT    f_num;
extern FATFS   fs;								/* FatFs文件系统对象 */
extern FIL     file;							/* file objects */
extern FRESULT result; 
extern DIR     dir;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/**
  * @brief 从存储器中读取数据
  * @note 无
  * @param 
  * @retval NumBytesRead：读到的字节数
  */
static int _GetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off)
{
	U8 *pData;
	FIL *Picfile;
	UINT NumBytesRead;
	static int FileAddr = 0;
	
	pData = (U8 *)*ppData;
	Picfile = (FIL *)p;
	
	if(Off == 1) FileAddr = 0;
	else FileAddr = Off;
	result = f_lseek(Picfile, FileAddr);
	
	/* 进入临界段 */
	taskENTER_CRITICAL();
	result = f_read(Picfile, pData, NumBytesReq, &NumBytesRead);
	/* 退出临界段 */
	taskEXIT_CRITICAL();
	
	return NumBytesRead;
}

/**
  * @brief 直接从存储器中绘制PNG图片数据
  * @note 无
  * @param sFilename：需要加载的图片名
  * @retval 无
  */
static void ShowPNGEx(const char *sFilename, int x0, int y0)
{
	/* 进入临界段 */
	taskENTER_CRITICAL();
	/* 打开图片 */
	result = f_open(&file, sFilename, FA_READ);
	if ((result != FR_OK))
	{
		printf("文件打开失败！\r\n");
	}
	/* 退出临界段 */
	taskEXIT_CRITICAL();
	
	GUI_PNG_DrawEx(_GetData, &file, x0, y0);
	
	/* 读取完毕关闭文件 */
	f_close(&file);
}

/**
  * @brief 加载PNG图片到内存中并绘制
  * @note 无
  * @param sFilename：需要加载的图片名
  * @retval 无
  */
static void ShowPNG(const char *sFilename, int x0, int y0)
{
	WM_HMEM hMem;
	
	/* 进入临界段 */
	taskENTER_CRITICAL();
	/* 打开图片 */
	result = f_open(&file, sFilename, FA_READ);
	if ((result != FR_OK))
	{
		printf("文件打开失败！\r\n");
		_acbuffer[0]='\0';
	}
	
	/* 申请一块动态内存空间 */
	hMem = GUI_ALLOC_AllocZero(file.fsize);
	/* 转换动态内存的句柄为指针 */
	_acbuffer = GUI_ALLOC_h2p(hMem);

	/* 读取图片数据到动态内存中 */
	result = f_read(&file, _acbuffer, file.fsize, &f_num);
	if(result != FR_OK)
	{
		printf("文件读取失败！\r\n");
	}
	/* 读取完毕关闭文件 */
	f_close(&file);
	/* 退出临界段 */
	taskEXIT_CRITICAL();
	
	GUI_PNG_Draw(_acbuffer, file.fsize, x0, y0);

	/* 释放内存 */
	GUI_ALLOC_Free(hMem);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/**
  * @brief GUI主任务
  * @note 无
  * @param 无
  * @retval 无
  */
void MainTask(void)
{
  int i = 0;
	
  GUI_SetBkColor(GUI_LIGHTCYAN);
  GUI_Clear();
  
	GUI_SetTextMode(GUI_TM_TRANS | GUI_TM_XOR);
	GUI_SetFont(GUI_FONT_24B_ASCII);
	
	while (1)
	{
    i++;
    
    switch(i)
    {
      case 1:
        GUI_DispStringHCenterAt("ShowPNGEx", LCD_GetXSize()/2, 10);
		    ShowPNGEx("0:/image/野火.png", 80, 153);
        break;
      case 2:
        GUI_DispStringHCenterAt("ShowPNG", LCD_GetXSize()/2, 10);
		    ShowPNG("0:/image/one_punch_man.png", 45, 80);
		    ShowPNG("0:/image/pokemon.png", 405, 60);
        break;
      case 3:
        GUI_DispStringHCenterAt("ShowPNG", LCD_GetXSize()/2, 10);
        ShowPNG("0:/image/滑稽.png", 280, 100);
        break;
      default:
        i = 0;
        break;
    }
		GUI_Delay(1000);
		GUI_Clear(); 
	}
}

/*************************** End of file ****************************/
