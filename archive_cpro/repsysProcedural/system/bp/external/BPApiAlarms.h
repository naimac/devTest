/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Interface for Alarms
*
*   Interface for functions used to handle alarms
*
*   Alarms are messages. Possible actions are quit and reset. \n
*   ActiveQuit     -> Reset and Quit -> ActiveNoQuit \n
*   ActiveNoQuit   -> Reset          -> InactiveNoQuit \n
*   ActiveNoQuit   -> Quit           -> InactiveQuit \n
*   InactiveNoQuit -> Quit           -> ActiveQuit \n
*   InactiveQuit   -> Reset          -> ActiveQuit \n
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_ALARMS_H
#define PACKAGE_API_ALARMS_H

#include "BPApiTypes.h"
#include "BPApiVariables.h"

#ifdef __cplusplus
extern "C" {
#endif

/** The alarm handle. */
typedef uint32_t BPApiAlarm;

/** BPApi wildcard, matches all subIds.  */
const BPApiAlarm BPApiAlarmWildcard = 0x7FFFFFFF;

/** Alarm SubIds */
typedef struct {
   uint32_t numberOfSubIds;                      /**< Number of subsequent SubIds used, valid values are 1-4. */
   uint32_t subId1;                              /**< The first SubId */
   uint32_t subId2;                              /**< The second SubId */
   uint32_t subId3;                              /**< The third SubId */
   uint32_t subId4;                              /**< The fourth SubId */
} BPApiAlarmSubIds;

/** Alarm parameter */
typedef struct {
   BPApiVarType type;                            /**< Type of parameter. Only BPApiVarTypeSTRING, BPApiVarTypeWSTRING, BPApiVarTypeREAL and BPApiVarTypeDINT are valid. */
   void* param;                                  /**< Pointer to parameter */
   uint32_t sizeParam;                           /**< Size of the parameter */
} BPApiAlarmParam;

/** Alarm state */
typedef uint32_t BPApiAlarmState;
enum {
   BPApiAlarmStateActiveQuit     = 0x6001,
   BPApiAlarmStateActiveNoQuit   = 0x6002,
   BPApiAlarmStateInactiveNoQuit = 0x6003,
   BPApiAlarmStateInactiveQuit   = 0x6004
};

/******************************************************************************/
/**
 * @brief Get alarm handle (ASCII)
 *
 * Get alarm handle from name in ASCII.
 * @return State information about the call.
 */
BPApiState BPApiAlarmGetA (
   const char *alarmName,                        /**< [in]  Name of Alarm (FU.Alarm) */
   BPApiAlarm *alarmHdl                          /**< [out] Returns the requested handle. */
   );


/******************************************************************************/
/**
 * @brief Get alarm handle (Unicode)
 *
 * Get alarm handle from name in Unicode.
 * @return State information about the call.
 */
BPApiState BPApiAlarmGetW (
   const wchar_t *alarmName,                     /**< [in]  Name of Alarm (FU.Alarm) in unicode */
   BPApiAlarm *alarmHdl                          /**< [out] Returns the requested handle. */
   );

/******************************************************************************/
/**
 * @brief Quit alarm
 *
 * Quit dedicated alarm
 * @return State information about the call.
 */
BPApiState BPApiAlarmQuit  (
   BPApiAlarm alarmHdl,                          /**< [in] The alarm handle. */
   BPApiAlarmSubIds subIds                       /**< [in] The alarm subIds. */
   );

/******************************************************************************/
/**
 * @brief Set an alarm
 *
 * Set an alarm with several parameters.
 * @return State information about the call.
 */
BPApiState BPApiAlarmSet   (
   BPApiAlarm alarmHdl,                          /**< [in] The alarm Handle */
   BPApiAlarmParam param1,                       /**< [in] The first alarm parameter, set to 0 if unused. */
   BPApiAlarmParam param2,                       /**< [in] The second alarm parameter, set to 0 if unused. */
   BPApiAlarmSubIds subIds                       /**< [in] The alarm subIds */
   );

/******************************************************************************/
/**
 * @brief Reset an alarm.
 *
 * Reset a dedicated alarm.
 * @return State information about the call.
 */
BPApiState BPApiAlarmReset (
   BPApiAlarm alarmHdl,                          /**< [in] The alarm Handle */
   BPApiAlarmSubIds subIds                       /**< [in] The alarm subIds */
   );

/******************************************************************************/
/**
 * @brief Get alarm state
 *
 * Request information about alarm state
 * @return State information about the call.
 */
BPApiState BPApiAlarmGetState (
   BPApiAlarm alarmHdl,                          /**< [in]  The alarm Handle */
   BPApiAlarmSubIds subIds,                      /**< [in]  The alarm subIds */
   BPApiAlarmState *alarmState                   /**< [out] Returns the state of an alarm. */
   );

/** @cond */
#ifdef UNICODE
   #define BPApiAlarmGet             BPApiAlarmGetW
#else
   #define BPApiAlarmGet             BPApiAlarmGetA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_ALARMS_H_INCLUDED */
