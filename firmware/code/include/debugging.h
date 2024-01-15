#ifndef __DEBUGGING_H__
#define __DEBUGGING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal.h"

void Error_Handler(void);

void DMA_Init(void);

extern UART_HandleTypeDef huart2;
void USART2_UART_Init(void);


#ifdef __cplusplus
}
#endif

#endif // __DEBUGGING_H__
