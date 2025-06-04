/**
 * @file Config.hpp
 * @author JIANG Yicheng RM2023
 * @brief
 * @version 0.1
 * @date 2023-01-23
 *
 * @copyright Copyright (c) 2023
 */

#pragma once

#define configASSERT(x) \
    if (!(x))           \
        __asm volatile("bkpt ");

// #define USE_CCMRAM_ALIAS

#ifdef USE_CCMRAM_ALIAS
#define CCMRAM_ALIAS_OFFSET (0x20018000 - 0x10000000)
#define CCMRAM_ALIAS_ADDRESS(pBuffer) \
    (reinterpret_cast<uint32_t *>(reinterpret_cast<uint32_t>(pBuffer) + CCMRAM_ALIAS_OFFSET))
#else
#define CCMRAM_ALIAS_ADDRESS(pBuffer) (pBuffer)
#endif
