#ifndef __MEM_ADDRESSES_H__
#define __MEM_ADDRESSES_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F401xC

#ifndef USE_BIT_BANDING
#define USE_BIT_BANDING 1
#endif

#define __GPIO_BASE_PORT(x) (GPIOA_BASE + (x * 0x400))

#define __GPIO_BB_BASE_PORT(x) (PERIPH_BB_BASE + (GPIOA_BASE + (x * 0x400) - PERIPH_BASE) * 0x20)


#else
#error "MCU not supported"
#endif

#ifdef __cplusplus
}
#endif

#endif // __MEM_ADDRESSES_H__
