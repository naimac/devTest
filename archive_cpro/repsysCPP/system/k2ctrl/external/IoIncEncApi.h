/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing the latching functionality of incremental encoders.
*	
*   Interface for controlling incremental encoders.
*/

#ifndef IOINCENCAPI_H_
#define IOINCENCAPI_H_

#include "IoApiTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

const uint32_t IoIncEncTimeoutInfinite = (uint32_t)(-1);

typedef uint8_t IoIncEncSetCountMode;
enum {
   IoIncEncSetCountModePLCTick      = 1,     /**< Set value with the next IO tick. */
   IoIncEncSetCountModeZero         = 2,     /**< Set value with the next passing of the encoders zero position. */
   IoIncEncSetCountModeDI           = 3      /**< Set value on a DI edge. */
};


/******************************************************************************/
/**
 * @brief Set the counter value of an incremental encoder.
 *
 * Set the counter value of an incremental encoder device.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvalidAddr, if ov points to no valid IoApiOverlapped.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiIncEncSetCountAsyncStart(
   IoApiHdl                 devHdl,       /**< [in]  Device handle. */
   uint32_t                 port,         /**< [in]  Specifies which port of the encoder device should be used. */
   IoIncEncSetCountMode     mode,         /**< [in]  Specifies the mode when to set the given counter. */
   int32_t                  count,        /**< [in]  Counter that should be set at the incremental encoder. */
   IoApiOverlapped         *ov            /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );



/******************************************************************************/
/**
 * @brief Read the counter value when passing the encoders zero position.
 *
 * Reads the counter value when the given incremental encoder passes its zero position.
 * This method works asynchronously because it can take some time until this happens.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvalidAddr, if ov points to no valid IoApiOverlapped.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiIncEncLatchZeroAsyncStart(
   IoApiHdl           devHdl,          /**< [in]  Device handle. */
   uint32_t           port,            /**< [in]  Specifies which port of the encoder device should be used. */
   int32_t           *count,           /**< [out] Counter value of the incremental encoder. */
   IoApiOverlapped   *ov               /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Read the counter value of a DI edge.
 *
 * Reads the counter value of a rising or falling DI edge.
 * This method works asynchronously because it can take some time until this happens.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvalidAddr, if ov points to no valid IoApiOverlapped.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiIncEncLatchDIAsyncStart(
   IoApiHdl           devHdl,          /**< [in]  Device handle. */
   uint32_t           port,            /**< [in]  Specifies which port of the encoder device should be used. */
   int32_t           *count,           /**< [out] Counter value of the incremental encoder. */
   uint32_t          *timestampUs,     /**< [out] Time since the last latch event in µs. */
   IoApiOverlapped   *ov               /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOINCENCAPI_H_ */
