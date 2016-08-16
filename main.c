#include "easyRTOS.h"
#include "easyRTOSkernel.h"
#include "easyRTOSport.h"
#include "easyRTOSTimer.h"

#define IDLE_STACK_SIZE_BYTES 256
#define TEST_STACK_SIZE_BYTES 512
NEAR static uint8_t idleTaskStack[IDLE_STACK_SIZE_BYTES];
NEAR static uint8_t testTaskStack[TEST_STACK_SIZE_BYTES];

EASYRTOS_TCB testTcb;
void testTaskFunc (uint32_t param);
int main( void )
{
  ERESULT status;
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  status = easyRTOSInit(&idleTaskStack[0], IDLE_STACK_SIZE_BYTES);
  
  if (status == EASYRTOS_OK)
  {
      /* Enable the system tick timer */
      archInitSystemTickTimer();

      /* Create an application task */
      status += eTaskCreat(&testTcb,
                   10, 
                   testTaskFunc, 
                   3,
                   &testTaskStack[0],
                   TEST_STACK_SIZE_BYTES,
                   "TEST",
                   1);
      if (status == EASYRTOS_OK)
      {
         easyRTOSStart();
      }
  }
  return 0;
}

void testTaskFunc (uint32_t param)
{
  ERESULT status1=0;
  status1 = status1;
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);
  while (1)
  {
    status1=eTimerDelay(DELAY_S(param));
    GPIO_WriteReverse(GPIOD, GPIO_PIN_2);
  }
}