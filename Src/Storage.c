#include <ctype.h>                          /* character functions            */
#include "flash_if.h"
#include <string.h>
#include <stdio.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "lwip/opt.h"
#include "lwip.h"
//#include <ctype.h>



#define STORAGE_ADDR     ((uint32_t)0x081D0000)  //sector 22 128 k
#define STORAGE_ADDR1    ((uint32_t)0x081E0000)  //sector 23 128 k

unsigned long DevId;
unsigned long TestMode;
unsigned long ProgSize;
unsigned char Reset;
unsigned long timercnt;
unsigned long write_cnt;


uint8_t MyMACAddr[6]; //18
//+ Ip + Mask + GW	  //30
uint8_t reserved[10];  //40
unsigned short CSum; //42
#define STORAGE_SIZE		 (42)

uint32_t SBuffer[STORAGE_SIZE];
char ReadStorage(void) {  //may be need init flash
	unsigned short tCSum = 0;
	DevId = 0x2345;
	TestMode = 1;
	ProgSize = 128000;
	MyMACAddr[0] = 0; //18
	MyMACAddr[1] = 0x11; //18
	MyMACAddr[2] = 0x11; //18
	MyMACAddr[3] = 0; //18
	MyMACAddr[4] = 0x23; //18
	MyMACAddr[5] = 0x45; //18
	IP_ADDRESS[0] = 192;
	IP_ADDRESS[1] = 168;
	IP_ADDRESS[2] = 3;
	IP_ADDRESS[3] = 220;
	GATEWAY_ADDRESS[0] = 192;
	GATEWAY_ADDRESS[1] = 168;
	GATEWAY_ADDRESS[2] = 3;
	GATEWAY_ADDRESS[3] = 1;
	NETMASK_ADDRESS[0] = 0x255;
	NETMASK_ADDRESS[1] = 0x255;
	NETMASK_ADDRESS[2] = 0;
	NETMASK_ADDRESS[3] = 0;

	memset(SBuffer,0, STORAGE_SIZE);
	FLASH_If_Init();
	FLASH_If_Read((__IO uint32_t)STORAGE_ADDR, (uint32_t*)SBuffer ,STORAGE_SIZE);
	CSum = SBuffer[STORAGE_SIZE-2] + (SBuffer[STORAGE_SIZE-1] << 8);
	for(int i = 0; i < STORAGE_SIZE-2; i++) {

	  tCSum +=  SBuffer[i];
   }
	tCSum-= 1;
	if(CSum !=  tCSum) {
//t		FLASH_If_Read((__IO uint32_t)STORAGE_ADDR1, (uint32_t*)SBuffer ,STORAGE_SIZE);
		CSum = SBuffer[STORAGE_SIZE-2] + (SBuffer[STORAGE_SIZE-1] << 8);
		for(int i = 0; i < STORAGE_SIZE-2; i++) {
		  tCSum +=  SBuffer[i];
	    }
		tCSum-= 1;
		if(CSum !=  tCSum) {
			//HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_7);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
			printfp("\n\r Storages Wrong\n\r");
//hier can set default values
			return -1;
			}
	}
	DevId = SBuffer[0];
	IP_ADDRESS[0] = SBuffer[1]>>24;
	IP_ADDRESS[1] = (SBuffer[1]>>16) & 0xff;
	IP_ADDRESS[2] = (SBuffer[1]>>8)  & 0xff;
	IP_ADDRESS[3] = SBuffer[1]       & 0xff;
	MyMACAddr[0] = SBuffer[2]>>16;
	MyMACAddr[1] = (SBuffer[2]>>8) & 0xff;
	MyMACAddr[2] = SBuffer[2]      & 0xff;
	MyMACAddr[3] = SBuffer[3]>>16;
	MyMACAddr[4] = (SBuffer[3]>>8) & 0xff;
	MyMACAddr[5] = SBuffer[3]      & 0xff;
	GATEWAY_ADDRESS[0] = SBuffer[4]>>24;
	GATEWAY_ADDRESS[1] = (SBuffer[4]>>16) & 0xff;
	GATEWAY_ADDRESS[2] = (SBuffer[4]>>8)  & 0xff;
	GATEWAY_ADDRESS[3] = SBuffer[4]       & 0xff;
	NETMASK_ADDRESS[0] = SBuffer[5]>>24;
	NETMASK_ADDRESS[1] = (SBuffer[5]>>16) & 0xff;
	NETMASK_ADDRESS[2] = (SBuffer[5]>>8)  & 0xff;
	NETMASK_ADDRESS[3] = SBuffer[5]       & 0xff;
	ProgSize = SBuffer[6];

	//	printfpd("\n\r read progsize1 : %d", ProgSize);
//	ProgSize = SBuffer[7];
//	printfpd("\n\r read progsize2 : %d", ProgSize);
//	ProgSize = SBuffer[8];
//	printfpd("\n\r read progsize3 : %d", ProgSize);
//	ProgSize = SBuffer[9];
//	printfpd("\n\r read progsize4 : %d", ProgSize);
	
	
 // for(i = 0; i < STORAGE_SIZE; i++) {
//		if(!(i%16)) printfp("\n\r");
//	printfpd (" %d",SBuffer[i]);
//	}	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
//	HAL_GPIO_TogglePin( GPIOB, GPIO_PIN_0);
//t    printfp("\n\r Storage Ok!\n\r");
//	for(i = 0; i < STORAGE_SIZE; i++) {
//	if(!(i%16)) printfp("\n\r");
//	printfpd (" %d",SBuffer[i]);
//	}	
	return 0;
}
char WriteStorage(void) {
	unsigned short tCSum = 0;
	__IO uint32_t  Addr = (__IO uint32_t)STORAGE_ADDR;
//	int i;
//	for(i = 0; i < STORAGE_SIZE; i++) {
//	}
	/*
	FLASH->CR &= ~FLASH_CR_PG;
  FLASH->CR |= FLASH_CR_LOCK; //
	Erase_flash(STORAGE_ADDR);
	Erase_flash(STORAGE_ADDR1);
	ReadBuffer(SBuffer,STORAGE_SIZE, STORAGE_ADDR);
	ProgSize = SBuffer[6];
	printfpd("\n\r read progsize1 : %d", ProgSize);
	ProgSize = SBuffer[7];
	printfpd("\n\r read progsize2 : %d", ProgSize);
	ProgSize = SBuffer[8];
	printfpd("\n\r read progsize3 : %d", ProgSize);
	ProgSize = SBuffer[9];
	printfpd("\n\r read progsize4 : %d", ProgSize);
	*/
	memset(SBuffer,0, STORAGE_SIZE);
	SBuffer[0] = DevId;
	SBuffer[1] =(IP_ADDRESS[0]<<24) + (IP_ADDRESS[1]<<16)+(IP_ADDRESS[2]<<8)+IP_ADDRESS[3];
	SBuffer[2]  = (MyMACAddr[0]<<16)+(MyMACAddr[1]<<8)+MyMACAddr[2];
	SBuffer[3] = (MyMACAddr[3]<<16)+(MyMACAddr[4]<<8)+MyMACAddr[5];
	SBuffer[4] = (GATEWAY_ADDRESS[0]<<24) + (GATEWAY_ADDRESS[1]<<16)+(GATEWAY_ADDRESS[2]<<8)+GATEWAY_ADDRESS[3];
	SBuffer[5] = (NETMASK_ADDRESS[0]<<24) + (NETMASK_ADDRESS[1]<<16)+(NETMASK_ADDRESS[2]<<8)+NETMASK_ADDRESS[3];
	SBuffer[6] = ProgSize;
	for(int i = 0; i < STORAGE_SIZE-2; i++) {
		  tCSum +=  SBuffer[i];
	    }
	tCSum -= 1;
	CSum = SBuffer[STORAGE_SIZE-2] + (SBuffer[STORAGE_SIZE-1] << 8);
	SBuffer[STORAGE_SIZE-2] = tCSum & 0xff;
	SBuffer[STORAGE_SIZE-1] = (tCSum >> 8) & 0xff;
//		printfpd("\n\r keep progsize1 : %d",SBuffer[6] );
//	SBuffer[7] = ProgSize;
//		printfpd("\n\r keep progsize2 : %d",SBuffer[7] );
//	SBuffer[8] = ProgSize;
//		printfpd("\n\r keep progsize3 : %d",SBuffer[8] );
//	SBuffer[9] = ProgSize;
	
//	printfpd("\n\r keep progsize4 : %d", SBuffer[9]);
	
//	Erase_flash(STORAGE_ADDR);
	FLASH_Erase_Sector(FLASH_SECTOR_22, FLASH_VOLTAGE_RANGE_3);
//t	HAL_Delay(2000);
	HAL_Delay(200);
//	FLASH_Erase_Sector(FLASH_SECTOR_23, FLASH_VOLTAGE_RANGE_3);
//	HAL_Delay(3000);

	FLASH_If_Write( (__IO uint32_t*)&Addr, (uint32_t*) SBuffer ,(uint16_t) STORAGE_SIZE);
//t	HAL_Delay(2000);
	HAL_Delay(200);
//	Erase_flash(STORAGE_ADDR1);
	FLASH_Erase_Sector(FLASH_SECTOR_23, FLASH_VOLTAGE_RANGE_3);
//	HAL_Delay(2000);
	HAL_Delay(200);
	Addr =  (__IO uint32_t)STORAGE_ADDR1;
//	HAL_Delay(10);
	FLASH_If_Write( (__IO uint32_t*)&Addr, (uint32_t*) SBuffer ,(uint16_t) STORAGE_SIZE);
//	HAL_Delay(10);
//	ReadBuffer(SBuffer,STORAGE_SIZE, STORAGE_ADDR);
//	ProgSize = SBuffer[6];
//	printfpd("\n\r read progsize1 : %d", ProgSize);
//	ProgSize = SBuffer[7];
//	printfpd("\n\r read progsize2 : %d", ProgSize);
//	ProgSize = SBuffer[8];
//	printfpd("\n\r read progsize3 : %d", ProgSize);
//	ProgSize = SBuffer[9];
//	printfpd("\n\r read progsize4 : %d", ProgSize);
	
	return 0;
}

	


