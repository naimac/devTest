/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing EtherCat devices
*	
*   Interface for sending/receiving mail packets, file transfers, ... for EtherCat devices
*/

#ifndef IOBUSAPI_H_
#define IOBUSAPI_H_

#include "IoApiTypes.h"
#include "IoApiEcatTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  EtherCat General
*/

/******************************************************************************/
/**
 *  @brief Send mailbox command to slave
 *
 *  Send mailbox command to slave. The call is not decoupled so it runs within
 *  the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoEcatMbxResultSuccess, if operation has been finished.
 *         IoEcatMbxResultNoMailbox, if mailbox is not supported.
 *         IoEcatMbxResultParamError, if command params are invalid.
 *         IoEcatMbxResultIoError, if an IO error occurred.
 *         IoEcatMbxResultTimeout, if an IO timeout occurred.
 */
IoApiState IoApiEcatMbxTransferToFromSlave(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t timeoutUs,                    /**< [in]  Timeout in us. */
   int      useBurst,                     /**< [in]  1 for burst optimization. */
   uint32_t count,                        /**< [in]  Amount of requests / responses. */
   IoEcatMbxData *pRequestData,           /**< [in]  Data buffer containing the single requests. */
   IoEcatMbxData *pResponseData,          /**< [out] Data buffer for the single responses. */
   uint32_t *requestsSent,                /**< [out] Amount of sent Requests. */
   uint32_t *responsesReceived            /**< [out] Amount of received Responses. */
   );


/******************************************************************************/
/**
 * @brief Execute mailbox command transfer to/from slave asynchronously.
 *
 *
 * Start execution of mailbox command transfer:
 *   Same functionality as IoApiEcatMbxTransferToFromSlave(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoEcatMbxResultSuccess, if operation has been finished.
 *         IoEcatMbxResultNoMailbox, if mailbox is not supported.
 *         IoEcatMbxResultParamError, if command params are invalid.
 *         IoEcatMbxResultIoError, if an IO error occurred.
 *         IoEcatMbxResultTimeout, if an IO timeout occurred.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatMbxTransferToFromSlaveAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t timeoutUs,                    /**< [in]  Timeout in us. */
   int      useBurst,                     /**< [in]  1 for burst optimization. */
   uint32_t count,                        /**< [in]  Amount of requests / responses. */
   IoEcatMbxData *pRequestData,           /**< [in]  Data buffer containing the single requests. */
   IoEcatMbxData *pResponseData,          /**< [out] Data buffer for the single responses. */
   uint32_t *requestsSent,                /**< [out] Amount of sent Requests. */
   uint32_t *responsesReceived,           /**< [out] Amount of received Responses. */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );

/******************************************************************************/
/**
 *  @brief Send mailbox command to slave.
 *
 *  Send mailbox command to slave. The call is not decoupled so it runs within
 *  the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoEcatMbxResultSuccess, if operation has been finished.
 *         IoEcatMbxResultNoMailbox, if mailbox is not supported.
 *         IoEcatMbxResultParamError, if command params are invalid.
 *         IoEcatMbxResultIoError, if an IO error occurred.
 *         IoEcatMbxResultTimeout, if an IO timeout occurred.
 */
IoApiState IoApiEcatMbxTransferToSlave(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatMbxOriginator originator,        /**< [in]  Coding of sender of data. */
   IoEcatMbxProtocol protocol,            /**< [in]  Protocol identifier */
   uint32_t channel,                      /**< [in]  Channel (according to actual EtherCAT-spec. always 0) */
   uint32_t priority,                     /**< [in]  Priority (0-3, 0=highest, 3=lowest) */
   uint32_t length,                       /**< [in]  Valid length of pData */
   IoEcatMbxData *pData                   /**< [out] Data buffer */
   );


/******************************************************************************/
/**
 * @brief Execute mailbox command transfer to slave asynchronously.
 *
 *
 * Start execution of mailbox command transfer:
 *   Same functionality as IoApiEcatMbxTransferToSlave(), but the transfer will be
 *   performed asynchronously.
 *   Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoEcatMbxResultSuccess, if operation has been finished.
 *         IoEcatMbxResultNoMailbox, if mailbox is not supported.
 *         IoEcatMbxResultParamError, if command params are invalid.
 *         IoEcatMbxResultIoError, if an IO error occurred.
 *         IoEcatMbxResultTimeout, if an IO timeout occurred.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatMbxTransferToSlaveAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatMbxOriginator originator,        /**< [in]  Coding of sender of data. */
   IoEcatMbxProtocol protocol,            /**< [in]  Protocol identifier */
   uint32_t channel,                      /**< [in]  Channel (according to actual EtherCAT-spec. always 0) */
   uint32_t priority,                     /**< [in]  Priority (0-3, 0=highest, 3=lowest) */
   uint32_t length,                       /**< [in]  Valid length of pData */
   IoEcatMbxData *pData,                  /**< [out] Data buffer */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Calling a slave method
 *
 *  Calling a slave method for waiting of a command. The call is not decoupled
 *  so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoEcatMbxResultSuccess, if operation has been finished.
 *         IoEcatMbxResultNoMailbox, if mailbox is not supported.
 *         IoEcatMbxResultParamError, if command params are invalid.
 *         IoEcatMbxResultIoError, if an IO error occurred.
 *         IoEcatMbxResultTimeout, if an IO timeout occurred.
 */
IoApiState IoApiEcatMbxTransferFromSlave(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatMbxOriginator *originator,       /**< [out] Coding of sender of data. */
   IoEcatMbxProtocol *protocol,           /**< [out] Protocol identifier */
   uint32_t *channel,                     /**< [out] channel (according to actual EtherCAT-spec. always 0) */
   uint32_t *priority,                    /**< [out] Priority (0-3, 0=highest, 3=lowest) */
   uint32_t *length,                      /**< [out] Valid length of pData */
   IoEcatMbxData *pData                   /**< [out] Data buffer */
   );


/******************************************************************************/
/**
 * @brief Execute slave method call asynchronously.
 *
 * Start execution of asynchronous slave method call:
 *    Same functionality as IoApiEcatMbxTransferFromSlave(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvalidAddr, if there is an invalid parameter.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoEcatMbxResultSuccess, if operation has been finished.
 *         IoEcatMbxResultNoMailbox, if mailbox is not supported.
 *         IoEcatMbxResultParamError, if command params are invalid.
 *         IoEcatMbxResultIoError, if an IO error occurred.
 *         IoEcatMbxResultTimeout, if an IO timeout occurred.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatMbxTransferFromSlaveAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatMbxOriginator *originator,       /**< [out] Coding of sender of data. */
   IoEcatMbxProtocol *protocol,           /**< [out] Protocol identifier */
   uint32_t *channel,                     /**< [out] channel (according to actual EtherCAT-spec. always 0) */
   uint32_t *priority,                    /**< [out] Priority (0-3, 0=highest, 3=lowest) */
   uint32_t *length,                      /**< [out] Valid length of pData */
   IoEcatMbxData *pData,                  /**< [out] Data buffer */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Request supported protocols
 *
 *  Request supported protocols directly from slave. The call is not decoupled
 *  so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatGetMbxProtocols(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatMbxProtBit *protocols            /**< [out] Bit combination of IoEcatMbxProtBitXxx */
   );


/******************************************************************************/
/**
 *  @brief Request supported protocols
 *
 *  Request supported protocols directly from slave. The call is not decoupled
 *  so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatGetMbxLengths(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t *sendMbxLength,               /**< [out] Size of slave-send-mailbox. */
   uint32_t *recvMbxLength                /**< [out] Size of slave-receive-mailbox. */
   );

/******************************************************************************/
/**
 *  @brief File download/upload.
 *
 *  File download/upload. The call is not decoupled so it runs within the
 *  context of the caller.
 *
 *  @attention Function waits internally for completion of the file transfer,
 *  it should not be used in high priority context.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatFileTransfer(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatFileDirection direction,         /**< [in]  Transfer direction. */
   IoEcatFileName slaveFileName,          /**< [in]  Filename at slave. */
   IoEcatFileName masterFileName,         /**< [in]  Filename at master. */
   uint32_t password,                     /**< [in]  Optional password. */
   uint32_t *errorCode                    /**< [out] Error code (see IEC 61158-6-12) */
   );


/******************************************************************************/
/**
 * @brief Execute file transfer asynchronously.
 *
 *
 * Start execution of asynchronous file transfer:
 *   Same functionality as IoApiEcatFileTransfer(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoEcatFoEResultSuccess, if operation has been finished.
 *         IoEcatFoEResultNoMailbox, if mailbox is not supported.
 *         IoEcatFoEResultCannotOpenMasterFile, if file could not be found.
 *         IoEcatFoEResultIoError, if an IO error occurred.
 *         IoEcatFoEResultTimeout, if an IO timeout occurred.
 *         IoEcatFoEResultProtocolError, if FoE mailbox protocol is not supported.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateInvalidAddr, if invalid output addresses have been given.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatFileTransferAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatFileDirection direction,         /**< [in]  Transfer direction. */
   IoEcatFileName slaveFileName,          /**< [in]  Filename at slave. */
   IoEcatFileName masterFileName,         /**< [in]  Filename at master. */
   uint32_t password,                     /**< [in]  Optional password. */
   uint32_t *errorCode,                   /**< [out] Error code (see IEC 61158-6-12) */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Requesting bootstrap state.
 *
 *  Requesting bootstrap state. The call is not decoupled so it runs within the
 *  context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatEnterBootstrap(
   IoApiHdl devHdl                        /**< [in]  The catalog handle. */
   );


/******************************************************************************/
/**
 * @brief Request bootstrap state asynchronously.
 *
 *
 * Start execution of asynchronous bootstrap state request:
 *    Same functionality as IoApiEcatEnterBootstrap(), but the transfer will be
 *    performed asynchronously.
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
IoApiState IoApiEcatEnterBootstrapAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Returning from bootstrap state to previous state.
 *
 *  Returning from bootstrap state to previous state. The call is not decoupled
 *  so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatLeaveBootstrap(
   IoApiHdl devHdl                        /**< [in]  The catalog handle. */
   );


/******************************************************************************/
/**
 * @brief Returning from bootstrap state to previous state asynchronously.
 *
 * Start returning from bootstrap state to previous state:
 *    Same functionality as IoApiEcatLeaveBootstrap(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatLeaveBootstrapAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );

/******************************************************************************/
/**
 *  @brief Requesting a special state
 *
 *  Requesting a special state from slave. The function returns as soon as the
 *  state transition is done or a timeout of 10s occurred. The call is not
 *  decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatEnterState(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatState state                      /**< [in]  Requested state. */
   );


/******************************************************************************/
/**
 * @brief Requesting a special state asynchronously.
 *
 * Start requesting a special state:
 *    Same functionality as IoApiEcatEnterState(), but the transfer will be
 *    performed asynchronously.
 *    Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatEnterStateAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatState state,                     /**< [in]  Requested state. */
   IoApiOverlapped *ov                    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 *  @brief Reading a special state
 *
 *  Reading a special state from slave. The call is not decoupled so it runs
 *  within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatGetState(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   IoEcatState *state                     /**< [out] actual state */
   );

/******************************************************************************/
/**
 *  @brief Requesting number of devices
 *
 *  Requesting number of devices attached to bus from Bus Topology-object of
 *  master. The call is not decoupled so it runs within the context of the
 *  caller.
 *
 * @return Result code of bus-topology information interface.
 *         IoEcatBusResultSuccess, if operation has been finished.
 *         IoEcatBusResultParamError, if devHdl does not point to suitable device.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatGetSlaveCount(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t *slaveCount                   /**< [out] Number of slaves. */
   );


/******************************************************************************/
/**
 *  @brief position address is negative value
 *
 *  The position address is negative value of auto increment. The call is not
 *  decoupled so it runs within the context of the caller.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatGetSlavePosAddr(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t *posAddr                      /**< [out] Position address of slave. */
   );

typedef struct {                          /**< Detailed information of an IO ECAT slave */
   uint32_t vendorId;                     /**< Vendor ID from EEPROM */
   uint32_t productCode;                  /**< Product code from EEPROM */
   uint32_t revisionNumber;               /**< Revision number from EEPROM */
   uint32_t serialNumber;                 /**< Serial number from EEPROM */
   uint16_t cfgStationAlias;              /**< Configured station alias from EEPROM */
   uint16_t parentPosAddr;                /**< Position address of the topological parent node */
   uint16_t linkCount;                    /**< Link count (max. number of topological child nodes */
   uint16_t dataLinkLayerStatus;          /**< Data-Link-Layer status register (0x0110 - 0x0111) */
} IoEcatSlaveInfo;


/******************************************************************************/
/**
 *  @brief Reading device information
 *
 *  Reading device information from node structure of bus topology. The call is
 *  not decoupled so it runs within the context of the caller.
 *
 * @return Result code of bus-topology information interface.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoEcatBusResultSuccess, if operation has been finished.
 *         IoEcatBusResultParamError, if devHdl does not point to suitable device.
 *         IoEcatBusResultIoError, if an IO error occurred.
 */
IoApiState IoApiEcatGetSlaveInfo(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t posAddr,                      /**< [in]  Position address of slave */
   IoEcatSlaveInfo *slaveInfo             /**< [out] Info data of slave */
   );


typedef struct {
   uint8_t  ctrlType;                     /**< Type of EtherCAT controller, register 0x0000 */
   uint8_t  ctrlRev;                      /**< Revision of EtherCAT controller, register 0x0001 */
   uint16_t ctrlBuild;                    /**< Actual build of EtherCAT controller, register 0x0002-0x0003 */
   uint8_t  fmmuCnt;                      /**< Number of supported FMMU channels, register 0x0004 */
   uint8_t  smCnt;                        /**< Number of supported SysncManager channels, register 0x0005 */
   uint8_t  pdRamSize;                    /**< Supported process data RAM size in KByte, register 0x0006 */
   uint8_t  portDesc;                     /**< Port descriptor, register 0x0007 */
   uint16_t features;                     /**< Supported ESC features, register 0x0008-0x0009 */
   uint8_t  reserved[54];                 /**< reserved for future use */
} IoEcatStaticSlaveInfo;

/******************************************************************************/
/**
 *  @brief Reading device information
 *
 *  Reading device information from node structure of bus topology. The call is
 *  not decoupled so it runs within the context of the caller.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoEcatBusResultSuccess, if operation has bin finished.
 *         IoEcatBusResultParamError, if devHdl does not point to suitable device or
 *         position address of slave is invalid.
 *         IoEcatBusResultIoError, if an IO error occurred.
 */
IoApiState IoApiEcatGetStaticSlaveInfo(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t posAddr,                      /**< [in]  Position address of slave. */
   IoEcatStaticSlaveInfo *staticSlaveInfo /**< [out] Info data of slave */
   );


/******************************************************************************/
/**
 *  @brief Reading a single slave register
 *
 *  Reading a single defined register of a slave device. The call is not
 *  decoupled so it runs within the context of the caller.
 *
 *  @attention Function waits internally for response from EtherCAT slave, it
 *  should not be used in high priority context.
 *
 * @return Result code of bus-topology information interface.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoEcatBusResultSuccess, if operation has bin finished.
 *         IoEcatBusResultParamError, if devHdl does not point to suitable device,
 *         the position address of slave is invalid, the register offset is out
 *         of bounds or the length of bytes to read is invalid.
 *         IoEcatBusResultIoError, if an IO error occurred.
 *         IoEcatBusResultAccessDenied, if access to slave register is not allowed.
 *         IoEcatBusResultInvalidState, if device state is invalid for operation.
 *         IoEcatBusResultWorkCounterInvalid, if the slave work counter is invalid.
 *         IoEcatBusResultTimeout, if a timeout occurred.
 *         IoEcatBusResultResourceError, if slave is out of resources.
 */
IoApiState IoApiEcatReadSlaveRegister(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t posAddr,                      /**< [in]  Position address of slave. */
   uint32_t offset,                       /**< [in]  Register offset in bytes. */
   uint32_t readDataLength,               /**< [in]  Length of bytes to read. */
   IoEcatRegisterData *slaveRegister      /**< [out] Register data of slave. */
   );


/** RX slave counters */
typedef struct {
   uint8_t invFrameCnt;
   uint8_t rxErrorCnt;
} IoEcatRxErrorCnt;

#define IO_ECAT_NUM_PORTS 4
/** Combined slave counter registers */
typedef struct {
   IoEcatRxErrorCnt rxErrors[IO_ECAT_NUM_PORTS];   /**< errors on ports 0-3, register 0x0300-0x0307 */
   uint8_t forwardedErrCnt[IO_ECAT_NUM_PORTS];     /**< forwarded RX error counter on port 0-3, register 0x0308-0x030B */
   uint8_t ecatProcUnitErrCnt;                     /**< ECAT processing unit error counter, register 0x030C */
   uint8_t pdiErrCnt;                              /**< PDI error counter, register 0x030D */
   uint8_t spiPdiErrCode;                          /**< SPI PCI error code, register 0x030E */
   uint8_t microCtrlPdiErrCode;                    /**< microcontroller PDI error code, register 0x030F */
   uint8_t lostLinkCnt[IO_ECAT_NUM_PORTS];         /**< lost link counter, register 0x0310-0x0313 */
   uint8_t syncManWdCnt;                           /**< watchdog counter process data, register 0x0442 */
   uint8_t pdiWdCnt;                               /**< watchdog counter PDI, register 0x0443 */
} IoEcatErrorCounters;

/******************************************************************************/
/**
 * @brief Start to execute a read transfer of all error counters from slave
 * registers.
 *
 * Start the asynchronous read transfer of all error counters from slave
 * registers.
 * Poll for result with function IoApiAsyncGetResult().
 *
 * @attention The memory range which is given with the pErrorCounters pointer
 * must be accessible until IoApiAsyncGetResult() return with IoApiStateOk or
 * IoApiStateNotOk.
 *
 * @attention The entries of pErrorCounters are only valid if
 * IoApiAsyncGetResult() returns with IoEcatBusResultSuccess.
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *         IoEcatBusResultParamError, if devHdl or posAddr are invalid for the operation.
 *         IoEcatBusResultSuccess, if operation has been finished.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 */
IoApiState IoApiEcatGetErrorCountersAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t posAddr,                      /**< [in]  Position address of slave. */
   IoEcatErrorCounters *pErrorCounters,   /**< [out] Error counters read from all slave registers. */
   IoApiOverlapped *ov                    /**< [out] IoApiOverlapped object will be needed for polling the result. */
   );


typedef uint32_t IoEcatResetType;         /**< Possible slave reset types. */
enum {
   IoEcatResetTypeErrorCounters = 0x000000001   /**< Reset slave error counters. */
};

/******************************************************************************/
/**
 * @brief Start to execute a reset of slave registers
 *
 * Start the asynchronous reset of specified slave registers depicted by type.
 * Poll for result with function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *         IoEcatBusResultParamError, if devHdl, posAddr or type are invalid for the operation.
 *         IoEcatBusResultSuccess, if operation has been finished.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted.
 */
IoApiState IoApiEcatResetSlaveDataAsyncStart(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   uint32_t posAddr,                      /**< [in]  Position address of slave. */
   IoEcatResetType type,                  /**< [in]  Type of slave data which is to reset. */
   IoApiOverlapped *ov                    /**< [out] IoApiOverlapped object will be needed for polling the result. */
   );

/******************************************************************************/
/**
 * @brief Activate DMA statistic.
 *
 * Activate the cyclic DMA statistic. The DMA statistic is only available for
 * hardware EtherCAT. The call is not decoupled so it runs within the context of
 * the caller.
 *
 * @return State information about operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatActivateDmaStat(
   IoApiHdl devHdl                        /**< [in]  The catalog handle. */
   );

/******************************************************************************/
/**
 * @brief Deactivate DMA statistic.
 *
 * Deactivate the cyclic DMA statistic. The DMA statistic is only available for
 * hardware EtherCAT. The call is not decoupled so it runs within the context of
 * the caller.
 *
 * @return State information about operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatDeactivateDmaStat(
   IoApiHdl devHdl                        /**< [in]  The catalog handle. */
   );

/******************************************************************************/
/**
 * @brief Read the status of DMA statistic.
 *
 * Reads the actual status of the cyclic DMA statistic. The call is not
 * decoupled so it runs within the context of the caller.
 *
 * @return State information about operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatGetDmaStatInfo(
   IoApiHdl  devHdl,                      /**< [in]  The catalog handle. */
   uint32_t *active                       /**< [out] State of DMA statistic (0 .. not active, 1 .. active). */
   );

/******************************************************************************/
/**
 * @brief Reset DMA statistic.
 *
 * Reset of the cyclic DMA statistic. The call is not decoupled so it runs
 * within the context of the caller.
 *
 * @return State information about operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiEcatResetDmaStat(
   IoApiHdl devHdl                        /**< [in]  The catalog handle. */
   );

#ifdef __cplusplus
}
#endif

#endif
