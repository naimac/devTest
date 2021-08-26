/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoApiRawCan base type definitions
*
*   IoApiRawCan standard return code definitions and declaration of types.
*/

#ifndef IOAPIRAWCANTYPES_H_
#define IOAPIRAWCANTYPES_H_

#include <stdint.h>


/******************************************************************************/
/**
 *  @brief Return code definition
 *
 *  Return code definition of raw CAN functions.
 *  These return codes extend the IoApiState which is defined in IoApiTypes.h.
 */
enum {
   IoApiRawCanStateRawModeNotSupported    = 0x00000501UL,      /**< Raw can mode not configured for CAN bus. */
   IoApiRawCanStateBusy                   = 0x00000502UL,      /**< Raw can already in use. */
   IoApiRawCanStateInvalidState           = 0x00000503UL,      /**< Hardware not accessible. */
   IoApiRawCanStateError                  = 0x00000504UL       /**< Error during access of raw can. */
};


/******************************************************************************/
/**
 * @brief Raw can message.
 */
typedef struct IoApiRawCanMsg {
   uint16_t msgId;            /**< CAN message id (11 Bit, 0 to 2031). */
   uint8_t  rtr;              /**< RTR-Bit, for fetch and response to fetch. */
   uint8_t  len;              /**< Message length. */
   uint8_t  data[8];          /**< Message data. */
} IoApiRawCanMsg;


#endif /* IOAPIRAWCANTYPES_H_ */
