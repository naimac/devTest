/*------------------------------------------------------------------------------
*                             (c) 2013 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief  Interface to the DeviceService
*
*   Interface to the DeviceService
*
*   This interface can be used to query the device state from the DeviceService,
*   and to trigger commands executed by the DeviceService.
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_DEVICE_H
#define PACKAGE_API_DEVICE_H

#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** A type indicating a device command. */
typedef int32_t BPApiDeviceCommand;
enum {
   BPApiDeviceCommandNop                   = 0,  /**< No command running. */
   BPApiDeviceCommandInitService           = 1,  /**< The device service is initializing. */
   BPApiDeviceCommandExitService           = 2,  /**< The device service is closing. */
   BPApiDeviceCommandStartController       = 3,  /**< The controller software is initializing and the applications will be started. */
   BPApiDeviceCommandStopController        = 4,  /**< The controller software will be closed, applications will be stopped. */
   BPApiDeviceCommandShutdownController    = 5,  /**< The device is shutting down (power off). */
   BPApiDeviceCommandRebootController      = 6,  /**< The device is rebooting. */
   BPApiDeviceCommandStartApplications     = 7,  /**< Controller applications will be started. */
   BPApiDeviceCommandStopApplications      = 8,  /**< Controller applications will be stopped. */
   BPApiDeviceCommandDeleteApplications    = 9,  /**< Controller applications will be deleted. */
   BPApiDeviceCommandClearRetain           = 10, /**< Retain data will of applications be deleted.  */
   BPApiDeviceCommandRestartController     = 11, /**< The controller software will be closed and restarted. */
   BPApiDeviceCommandRestartApplications   = 12, /**< The controller applications will be stopped and restarted. */
   BPApiDeviceCommandInitController        = 13, /**< The controller software is initializing, applications will not be started automatically. */
   BPApiDeviceCommandReconfigureController = 14  /**< The controller will re-evaluate configuration files. This will restart some running applications. */
};


/******************************************************************************/
/**
 * @brief Trigger a command which is executed by the DeviceService
 *
 * This function will trigger the execution of a command within the DeviceService.
 * Note that commands are executed asynchronously, and this function will only provide
 * information on whether or not the command could be initiated. The state of a
 * currently running command can be obtained from BPApiDeviceGetState.
 * In case the command could not be initiated, BPApiDeviceRunCommand returns an error
 * immediately (synchronously).
 *
 * @return  ::BPApiStateOk on success - the command is pending,<BR>
 *          ::BPApiStateDeviceCommandTemporarilyUnavailable if command is currently not available,<BR>
 *          ::BPApiStateDeviceCommandPermanentlyUnavailable if command is unknown/not supported,<BR>
 *          ::BPApiStateFuncNotFound if remote function is currently not available,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiDeviceRunCommand (
   BPApiDeviceCommand command                    /**< [in] command to be initiated. */
   );


/******************************************************************************/
/**
 * @brief Get a list of commands that are currently available.
 *
 * This function returns a list of commands which may be executed in the
 * current state of the controller.
 * Note that this list may change over time, depending on the state of the device and
 * the software subsystems. Thus, it is still required to check the return codes of
 * BPApiDeviceRunCommand if a (formerly) available command has been succesfully initiated.
 *
 * @return  ::BPApiStateOk on success, all outputs are valid,<BR>
 *          ::BPApiStateParamError if 'commands' or 'commandsCount' is NULL,<BR>
 *          ::BPApiStateOutOfMemory if 'commandsSize' is too small,<BR>
 *          ::BPApiStateFuncNotFound if remote function is currently not available,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiDeviceGetAvailableCommands (
   BPApiDeviceCommand *commands,                 /**< [out] buffer which should receive the list of available commands. */
   uint32_t            commandsSize,             /**< [in] size of the 'commands' buffer in number of elements. */
   uint32_t           *commandsCount             /**< [out] number of elements within the 'command' list which were actually filled. */
   );


/** A type indicating a device main state. */
typedef int32_t BPApiDeviceMainState;
enum {
   BPApiDeviceMainStateUnknown =   0,            /**< state is unknown (DeviceService not initialized). */
   BPApiDeviceMainStateOsReady = 100,            /**< state is OsReady (DeviceService and operating system are ready). */
   BPApiDeviceMainStateStop    = 200,            /**< state is Stop (controller is initialized, controller applications are not running). */
   BPApiDeviceMainStateRun     = 300             /**< state is Run */
};


/******************************************************************************/
/**
 * @brief Get the device state.
 *
 * This function returns information on the device state and commands.
 *
 * @return  ::BPApiStateOk on success, all outputs are valid,<BR>
 *          ::BPApiStateParamError if called with invalid parameters,<BR>
 *          ::BPApiStateStringChopped if 'errorItemSize' or 'errorTextSize' is too small,<BR>
 *          ::BPApiStateFuncNotFound if remote function is currently not available,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiDeviceGetStateA (
   BPApiDeviceMainState *mainState,              /**< [out] the main state of the device. */
   BPApiDeviceCommand   *command,                /**< [out] the last or currently active command. */
   int                  *commandActive,          /**< [out] indicates if 'command' is still active (0/1). */
   int                  *commandDone,            /**< [out] indicates if 'command' has been completed (0/1). */
   int                  *commandFailed,          /**< [out] indicates if 'command' failed (0/1). */
   int32_t              *commandProgress,        /**< [out] returns the progress of 'command' (0-100). */
   char                 *errorItem,              /**< [out] buffer for the name of the device service item which returned an error. */
   uint32_t              errorItemSize,          /**< [in] size of 'errorItem' buffer in bytes. */
   char                 *errorText,              /**< [out] buffer for the error description. */
   uint32_t              errorTextSize           /**< [in] size of 'errorText' buffer in bytes. */
   );


/******************************************************************************/
/**
 * @brief Get the device state.
 *
 * This function returns information on the device state and commands.
 *
 * @return  ::BPApiStateOk on success, all outputs are valid,<BR>
 *          ::BPApiStateParamError if called with invalid parameters,<BR>
 *          ::BPApiStateStringChopped if 'errorItemSize' or 'errorTextSize' is too small,<BR>
 *          ::BPApiStateInvalidMultiByteChar if convertion to wide char string failed,<BR>
 *          ::BPApiStateFuncNotFound if remote function is currently not available,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiDeviceGetStateW (
   BPApiDeviceMainState *mainState,              /**< [out] the main state of the device. */
   BPApiDeviceCommand   *command,                /**< [out] the last or currently active command. */
   int                  *commandActive,          /**< [out] indicates if 'command' is still active (0/1). */
   int                  *commandDone,            /**< [out] indicates if 'command' has been completed (0/1). */
   int                  *commandFailed,          /**< [out] indicates if 'command' failed (0/1). */
   int32_t              *commandProgress,        /**< [out] returns the progress of 'command' (0-100). */
   wchar_t              *errorItem,              /**< [out] buffer for the name of the device service item which returned an error. */
   uint32_t              errorItemSize,          /**< [in] size of 'errorItem' buffer in wchar_t elements. */
   wchar_t              *errorText,              /**< [out] buffer for the error description. */
   uint32_t              errorTextSize           /**< [in] size of 'errorText' buffer in wchar_t elements. */
   );


/******************************************************************************/
/**
 * @brief Get the realtime capability of the device.
 *
 * This function returns information on the realtime capability of the device.
 *
 * @return  ::BPApiStateOk on success, all outputs are valid,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateParamError if called with invalid parameter,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiDeviceGetRTCapability (
   uint8_t *rtCapability                       /**< [out] the realtime capability of the device. */
   );


/** @cond */
#ifdef UNICODE
   #define BPApiDeviceGetState        BPApiDeviceGetStateW
#else
   #define BPApiDeviceGetState        BPApiDeviceGetStateA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_DEVICE_H_INCLUDED */
