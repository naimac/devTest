/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for access to axis state informations
*
*   Reading the pulse interval and reading/writing the mileage indicator of an IO axis.
*/

#ifndef IOSERVOLIBAPI_H_
#define IOSERVOLIBAPI_H_

#include "IoApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  ServoLib
*/

/******************************************************************************/
/**
 *  @brief Read the pulse interval
 *
 *  Detect the interval between 2 null impulses.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if pDPosZero pointer is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiAxisGetIndexPulseInterval(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   float *pDPosZero                       /**< [out] Null-Impulse-Interval */
   );

/******************************************************************************/
/**
 *  @brief Setting mileage indicator
 *
 *  Setting the kilometer counter of a servo.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiAxisSetMileageIndicator(
   IoApiHdl devHdl,                       /**< [in] The catalog handle. */
   float positionUnits,                   /**< [in] Position unit */
   float minDelta,                        /**< [in] Minimum delta */
   int   updateMileage                    /**< [in] Boolean flag for updating */
   );

/******************************************************************************/
/**
 *  @brief Reading mileage indicator
 *
 *  Reading the kilometer counter of a servo.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if pDPosZero pointer is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiAxisGetMileageIndicator(
   IoApiHdl devHdl,                       /**< [in]  The catalog handle. */
   float *positionUnit                    /**< [out] Position unit */
   );

#ifdef __cplusplus
}
#endif

#endif
