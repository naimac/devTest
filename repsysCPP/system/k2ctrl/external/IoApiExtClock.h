/*------------------------------------------------------------------------------
*                             (c) 2014 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing the external clock synchronization
*	
*   Interface for checking state of external clock synchronization and re-start.
*/

#ifndef IOAPIEXTCLOCK_H_
#define IOAPIEXTCLOCK_H_

#include "IoApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** State of external clock synchronization. */
typedef int32_t IoApiExtClockSyncState;
enum {
   IoApiExtClockSyncStateInactive  = 0,   /**< external clock synchronization
                                            not active/used */
   IoApiExtClockSyncStateWaitSync  = 1,   /**< wait for external clock synchronization */
   IoApiExtClockSyncStateSyncReady = 2,   /**< external clock synchronization ready */
   IoApiExtClockSyncStateSyncLost  = 3,   /**< external clock synchronization lost */
};

/******************************************************************************/
/**
 *  @brief Reads state of external clock synchronization.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateInvalidAddr, if pointer to output variables are invalid
 *         IoApiStateNotOk, if an error occurred
 */
IoApiState IoApiExtClockGetSyncState(
   IoApiExtClockSyncState *syncState,     /**< [out] state of synchronization */
   IoApiHdl               *ioNodeHdl      /**< [out] handle of IO node which does
                                                     the synchronization */
   );

/******************************************************************************/
/**
 *  @brief Enable external clock synchronization after lost synchronization.
 *
 *  When external clock synchronization has been lost (eg. bus connection is
 *  interrupted) the system switches to a local clock source.
 *  Application has to react on lost synchronization (eg. deactivate outputs).
 *  After that a new external clock synchronization can be enabled by calling
 *  this function.
 *  During external clock synchronization phase all IO drivers are stopped
 *  until synchronization is finished.
 *
 * @return State information about the call.
 *         IoApiStateOk, if the call has been successful
 *         IoApiStateNotOk, if external clock synchronization is not activated
 */
IoApiState IoApiExtClockResync();

#ifdef __cplusplus
}
#endif

#endif
