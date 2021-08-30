/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for starting asynchronous IO operations
*
*   Interface for starting asynchronous IO operations
*/

#ifndef IOAPIASYNC_H_
#define IOAPIASYNC_H_

#include <stdint.h>
#include "IoApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This structure is needed to perform asynchronous operations.
 * The elements must not be changed!
*/
typedef struct IoApiOverlapped {
   uint32_t _internal1;       /**< do not use */
   uint32_t _internal2;       /**< do not use */
   uint32_t _internal3;       /**< do not use */
   uint32_t _internal4;       /**< do not use */
   uint32_t _reserved1;       /**< do not use */
   uint32_t _reserved2;       /**< do not use */
} IoApiOverlapped;

/******************************************************************************/
/**
 * @brief Initialize an IoApiOverlapped object.
 *
 * Initializes a given IoApiOverlapped object.
 */
void InitIoApiOverlapped(
   IoApiOverlapped *ov        /**< [out]  use the IoApiOverlapped object returned by IoApiAsyncStart() functions */
   );


/******************************************************************************/
/**
 * @brief Check completion of an asynchronous operation and get the result.
 *
 * Poll for the result of an asynchronous operation started by an IoApiAsyncStart() function.
 *    ATTENTION:
 *        An asynchronous operation must be polled with this method until the returned IoApiState is not IoApiStatePending.
 *        This is necessary to avoid memory leaks.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if the operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStatePending, if the operation is not completed yet
 *         In case of an error specific error codes depending on the called IoApiXXXAsyncStart function are returned.
 */
IoApiState IoApiAsyncGetResult(
   IoApiOverlapped *ov        /**< [in]  use the IoApiOverlapped object returned by IoApiAsyncStart() functions */
   );

#ifdef __cplusplus
}
#endif

#endif /* IOAPIASYNC_H_ */
