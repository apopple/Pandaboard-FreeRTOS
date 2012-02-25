#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

static void LedFlash(void *Parameters)
{
  int i;
  portTickType LastWake;

  *(int *) 0xfff10134 &= ~(1 << 8);

  LastWake = xTaskGetTickCount();

  while(1)
  {
    *(int *) 0xfff1013c ^= (1 << 8);
    vTaskDelayUntil(&LastWake, 1000);
  }
}

int main()
{
  xTaskCreate(LedFlash, "LedFlash", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  vTaskStartScheduler();

  while( 1 );
}
