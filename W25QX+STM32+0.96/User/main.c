/************************************************************************************
//（店名“众明工作室”）淘宝链接: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//淘宝店内搜索关键词：K_A39_012
//  版 本 号   : v1.0
//  作    者   : 众明工作室
//  交流群 :			 1041406448（其它更多资料请关注公告）
//    CSDN  （基本参数，资源更新列表，所有接线说明）   :单片机代码搬运工(搜索关键词：K_A39_012)
//    BILIBILI（演示视频） :众明工作室(搜索关键词：K_A39_012)
//  生成日期   : 2021-6-21
//  最近修改   : 2021-11-21
//  功能描述   : W25Q32模块测试程序
//  测试条件   : STM32F103C8T6   晶振8M  系统时钟72M
接线
W25Q32模块-------------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
CS-------------------------------------PA4 //
SCK------------------------------------PA5 //	
MISO-----------------------------------PA6 //	DO
MOSI-----------------------------------PA7 //	DI

OLED0.96模块---------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
SCL------------------------------------PB8 //
SDA------------------------------------PB9 //	
*************************************************************************************/


#include "oled.h"
#include "delay.h"
#include "W25QX.h"
#include "bsp_usart.h"
#include <stdio.h>

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* 获取缓冲区的长度 */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

     

/* 发送缓冲区初始化 */
uint8_t Tx_Buffer[] = "QQ:1795190213 ";

uint8_t Rx_Buffer[BufferSize];

__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;

// 函数原型声明
void Delay(__IO uint32_t nCount);
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);


int main(void)
{

		DelayInit();
		OLED_Init();
		OLED_Clear();
		USART_Config();

		/* 8M串行flash W25Q64初始化 */
		SPI_FLASH_Init();

		/* 获取 Flash Device ID */
		DeviceID = SPI_FLASH_ReadDeviceID();	
		Delay( 200 );

		/* 获取 SPI Flash ID */
		FlashID = SPI_FLASH_ReadID();	
		printf("\r\n FlashID is 0x%X \r\n Device ID is 0x%X\r\n", FlashID, DeviceID);
	

		/* 检验 SPI Flash ID */
		if (FlashID == sFLASH_ID)
		{	
				printf("\r\n 检测到串行flash W25Q64 !\r\n");

				/* 擦除将要写入的 SPI FLASH 扇区，FLASH写入前要先擦除 */
				// 这里擦除4K，即一个扇区，擦除的最小单位是扇区
				SPI_FLASH_SectorErase(FLASH_SectorToErase);	 	 

				/* 将发送缓冲区的数据写到flash中 */
				// 这里写一页，一页的大小为256个字节
				SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);		
				printf("\r\n 写入的数据为：%s \r\t", Tx_Buffer);
				OLED_ShowString(0,0,"write:",16);
				OLED_ShowString(0,2,Tx_Buffer,16);
			
				/* 将刚刚写入的数据读出来放到接收缓冲区中 */
				SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
				printf("\r\n 读出的数据为：%s \r\n", Rx_Buffer);
			
				OLED_ShowString(0,4,"Read:",16);
				OLED_ShowString(0,6,Rx_Buffer,16);
				/* 检查写入的数据与读出的数据是否相等 */
				TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);

				if( PASSED == TransferStatus1 )
				{ 

						printf("\r\n 8M串行flash(W25Q64)测试成功!\n\r");
				}
				else
				{        

						printf("\r\n 8M串行flash(W25Q64)测试失败!\n\r");
				}
		}// if (FlashID == sFLASH_ID)
		else// if (FlashID == sFLASH_ID)
		{ 

				printf("\r\n 获取不到 W25Q64 ID!\n\r");
		}
		while(1)
		{

		}
}
/*
 * 函数名：Buffercmp
 * 描述  ：比较两个缓冲区中的数据是否相等
 * 输入  ：-pBuffer1     src缓冲区指针
 *         -pBuffer2     dst缓冲区指针
 *         -BufferLength 缓冲区长度
 * 输出  ：无
 * 返回  ：-PASSED pBuffer1 等于   pBuffer2
 *         -FAILED pBuffer1 不同于 pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}