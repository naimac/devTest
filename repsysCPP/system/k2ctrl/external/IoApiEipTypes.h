/*------------------------------------------------------------------------------
*                             (c) 2015 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoApiEip base type definitions
*
*   IoApiEip standard return code definitions and declaration of types.
*/


#ifndef IOAPIEIPTYPES_H_
#define IOAPIEIPTYPES_H_

#include <stdint.h>

/******************************************************************************/
/**
 *  @brief Return code definition
 *
 *  Return code definition of EtherNet/IP slave functions.
 *  These return codes extend the IoApiState which is defined in IoApiTypes.h.
 */
enum {
  IoApiEipSlaveStateInvalidState       = 0x00001300UL    /**< Invalid slave state. */
};


typedef uint32_t IoApiEipSlaveDeviceState;  /**< EtherNet/IP slave device state information */
enum {
  IoApiEipSlaveDeviceStateConfigure       = 0,   /**< configuration active */
  IoApiEipSlaveDeviceStateNoLink          = 1,   /**< no link */
  IoApiEipSlaveDeviceStateIdle            = 2,   /**< no process data exchange */
  IoApiEipSlaveDeviceStateRunning         = 3,   /**< process data exchange active */
  IoApiEipSlaveDeviceStateWatchdogTimeout = 4,   /**< watchdog timeout occurred */
  IoApiEipSlaveDeviceStateError           = 5    /**< other error */
};

#endif /* IOAPIEIPTYPES_H_ */
