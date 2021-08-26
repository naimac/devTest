/*------------------------------------------------------------------------------
*                             (c) 2018 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing the system bus on an UC20 control
*
*   The interface contains functions for handling of diagnosis and alarms.
*/

#ifndef IOAPISYSBUS_H_
#define IOAPISYSBUS_H_

#include "IoApiTypes.h"
#include "IoApiSysBusTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  System bus
*/

/******************************************************************************/
/**
 *  @brief Get diagnosis data of a system bus device.
 *
 * @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidHandle, if device handle is invalid.
 *         IoApiStateInvalidAddr, if there is an invalid address.
 *         IoApiStateInvalidParam, if parameter is invalid.
 *         IoApiStateNotSupported, if diagnosis is not enabled.
 *         IoApiStateNoData, if no diagnosis is available.
 *         IoApiStateOk, if diagnosis data was read successfully.
 */
IoApiState IoApiSysBusGetDiagData(
   IoApiHdl devHdl,                    /**< [in]  Device handle */
   TIoApiSysBusDiagData *pDiagData     /**< [out] diagnosis data */
   );


/******************************************************************************/
/**
 *  @brief Quit diagnosis of a system bus device.
 *
 *  @attention: If a diagnosis is not quit for more than
 *              one day, the time stamp of another
 *              pending diagnosis may not be converted
 *              correctly.
 *
 * @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidHandle, if device handle is invalid.
 *         IoApiStateNotSupported, if diagnosis is not enabled.
 *         IoApiStateNoData, if no new diagnosis is available for quitting.
 *         IoApiStateOk, if diagnosis data was quit successfully.
 */
IoApiState IoApiSysBusQuitDiag(
   IoApiHdl devHdl                     /**< [in]  Device handle */
   );


/******************************************************************************/
/**
 *  @brief Get alarm data of system bus device.
 *
 * @return State information about the synchronous operation.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateInvalidHandle, if device handle is invalid.
 *         IoApiStateInvalidAddr, if there is an invalid address.
 *         IoApiStateInvalidParam, if parameter is invalid.
 *         IoApiStateNotSupported, if alarms are not enabled.
 *         IoApiStateNoData, if no alarm is available.
 *         IoApiStateOk, if alarm data was read successfully.
 */
IoApiState IoApiSysBusGetAlarmData(
   IoApiHdl devHdl,                    /**< [in]  Device handle */
   TIoApiSysBusAlarmData *pAlarmData,  /**< [out] alarm data */
   uint8_t *pMore                      /**< [out] 1, if more alarms available; else 0 */
   );


#ifdef __cplusplus
}
#endif

#endif /* IOAPISYSBUS_H_ */
