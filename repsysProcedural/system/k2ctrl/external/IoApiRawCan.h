/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing a raw CAN bus
*
*   The interface contains raw CAN related functions for opening, closing and
*   read/write CAN messages.
*/

#ifndef IOAPIRAWCAN_H_
#define IOAPIRAWCAN_H_

#include "IoApiTypes.h"
#include "IoApiRawCanTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  RAW CAN
*/

/******************************************************************************/
/**
 * @brief Get first configured CAN handle.
 *
 * Deliver first configured CAN bus handle for raw access.
 *
 * @return State information about the call.
 *          IoApiStateOk, if CAN handle for raw access could be delivered.
 *          IoApiStateNotOk, if no CAN handle could be found.
 */
IoApiState IoApiRawCanGetFirstHdl(
   IoApiHdl *canHdl              /**< [out] CAN bus handle. */
   );


/******************************************************************************/
/**
 * @brief Get next configured CAN handle.
 *
 * Iterate over all installed CAN busses. If successful nextHdl is set to
 * handle of next CAN bus.
 *
 * @return State information about the call.
 *          IoApiStateOk, if nextHdl could successfully be delivered.
 *          IoApiStateInvalidAddr, if nextHdl
 *          IoApiStateNotOk, if no more CAN busses are configured.
 */
IoApiState IoApiRawCanGetNextHdl(
   IoApiHdl  canHdl,             /**< [in]  CAN bus handle. */
   IoApiHdl *nextHdl             /**< [out] Next configured CAN bus handle. */
   );


/******************************************************************************/
/**
 * @brief Connect to raw CAN bus.
 *
 * Connect to a raw CAN bus which will be initialized and prepared for raw
 * access. Multiple open of the same CAN bus is not possible.
 *
 * @return State information about the call.
 *          IoApiStateOk, if operation has been finished.
 *          IoApiStateNotOk, if an error occurred.
 *          IoApiRawCanStateRawModeNotSupported, if raw mode is not configured
 *             for the given bus.
 *          IoApiStateInvalidHandle, if given handle is invalid.
 *          IoApiRawCanStateBusy, if raw CAN bus is already in use.
 *          IoApiRawCanStateInvalidState, if hardware is not accessible.
 *          IoApiRawCanStateError, if opening of raw CAN bus failed.
 */
IoApiState IoApiRawCanOpen(
   IoApiHdl    canHdl            /**< [in]  CAN bus handle. */
   );


/******************************************************************************/
/**
 * @brief Disconnect from raw CAN bus.
 *
 * Disconnect from a raw CAN bus. Send and receive queues of the CAN bus
 * will be reseted.
 *
 * @return State information about the call.
 *          IoApiStateOk, if operation has been finished.
 *          IoApiStateNotOk, if an error occurred.
 *          IoApiStateInvalidHandle, if given handle is invalid.
 *          IoApiRawCanStateError, if closing of raw CAN bus failed.
 */
IoApiState IoApiRawCanClose(
   IoApiHdl    canHdl            /**< [in]  CAN bus handle. */
   );


/******************************************************************************/
/**
 * @brief Reset the raw CAN bus.
 *
 * Reset the raw CAN bus. Send and receive queues will be emptied. Error
 * flags will be reseted.
 *
 * @return State information about the call.
 *          IoApiStateOk, if operation has been finished.
 *          IoApiStateNotOk, if an error occurred.
 *          IoApiStateInvalidHandle, if given handle is invalid.
 *          IoApiRawCanStateError, if reset failed.
 */
IoApiState IoApiRawCanReset(
   IoApiHdl    canHdl            /**< [in]  CAN bus handle. */
   );


/******************************************************************************/
/**
 * @brief Read a raw CAN message.
 *
 * Read a raw CAN message. All message ids from the CAN bus will be
 * delivered. A filter of specific message ids is not supported. If no message
 * is available IoApiStateOk is returned and 'msgRead' is set to 0.
 *
 * @return State information about the call.
 *          IoApiStateOk, if operation has been finished.
 *          IoApiStateNotOk, if an error occurred.
 *          IoApiStateInvalidHandle, if given handle is invalid.
 *          IoApiStateInvalidParam, if one of the output pointers is invalid.
 *          IoApiRawCanStateError, if an error during reading occurred.
 */
IoApiState IoApiRawCanRead(
   IoApiHdl        canHdl,          /**< [in]  CAN bus handle. */
   IoApiRawCanMsg *canMsg,          /**< [out] CAN message. */
   uint8_t        *msgRead,         /**< [out] Set to 1 if message was read successfully, 0 else. */
   uint32_t       *numMsgToRead,    /**< [out] Number of remaining available messages. */
   int8_t         *overflow         /**< [out] Set to 1 if not all incomming messages since last read could be stored. */
   );


/******************************************************************************/
/**
 * @brief Write a raw CAN message.
 *
 * Write a raw CAN message. If an onboard CAN is used the message will be
 * transferred immediately if the CAN controller is idle or else it will be
 * transferred within the next send interrupt. If an EtherCAT CAN is used the
 * message will be sent during the next EtherCAT cycle.
 * This function will block internally until the actual send activity starts.
 * If the write transfer fails the 'badSendMsgCnt' of the bus statistic will be
 * incremented.
 *
 * @return State information about the call.
 *          IoApiStateOk, if disposal of write transfer succeeded.
 *          IoApiStateNotOk, if an error occurred.
 *          IoApiStateInvalidHandle, if given handle is invalid.
 *          IoApiRawCanStateBusy, if message could not be transferred (CAN
 *             controller not ready or overflow of transmit queue).
 *          IoApiSRawCanStateError, if an error occurred during writing.
 */
IoApiState IoApiRawCanWrite(
   IoApiHdl        canHdl,          /**< [in]  CAN bus handle. */
   const IoApiRawCanMsg *pCanMsg    /**< [in]  pointer to CAN message. */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOAPIRAWCAN_H_ */
