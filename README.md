# K_A39_012_based_on_the_STM32_driver_W25Q32_module_read_and_write_data-
Based on STM32 drive W25Q32 module read and write data serial port +OLED0.96 display

此程序是用STM32F103C8T6驱动 W25Q32 并用OLED 0.96(SSD1603驱动芯片)显示和串口打印 基本说明

This program uses STM32F103C8T6  to drive W25Q32 and use OLED 0.96 (SSD1603 drive chip) to display and print and print the serial port.

这里有种英文说明 前部分为中文说明 后半部分为英文说明 请悉知

Here is a kind of English description in the previous part of the Chinese description.

如果发现程序有BUG 或者又可以改进的地方 欢迎联系我们

If you find that the program has bugs or can be improved, please contact us

- [所有资源导航](#所有资源导航)
- [一、资源说明](#一资源说明)
- [二、基本参数](#二基本参数)
  * [参数](#参数)
  * [引脚说明](#引脚说明)
- [三、驱动说明](#三驱动说明)
  * [时序](#时序)
  * [对应程序](#对应程序)
- [四、部分代码说明](#四部分代码说明)
  * [1、接线引脚定义](#1接线引脚定义)
    + [1.2.STM32F103C8T6+W25Q32](#1.2STM32F103C8T6+W25Q32)
- [五、基础知识学习与相关资料下载](#五基础知识学习与相关资料下载)
- [六、视频效果展示与程序资料获取](#六视频效果展示与程序资料获取)
- [七、注意事项](#七注意事项)
- [八、接线说明](#八接线说明)
  * [STM32F103C8T6](#stm32f103c8t6)
- [All resource navigation](#all-resource-navigation)
- [1. Resource description](#1-resource-description)
- [2. basic parameters](#2-basic-parameters)
  * [parameter](#parameter)
  * [pin explanation](#pin-explanation)
- [3. Drive Instructions](#3-drive-instructions)
  * [Sequential chart](#sequential-chart)
  * [corresponding program](#corresponding-program)
- [4. Partial code description](#4-partial-code-description)
  * [1.1. Wiring pin definition](#11-wiring-pin-definition)
    + [1.1.2, STM32F103C8T6+W25Q32 module](#112--stm32f103c8t6-w25q32-module)
- [5. Basic knowledge learning and related information download](#5-basic-knowledge-learning-and-related-information-download)
- [6. Video effect display and program data acquisition](#6-video-effect-display-and-program-data-acquisition)
- [7. Notice](#7-notice)
- [8. Wiring description](#8-wiring-description)
  * [STM32F103C8T6](#stm32f103c8t6-1)


@[TOC](K_A39_012  基于STM32驱动W25Q32 模块读写数据 串口+OLED0.96显示)

@[TOC](Based on the STM32 driver W25Q32 module read and write data serial port+OLED0.96 display)

![请添加图片描述](https://img-blog.csdnimg.cn/e00ccd57499f4cd8883cec21fb29a138.jpeg)

#  所有资源导航
[**其他资料目录**](https://blog.csdn.net/lfmnlxx79691557/article/details/128323460?spm=1001.2014.3001.5501)     	直戳跳转
# 一、资源说明
| 单片机型号 | 测试条件|模块名称 |代码功能 |
|:--------:| -------------:| -------------:|-------------:|
| STM32F103C8T6 | 晶振8M/系统时钟72M |W25Q32 模块 |STM32F103C8T6驱动W25Q32 模块 串口与OLED0.96双显示 |


# 二、基本参数
## 参数


![请添加图片描述](https://img-blog.csdnimg.cn/c454ade430064f6e9a23a0e04f45c445.png)

## 引脚说明

W25Q32 模块| 	引脚说明
-------- | -----
VCC	|正极 3.3V供电
GND	|GND 电源负极
MISO	|SPI总线 主机输入从机输出引脚
MOSI	|SPI总线 主机输出从机输入引脚
SCK	|SPI总线  时钟引脚
CS	|片选信号脚

# 三、驱动说明

## 时序

![请添加图片描述](https://img-blog.csdnimg.cn/3e6371eaeeac4545ae63650e3a9a1cca.png)

## 对应程序:

```javascript
SPI初始化程序
/**
  * @brief  SPI_FLASH初始化
  * @param  无
  * @retval 无
  */
void SPI_FLASH_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	/* 使能SPI时钟 */
	FLASH_SPI_APBxClock_FUN ( FLASH_SPI_CLK, ENABLE );
	
	/* 使能SPI引脚相关的时钟 */
 	FLASH_SPI_CS_APBxClock_FUN ( FLASH_SPI_CS_CLK|FLASH_SPI_SCK_CLK|
																	FLASH_SPI_MISO_PIN|FLASH_SPI_MOSI_PIN, ENABLE );
	
  /* 配置SPI的 CS引脚，普通IO即可 */
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(FLASH_SPI_CS_PORT, &GPIO_InitStructure);
	
  /* 配置SPI的 SCK引脚*/
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(FLASH_SPI_SCK_PORT, &GPIO_InitStructure);

  /* 配置SPI的 MISO引脚*/
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
  GPIO_Init(FLASH_SPI_MISO_PORT, &GPIO_InitStructure);

  /* 配置SPI的 MOSI引脚*/
  GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
  GPIO_Init(FLASH_SPI_MOSI_PORT, &GPIO_InitStructure);

  /* 停止信号 FLASH: CS引脚高电平*/
  SPI_FLASH_CS_HIGH();

  /* SPI 模式配置 */
  // FLASH芯片 支持SPI模式0及模式3，据此设置CPOL CPHA
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(FLASH_SPIx , &SPI_InitStructure);

  /* 使能 SPI  */
  SPI_Cmd(FLASH_SPIx , ENABLE);
	
}
```
# 四、部分代码说明
## 1、接线引脚定义
需要自定义引脚可在此处更改，STM32要自定义引脚的话也要注意引脚时钟使能的更改

### 1.2、STM32F103C8T6+W25Q32 模块
```javascript

#define      FLASH_SPIx                        SPI1
#define      FLASH_SPI_APBxClock_FUN          RCC_APB2PeriphClockCmd
#define      FLASH_SPI_CLK                     RCC_APB2Periph_SPI1

//CS(NSS)引脚 片选选普通GPIO即可
#define      FLASH_SPI_CS_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define      FLASH_SPI_CS_CLK                  RCC_APB2Periph_GPIOA    
#define      FLASH_SPI_CS_PORT                 GPIOA
#define      FLASH_SPI_CS_PIN                  GPIO_Pin_4

//SCK引脚
#define      FLASH_SPI_SCK_APBxClock_FUN      RCC_APB2PeriphClockCmd
#define      FLASH_SPI_SCK_CLK                 RCC_APB2Periph_GPIOA   
#define      FLASH_SPI_SCK_PORT                GPIOA   
#define      FLASH_SPI_SCK_PIN                 GPIO_Pin_5
//MISO引脚
#define      FLASH_SPI_MISO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      FLASH_SPI_MISO_CLK                RCC_APB2Periph_GPIOA    
#define      FLASH_SPI_MISO_PORT               GPIOA 
#define      FLASH_SPI_MISO_PIN                GPIO_Pin_6
//MOSI引脚
#define      FLASH_SPI_MOSI_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define      FLASH_SPI_MOSI_CLK                RCC_APB2Periph_GPIOA    
#define      FLASH_SPI_MOSI_PORT               GPIOA 
#define      FLASH_SPI_MOSI_PIN                GPIO_Pin_7


```

# 五、基础知识学习与相关资料下载

1、[STC89C52RC程序下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127114912?spm=1001.2014.3001.5501)			直戳跳转

2、STM32F103C8T6程序下载		

(1)[串口下载](https://blog.csdn.net/lfmnlxx79691557/article/details/122862183?spm=1001.2014.3001.5501)                直戳跳转 

(2)[ST-LINK下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127140554?spm=1001.2014.3001.5501)             直戳跳转

(3)[J-LINK下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127140823?spm=1001.2014.3001.5501)              直戳跳转

(4)[DAP-LINK下载](https://blog.csdn.net/lfmnlxx79691557/article/details/127141244?spm=1001.2014.3001.5501)            直戳跳转


3、[OLED0.96程序说明](https://blog.csdn.net/lfmnlxx79691557/article/details/127208887?spm=1001.2014.3001.5501)			直戳跳转

4、串口助手下载与使用

(1)[安信可调试助手使用](https://blog.csdn.net/lfmnlxx79691557/article/details/128335660?spm=1001.2014.3001.5502) 						直戳跳转

(2) [sscom33串口调试助手使用](https://blog.csdn.net/lfmnlxx79691557/article/details/128335808?spm=1001.2014.3001.5502)			直戳跳转

(3)[STC-ISP串口调试助手使用](https://blog.csdn.net/lfmnlxx79691557/article/details/128335896?spm=1001.2014.3001.5502)			    直戳跳转


# 六、视频效果展示与程序资料获取
[视频连接](https://www.bilibili.com/video/BV1v24y1T7Ac/?vd_source=7933b82b52c9cbf1c7966eb9f0dbd29f)  	直戳跳转
资料获取            （可直接下载仓库）

# 七、注意事项
1、VCC GND请勿接反，接反易烧
2、OLED显示异常时，排除接线接触不良

# 八、接线说明

## STM32F103C8T6 
```javascript
  
/************************************************************************************
//  功能描述   : W25Q32模块测试程序
//  测试条件   : STM32F103C8T6   晶振8M  系统时钟72M
接线
W25Q32模块-------------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
CS-------------------------------------PA4 //
SCK------------------------------------PA5 //	
MISO-----------------------------------PA6 //	
MOSI-----------------------------------PA7 //	

OLED0.96模块---------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
SCL------------------------------------PB8 //
SDA------------------------------------PB9 //	

*************************************************************************************/
```


@[TOC] (K_A39_012 based on the STM32 driver W25Q32 module read and write data serial port+OLED0.96 display)

![Please add picture description](https://img-blog.csdnimg.cn/e00ccd57499f4cd8883cec21fb29a138.jpeg)

# All resource navigation
[ Other data catalog ](https://blog.csdn.net/lfmnlxx79691557/article/details/128323460?spm=1001.2014.3001.5501)  Direct link to jump

# 1. Resource description
| Single -chip Machine Model | Test Conditions | Module Name | Code Function |
|:--------:| -------------:| -------------:|-------------:|
| STM32F103C8T6 | Crystal 8M/System Clock 72M | W25Q32 Module | STM32F103C8T6 Drive W25Q32 module serial port and OLED0.96 dual display |


# 2. basic parameters
## parameter

![Please add picture description](https://img-blog.csdnimg.cn/c454ade430064f6e9a23a0e04f45c445.png)

## pin explanation

W25Q32 module | pin explanation
-------- | -------
Vcc | Power 3.3V power supply
GND | GND power supply negative electrode
MISO | SPI bus host input from the machine output pin
MOSI | SPI bus host output from the machine input pin from the machine
SCK | SPI bus clock pin
CS | Selection signal pin

# 3. Drive Instructions

## Sequential chart

![Please add picture description](https://img-blog.csdnimg.cn/3e6371eaeeac4545ae63650e3a9a1cca.png)


## corresponding program

```javascript
//SPI initialization program:
/**
 * @Brief SPI_FLASH initialization
 * @param None
 * @Retval none
 */
void spi_flash_init (void)
{
    Spi_inittypedef spi_initStruction;
    Gpio_inittypedef gpio_initStruction;

    / * Make SPI clock * /
    Flash_spi_apbxclock_fun (Flash_spi_CLK, Enable);

    / * Make clocks related to SPI pin * /
    Flash_spi_cs_apbxclock_fun (FLASH_SPI_CS_CLK | FLASH_SPI_SCK_CLK |
    Flash_spi_miso_pin | Flash_SPI_MOSI_PIN, Enable);

    / * Configure the SPI CS pin, ordinary IO can */
    Gpio_initStructure.gpio_pin = FLASH_SPI_CS_PIN;
    Gpio_initStructure.gpio_speed = gpio_speed_50MHz;
    Gpio_initStructure.gpio_mode = gpio_mode_out_pp;
    Gpio_init (flash_spi_cs_port, & gpio_initStruction);

    /* Configure the SPI SCK pin*/
    Gpio_initStructure.gpio_pin = FLASH_SPI_SCK_PIN;
    Gpio_initStructure.gpio_mode = gpio_mode_af_pp;
    Gpio_init (Flash_spi_SCK_PORT, & GPIO_INITSTRUCTURE);

    /* Configure SPI Miso pin*/
    Gpio_initStructure.gpio_pin = FLASH_SPI_MISO_PIN;
    Gpio_init (flash_spi_miso_port, & gpio_initStruction);

    /* Configure the SPI MOSI pin*/
    Gpio_initStruction.gpio_pin = Flash_spi_mosi_pin;
    Gpio_init (flash_spi_mosi_port, & gpio_initStruction);

    /* Stop signal Flash: CS pin high level*/
    Spi_flash_cs_high ();

    / * SPI mode configuration */
    // Flash chip supports SPI mode 0 and mode 3, set up CPOL CPHA accordingly
    Spi_initStruction.spi_direction = spi_direction_2Lines_fullDuplex;
    Spi_initStruction.spi_mode = spi_mode_master;
    Spi_initStruction.spi_datasize = spi_datasize_8b;
    Spi_initStruction.spi_cpol = spi_cpol_high;
    Spi_initStruction.spi_CPHA = spi_cpha_2edge;
    Spi_initStruction.SPI_NSS = spi_nss_soft;
    Spi_initStruction.spi_baudrateprescaler = spi_baudrateprescaler_4;
    Spi_initStruction.spi_firstbit = SPI_FIRSTBIT_MSB;
    Spi_initStruction.spi_crcpolynomial = 7;
    Spi_init (flash_spix, & spi_initStruction);

    / * Make SPI */
    Spi_cmd (flash_spix, enable);

}
```
# 4. Partial code description
## 1.1. Wiring pin definition
You need to customize the pin can be changed here. If STM32 needs to customize the pin, you should also pay attention

### 1.1.2, STM32F103C8T6+W25Q32 module
```javascript
#Define Flash_spix SPI1
#Define Flash_SPI_APBXCLOCK_FUN RCC_APB2PERIPEHCLOCLOCKCMD
#Define Flash_SPI_CLK RCC_APB2PERIPH_SPI1

// CS (NSS) pin tablets to select ordinary GPIO
#Define Flash_SPI_CS_APBXCLOCK_FUN RCC_APB2PERIPEHCLOCLOCKCMD
#Define Flash_SPI_CLK RCC_APB2PERIPH_GPIOA
#Define Flash_SPI_CS_PORT GPIOA
#Define Flash_SPI_CS_PIN GPIO_PIN_4

// SCK pin
#Define Flash_SPI_SCK_APBXCLOCK_FUN RCC_APB2PERIPHCLOCLOCKCMD
#Define Flash_SPI_SCK_CLK RCC_APB2PERIPH_GPIOA
#Define Flash_SPI_SCK_PORT GPIOA
#Define Flash_SPI_SCK_PIN GPIO_PIN_5
// Miso pin
#Define Flash_SPI_MISO_APBXCLOCK_FUN RCC_APB2PERIPHCLOCLOCKCMD
#Define Flash_SPI_MISO_CLK RCC_APB2PERIPH_GPIOA
#Define Flash_SPI_MISO_PORT GPIOA
#Define Flash_SPI_MISO_PIN GPIO_PIN_6
// MOSI pin
#Define Flash_SPI_MOSI_APBXCLOCK_FUN RCC_APB2PERIPEHCLOCLOCKCMD
#Define Flash_SPI_MOSI_CLK RCC_APB2PERIPH_GPIOA
#Define Flash_SPI_MOSI_PORT GPIOA
#Define Flash_SPI_MOSI_PIN GPIO_PIN_7

```

# 5. Basic knowledge learning and related information download

5.1. [STC89C52RC program download](https://blog.csdn.net/lfmnlxx79691557/article/details/127114912?spm=1001.2014.3001.5501)   Direct link to jump

5.2. STM32F103C8T6 program download

(1) [serial port download](https://blog.csdn.net/lfmnlxx79691557/article/details/122862183?spm=1001.2014.3001.5501)    Direct link to jump

(2) [ST-LINK Download](https://blog.csdn.net/lfmnlxx79691557/article/details/127140554?spm=1001.2014.3001.5501)   Direct link to jump

(3) [j-link download](https://blog.csdn.net/lfmnlxx79691557/article/details/127140823?spm=1001.2014.3001.5501)   Direct link to jump

(4) [dap-link download](https://blog.csdn.net/lfmnlxx79691557/article/details/127141244?spm=1001.2014.3001.5501)   Direct link to jump


5.3. [OLED0.96 Program Instructions](https://blog.csdn.net/lfmnlxx79691557/article/details/127208887?spm=1001.2014.3001.5501)   Direct link to jump

5.4. Download and use serial assistant

(1) [Anxin's debugging assistant use](https://blog.csdn.net/lfmnlxx79691557/article/details/128335660?spm=1001.2014.3001.5502)   Direct link to jump

(2) [SSCOM33 serial debug assistant use](https://blog.csdn.net/lfmnlxx79691557/article/details/128335808?spm=1001.2014.3001.5502)   Direct link to jump

(3) [STC -ISP serial debugging assistant use](https://blog.csdn.net/lfmnlxx79691557/article/details/128335896?spm=1001.2014.3001.5502)   Direct link to jump



# 6. Video effect display and program data acquisition
[Video Connection] (https://www.bilibili.com/video/bv1v24y1t7ac/?vd_source=7933B82B52CBF1C7966EB9F0DBD29F) Stranding jumping
Data acquisition (can download the warehouse directly)

# 7. Notice
1. Please do not recalculate VCC GND.
2. When the OLED display is abnormal, exclude poor wiring contact

# 8. Wiring description

## STM32F103C8T6
```javascript
  
/*************************************************** *****************************************
// Function description: W25Q32 module test program
// Test conditions: STM32F103C8T6 Crystal 8M System Clock 72M
wiring

W25Q32 Module--------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
CS-------------------------------------PA4 //
SCK------------------------------------PA5 //	
MISO-----------------------------------PA6 //	
MOSI-----------------------------------PA7 //	

OLED0.96 Module------------------------STM32F103C8T6
VCC------------------------------------3.3V
GND------------------------------------GND
SCL------------------------------------PB8 //
SDA------------------------------------PB9 //	

```

