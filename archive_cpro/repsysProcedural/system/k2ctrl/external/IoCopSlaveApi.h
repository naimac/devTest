/*------------------------------------------------------------------------------
*                             (c) 2014 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing the CANopen protocol
*	
*   The interface contains CANOpen slave related functions. This includes sending
*   emergencies, checking state. Interaction on SDO transfers is possible. Data
*   of SDO write requests can be evaluated, data for SDO read requests can be
*   provided.
*/

#ifndef IOCOPSLAVEAPI_H_
#define IOCOPSLAVEAPI_H_

#include "IoApiTypes.h"
#include "IoCopApiTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  CANopen
*/


/******************************************************************************/
/**
 * @brief Connect application to slave IO driver.
 *
 * If "autoStart=0" is configured, this method is used
 * to signal the IO driver that the application is ready.
 * After that, the Network Management (NMT) state changes to Pre-Operational.
 * The call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoCopApiStateConInvalidConfig, if autoStart = 1 is configured
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveConnect(
   IoApiHdl     devHdl      /**< [in]  Device handle. */
   );


/******************************************************************************/
/**
 * @brief Disconnect application from slave IO driver.
 *
 * If "autoStart=0" is configured, this method is used
 * to signal the IO driver that the application is not ready any more.
 * After that, the Network Management (NMT) state changes to Init.
 * The call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoCopApiStateConInvalidConfig, if autoStart = 1 is configured
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveDisconnect(
   IoApiHdl     devHdl      /**< [in]  Device handle. */
   );


/******************************************************************************/
/**
 * @brief Send an emergency for CANOpen Slave asynchronously.
 *
 * Start sending an emergency message asynchronous. The configured COB-ID
 * (SDO 0x1014) is used:
 *    Error register value is written to 0x1001 automatically.
 *    Poll for result with function IoApiAsyncGetResult().
 *    For this asynchronous method, the function IoApiAsyncGetResult() can
 *    have the following return states:
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoCopApiStateEmcyInvalidState, if autoStart = 1 is configured
 *         IoApiStateNotOk, if an error occurred
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiCopSlaveSendEmergencyAsyncStart(
   IoApiHdl          devHdl,      /**< [in]  Device handle. */
   IoCopEmergency   *data,        /**< [in]  Emergency data. */
   IoApiOverlapped  *ov           /**< [out] This function fills an IoApiOverlapped
                                             object which can be passed to
                                             IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Get event.
 *
 * This method gets a pending event from slave's event fifo. The event fifo
 * should be polled cyclically, eg. every 200 milliseconds.
 * If the event fifo is not empty it should be read again as long as
 * IoCopApiStateEvtNoMoreData is returned. The call is not decoupled so it runs
 * within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoCopApiStateEvtNoMoreData, if event fifo is empty
 *         IoCopApiStateEvtQueueOverrun, if event fifo run over
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveGetEvent(
   IoApiHdl          devHdl,      /**< [in]  Device handle. */
   IoCopSlaveEvent  *event        /**< [out] Pending event type. */
   );


/******************************************************************************/
/**
 * @brief Get NMT state of the slave.
 *
 * This method gets the Network Management (NMT) state of the slave.
 * The NMT state changes after NMT commands from CANOpen master. By means of
 * configuration "autoStart=0" and @see IoApiCopSlaveConnect the state change
 * to Pre-Operational can be delayed until application is ready. The call is
 *  not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveGetNmtState(
   IoApiHdl        devHdl,      /**< [in]  Device handle. */
   IoCopNmtState  *state        /**< [out] NMT state of the slave. */
   );


/******************************************************************************/
/**
 * @brief Get Guarding state of a slave.
 *
 * This method gets the Guarding state of a slave.
 * (Node and Life) Guarding is activated from CANOpen master with access to
 * objects 0x100C and 0x100D. The call is not decoupled so it runs within the
 * context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveGetGuardingState(
   IoApiHdl             devHdl,      /**< [in]  Device handle. */
   IoCopGuardingState  *state        /**< [out] Guarding state of the slave. */
   );


/******************************************************************************/
/**
 * @brief Get Heartbeat state of a slave.
 *
 * This method gets the Heartbeat state of a slave.
 * Heartbeat consume and heartbeat produce is activated from CANOpen master
 * with access to objects 0x1016 and 0x1017. The call is not decoupled so it
 * runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveGetHeartbeatState(
   IoApiHdl                  devHdl,      /**< [in]  Device handle. */
   IoCopHeartbeatProdState  *prodState,   /**< [out] Heartbeat produce state of the slave. */
   IoCopHeartbeatConsState  *consState    /**< [out] Heartbeat consume state of the slave. */
   );


/******************************************************************************/
/**
 * @brief Get PDO state.
 *
 * This method gets the state of a PDO from a slave. The call is not decoupled
 * so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateInvalidParam, if the parameter is invalid
 *         IoCopApiStateNoMorePdoData, if PDO number is greater than available PDO's.
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveGetPdoState(
   IoApiHdl          devHdl,      /**< [in]  Device handle. */
   IoCopPdoDir       pdoDir,      /**< [in]  PDO type. */
   uint32_t          pdoNr,       /**< [in]  PDO number within valid range (1..21). */
   IoCopPdoState    *state        /**< [out] PDO state. */
   );


/******************************************************************************/
/**
 * @brief Add SDO to request indication of slave.
 *
 * This method adds a SDO to request indication of slave.
 * To get indication about a SDO request the index and subindex of the SDO has
 * to be registered at request indication.
 * A SDO request of a registered index and subindex is indicated by event
 * @see IoCopSlaveEventSdoRequest.
 * The call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateInvalidParam, if the parameter is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveAddSdoToRequestInd(
   IoApiHdl     devHdl,         /**< [in]  Device handle. */
   uint32_t     index,          /**< [in]  Index. */
   uint32_t     subIndex        /**< [in]  Sub index. */
   );


/******************************************************************************/
/**
 * @brief Remove SDO from request indication of a slave.
 *
 * This method removes a SDO from request indication of a slave. The call is
 * not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateInvalidParam, if the parameter is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveRemoveSdoFromRequestInd(
   IoApiHdl     devHdl,         /**< [in]  Device handle. */
   uint32_t     index,          /**< [in]  Index. */
   uint32_t     subIndex        /**< [in]  Sub index. */
   );


/******************************************************************************/
/**
 * @brief Get data of indicated SDO request of a slave.
 *
 * Index, sub index, direction and for SDO Write the data can be read.
 * SDO request indication has to be confirmed with
 * @see IoApiCopSlaveConfirmSdoRequestInd.
 * Otherwise no SDO response message is sent and SDO transfer at CANOpen master
 * runs into timeout.
 * The call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateInvalidParam, if the parameter is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveGetSdoRequestIndData(
   IoApiHdl      devHdl,        /**< [in]  Device handle. */
   uint32_t     *pIndex,        /**< [out] Buffer for index. */
   uint32_t     *pSubIndex,     /**< [out] Buffer for sub index. */
   IoCopSdoDir  *pSdoDir,       /**< [out] Buffer for SDO direction */
   SdoData      *pData,         /**< [out] Buffer for SDO data if SDO direction
                                           is IoCopDirSdoWrite, download data from
                                           master is copied to buffer. */
   uint32_t     *pDataLen       /**< [out] Buffer for length of data in pData
                                           if SDO direction is IoCopDirSdoWrite. */
   );


/******************************************************************************/
/**
 * @brief Confirm indicated SDO request of a slave.
 *
 * Data of SDO request is read with @see IoApiCopSlaveGetSdoRequestIndData.
 * This method is required to send a SDO response message.
 * The call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateInvalidParam, if the parameter is invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopSlaveConfirmSdoRequestInd(
   IoApiHdl      devHdl,        /**< [in]  Device handle. */
   SdoData      *data,          /**< [in]  Buffer for SDO data if SDO direction is
                                           IoCopDirSdoRead, contains upload data
                                           from slave. */
   uint32_t      dataLen,       /**< [in]  Data length in pData if SDO direction
                                           is IoCopDirSdoRead. */
   uint32_t      abortCode      /**< [in]  SDO abort code, 0 for successful SDO
                                           transfer. In case of an error, use SDO
                                           abort code values from CANOpen specification. */
   );

#ifdef __cplusplus
}
#endif

#endif /* IOCOPSLAVEAPI_H_ */
