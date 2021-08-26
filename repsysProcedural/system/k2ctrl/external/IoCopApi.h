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
*   The interface contains CANOpen master related functions for reading and
*   writing Service Data Objects (SDO), emergency message access, node guarding,
*   triggering of remote-transmit-request (RTR) process data objects (PDO),
*   triggering of sending asynchronous PDO's, network management (NMT) commands.
*/

#ifndef IOCOPAPI_H_
#define IOCOPAPI_H_

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
 *  @brief Execute a SDO transfer.
 *
 *  Execute a Service Data Objects (SDO) transfer.
 *
 *  @attention Function waits internally for response from CANOpen slave, it
 *  should not be used in high priority context.
 *
 *  @attention For each device only 16 sdo requests may be started at the
 *  same time.
 *
 * @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if transfer has been finished.
 */
IoApiState IoApiCopReadSdo(
   IoApiHdl  devHdl,                       /**< [in]  Device handle. */
   uint32_t  index,                        /**< [in]  Index. */
   uint32_t  subIndex,                     /**< [in]  Sub index. */
   uint32_t  cnfTimeout,                   /**< [in]  Max. wait time for response of a SDO-request. Unit: us */
   uint32_t  len,                          /**< [in]  Length of data buffer. */
   SdoData  *pData,                        /**< [out] Data buffer. */
   uint32_t *pBytesRead                    /**< [out] Number of bytes transferred. */
   );


/******************************************************************************/
/**
 *  @brief Start an asynchronous read SDO transfer.
 *
 *  Start the execution of a Service Data Objects (SDO) read transfer. If the
 *  registration of the read task was successful a job handle is delivered.
 *  After the transfer the job handle must be closed with the 'IoApiEndSdo'
 *  function. The function is performed asynchronously so the results must be
 *  polled with 'IoApiAsyncGetResult'. The SDO transfer length can be bigger
 *  than the standard 256 bytes buffer and is given by 'maxSdoLength'. An
 *  internal data buffer is filled during the read operation and can be read
 *  in 256 byte chunks with the 'IoApiCopGetReadSdoData' function.
 *
 *  @attention For each device only 16 sdo requests may be started at the
 *  same time.
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateQueueOverrun, if the transfer could not be started because
 *         of too many pending transfers. For each device the possible number
 *         of parallel transfers is 16.
 *         IoApiStateInvalidParam, if an parameter is invalid
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateNotSupported, if this function is not supported for the device
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateInvalidParam, if invalid IoApiOverlapped is given.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiCopBeginReadSdo(
   IoApiHdl         devHdl,                /**< [in]  Device handle. */
   uint32_t         index,                 /**< [in]  Index. */
   uint32_t         subIndex,              /**< [in]  Sub index. */
   uint32_t         cnfTimeout,            /**< [in]  Max. wait time for confirmation of a SDO-request. Unit: us */
   uint32_t         maxWaitTime,           /**< [in]  Max. wait time for start of SDO transfer. Unit: us */
   uint32_t         maxSdoLength,          /**< [in]  Max. data length of SDO data. */
   IoCopSdoOption   sdoOption,             /**< [in]  Access option for SDO transfer. */
   IoCopSdoResult  *pSdoResult,            /**< [out] Result of SDO transfer. */
   uint32_t        *pJobHdl,               /**< [out] Job handle. */
   IoApiOverlapped *ov                     /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Get SDO data which were read by 'IoApiCopBeginReadSdo'.
 *
 *  Get the SDO data from the internal data buffer which is filled by the
 *  'IoApiCopBeginReadSdo' function. The data will be read beginning at the
 *  offset given by 'dataOffset'. The data can be read in data chunks of maximal
 *  256 byte lengths. This means if a 1kByte transfer should be read the
 *  'IoApiCopGetReadSdoData' functions need to be called four times with
 *  'dataOffset' accordingly set to 0, 256, 512 and 768. The call is
 *  not decoupled so it runs within the context of the caller.
 *
 *  @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiCopGetReadSdoData(
   uint32_t  jobHdl,                       /**< [in]  Job handle. */
   uint32_t  dataOffset,                   /**< [in]  Data offset.  */
   uint32_t  len,                          /**< [in]  Length of data to be read from the internal transfer buffer. */
   SdoData  *pData                         /**< [out] Data buffer into which should be read from the internal transfer buffer. */
   );

/******************************************************************************/
/**
 *  @brief Execute a SDO download.
 *
 *  Execute a Service Data Objects (SDO) download.
 *
 *  @attention Function waits internally for response from CANOpen slave, it
 *  should not be used in high priority context.
 *
 *  @attention For each device only 16 sdo requests may be started at the
 *  same time.
 *
 * @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiCopWriteSdo(
   IoApiHdl  devHdl,                       /**< [in]  Device handle. */
   uint32_t  index,                        /**< [in]  Index. */
   uint32_t  subIndex,                     /**< [in]  Sub index. */
   uint32_t  cnfTimeout,                   /**< [in]  Max. wait time for response of a SDO-request. Unit: us */
   uint32_t  len,                          /**< [in]  Length of data buffer. */
   SdoData  *pData,                        /**< [in]  Data buffer. */
   uint32_t *pBytesWritten                 /**< [out] Number of bytes transferred. */
   );


/******************************************************************************/
/**
 *  @brief Start an asynchronous write SDO transfer.
 *
 *  Start the execution of a Service Data Objects (SDO) write transfer for which
 *  the transferred SDO data length can be bigger than the standard SDO size of
 *  256 bytes. The actual length is given by 'sdoLength'. If the registration
 *  of the write task was successful a job handle is delivered. The data itself
 *  can be set with the 'IoApiCopSetWriteSdoData' function. To execute the
 *  actual write activity 'IoApiCopExecuteWriteSdo' must be called. After the
 *  transfer the job handle must be closed with the 'IoApiEndSdo' function. The
 *  call itself is not decoupled so it runs within the context of the caller.
 *
 *  @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiCopBeginWriteSdo(
   IoApiHdl        devHdl,                 /**< [in]  Device handle. */
   uint32_t        index,                  /**< [in]  Index. */
   uint32_t        subIndex,               /**< [in]  Sub index. */
   uint32_t        cnfTimeout,             /**< [in]  Max. wait time for confirmation of a SDO-request. Unit: us */
   uint32_t        maxWaitTime,            /**< [in]  Max. wait time for start of SDO transfer. Unit: us */
   uint32_t        sdoLength,              /**< [in]  Length of SDO data to transfer. */
   IoCopSdoOption  sdoOption,              /**< [in]  Access option for SDO transfer. */
   uint32_t       *pJobHdl                 /**< [out] Job handle. */
   );


/******************************************************************************/
/**
 *  @brief Set SDO data to be transferred by 'IoApiCopBeginWriteSdo'.
 *
 *  Set the SDO data into the internal data buffer which should be transferred
 *  by calling the 'IoApiCopExecuteWriteSdo' function. The data is set in data
 *  chunks of maximal 256 byte lengths. This means if a 1kByte transfer should
 *  be set the 'IoApiCopSetWriteSdoData' functions need to be called four times
 *  with 'dataOffset' accordingly set to 0, 256, 512 and 768. The call itself
 *  is not decoupled so it runs within the context of the caller.
 *
 *  @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiCopSetWriteSdoData(
   uint32_t  jobHdl,                       /**< [in]  Job handle. */
   uint32_t  dataOffset,                   /**< [in]  Data offset. */
   uint32_t  len,                          /**< [in]  Length of data to be set within internal transfer buffer. */
   SdoData  *pData                         /**< [in]  Data buffer which should be set within internal transfer buffer. */
   );


/******************************************************************************/
/**
 *  @brief Execute the SDO write activity
 *
 *  Executes the actual write activity for an SDO transfer. The SDO transfer
 *  must be initiated with the 'IoApiCopBeginWrite' function. The data which
 *  should be transferred must be set with the 'IoApiCopSetWriteSdoData'
 *  function. The execution of the SDO transfer itself is performed
 *  asynchronously so the results must be polled with 'IoApiAsyncGetResult'.
 *
 *  @attention For each device only 16 sdo requests may be started at the
 *  same time.
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateQueueOverrun, if the transfer could not be started because
 *         of too many pending transfers. For each device the possible number
 *         of parallel transfers is 16.
 *         IoApiStateInvalidParam, if an parameter is invalid
 *         IoApiStateInvalidHandle, if the device handle is invalid
 *         IoApiStateNotSupported, if this function is not supported for the device
 *         IoApiStateNotOk, if an error occurred.
 *
 *  @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiCopExecuteWriteSdo(
   uint32_t         jobHdl,                /**< [in]  Job handle. */
   IoCopSdoResult  *pSdoResult,            /**< [out] Result of SDO transfer. */
   IoApiOverlapped *ov                     /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Close job handle.
 *
 *  Close the job handle which was created by calling the 'IoApiCopBeginReadSdo'
 *  or 'IoApiCopBeginWriteSdo' functions. The internally used data buffer is
 *  freed. The call itself is not decoupled so it runs within the context of
 *  the caller.
 *
 *  @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if operation has been finished.
 */
IoApiState IoApiEndSdo(
   uint32_t jobHdl                         /**< [in]  Job handle. */
   );


/******************************************************************************/
/**
 * @brief Execute a SDO transfer asynchronously.
 *
 * Start to execute a Service Data Objects (SDO) transfer:
 *
 *  @attention For each device only 16 sdo requests may be started at the
 *  same time.
 *
 *    Same functionality as IoApiCopReadSdo(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiCopReadSdoAsyncStart(
   IoApiHdl  devHdl,                       /**< [in]  Device handle. */
   uint32_t  index,                        /**< [in]  Index. */
   uint32_t  subIndex,                     /**< [in]  Sub index. */
   uint32_t  cnfTimeout,                   /**< [in]  Max. wait time for response of a SDO-request. Unit: us */
   uint32_t  len,                          /**< [in]  Length of data buffer. */
   SdoData  *pData,                        /**< [out] Data buffer. */
   uint32_t *pBytesRead,                   /**< [out] Number of bytes transferred. */
   IoApiOverlapped *ov                     /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Execute a SDO download asynchronously.
 *
 * Start execute a Service Data Objects (SDO) download:
 *
 *  @attention For each device only 16 sdo requests may be started at the
 *  same time.
 *
 *    Same functionality as IoApiCopWriteSdo(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiCopWriteSdoAsyncStart(
   IoApiHdl  devHdl,                       /**< [in]  Device handle. */
   uint32_t  index,                        /**< [in]  Index. */
   uint32_t  subIndex,                     /**< [in]  Sub index. */
   uint32_t  cnfTimeout,                   /**< [in]  Max. wait time for response of a SDO-request. Unit: us */
   uint32_t  len,                          /**< [in]  Length of data buffer. */
   SdoData  *pData,                        /**< [in]  Data buffer. */
   uint32_t *pBytesWritten,                /**< [out] Number of bytes transferred. */
   IoApiOverlapped *ov                     /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Gets the amount of emergencies.
 *
 * This method gets the amount of existing CanOpen emergencies in the queue.
 * The call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateQueueOverrun, if the call has been successful and the emergencies exceeded the queue size
 *         IoApiStateInvalidHandle, if the given device handle is invalid.
 *         IoApiStateNotReady, if the device is not ready.
 *         IoApiStateNotOk, if emergency queue is disabled or an undefined error occurred.
 */
IoApiState IoApiCopGetNoOfEmergencies(
   IoApiHdl     devHdl,                    /**< [in]  Device handle. */
   uint32_t    *noOfEmergencies            /**< [out] Amount of emergencies in the queue. */
   );


/******************************************************************************/
/**
 * @brief Gets an emergency from the queue.
 *
 * This method gets the first CanOpen emergency from the queue. The call is not
 * decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if emergency queue is disabled or an undefined error occurred.
 */
IoApiState IoApiCopGetEmergency(
   IoApiHdl           devHdl,            /**< [in]  Device handle. */
   IoCopEmergency    *data               /**< [out] Emergency data. */
   );



/******************************************************************************/
/**
 * @brief Enable Node-Guarding.
 *
 * This method enables the Node-Guarding feature for a CANOpen device. The call
 * is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopEnableNodeGuarding(
   IoApiHdl          devHdl            /**< [in]  Device handle. */
   );


/******************************************************************************/
/**
 * @brief Disable Node-Guarding.
 *
 * This method disables the Node-Guarding feature for a CANOpen device. The
 * call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopDisableNodeGuarding(
   IoApiHdl          devHdl            /**< [in]  Device handle. */
   );


/******************************************************************************/
/**
 * @brief Update node state.
 *
 * This method triggers a node state request.
 * This is only necessary for devices where NodeGuarding is disabled.
 * If NodeGuarding is enabled, this call is useless because
 * the state will be updated with the cyclic NodeGuarding. The call is not
 * decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopUpdateNodeState(
   IoApiHdl          devHdl             /**< [in]  Device handle. */
   );


/******************************************************************************/
/**
 * @brief Get nodes NMT state.
 *
 * This method gets the Network Management (NMT) state of a CANOpen device. The
 * call is not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopGetNodeState(
   IoApiHdl          devHdl,            /**< [in]  Device handle. */
   IoCopNmtState    *nmtState           /**< [out] NMT state of the slave. */
   );


/******************************************************************************/
/**
 * @brief Trigger PDO read.
 *
 * This method triggers a remote transmit request on a RTR-PDO.
 * Poll result with IoApiCopGetPdoState(). The call is not decoupled so it runs
 * within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopReadPdo(
   IoApiHdl     pdoHdl      /**< [in]  PDO handle. */
   );


/******************************************************************************/
/**
 * @brief Get PDO-State.
 *
 * This method checks if the RTR-PDO has been received since the last call of
 * IoApiCopReadPdo(). The call is not decoupled so it runs within the context of
 * the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopGetPdoState(
   IoApiHdl     pdoHdl,     /**< [in]  PDO handle. */
   int         *isValid     /**< [out] PDO is valid. */
   );


/******************************************************************************/
/**
 * @brief Trigger PDO write.
 *
 * This method sends a PDO to a CANOpen device. The configured transmission
 * type of the PDO may not be "cyclic synchronous". The call is not decoupled
 * so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopWritePdo(
   IoApiHdl     pdoHdl      /**< [in]  PDO handle. */
   );


/******************************************************************************/
/**
 * @brief Execute NMT command.
 *
 * Start execute a  Network Management (NMT) action at a CANOpen device:
 *    Poll for result with function IoApiAsyncGetResult().
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
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiCopNmtAsyncStart(
   IoApiHdl         devHdl,               /**< [in]  Device handle. */
   IoCopNmtAction   nmtAction,            /**< [in]  NMT action. */
   uint32_t         maxWaitTimeUs,        /**< [in]  Maximum time to wait until the NMT action is executed. Unit: us */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Get parameter of a CANOpen device.
 *
 * This method gets the relevant parameter of a CANOpen device. The call is
 * not decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiCopGetDeviceParam(
   IoApiHdl           devHdl,             /**< [in]  Device handle. */
   uint32_t          *nodeAddress,        /**< [out] CANOpen node address. */
   uint32_t          *guardTimeUs,        /**< [out] Node guarding time (default: guard time of the bus). Unit: us*/
   uint32_t          *lifeTimeFactor,     /**< [out] reserved for future use: life time factor of the node guarding. */
   IoCopPdoParam     *rxPdo[4],           /**< [out] Parameter of the RxPDOs (Index 0..3). */
   IoCopPdoParam     *txPdo[4]            /**< [out] Parameter of the TxPDOs (Index 0..3). */
   );


/******************************************************************************/
/**
 * @brief Execute a SDO file upload asynchronously.
 *
 * Start to execute an asynchronous Service Data Objects (SDO) file upload:
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiCopReadSdoFileAsyncStart(
   IoApiHdl           devHdl,       /**< [in]  Device handle. */
   uint32_t           index,        /**< [in]  Index. */
   uint32_t           subIndex,     /**< [in]  Sub index. */
   uint32_t           cnfTimeout,   /**< [in]  Max. wait time for response of a SDO-request. Unit: us */
   IoCopFileName      pFileName,    /**< [in]  Filename. */
   uint32_t          *pBytesRead,   /**< [out] Number of bytes transferred. */
   IoApiOverlapped   *ov            /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Execute a SDO file download asynchronously.
 *
 * Start to execute an asynchronous Service Data Objects (SDO) file download:
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiCopWriteSdoFileAsyncStart(
   IoApiHdl  devHdl,                       /**< [in]  Device handle. */
   uint32_t  index,                        /**< [in]  Index. */
   uint32_t  subIndex,                     /**< [in]  Sub index. */
   uint32_t  cnfTimeout,                   /**< [in]  Max. wait time for response of a SDO-request. Unit: us */
   char     *pFileName,                    /**< [in]  Filename. */
   uint32_t *pBytesWritten,                /**< [out] Number of bytes transferred. */
   IoApiOverlapped *ov                     /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );

#ifdef __cplusplus
}
#endif

#endif /* IOCOPAPI_H_ */
