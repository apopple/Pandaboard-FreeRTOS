#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

volatile int *GPIO1_DATAOUT;
volatile int *GPIO1_OE;

static void LedFlash(void *Parameters)
{
  portTickType LastWake;

  *GPIO1_OE &= ~(1 << 8);

  LastWake = xTaskGetTickCount();

  while(1)
  {
    *GPIO1_DATAOUT ^= (1 << 8);
    vTaskDelayUntil(&LastWake, 1000);
  }
}

int main()
{
  volatile int i;
  GPIO1_DATAOUT = (int *) 0xfff1013c;
  GPIO1_OE = (int *) 0xfff10134;

  *GPIO1_OE &= ~(1 << 8);

  /* Only continue execution on one core ... there is an obvious race condition here howver so we need a better
     way of determining which processor we are running on. But this quick and nasty hack works for demo
     purposes. */
  if( *GPIO1_DATAOUT & (1 << 8))
  {
    while(1);
  }

  *GPIO1_DATAOUT |= (1 << 8);

  xTaskCreate(LedFlash, (signed char *) "LedFlash", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  vTaskStartScheduler();

  /* Just sit and flash the LED quickly if we fail */
  while( 1 )
  {    
    for( i = 0; i < 100000; i++ );
    *GPIO1_DATAOUT ^= (1 << 8);
  }
}
