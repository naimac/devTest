/*------------------------------------------------------------------------------
*                             (c) 2018 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoApiSysBus base type definitions
*
*   IoApiSysBus declaration of types.
*/

#ifndef IOAPISYSBUSTYPES_H_
#define IOAPISYSBUSTYPES_H_

#include <stdint.h>

typedef struct {
   uint8_t data[47];    /**< diagnosis data */
} TIoApiSysBusDiagData;

typedef struct {
   uint8_t data[4];    /**< alarm data */
} TIoApiSysBusAlarmData;

#endif /* IOAPISYSBUSTYPES_H_ */
