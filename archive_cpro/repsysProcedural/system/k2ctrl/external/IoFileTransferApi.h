/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for transferring files.
*
*   Interface for transferring files between the PLC and supported devices.
*/

#ifndef IOFILETRANSFERAPI_H_
#define IOFILETRANSFERAPI_H_

#include "IoApiTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t IoApiFileDownloadOption;       /**< Extended options that can be specified */
enum {
   IoApiFileDownloadOptionDefault   = 0,        /**< Default (Only download the file if version is newer) */
   IoApiFileDownloadOptionForce     = 1,        /**< Force download (Always download the file) */
   IoApiFileDownloadOptionChangePM  = 256       /**< Change to param mode before writing parameter set */
};

typedef uint32_t IoApiFileUploadOption;         /**< Extended options that can be specified */
enum {
   IoApiFileUploadOptionDefault     = 0         /**< Default */
};

typedef uint32_t IoApiFileType;                 /**< Specifies the file type to be transferred */
enum {
   IoApiFileTypeParamSet            = 0,        /**< Parameter set */
   IoApiFileTypeFirmware            = 1,        /**< Firmware */
   IoApiFileTypeDeviceCopy          = 2,        /**< Copy firmware and parameter set of a device without device specific settings like ip-address */
   IoApiFileTypeDeviceClone         = 3,        /**< Clone a device including all device specific settings */
   IoApiFileTypeBusMonitordata      = 4         /**< Bus monitor data */
};


enum {
   IoApiStateInvFileName            = 0x00000201UL,   /**< File not found */
   IoApiStateBusy                   = 0x00000202UL,   /**< Another file transfer is in progress */
   IoApiStateCommunicationError     = 0x00000203UL    /**< Error in device communication */
};


/******************************************************************************/
/**
 * @brief Perform an asynchronous file download.
 *
 * Start to execute a file download.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvFileName, if given sourceFileName is not found.
 *         IoApiStateBusy, if device is busy with another operation.
 *         IoApiStateNotReady, if device is not ready for file transfer.
 *         IoApiStateCommunicationError, if an error during communication occurred.
 *         IoApiStateNotSupported, if function is not supported.
 *         IoApiStateInvalidParam, if fileType or option is not supported on
 *         specified device.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiFileDownloadAsyncStart(
   IoApiHdl                 devHdl,             /**< [in]  Device handle */
   IoApiFileType            fileType,           /**< [in]  File type that should be transferred */
   const char              *sourceFileName,     /**< [in]  Name of the source file */
   IoApiFileDownloadOption  option,             /**< [in]  Additional options */
   IoApiOverlapped         *ov                  /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult() */
   );


/******************************************************************************/
/**
 * @brief Perform an asynchronous single axis parameter set download.
 *
 * Start to execute a single axis parameter set download.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvFileName, if given sourceFileName is not found.
 *         IoApiStateBusy, if device is busy with another operation.
 *         IoApiStateNotReady, if device is not ready for file transfer.
 *         IoApiStateCommunicationError, if an error during communication occurred.
 *         IoApiStateNotSupported, if function is not supported.
 *         IoApiStateInvalidParam, if fileType or option is not supported on
 *         specified device.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiSingleAxisParamSetDownloadAsyncStart(
   IoApiHdl          devHdl,                    /**< [in]  Device handle */
   const char       *sourceFileName,            /**< [in]  Name of the source file */
   uint32_t          axisNumber,                /**< [in]  Axis number */
   IoApiOverlapped  *ov                         /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult() */
   );

/******************************************************************************/
/**
 * @brief Perform an asynchronous file upload.
 *
 * Start to execute a file upload.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvFileName, if given sourceFileName is not found.
 *         IoApiStateBusy, if device is busy with another operation.
 *         IoApiStateNotReady, if device is not ready for file transfer.
 *         IoApiStateCommunicationError, if an error during communication occurred.
 *         IoApiStateNotSupported, if function is not supported.
 *         IoApiStateInvalidParam, if fileType or option is not supported on
 *         specified device.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiFileUploadAsyncStart(
   IoApiHdl                 devHdl,             /**< [in]  Device handle */
   IoApiFileType            fileType,           /**< [in]  Filetype that should be transferred */
   const char              *targetFileName,     /**< [in]  Name of the target file */
   IoApiFileUploadOption    option,             /**< [in]  Additional options */
   IoApiOverlapped         *ov                  /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult() */
   );


/******************************************************************************/
/**
 * @brief Perform an asynchronous single axis parameter set upload.
 *
 * Start to execute a single axis parameter set upload.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStatePending, if the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped, if the used IoApiOverlapped is corrupt.
 *         IoApiStateInvalidHandle, if devHdl points to no valid device.
 *         IoApiStateInvFileName, if given sourceFileName is not found.
 *         IoApiStateBusy, if device is busy with another operation.
 *         IoApiStateNotReady, if device is not ready for file transfer.
 *         IoApiStateCommunicationError, if an error during communication occurred.
 *         IoApiStateNotSupported, if function is not supported.
 *         IoApiStateInvalidParam, if fileType or option is not supported on
 *         specified device.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStatePending, if the operation has been submitted
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiSingleAxisParamSetUploadAsyncStart(
   IoApiHdl          devHdl,                    /**< [in]  Device handle */
   const char       *targetFileName,            /**< [in]  Name of the source file */
   uint32_t          axisNumber,                /**< [in]  Axis number */
   IoApiOverlapped  *ov                         /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult() */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOFILETRANSFERAPI_H_ */
