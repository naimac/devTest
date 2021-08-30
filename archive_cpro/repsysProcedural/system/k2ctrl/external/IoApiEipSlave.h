/*------------------------------------------------------------------------------
*                             (c) 2015 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing EtherNet/IP slave devices
*
*   Interface for controlling EtherNet/IP slave.
*/


#ifndef IOAPIEIPSLAVE_H_
#define IOAPIEIPSLAVE_H_

#include "IoApiTypes.h"
#include "IoApiAsync.h"
#include "IoApiEipTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/**
 * @brief Get the state of a EtherNet/IP slave device.
 *
 * This method gets the actual state of a EtherNet/IP slave device. The call is
 * not blocking and returns immediately after the operation has been submitted.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    For this asynchronous method, the function IoApiAsyncGetResult() can
 *    have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvOverlapped, if the given IoApiOverlapped is already in
 *         use.
 */

IoApiState IoApiEipSlaveGetDeviceStateAsyncStart(
   IoApiHdl                    devHdl,        /**< [in]  Device handle. */
   IoApiEipSlaveDeviceState   *devState,      /**< [out] Device state. */
   IoApiOverlapped            *ov             /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Enables the watchdog of a EtherNet/IP slave device.
 *
 * This method enables the watchdog of a EtherNet/IP slave device. The call is
 * not blocking and returns immediately after the operation has been submitted.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    For this asynchronous method, the function IoApiAsyncGetResult() can
 *    have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid address.
 *         IoApiStateInvalidParam, if there is an invalid parameter.
 *         IoApiStateTimeout, if a timeout occurred.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvOverlapped, if the given IoApiOverlapped is already in
 *         use.
 */
IoApiState IoApiEipSlaveEnableWatchdogAsyncStart(
   IoApiHdl          devHdl,         /**< [in]  Device handle. */
   IoApiOverlapped  *ov              /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Disables the watchdog of a EtherNet/IP slave device.
 *
 * This method disables the watchdog of a EtherNet/IP slave device. The call is
 * not blocking and returns immediately after the operation has been submitted.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    For this asynchronous method, the function IoApiAsyncGetResult() can
 *    have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid address.
 *         IoApiStateInvalidParam, if there is an invalid parameter.
 *         IoApiStateTimeout, if a timeout occurred.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvOverlapped, if the given IoApiOverlapped is already in
 *         use.
 */
IoApiState IoApiEipSlaveDisableWatchdogAsyncStart(
   IoApiHdl          devHdl,         /**< [in]  Device handle. */
   IoApiOverlapped  *ov              /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Triggers the watchdog of a EtherNet/IP slave device.
 *
 * This method triggers the watchdog of a EtherNet/IP slave device. The call is
 * not decoupled so it runs within the context of the caller.
 *
* @return State information about the operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidParam, if there is an invalid parameter.
 *         IoApiEipSlaveStateInvalidState, if the state is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEipSlaveTriggerWatchdog(
   IoApiHdl       devHdl         /**< [in]  Device handle. */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOAPIEIPSLAVE_H_ */
