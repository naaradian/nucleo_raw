#include "main.h"
#include "lwip.h"
#include "storage.h"
#include "stm32f4xx_hal.h"
#include "usart.h"

#include <ctype.h> 

//#include "MxL_MJSK_Common.h"
//extern osSemaphoreId myBinarySem02_USART2THandle;

//extern void StartWriteFw(UINT32);
//extern U8 own_hw_adr[];

//extern void UART3_Send(unsigned long , char *);
extern osSemaphoreId myBinarySem02_USART2THandle;
//extern osSemaphoreId myBinarySem03_USART2RHandle;
char * pTBuff;

extern void RunTestMode(void) { //called for setted new testmode
	switch(TestMode) {
		case 0 : break;
		case 1 : break;
		default : break;
	}
}

/*
DevId.Init( &theAnyStrings.c5d[0],  //140203 format
  //140203				  16, 1,  //x,y
				  11, 2,  //x,y
				   0 ,		// not changable
		   //		   &ExpertStorage.Clk0, //storageaddr
					ZeroStorage, //sweep in storage - new
//				  40000000l,
		 //	    4,  //chars
		   		    5,  //chars
//					 3,
					&theCntFunc, //pControl
				  12,//6,  //cntnum - function for control of value
				   12, //	6, //oprnum - operation if setted new value
					&theAnyStrings.cmes0[0], // message line 0 
 					&theAnyStrings.cmes1[0], // mesaage line 1
			//		 1, 1, 0//,		//have sign, 1 digit after point, decimal			  
					 //	 0, 1//, 0//,		//  0 digit after point, hex	
					 	 0, 0//, 0//,		//  0 digit after point, dec			  		  
		//		4
		,0,  //init value
		&theAnyStrings.cRemId[0] //remote command	  (B9)
	//	, &theAnyStrings.c8d[0], //remote format
		, &theAnyStrings.c4X[0], //remote format
		 4,  //remchars 
		 12 //remnum
			//  ,1,0,0,0);
			 , 1,	 MIN_DEVID,
			      MAX_DEVID,
			     1);
					 
				strcpy(cRemId      ,"BE");	
	 strcpy(c4X,	   	   "%04X");
*/
					 


int FindCommand(char * pCommand) {
int ret	= 0;
//printfp(pCommand);

 	if(strstr(pCommand, "BE") == pCommand)  ret = 1;
	if(strstr(pCommand, "@") == pCommand)   ret = 2;
	if(strstr(pCommand, "BH") == pCommand)  ret = 3;
	if(strstr(pCommand, "H0") == pCommand)  ret = 4;  //filesize
	if(strstr(pCommand, "H1") == pCommand)  ret = 5;  //fileportion
	if(strstr(pCommand, "B8") == pCommand)  ret = 6;  //ip address
	if(strstr(pCommand, "BP") == pCommand)  ret = 7;  //mac0
	if(strstr(pCommand, "BR") == pCommand)  ret = 8;  // mac1
	if(strstr(pCommand, "Fe") == pCommand)  ret = 9;  // def gat ip
	if(strstr(pCommand, "Ff") == pCommand)  ret = 10;  // def gat ip
	if(strstr(pCommand, "BL") == pCommand)  ret = 11;
return ret;	
}	

int Getlen(int type) {
	int len[] ={0,2,1,2,2,2,2,2,2,2,2,2};   //len of pCommand of type
return len[type];	
}

char * GetFormat(int type) {
//need make switch	
	
	switch(type) {
		case 1 : return "%04X";
		case 2 : return "%1d";
		case 3 : return "%04X";
		case 4 : return "%08X"; //size
		case 5 : return "%04X";
		case 6 : return "%08X"; //ip
		case 7 : return "%06X"; //mac0 first three values
		case 8 : return "%06X"; //mac1  last three elues
		case 9 : return "%08X"; //gat ip
		case 10 : return "%08X"; //netmask
		case 11 : return "%08X"; //status
		default : return "%d"; 
	}
//return "%04X";
}

void CopyRemote(int type) {
	switch(type) {
    case 1 :	strcpy(pTBuff, "BE"); break; 
		case 2 :	strcpy(pTBuff, "@"); break; 
		case 3 :	strcpy(pTBuff, "BH"); break; 
		case 4 :	strcpy(pTBuff, "H0"); break;
		case 5 :	strcpy(pTBuff, "H1"); break;
		case 6 :	strcpy(pTBuff, "B8"); break;
		case 7 :	strcpy(pTBuff, "BP"); break;
		case 8 :	strcpy(pTBuff, "BR"); break;
		case 9 :	strcpy(pTBuff, "Fe"); break;
		case 10 :	strcpy(pTBuff, "Ff"); break;
		case 11 :	strcpy(pTBuff, "BL"); break;
 		default : strcpy(pTBuff, "ABC"); //
	}	
}

void CopyRemoteE(int type, char* pBuff) {
	//return;
	switch(type) {
    	case 1 :	strcpy(pBuff, "BE"); break;
		case 2 :	strcpy(pBuff, "@"); break;
		case 3 :	strcpy(pBuff, "BH"); break;
		case 4 :	strcpy(pBuff, "H0"); break;
		case 5 :	strcpy(pBuff, "H1"); break;
		case 6 :	strcpy(pBuff, "B8"); break;
		case 7 :	strcpy(pBuff, "BP"); break;
		case 8 :	strcpy(pBuff, "BR"); break;
		case 9 :	strcpy(pBuff, "Fe"); break;
		case 10 :	strcpy(pBuff, "Ff"); break;
		case 11 :	strcpy(pBuff, "BL"); break;
 		default : 	strcpy(pBuff, "ABC"); //
	}
}


int GetRemChars(int type) {
	switch(type) {
		case 1  : return 5;
		case 2  : return 2;
		case 3  : return 5;
		case 4  : return 9;
		case 5  : return 5;
		case 6  : return 9;  //ip 8 hex digits + point
		case 7  : return 7;
		case 8  : return 7;
		case 9  : return 9;
		case 10 : return 9; 
		case 11 : return 9;
		default : return 5; 
	}
// return 5;//12;
}

unsigned long GetValue(int type ) {
	unsigned long ret = 0;
	switch(type) {
		case 1 : ret = DevId; break;
		case 2 : ret = Reset; break;
		case 3 : ret = TestMode; break;
//		case 4 : ret = FwFileSize; break;
		case 5 : ret = 0x55; break; //dummy answer
		case 6 : ret = (IP_ADDRESS[0]<<24) + (IP_ADDRESS[1]<<16)+(IP_ADDRESS[2]<<8)+IP_ADDRESS[3]; break;
		case 7 : ret = (MyMACAddr[0]<<16)+(MyMACAddr[1]<<8)+MyMACAddr[2]; break;
		case 8 : ret = (MyMACAddr[3]<<16)+(MyMACAddr[4]<<8)+MyMACAddr[5]; break;
		case 9 : ret = (GATEWAY_ADDRESS[0]<<24) + (GATEWAY_ADDRESS[1]<<16)+(GATEWAY_ADDRESS[2]<<8)+GATEWAY_ADDRESS[3]; break;
		case 10 : ret = (NETMASK_ADDRESS[0]<<24) + (NETMASK_ADDRESS[1]<<16)+(NETMASK_ADDRESS[2]<<8)+NETMASK_ADDRESS[3]; break;
		case 11 : ret = 1;  break; //status temporary
		default: break;
	}
return ret;
}
void SetValue(int type , unsigned long val) {
//	char Buff[10];  //for debug only
	switch(type) {
		case 1 : DevId = val; break;
		case 2 : Reset = (unsigned char)val; break;
		case 3 : TestMode = val;  RunTestMode(); break;
//		case 4 : FwFileSize = val; //StartWriteFw(val);
			//			 UART3_Send(8, "RECV LEN"); //DEBUG ONLY
			//			 sprintf(Buff," %08d",(int)val);
		//				 UART3_Send(10, Buff);
						 break;
		case 5 : //WriteFwSector(); // UART3_Send(8, "\n\rRECV Data");
						 break;
		case 6 : IP_ADDRESS[0] = val>>24;
				IP_ADDRESS[1] = (val>>16) & 0xff;
				IP_ADDRESS[2] = (val>>8)  & 0xff;
				IP_ADDRESS[3] = val       & 0xff;
				 My_ChangeIp();
						 break;
		case 7 : MyMACAddr[0] = val>>16;
				MyMACAddr[1] = (val>>8) & 0xff;
				MyMACAddr[2] = val      & 0xff;
						 break;	
	 	case 8 : MyMACAddr[3] = val>>16;
	 			MyMACAddr[4] = (val>>8) & 0xff;
	 			MyMACAddr[5] = val      & 0xff;
	 			//it can be used after restart
						 break;
		case 9 : GATEWAY_ADDRESS[0] = val>>24;
				GATEWAY_ADDRESS[1] = (val>>16) & 0xff;
				GATEWAY_ADDRESS[2] = (val>>8)  & 0xff;
				GATEWAY_ADDRESS[3] = val       & 0xff;
				 My_ChangeIp();
						 break;
	 	case 10 : NETMASK_ADDRESS[0] = val>>24;
	 			NETMASK_ADDRESS[1] = (val>>16) & 0xff;
	 			NETMASK_ADDRESS[2] = (val>>8)  & 0xff;
	 			NETMASK_ADDRESS[3] = val       & 0xff;
	 			 My_ChangeIp();
							break;	
	 	case 11 :			break;
		default: break;
	}
}	

//char RunRemoteS(char * pCommand, char SysS)
char RunCommandS(char * pCommand) {
unsigned long	 Value;	
unsigned long tmpl;
char Buf[32];
char * end;
char ret = 0;
int i;	
int type = FindCommand(pCommand) ;
end = &Buf[0];
counter = 0;  //do not jump
 if(type)	
//	if(strstr(pCommand, pRemote) == pCommand) // command or request
  //	if(1) // for test
 //  if(strstr(pCommand, pRemote) == pCommand) 
  	{
   //		UsedRemote.IdCommand = 1; //right command
	//    IdCommand = 1; //right command
	  ret = 1;
//		if(strlen(pCommand) == strlen(pRemote)) //request
			
//		printfpd("len: %d", strlen(pCommand));	
		if(strlen(pCommand) == Getlen(type)) //request
		{
		CopyRemote(type);	
	//t	strcpy(pTBuff, pRemote); //add to  transmit buffer command
	
//			for(i = strlen(pRemote); i > 0; i--)
			for(i = Getlen(type); i > 0; i--)
		{
	//	UsedRemote.pTBuff++;
		pTBuff++;
		}
   //		Uint32 tmp = Value;
   //		sprintf(pTBuffS, pRemFormat, tmp);

//   if(DgAftPnt)
//		if(0)
//		sprintf(pTBuff, pRemFormat, Value);//
//		else
	//	sprintf(pTBuff, pRemFormat, (Uint32)Value);
		sprintf(pTBuff, GetFormat(type), (unsigned int)GetValue(type));
		for(i = GetRemChars(type); i > 0; i--)
		{
		pTBuff++;
		}	
		
//t		pControl->OperateInRead(OprNum);
		}
	else //command
		{
//  		for(i = strlen(pRemote); i > 0; i--)
				for(i = Getlen(type); i > 0; i--)
		{
		pCommand++; //to get only  content of command
		}
   //		tmpl = (float64)strtol(pCommand, &end, SysS);
		if(type != 5) {  //not sed file
					tmpl = strtoll(pCommand, &end, 16);
		}
		else {  //receive block
			//hier nedd copy block to buffer
//			CopyBlockToBuffer(pCommand);  //writing fw
		}
//		printfpd("\n\r val : 0x%x", tmpl);
//			 if(pControl->Control(CntNum, tmpl))
			if(1) 
			 {
				 
	//		 ChangingValue =  tmpl;
			 Value =  tmpl;
			 SetValue(type, Value);	
			 //WriteStorage();	
			 write_cnt = WRITE_DELAY;				 
//			 WriteStorageC(StorageAddr,Value);
//			 pControl->Operate(OprNum);
//			 UsedExp.State.Reg2.bit.Draw = 1;
//			 UsedExp.State.Reg2.bit.Some = 1;
				 
			 }
			 else //
			 {
   	//	 UsedMenu.DrawMessage(pMes0,pMes1);
			 }
 // 		pControl->Remote(RemNum, pCommand, CntNum);		
    		strcpy(pTBuff, "K0"); //add"K0"
		for(i = strlen("K0")+1; i > 0; i--)
		{
		pTBuff++;
		}
	 }
  }
 else  //wrong type
 {
		strcpy(pTBuff, "K1"); //add"K0"
		for(i = strlen("K1")+1; i > 0; i--)
		{
		pTBuff++;
		}
 }
		strcpy(pTBuff++, ";");

	return ret;
}




//void  RunCommandS(char * pPrev) {
//}

void ParseBufferS(char *pStart,  char razd)
{
	char * pPrev;
   char * pNext;
	int i;

   pPrev = pStart;
   pNext = pStart;
 //	p = strtok(pStart, &razd);
    for(i = 0; i < RCV_BUFF_SIZE; i++)
    { /* Body */
     if((*pNext & 0xff) == '\0')
     { 
         //   if(pNext > pPrev)
         //   { 
               RunCommandS(pPrev);
         //   } 
        break;
     } 
      //   if((*pNext & 0xff)  ==';')
          if(((*pNext & 0xff)  == razd)	|| 	((*pNext & 0xff)  == '.'))
     {
      *pNext = '\0';
      RunCommandS(pPrev);
      pPrev = pNext;
       pPrev++; //to first symbol of next command
     }
      pNext++;
   } /* Endbody */
}

char RunCommandE(char * pCommand, char ** pBuff) {
unsigned long	 Value;
unsigned long tmpl;
char Buf[32];
char * end;
char ret = 0;
int i;
int tmp;
//int type = FindCommand(pCommand+3) ;
int type = FindCommand(pCommand) ;

end = &Buf[0];
counter = 0;  //do not jump

//**pBuff = '8'; //t1
//*pBuff += 1;
//**pBuff = '9';
//*pBuff += 1;
//**pBuff = 'a';
//*pBuff += 1;
//	return 1;   //t1

 if(type)
//	if(strstr(pCommand, pRemote) == pCommand) // command or request
  //	if(1) // for test
 //  if(strstr(pCommand, pRemote) == pCommand)
  	{
   //		UsedRemote.IdCommand = 1; //right command
	//    IdCommand = 1; //right command
	  ret = 1;
//		if(strlen(pCommand) == strlen(pRemote)) //request
//	  printfp(pCommand);
//ok		return 1;
//		printfpd("len: %d", strlen(pCommand));
//		if(strlen(pCommand+3) == Getlen(type)) //request
	  tmp = strlen(pCommand);
	  if(strlen(pCommand) == Getlen(type)) //request
		{

	//ok		return 1;
		CopyRemoteE(type, *pBuff);
	//t	strcpy(pTBuff, pRemote); //add to  transmit buffer command
//		return 1;
//			for(i = strlen(pRemote); i > 0; i--)
			for(i = Getlen(type); i > 0; i--)
		{
	//	UsedRemote.pTBuff++;
		*pBuff += 1;
		}

//return 1;

   //		Uint32 tmp = Value;
   //		sprintf(pTBuffS, pRemFormat, tmp);

//   if(DgAftPnt)
//		if(0)
//		sprintf(pTBuff, pRemFormat, Value);//
//		else
	//	sprintf(pTBuff, pRemFormat, (Uint32)Value);
//		printfp(pBuff - 5); //%001  if - 3 0BL

    	sprintf(*pBuff, GetFormat(type), (unsigned int)GetValue(type));

		for(i = GetRemChars(type); i > 0; i--)
		{
		*pBuff += 1;
		}

//t		pControl->OperateInRead(OprNum);
		}
	else //command
		{
//  		for(i = strlen(pRemote); i > 0; i--)
				for(i = Getlen(type); i > 0; i--)
		{
		pCommand++; //to get only  content of command
		}
   //		tmpl = (float64)strtol(pCommand, &end, SysS);
		if(type != 5) {  //not sed file
//					tmpl = strtoll(pCommand+3, &end, 16);
					tmpl = strtoll(pCommand, &end, 16);

		}
		else {  //receive block
			//hier nedd copy block to buffer
//			CopyBlockToBuffer(pCommand);  //writing fw
		}
//		printfpd("\n\r val : 0x%x", tmpl);
//			 if(pControl->Control(CntNum, tmpl))
			if(1)
			 {

	//		 ChangingValue =  tmpl;
			 Value =  tmpl;
			 SetValue(type, Value);
			 //WriteStorage();
			 write_cnt = WRITE_DELAY;
//			 WriteStorageC(StorageAddr,Value);
//			 pControl->Operate(OprNum);
//			 UsedExp.State.Reg2.bit.Draw = 1;
//			 UsedExp.State.Reg2.bit.Some = 1;

			 }
			 else //
			 {
   	//	 UsedMenu.DrawMessage(pMes0,pMes1);
			 }
 // 		pControl->Remote(RemNum, pCommand, CntNum);
    		strcpy(*pBuff, "K0"); //add"K0"
		for(i = strlen("K0")+1; i > 0; i--)
		{
		*pBuff += 1;
		}
	}
}
 else  //wrong type
 {
		strcpy(*pBuff, "K1"); //add"K0"
		for(i = strlen("K1")+1; i > 0; i--)
		{
		*pBuff += 1;
		}
 }
 	 	*pBuff -= 1;
		strcpy(*pBuff, ";");
		*pBuff += 1;
//		printfp(pBuff - 5 - 9 - 1);
	return ret;
}



void ParseBufferE(char *pStart, char *pBuff,  char razd)
{
	char * pPrev;
    char * pNext;
	int i;
	*pBuff++ = '%';
	*pBuff++ = '0';//temporary first digit of address
	*pBuff++ = '0';//temporary second digit of address

//	*pBuff++ = '1';
//	*pBuff++ = '2';
//	*pBuff++ = '3';
//	*pBuff++ = '4';

   pStart += 3;  //#ff - do not need
   pPrev = pStart;
   pNext = pStart;

//   printfp(pStart);
 //	p = strtok(pStart, &razd);
    for(i = 0; i < RCV_BUFF_SIZE; i++)
    { /* Body */
    	 //if(!strcmp(pNext, "BP;BR.")) {
    //	 if(!strncmp(pNext, "BP;BR.",2)) {
    //		i++;
    //		i--;
   // 	 }

  //   if((*pNext & 0xff) == '\0')
   //  {
         //   if(pNext > pPrev)
         //   {
     //          RunCommandE(pPrev, &pBuff);
         //   }
      //  break;
    // }
      //   if((*pNext & 0xff)  ==';')
      if(((*pNext & 0xff)  == razd)	|| 	((*pNext & 0xff)  == '.'))
     {
     *pNext = '\0';  //it's need for strlen == getlen to check request or command
      RunCommandE(pPrev, &pBuff);
      pPrev = pNext;
      pPrev++; //to first symbol of next command
     }
      pNext++;
   } /* Endbody */
    pBuff--;
	strcpy(pBuff, ".");
}

void ReplacePC()
{
 			char *pTBuff = &TrBuff[0];
 			do
 			{
 			if(*pTBuff == '.') *pTBuff = ',';
 			}
 			while(*pTBuff++);
}

void Transmit(void) {
//unsigned long len = strlen(TrBuff);
// SER_Send(len, TrBuff);
//	if(osSemaphoreWait(myBinarySem02_USART2THandle , 1) == osOK) {
		HAL_UART_Transmit_DMA(&huart2,TrBuff,  strlen(TrBuff));
	//	HAL_UART_Transmit_DMA(&huart2,TrBuff,  5); //t
//	}
 // HAL_UART_Transmit(&huart2, TrBuff,  strlen(TrBuff), 100);
}

void Receive(unsigned char OpChar)
{

	static char step = 0;
	static unsigned short CommandSize = 0;
	static char * pRBuff;
//	static char * pTBuff;
//	char OpChar = ReadChar();
//	char OpChar = SetOpChar;
//	ResetWD();
//		printfp3("\n\r Receive");
//	printfpd("%c", OpChar);
//	printfpd(" >%d ", step);
switch (step) {
case 0 :
	if (step == 0) //need wait '#'
	{
//		ResetWD();
		if(OpChar == '#') 
		{
		CommandSize = 0; //start command
		step = 1;
		pRBuff = &RcvBuff[0];
		}
	}
	break;
case 1:
	if (step == 1) // need wait property address
	{
		//need make address class
		if((OpChar == 'f') || (OpChar == 'F'))  //temporary first digit of address
		{
			step = 2;
		}
		else //bad addr
		{
			pRBuff = &RcvBuff[0];
			step = 0;
		}
	}
	break;
case 2:
	 if (step == 2) // need wait property address
	{
		//need make address class
//		if(OpChar == '0') //temporary second digit of address
  	if((OpChar == 'f') || (OpChar == 'F'))  //temporary first digit of address
		{
			step = 3;
			pTBuff = &TrBuff[0];
			*pTBuff++ = '%';
			*pTBuff++ = '0';//temporary first digit of address
			*pTBuff++ = '0';//temporary second digit of address
		}
		else //bad addr
		{
			pRBuff = &RcvBuff[0];
			step = 0;
		}
	}	
	break;
case 3:
	if (step == 3) // write and finished command
	{
		//need make address class
		if(OpChar == '.') //wait end command  
		{
			*pRBuff = '\0'; //to finish string in buffer
			pRBuff = &RcvBuff[0];
			ParseBufferS(pRBuff, ';');
		//hier need get off all points from string (1.<- this points222e11)
	//t		pTBuff--;
	//t		strcpy(pTBuff++, theAnyStrings.cPoint); 
			*pTBuff = '\0'; //	
	    	ReplacePC();
			pTBuff--;
			pTBuff--;
//			printfp("\n\rTrBuff:");
//			printfp(TrBuff);
//			printfp("\n\rpTBuff:");
//			printfp(pTBuff);
//  	strcpy(pTBuff++, '.'); 
			*pTBuff++ = '.';
//			*pTBuff++ = '+';
//		*pTBuff++ = '+';
//		*pTBuff++ = '+';
//		*pTBuff++ = '+';			
			*pTBuff = '\0'; //	
//		printfp("\n\rTrBuff1:");
//			printfp(TrBuff);
//			printfp("\n\rpTBuff1:");
//			printfp(pTBuff);			
			Transmit();
			pTBuff = &TrBuff[0];
			pRBuff = &RcvBuff[0];
			step = 0;
		}
		else if(OpChar == '#') //wait  start new command if previons command is lost
		{
			pRBuff = &RcvBuff[0];
			*pRBuff++ = OpChar;
			step = 1;
		}
		else //write command to buffer
		{
			CommandSize++;
			if(CommandSize < RCV_BUFF_SIZE)
			{
			*pRBuff++ = OpChar;
			}
			else
			{
			pRBuff = &RcvBuff[0];
			step = 0;			
			}
		}		
	  } //3
	 break;
default :

	break;
} //switch
}

