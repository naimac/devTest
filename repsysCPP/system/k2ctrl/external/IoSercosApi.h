/*------------------------------------------------------------------------------
*                             (c) 2016 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing the SERCOS protocol
*
*   The interface contains SERCOS related functions for reading and
*   writing parameter and changing communication phase of SERCOS bus.
*/

#ifndef IOSERCOSAPI_H_
#define IOSERCOSAPI_H_

#include "IoApiTypes.h"
#include "IoSercosApiTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------------
*  SERCOS
*/
/******************************************************************************/
/**
 * @brief Read a SERCOS parameter asynchronously.
 *
 * Start to read a SERCOS parameter.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if handle is 0 or not a handle of a SERCOS device.
 *         IoSercosApiStateBufSizeTooSmall, if pData is too small
 *         IoSercosApiStateReadError, if reading from device returned an error (e.g. parameter is not available, ...)
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidHandle, if handle is 0 or not a handle of a SERCOS device.
 *         IoApiStateInvalidParam, if pData is 0.
 *         IoSercosApiStateBufSizeTooSmall, if pData is too small
 *         IoSercosApiStateReadError, if reading from device returned an error (e.g. parameter is not available, ...)
 */
IoApiState IoApiSercosReadParameterAsyncStart(
   IoApiHdl          devHdl,                    /**< [in]  Device handle of the SERCOS device. */
   uint32_t          identNr,                   /**< [in]  Identnumber of the parameter. */
   IoSercosElement   element,                   /**< [in]  Element of the datablock - elements between 1 and 7 could be read. */
   IoSercosPriority  priority,                  /**< [in]  Priority. */
   uint32_t          len,                       /**< [in]  Length of data buffer. */
   uint8_t          *pData,                     /**< [out] Data buffer (max. size is 65532). */
   uint32_t         *pBytesRead,                /**< [out] Number of bytes transferred. */
   IoApiOverlapped  *ov                         /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Write a SERCOS parameter asynchronously.
 *
 * Start to write a SERCOS parameter (only element 7 - operation data - could be written).
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if handle is 0 or not a handle of a SERCOS device.
 *         IoSercosApiStateLengthError, if length of data buffer (len) is not equal to expected data length.
 *         IoSercosApiStateWriteError, if SERCOS parameter could not be written (Readonly, sercos phase).
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk, if writing finished successful.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidHandle, if handle is 0 or not a handle of a SERCOS device.
 *         IoApiStateInvalidParam, if pData is 0.
 *         IoSercosApiStateLengthError, if length of data buffer (len) is not equal to expected data length.
 *         IoSercosApiStateWriteError, if SERCOS parameter could not be written (Readonly, sercos phase).
 */
IoApiState IoApiSercosWriteParameterAsyncStart(
   IoApiHdl          devHdl,                    /**< [in]  Device handle of the SERCOS device. */
   uint32_t          identNr,                   /**< [in]  Identnumber of the parameter. */
   IoSercosPriority  priority,                  /**< [in]  Priority. */
   uint32_t          len,                       /**< [in]  Length of data buffer. */
   uint8_t          *pData,                     /**< [in]  Data buffer (max. size is 65532). */
   IoApiOverlapped  *ov                         /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


/******************************************************************************/
/**
 * @brief Change SERCOS communication phase asynchronously.
 *
 * Start to change SERCOS phase.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if changing SERCOS phase was successful.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateChangePhaseError, if phase change is not possible (stopped).
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred (invalid destPhase, internal error: reading/writing shared memory failed, ...).
 *         IoApiStateInvalidHandle, if handle is 0 or not a handle of a SERCOS bus.
 *         IoApiStateInvalidAddr, if overlapped is 0 (for this function a blocking call is not yet supported).
 *         IoApiStateChangePhaseError, if phase change is not possible (stopped).
 */
IoApiState IoApiSercosChangePhaseAsyncStart(
   IoApiHdl          devHdl,                    /**< [in]  Device handle of the SERCOS bus. */
   int               destPhase,                 /**< [in]  destination communication phase (Possible values are: -1, 0, 1, 2, 3, 4; reasonable values are: 2 for following parameterization, 4 for total phase run-up). */
   int               viaPhase0,                 /**< [in]  Indicates, if a phase change should be enforced via phase 0 (e.g. at phase change to a bigger phase possible, at change to a smaller phase the change automatically happens via phase 0). */
   IoApiOverlapped  *ov                         /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOSERCOSAPI_H_ */
