#ifndef __HAL_H__
#define __HAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F401xC
#include "stm32f4xx_hal.h"
#endif


void GPIO_Init(void);


#ifdef __cplusplus
}
#endif

#endif // __HAL_H__
