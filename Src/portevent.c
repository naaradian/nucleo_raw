/*
 * FreeModbus Libary: lwIP Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portevent.c,v 1.1 2006/08/30 23:18:07 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "assert.h"

/* ----------------------- lwIP ---------------------------------------------*/
#include "lwip/api.h"
#include "lwip/sys.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_POLL_CYCLETIME       100     /* Poll cycle time is 100ms */
/* ----------------------- Static variables ---------------------------------*/
static sys_mbox_t xMailBox = SYS_MBOX_NULL;
static eMBEventType eMailBoxEvent;

/* ----------------------- Start implementation -----------------------------*/
/*
BOOL
xMBPortEventInit( void )
{
    eMailBoxEvent = EV_READY;
    xMailBox = sys_mbox_new(  );
    return xMailBox != SYS_MBOX_NULL ? TRUE : FALSE;
}

*/
typedef struct QueueDefinition
{
	int8_t *pcHead;					/*< Points to the beginning of the queue storage area. */
	int8_t *pcTail;					/*< Points to the byte at the end of the queue storage area.  Once more byte is allocated than necessary to store the queue items, this is used as a marker. */
	int8_t *pcWriteTo;				/*< Points to the free next place in the storage area. */

	union							/* Use of a union is an exception to the coding standard to ensure two mutually exclusive structure members don't appear simultaneously (wasting RAM). */
	{
		int8_t *pcReadFrom;			/*< Points to the last place that a queued item was read from when the structure is used as a queue. */
		UBaseType_t uxRecursiveCallCount;/*< Maintains a count of the number of times a recursive mutex has been recursively 'taken' when the structure is used as a mutex. */
	} u;

	List_t xTasksWaitingToSend;		/*< List of tasks that are blocked waiting to post onto this queue.  Stored in priority order. */
	List_t xTasksWaitingToReceive;	/*< List of tasks that are blocked waiting to read from this queue.  Stored in priority order. */

	volatile UBaseType_t uxMessagesWaiting;/*< The number of items currently in the queue. */
	UBaseType_t uxLength;			/*< The length of the queue defined as the number of items it will hold, not the number of bytes. */
	UBaseType_t uxItemSize;			/*< The size of each items that the queue will hold. */

	volatile int8_t cRxLock;		/*< Stores the number of items received from the queue (removed from the queue) while the queue was locked.  Set to queueUNLOCKED when the queue is not locked. */
	volatile int8_t cTxLock;		/*< Stores the number of items transmitted to the queue (added to the queue) while the queue was locked.  Set to queueUNLOCKED when the queue is not locked. */

	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
		uint8_t ucStaticallyAllocated;	/*< Set to pdTRUE if the memory used by the queue was statically allocated to ensure no attempt is made to free the memory. */
	#endif

	#if ( configUSE_QUEUE_SETS == 1 )
		struct QueueDefinition *pxQueueSetContainer;
	#endif

	#if ( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t uxQueueNumber;
		uint8_t ucQueueType;
	#endif

} xQUEUE;


BOOL
xMBPortEventInit( void )
{
//	sys_mbox_t mbox;
	int size= sizeof(eMBEventType) * 10; //need check value
//	int ret;
    eMailBoxEvent = EV_READY;
 //   xQueueHandle xQueueCreate(unsigned portBASE_TYPE uxQueueLength,
 //    unsigned portBASE_TYPE uxItemSize);
    xMailBox = xQueueCreate(4,sizeof(eMBEventType));
//    sys_mbox_new(&xMailBox, size);
    xQUEUE * const pxQueue = (xQUEUE * ) xMailBox;

    return xMailBox != SYS_MBOX_NULL ? TRUE : FALSE;
}

void
vMBPortEventClose( void )
{
    if( xMailBox != SYS_MBOX_NULL )
    {
        sys_mbox_free( xMailBox );
    }
}

BOOL
xMBPortEventPost( eMBEventType eEvent )
{
    eMailBoxEvent = eEvent;
 //t   sys_mbox_post( xMailBox, &eMailBoxEvent );
    xQueueSend( (xQUEUE * )xMailBox, &eMailBoxEvent, 1000);
    return TRUE;
}

BOOL
xMBPortEventGet( eMBEventType * eEvent )
{
  //  void           *peMailBoxEvent;
   // BOOL            xEventHappend = FALSE;
   // u32_t           uiTimeSpent;
    osEvent event;

  //  uiTimeSpent = sys_arch_mbox_fetch( xMailBox, &peMailBoxEvent, MB_POLL_CYCLETIME );


     event = osMessageGet (xMailBox,0);

    if(event.status == osEventMessage)
      {
     //   *eEvent = *(eMBEventType *)event.value.v;
    	   *eEvent = event.value.v;
 //       return (osKernelSysTick() - starttime);
        return TRUE;
      }
      else
      {
  //      return SYS_ARCH_TIMEOUT;
    	return FALSE;
      }

//    if( uiTimeSpent != SYS_ARCH_TIMEOUT )
 //   {
  //      *eEvent = *( eMBEventType * ) peMailBoxEvent;

    //    eMailBoxEvent = EV_READY;
   //     xEventHappend = TRUE;
  //  }
 //   return xEventHappend;
}
