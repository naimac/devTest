/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoCopApi base type definitions
*
*   IoCopApi standard return code definitions and declaration of types.
*/

#ifndef IOCOPTYPESAPI_H_
#define IOCOPTYPESAPI_H_

#include <stdint.h>


/******************************************************************************/
/**
 *  @brief Return code definition
 *
 *  Return code definition of CANOpen functions.
 *  These return codes extend the IoApiState which is defined in IoApiTypes.h.
 */
enum {
  IoCopApiStateConInvalidConfig   = 0x00000301UL,     /**< Invalid config occurres (eg. autoStart=1) */
  IoCopApiStateEmcyInvalidState   = 0x00000302UL,     /**< Device is in invalid state! Emergency can only be sent in Operational or Pre-Operational. */
  IoCopApiStateEvtNoMoreData      = 0x00000303UL,     /**< Event fifo is empty. */
  IoCopApiStateEvtQueueOverrun    = 0x00000304UL,     /**< Event fifo run over. */
  IoCopApiStateNoMorePdoData      = 0x00000305UL      /**< Result if PDO number is greater than available PDO's. */
};





/******************************************************************************/
/**
 *  Type definition
 */

#define CAN_SDO_DATA_SIZE 256
typedef uint8_t SdoData[CAN_SDO_DATA_SIZE];  /**< Data buffer for service data objects (SDO). */

#define IO_COP_FILENAME_SIZE 256
typedef char IoCopFileName[IO_COP_FILENAME_SIZE]; /**< ECat filename data buffer */



/******************************************************************************/
/**
 * @brief Data of an emergency message.
 */
typedef struct IoCopEmergency {
   uint16_t         errCode;          /**< Emergency Error Code. */
   uint8_t          errReg;           /**< Error Register. */
   uint8_t          addInfo[5];       /**< Manufacturer-specific Error Field. */
} IoCopEmergency;


typedef uint32_t  IoCopNmtAction;       /**< Network Management (NMT) Action. */
enum {
   IoCopNmtActionStart               = 0x01,    /**< Start. */
   IoCopNmtActionStop                = 0x02,    /**< Stop. */
   IoCopNmtActionEnterPreOperational = 0x80,    /**< Enter Pre-Operational state. */
   IoCopNmtActionResetNode           = 0x81,    /**< Reset node. */
   IoCopNmtActionResetCommunication  = 0x82     /**< Reset communication. */
};


typedef uint32_t IoCopNmtState;         /**< Network Management (NMT) state of a slave. */
enum {
   IoCopNmtStateInit                = 0x00,    /**< Init. */
   IoCopNmtStateStopped             = 0x04,    /**< Stopped. */
   IoCopNmtStateOperational         = 0x05,    /**< Operational. */
   IoCopNmtStatePreOperational      = 0x7F     /**< Pre-Operational. */
};


typedef uint32_t IoCopPdoTransmissionType;   /**< Transmission type of the process data object (PDO). */
enum {
   IoCopPdoTransmissionTypeSynchronousCyclic       = 0x00,    /**< synchronous cyclic PDO. */
   IoCopPdoTransmissionTypeRTR                     = 0x01,    /**< (a)synchronous RTR-PDO (RxPDO only). */
   IoCopPdoTransmissionTypeAsynchronous            = 0x02,    /**< asynchronous send-PDO (TxPDO only). */
   IoCopPdoTransmissionTypeEvent                   = 0x03     /**< event triggered PDO (RxPDO only). */
};


typedef uint32_t IoCopSlaveEvent;   /**< Eventtypes of CANOpen slaves. */
enum {
  IoCopSlaveEventUndefined         = 0,      /**< Undefined event. */
  IoCopSlaveEventNmtStateChange    = 1,      /**< NMT state changed event. */
  IoCopSlaveEventLifeGuard         = 2,      /**< Life guard event. */
  IoCopSlaveEventHeartbeatConsume  = 3,      /**< Heartbeat consume event. */
  IoCopSlaveEventPdo               = 4,      /**< PDO event. */
  IoCopSlaveEventSdoRequest        = 5       /**< SDO request event. */
};


typedef uint32_t IoCopGuardingState;         /**< States for Node- and Life-Guarding */
enum {
  IoCopGuardingStateUndefined         = 0,    /**< State is undefined. */
  IoCopGuardingStateInactive          = 1,    /**< Guarding is inactive. */
  IoCopGuardingStateNodeGuard         = 2,    /**< Node Guarding is active. */
  IoCopGuardingStateLifeGuard         = 3,    /**< Life Guarding is active. */
  IoCopGuardingStateLifeGuardNotRecv  = 4     /**< Life Gurading error occurred. Slave wasn't able to receive an exptected Life Gurading message from master. */
};


typedef uint32_t IoCopHeartbeatProdState;    /**< States for heartbeat produce */
enum {
  IoCopHeartbeatProdStateUndefined   = 0,    /**< State is undefined. */
  IoCopHeartbeatProdStateInactive    = 1,    /**< Heartbeat is inactive. */
  IoCopHeartbeatProdStateActive      = 2    /**< Heartbeat is active. */
};


typedef uint32_t IoCopHeartbeatConsState;    /**< States for heartbeat consume */
enum {
  IoCopHeartbeatConsStateUndefined   = 0,    /**< State is undefined. */
  IoCopHeartbeatConsStateInactive    = 1,    /**< Heartbeat is inactive. */
  IoCopHeartbeatConsStateActive      = 2,    /**< Heartbeat is active. */
  IoCopHeartbeatConsStateNotRecv     = 3     /**< Heartbeat error occurred. Slave wasn't able to receive an expected Heartbeat message from master. */
};


typedef uint32_t IoCopPdoDir;    /**< process data object (PDO) type. */
enum {
  IoCopDirPdoRx = 0,        /**< Receiving PDO. Outputs are configured (TxPDO). */
  IoCopDirPdoTx = 1         /**< Sending PDO. Inputs are configured (RxPDO). */
};


typedef uint32_t IoCopPdoState;    /**< States of a process data object (PDO). */
enum {
  IoCopPdoStateUndefined   = 0,    /**< State is undefined. */
  IoCopPdoStateInactive    = 1,    /**< PDO is inactive or not enabled. */
  IoCopPdoStateCommOk      = 2,    /**< for receive PDO: PDO received
                                        for send PDO:    PDO sent*/
  IoCopPdoStateCommNotOk   = 3     /**< for receive PDO: PDO receive failed
                                        for send PDO:    PDO send failed*/
};

/******************************************************************************/
/**
 * @brief Parameter of a process data object (PDO).
 */
typedef struct IoCopPdoParam {
   IoApiHdl                   pdoHdl;               /**< IO-Handle of the PDOs. */
   uint32_t                   dataLength;           /**< Lenght of the PDOs in Byte. */
   IoCopPdoTransmissionType   transmissionType;     /**< Transmission type of the PDOs. */
   uint32_t                   cycleTimeReduction;   /**< Reduction factor of the PDOs (only synchronous cyclic PDOs). */
} IoCopPdoParam;


typedef uint32_t IoCopSdoDir;    /**< SDO direction */
enum {
  IoCopDirSdoWrite    = 0,      /**< SDO write. */
  IoCopDirSdoRead     = 1       /**< SDO read. */
};


typedef uint32_t IoCopSdoState;        /** State of the actual SDO transfer. <*/
enum {
   IoCopSdoStateNotInitiatedYet  = 0,  /**< SDO transfer not yet initiated. */
   IoCopSdoStateInitiateDlCnf    = 1,  /**< Initiate SDO download. */
   IoCopSdoStateInitiateUplCnf   = 2,  /**< Initiate SDO upload. */
   IoCopSdoStateDownloadSegCnf   = 3,  /**< SDO download. */
   IoCopSdoStateUploadSegCnf     = 4,  /**< SDO upload. */
   IoCopSdoStateAborted          = 5,  /**< SDO transfer aborted. */
   IoCopSdoStateReady            = 6,  /**< SDO transfer ready. */
   IoCopSdoStateBusy             = 7   /**< SDO transfer running. */
};

typedef uint32_t IoCopSdoOption;       /**< Access options for SDO transfer. */
enum {
   IoCopSdoOptionNone           = 0x0, /**< No specific option */
   IoCopSdoOptionCompleteAccess = 0x1  /**< Bit 0: 0: no complete access
                                                   1: complete access active */
};

/******************************************************************************/
/**
 * @brief Result of an SDO transfer.
 */
typedef struct IoCopSdoResult {
   uint32_t       transferredBytes;    /**< Number of transferred bytes. */
   IoCopSdoState  sdoState;            /**< State of the actual SDO transfer. */
   uint32_t       abortCode;           /**< SDO abort code (if SDO transfer was aborted) */
} IoCopSdoResult;

#endif  /* IOCOPTYPESAPI_H_ */
