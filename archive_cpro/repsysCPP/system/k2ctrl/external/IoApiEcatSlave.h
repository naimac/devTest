/*------------------------------------------------------------------------------
*                             (c) 2014 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing EtherCat slave devices
*	
*   Interface for gathering state information of EtherCat slaves.
*/

#ifndef IOAPIECATSLAVE_H_
#define IOAPIECATSLAVE_H_

#include "IoApiTypes.h"
#include "IoApiEcatTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/**
 *  @brief Get the state of the EtherCat slave.
 *
 * This method gets the current state of the slaves EtherCat. The call is not
 * decoupled so it runs within the context of the caller.
 *
 * @return IoApiStateOk if state transition is done else IoApiStateNotOk.
 */
IoApiState IoApiEcatSlaveGetState(
   IoApiHdl        devHdl,          /**< [in]  The catalog handle. */
   IoEcatState    *state            /**< [out] actual state */
   );

#ifdef __cplusplus
}
#endif

#endif /* IOAPIECATSLAVE_H_ */
