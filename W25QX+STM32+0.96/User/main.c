/************************************************************************************
//�����������������ҡ����Ա�����: https://shop149406681.taobao.com/?spm=a1z10.1-c.0.0.64cb457fKzgKea 
//�Ա����������ؼ��ʣ�K_A39_012
//  �� �� ��   : v1.0
//  ��    ��   : ����������
//  ����Ⱥ :			 1041406448�����������������ע���棩
//    CSDN  ��������������Դ�����б����н���˵����   :��Ƭ��������˹�(�����ؼ��ʣ�K_A39_012)
//    BILIBILI����ʾ��Ƶ�� :����������(�����ؼ��ʣ�K_A39_012)
//  ��������   : 2021-6-21
//  ����޸�   : 2021-11-21
//  ��������   : W25Q32ģ����Գ���
//  ��������   : STM32F103C8T6   ����8M  ϵͳʱ��72M
����
W25Q32ģ��-------------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
CS-------------------------------------PA4 //
SCK------------------------------------PA5 //	
MISO-----------------------------------PA6 //	DO
MOSI-----------------------------------PA7 //	DI

OLED0.96ģ��---------------------------STM32F103C8T6
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

/* ��ȡ�������ĳ��� */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

     

/* ���ͻ�������ʼ�� */
uint8_t Tx_Buffer[] = "QQ:1795190213 ";

uint8_t Rx_Buffer[BufferSize];

__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;

// ����ԭ������
void Delay(__IO uint32_t nCount);
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);


int main(void)
{

		DelayInit();
		OLED_Init();
		OLED_Clear();
		USART_Config();

		/* 8M����flash W25Q64��ʼ�� */
		SPI_FLASH_Init();

		/* ��ȡ Flash Device ID */
		DeviceID = SPI_FLASH_ReadDeviceID();	
		Delay( 200 );

		/* ��ȡ SPI Flash ID */
		FlashID = SPI_FLASH_ReadID();	
		printf("\r\n FlashID is 0x%X \r\n Device ID is 0x%X\r\n", FlashID, DeviceID);
	

		/* ���� SPI Flash ID */
		if (FlashID == sFLASH_ID)
		{	
				printf("\r\n ��⵽����flash W25Q64 !\r\n");

				/* ������Ҫд��� SPI FLASH ������FLASHд��ǰҪ�Ȳ��� */
				// �������4K����һ����������������С��λ������
				SPI_FLASH_SectorErase(FLASH_SectorToErase);	 	 

				/* �����ͻ�����������д��flash�� */
				// ����дһҳ��һҳ�Ĵ�СΪ256���ֽ�
				SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);		
				printf("\r\n д�������Ϊ��%s \r\t", Tx_Buffer);
				OLED_ShowString(0,0,"write:",16);
				OLED_ShowString(0,2,Tx_Buffer,16);
			
				/* ���ո�д������ݶ������ŵ����ջ������� */
				SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
				printf("\r\n ����������Ϊ��%s \r\n", Rx_Buffer);
			
				OLED_ShowString(0,4,"Read:",16);
				OLED_ShowString(0,6,Rx_Buffer,16);
				/* ���д�������������������Ƿ���� */
				TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);

				if( PASSED == TransferStatus1 )
				{ 

						printf("\r\n 8M����flash(W25Q64)���Գɹ�!\n\r");
				}
				else
				{        

						printf("\r\n 8M����flash(W25Q64)����ʧ��!\n\r");
				}
		}// if (FlashID == sFLASH_ID)
		else// if (FlashID == sFLASH_ID)
		{ 

				printf("\r\n ��ȡ���� W25Q64 ID!\n\r");
		}
		while(1)
		{

		}
}
/*
 * ��������Buffercmp
 * ����  ���Ƚ������������е������Ƿ����
 * ����  ��-pBuffer1     src������ָ��
 *         -pBuffer2     dst������ָ��
 *         -BufferLength ����������
 * ���  ����
 * ����  ��-PASSED pBuffer1 ����   pBuffer2
 *         -FAILED pBuffer1 ��ͬ�� pBuffer2
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