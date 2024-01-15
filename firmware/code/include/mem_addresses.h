#ifndef __MEM_ADDRESSES_H__
#define __MEM_ADDRESSES_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F401xC

#define __GPIO_BASE_PORT(x) (GPIOA_BASE + (x * 0x400))

#else
#error "MCU not supported"
#endif

#ifdef __cplusplus
}
#endif

#endif // __MEM_ADDRESSES_H__
