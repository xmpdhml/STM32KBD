#include "hal.h"
#include "stm32_it.h"

// generic handlers

void NMI_Handler(void)
{
  HAL_RCC_NMI_IRQHandler();
  while (1)
  {
  }
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

// peripheral handlers

extern DMA_HandleTypeDef hdma_usart2_tx;
extern UART_HandleTypeDef huart2;

void DMA1_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_usart2_tx);
}

void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&huart2);
}
