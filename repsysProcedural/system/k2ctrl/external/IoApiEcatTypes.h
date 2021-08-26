/*------------------------------------------------------------------------------
*                             (c) 2014 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoEcatApi base type definitions
*
*   IoEcatApi standard return code definitions and declaration of types.
*/

#ifndef IOAPIECATTYPES_H_
#define IOAPIECATTYPES_H_

#include <stdint.h>


/******************************************************************************/
/**
 *  @brief Return code definition
 *
 *  Return code definition of CANOpen functions.
 *  These return codes extend the IoApiState which is defined in IoApiTypes.h.
 */
enum {
/** Return code definition ECat mailbox functions */
  IoEcatMbxResultSuccess                = 0x00000010UL,   /**< Successful */
  IoEcatMbxResultNoMailbox              = 0x00000011UL,   /**< Slave does not possess a mailbox. */
  IoEcatMbxResultParamError             = 0x00000012UL,   /**< Illegal parameter */
  IoEcatMbxResultIoError                = 0x00000013UL,   /**< Device error */
  IoEcatMbxResultTimeout                = 0x00000014UL,   /**< Timeout occurred */

/** Return code definition for File Transfer functions */
  IoEcatFoEResultSuccess                = 0x00000100UL,   /**< Transfer successfully finished. */
  IoEcatFoEResultNoMailbox              = 0x00000101UL,   /**< Slave does not possess a mailbox or FoE. */
  IoEcatFoEResultCannotOpenMasterFile   = 0x00000102UL,   /**< Master file is not readable/writable. */
  IoEcatFoEResultIoError                = 0x00000103UL,   /**< Device error during transmission. */
  IoEcatFoEResultTimeout                = 0x00000104UL,   /**< Timeout occurred during transmission. */
  IoEcatFoEResultProtocolError          = 0x00000105UL,   /**< Error response in FoE-protocol. */

/** Result coding of bus-topology and slave information interface */
  IoEcatBusResultSuccess                = 0x00001000UL,   /**< Success */
  IoEcatBusResultParamError             = 0x00001001UL,   /**< Illegal parameter (handle, address, offset, length */
  IoEcatBusResultIoError                = 0x00001002UL,   /**< Communication error */
  IoEcatBusResultTimeout                = 0x00001003UL,   /**< Timeout on EEPROM-access (>300ms) */
  IoEcatBusResultSiiError               = 0x00001004UL,   /**< SII-error */
  IoEcatBusResultResourceError          = 0x00001005UL,   /**< Request for resource failed */
  IoEcatBusResultInvalidState           = 0x00001006UL,   /**< Target device in invalid state */
  IoEcatBusResultAccessDenied           = 0x00001007UL,   /**< Target device denied access */
  IoEcatBusResultWorkCounterInvalid     = 0x00001008UL,   /**< Invalid working counter */

/** Return code definition ECat slave functions */
  IoEcatSlaveResultInvalidState         = 0x00001010UL,   /**< Invalid slave state. */
  IoEcatSlaveResultComError             = 0x00001010UL    /**< Slave communication error. */
};


/******************************************************************************/
/**
 *  Type definition
 */

/** EtherCat mailbox data buffer */
#define IO_ECAT_MBX_DATA_SIZE 1480
typedef char IoEcatMbxData[IO_ECAT_MBX_DATA_SIZE];  /**< ECat mailbox data buffer */


typedef uint32_t IoEcatMbxOriginator;      /**< Bit coding of mailbox originator, 0=master, >0=slave */

typedef uint32_t IoEcatMbxProtBit;        /**< Bit coding of protocols according to IEC-61158-6-12/FDIS (page 12038) */
enum {
   IoEcatMbxProtBitEoE = 0x02,            /**< Ethernet over EtherCAT */
   IoEcatMbxProtBitCoE = 0x04,            /**< CANopen over EtherCAT */
   IoEcatMbxProtBitFoE = 0x08,            /**< File access over EtherCAT */
   IoEcatMbxProtBitSoE = 0x10,            /**< Servo drive over EtherCAT */
   IoEcatMbxProtBitVoE = 0x20             /**< Vendor-specific profile over EtherCAT */
};


typedef uint32_t IoEcatMbxProtocol;        /**< Protocol coding according to IEC-61158-6-12/FDIS (12038)
                                                6-14 are reserved according to EtherCAT-specification */

/******************************************************************************/
/**
 *  @brief IoEcatMbsProtocol
 *
 *  IoEcatMbsProtocol definitions
 */
enum {
   IoEcatMbxProtocolEoE = 2,              /**< Ethernet over EtherCAT */
   IoEcatMbxProtocolCoE = 3,              /**< CANopen over EtherCAT */
   IoEcatMbxProtocolFoE = 4,              /**< File access over EtherCAT */
   IoEcatMbxProtocolSoE = 5,              /**< Servo drive over EtherCAT */
   IoEcatMbxProtocolVoE = 15              /**< Vendor-specific profile over EtherCAT */
};

#define IO_ECAT_FILENAME_SIZE 256
typedef char IoEcatFileName[IO_ECAT_FILENAME_SIZE]; /**< ECat filename data buffer */


typedef uint32_t IoEcatFileDirection;  /**< Possible file operation directions */
/******************************************************************************/
/**
 *  @brief IoEcatFileDirection
 *
 *  IoEcatFileDirection definitions
 */
enum {
   IoEcatFileDirectionUpload     = 0,     /**< Upload */
   IoEcatFileDirectionDownload   = 1      /**< Download */
};


typedef uint32_t IoEcatState;
enum {
   eCatState_Init            = 1,
   eCatState_PreOperational  = 2,
   eCatState_Bootstrap       = 3,
   eCatState_SafeOperational = 4,
   eCatState_Operational     = 8
};


typedef uint32_t IoApiEcatSlaveDeviceState;  /**< EtherCAT slave device state information */
enum {
  IoApiEcatSlaveDeviceStateConfigure       = 0,   /**< configuration active */
  IoApiEcatSlaveDeviceStateNoLink          = 1,   /**< no link */
  IoApiEcatSlaveDeviceStateIdle            = 2,   /**< no process data exchange */
  IoApiEcatSlaveDeviceStateRunning         = 3,   /**< process data exchange active */
  IoApiEcatSlaveDeviceStateWatchdogTimeout = 4,   /**< watchdog timeout occurred */
  IoApiEcatSlaveDeviceStateError           = 5    /**< other error */
};

#define ECAT_REGISTER_DATA_SIZE 256
typedef char IoEcatRegisterData[ECAT_REGISTER_DATA_SIZE];  /**< Data buffer for an ECat register */


#endif  /* IOAPIECATTYPES_H_ */
