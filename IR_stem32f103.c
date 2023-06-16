#include "stm32f10x.h"

// define the pin for IR sensor
#define IR_SENSOR_PIN GPIO_Pin_0
#define IR_SENSOR_PORT GPIOA
// some function
void GPIO_Configuration(void);
void EXTI_Configuration(void);
void Delay( uint8_t counter);

int main(void)
{
  GPIO_Configuration();
  EXTI_Configuration();

  while (1)
  {

    uint8_t irState = GPIO_ReadInputDataBit(IR_SENSOR_PORT, IR_SENSOR_PIN);

    if (irState == 0)
    {
     printf("detected");
    }
    else
    {
      printf("not detection");
    }
  }
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // Enable GPIOA clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


  GPIO_InitStructure.GPIO_Pin = IR_SENSOR_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(IR_SENSOR_PORT, &GPIO_InitStructure);
}

void EXTI_Configuration(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;


  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);


  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);


  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
// interrupt 

  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    // Handle the interrupt

    // Clear the EXTI line pending bit
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void Delay(uint_8t counter)
{
  for (; counter != 0; counter--)
    ;
}
