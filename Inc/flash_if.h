/**
  ******************************************************************************
  * @file    flash_if.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-October-2011
  * @brief   Header for flash_if.c module
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include  "stm32f4xx_hal_flash.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define USER_FLASH_SIZE   (USER_FLASH_END_ADDRESS - USER_FLASH_FIRST_PAGE_ADDRESS)
/*
typedef enum
{
  FLASH_BUSY = 1,
  FLASH_ERROR_PGS,
  FLASH_ERROR_PGP,
  FLASH_ERROR_PGA,
  FLASH_ERROR_WRP,
  FLASH_ERROR_PROGRAM,
  FLASH_ERROR_OPERATION,
  FLASH_COMPLETE
}FLASH_Status;
*/
/*
Sector 0 0x0800 0000 - 0x0800 3FFF 16 Kbytes
Sector 1 0x0800 4000 - 0x0800 7FFF 16 Kbytes
Sector 2 0x0800 8000 - 0x0800 BFFF 16 Kbytes
Sector 3 0x0800 C000 - 0x0800 FFFF 16 Kbyte
Sector 4 0x0801 0000 - 0x0801 FFFF 64 Kbytes
Sector 5 0x0802 0000 - 0x0803 FFFF 128 Kbytes
Sector 6 0x0804 0000 - 0x0805 FFFF 128 Kbytes
Sector 7 0x0806 0000 - 0x0807 FFFF 128 Kbytes
Bank 2
Sector 12 0x0808 0000 - 0x0808 3FFF 16 Kbytes
Sector 13 0x0808 4000 - 0x0808 7FFF 16 Kbytes
Sector 14 0x0808 0000 - 0x0808 BFFF 16 Kbytes
Sector 15 0x0808 C000 - 0x0808 FFFF 16 Kbytes
Sector 16 0x0809 0000 - 0x0809 FFFF 64 Kbytes
Sector 17 0x080A 0000 - 0x080B FFFF 128 Kbytes
Sector 18 0x080C 0000 - 0x080D FFFF 128 Kbytes
Sector 19 0x080E 0000 - 0x080F FFFF 128 Kbytes
System memory 0x1FFF 0000 - 0x1FFF 77FF 30 Kbytes
OTP 0x1FFF 7800 - 0x1FFF 7A0F 528 bytes
Option bytes
Bank 1 0x1FFF C000 - 0x1FFF C00F 16 bytes
Bank 2 0x1FFE C000 - 0x1FFE C00F 16 bytes
*/


#define FLASH_COMPLETE  (0) //(8)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint32_t FLASH_If_Write(__IO uint32_t* Address, uint32_t* Data, uint16_t DataLength);
uint32_t FLASH_If_Read(__IO uint32_t Address, uint32_t* Data, uint16_t DataLength);
int8_t FLASH_If_Erase(uint32_t StartSector);
void FLASH_If_Init(void);

#endif /* __FLASH_IF_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
