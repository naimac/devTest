/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing the IoTree
*	
*   Interface for browsing the IoTree and reading state and information.
*/

#ifndef IOTREEAPI_H_
#define IOTREEAPI_H_

#include "IoApiTypes.h"
#include "IoApiAsync.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  IO tree
*/

/******************************************************************************/
/**
 *  @brief Delivers handle of an IO-node
 *
 *  Delivers handle of an IO-node (device, bus, end point) named by
 *  ioDeviceName. If ioDeviceName is 0 or empty the "IO" root handle is
 *  returned.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if ioDeviceHdl pointer is invalid.
 *         IoApiStateInvalidHandle, if device with name ioDeviceName could not be found.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetIoHdl(
   const char *ioDeviceName,                 /**< [in]  The IO-node name. */
   IoApiHdl  *ioDeviceHdl                    /**< [out] Returns the cfg-handle. */
   );

/******************************************************************************/
/**
 *  @brief Delivers IO-node handle
 *
 *  Delivers IO-node handle of parent node.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if resultHdl pointer is invalid.
 *         IoApiStateInvalidHandle, if no parent device could be found.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetParentHdl(
   IoApiHdl  ioNodeHdl,                      /**< [in]  The actual source handle. */
   IoApiHdl *resultHdl                       /**< [out] The parent handle. */
   );

/******************************************************************************/
/**
 *  @brief Delivers the first IO-node handle
 *
 *  Delivers the first IO-node handle from a branch of the actual handle.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if resultHdl pointer is invalid.
 *         IoApiStateInvalidHandle, if no child device could be found.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetFirstHdl(
   IoApiHdl  ioNodeHdl,                      /**< [in]  The actual source handle. */
   IoApiHdl *resultHdl                       /**< [out] The first handle from the branch. */
   );

/******************************************************************************/
/**
 *  @brief  Delivers the next IO-node handle
 *
 *  Delivers the next IO-node handle of the actual node.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if resultHdl pointer is invalid.
 *         IoApiStateInvalidHandle, if no next device could be found.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetNextHdl(
   IoApiHdl  ioNodeHdl,                      /**< [in]  The actual source handle. */
   IoApiHdl *resultHdl                       /**< [out] The next handle of the actual branch. */
   );

/******************************************************************************/
/**
 *  @brief  Get path of IO-node handle
 *
 *  Get an ASCII string containing the path of corresponding bus or device, starting with “IO.ONBOARD”.
 *
 *  This function can be used to get a connection with the bus or device in
 *  the variable browser by adding "SYS." at the beginning.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if pPathName pointer is invalid.
 *         IoApiStateInvalidHandle, if no bus or device could be found.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetPath(
   IoApiHdl       ioHdl,               /**< [in] handle of bus or io device */
   char          *pPathName,           /**< [out] Path of corresponding bus or device, starting with “IO.ONBOARD” */
   unsigned int   maxPathLen           /**< [in]  Maximal length of the pPathName string */
   );

/******************************************************************************/
/**
 *  @brief State definition of an IO-module for calling from an application.
 *
 *  The state definition of an IO-module can be a combination of the defined
 *  bit flags and must be analyzed separately.
 *
 *    IoApiStateBitValid is set if the device is valid and has no error.
 *    IoApiStateBitValidSubTree is set if the device has a children that are
 *    valid and have no errors.
 *    IoApiStateBitError is set if the device has an error.
 *    IoApiStateBitErrorSubTree is set if the device has a children that has an
 *    error.
 *    IoApiStateBitSimulated is set if the device is simulated.
 *    IoApiStateBitSimulatedSubTree is set if the device has children that are
 *    simulated.
 *    IoApiStateBitForcedSubTree is set if the children of the device are forced.
 *    IoApiStateBitDetected is set if the device has been detected.
 *    IoApiStateBitOptional is set if the device is configured as optional.
 *    Once the device has been detected, this bit is set to 0.
 *    IoApiStateBitGuardingOff is set if the device is guarded. For guarded
 *    devices state changes like errors, connects and disconnects are
 *    recognized.
 *    IoApiStateBitOptionalCfg is set if the device is configured as optional or
 *    if an optional configuration has been inherited from the parent node.
 */
typedef uint32_t IoStateBit;
enum {
   IoApiStateBitValid            = 0x0001,   /**< Module has no error. */
   IoApiStateBitValidSubTree     = 0x0002,   /**< Total state (node and sub tree). */
   IoApiStateBitError            = 0x0004,   /**< Node is at error state. */
   IoApiStateBitErrorSubTree     = 0x0008,   /**< Total state (node and sub tree). */
   IoApiStateBitSimulated        = 0x0010,   /**< Node is simulated. */
   IoApiStateBitSimulatedSubTree = 0x0020,   /**< Total state (node and sub tree). */
   IoApiStateBitForcedSubTree    = 0x0040,   /**< Total state of all configured end points. */
   IoApiStateBitDetected         = 0x0080,   /**< Module detected. */
   IoApiStateBitOptional         = 0x0100,   /**< Module optional. */
   IoApiStateBitGuardingOff      = 0x0200,   /**< Failure detection inactive. */
   IoApiStateBitOptionalCfg      = 0x0400,   /**< Module configured as optional. */
   IoApiStateBitReserved1        = 0x0800,
   IoApiStateBitReserved2        = 0x1000,
   IoApiStateBitReserved3        = 0x2000,
   IoApiStateBitReserved4        = 0x4000,
   IoApiStateBitReserved5        = 0x8000
};

typedef uint32_t IoModuleNodeType;  /**< Predefined type numbers of catalog entries.*/
enum {
   /* Objects with signaling mechanism: */
   IoApiNodeTypeDir              = 1,        /**< Catalog entry descriptor */
   IoApiNodeTypeTask             = 2,        /**< Task, record in "TASK" */
   IoApiNodeTypeTimer            = 3,        /**< Timer, record in "TIMER" */
   IoApiNodeTypeEvent            = 4,        /**< Event, record in "EVENT" */
   IoApiNodeTypeSema             = 5,        /**< Semaphore, record in "SEMA" */
   IoApiNodeTypeMsgQueue         = 6,        /**< Message queue, record in "MSGQUEUE " */
   IoApiNodeTypeRegion           = 7,        /**< Region, record in "REGION" */
   IoApiNodeTypeShMem            = 8,        /**< Shared memory, record in "SHMEM" */
   IoApiNodeTypeProcCall         = 9,        /**< External procedure, record in "PROCCALL" */
   IoApiNodeTypeMsgHandler       = 10,       /**< Message handler, record in "MSGHANDLER" */
   IoApiNodeTypeMsgBuffer        = 11,       /**< Message buffer, record in "MSGBUFFER" */
   IoApiNodeTypeMsgLogger        = 12,       /**< Message logger, record in "MSGLOGGER" */

   /* Objects without signaling mechanism: */
   IoApiNodeTypeTypeTrace        = 20,       /**< Trace buffer, record in "TRACE" */
   IoApiNodeTypeVarTab           = 21,       /**< Variable table, record in "VARTAB" */

   /* Interface objects: */
   IoApiNodeTypeInterface        = 50,       /**< Interface entry: an array of function pointer */

   /* Data objects: */
   IoApiNodeTypeBOOL             = 60,       /**< Boolean entry, 8 bit, 0 or 1 */
   IoApiNodeTypeINT32            = 61,       /**< Integer entry, 32 bit signed integer */
   IoApiNodeTypeINT64            = 62,       /**< Long entry, 64 bit signed integer */
   IoApiNodeTypeREAL             = 63,       /**< Double entry, 64 bit float */
   IoApiNodeTypeSTRING           = 64,       /**< String entry, null-terminated */

   /* End point, bus, device object */
   IoApiNodeTypeEpMin            = 100,      /**< Begin end point types */
   IoApiNodeTypeEpMax            = 199,      /**< End end point types */
   IoApiNodeTypeBusMin           = 200,      /**< Begin bus types */
   IoApiNodeTypeBusMax           = 299,      /**< End bus types */
   IoApiNodeTypeDeviceMin        = 300,      /**< Begin device types */
   IoApiNodeTypeDeviceMax        = 999       /**< End device types */
};

/** State data of an IO-module for calling from an application via IoApiGetIoState */
typedef struct {
   IoStateBit       ioStateBit;              /**< State definition of IO-module */
   IoModuleNodeType nodeTyp;                 /**< Type of IO-module */
   char             nodeKey[32];             /**< Node key of IO-module */
   char             configName[32];          /**< Configured node name of IO-module */
   uint32_t         reserved1;
   uint32_t         reserved2;
} IoStateData;

/******************************************************************************/
/**
 *  @brief Reads state of IO-node
 *
 *  Reads state of IO-node (bus, device, end point).
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidAddr, if stateData pointer is invalid.
 *         IoApiStateInvalidHandle, if ioNodeHdl points to an invalid device.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetIoState(
   IoApiHdl     ioNodeHdl,                   /**< [in]  Device node handle. */
   IoStateData *stateData                    /**< [out] Returns state data of the IO-module. */
   );

/******************************************************************************/
/**
 *  @brief Gets the bus of the given IO node.
 *
 *  Gets the bus of the given IO node.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidHandle, if ioNodeHdl points to an invalid device.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetBus(
   IoApiHdl     ioNodeHdl,                   /**< [in]  IO node handle. */
   IoApiHdl    *ioBusHdl                     /**< [out] IO bus handle of the given node. */
   );

/******************************************************************************/
/**
 *  @brief Delivers the next sibling of the given catalog handle
 *
 *  Delivers the next sibling of the given catalog handle.
 *
 * @return State information about the call.
 *         IoApiStateOk on success, busObjectId contains the Id as ASCII string.
 *         IoApiStateInvalidAddr, if busObjectId pointer is invalid.
 *         IoApiStateInvalidHandle, if no busObjectId could be found.
 */
IoApiState IoApiGetBusObjectId(
   IoApiHdl devHdl,                          /**< [in]  The actual Ecat handle. */
   int      maxBusObjectIdLen,               /**< [in]  Maximal length of the busObjectId string */
   char   **busObjectId                      /**< [out] An ASCII string containing the busObjectId */
   );

typedef uint32_t IoBusStatisticsState;       /**< Current state of bus statistics. */
enum {
   IoBusStatisticsStateNotSupported = 0,     /**< Bus statistics not supported. */
   IoBusStatisticsStateAlwaysActive = 1,     /**< Bus statistics is always active.
                                                  Can not be started/stopped manually. */
   IoBusStatisticsStateStarted      = 2,     /**< Bus statistics is started. */
   IoBusStatisticsStateStopped      = 3      /**< Bus statistics is stopped. */
};

/******************************************************************************/
/**
 *  @brief Get current state of bus statistics
 *
 *  Get current state of bus statistics (Is bus statistics supported/started/
 *  stopped?). ioBusHdl is delivered by IoApiGetBus or IoApiGetIoHdl (where
 *  ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success, busState contains the current state of bus
 *         statistics.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetBusStatisticsState(
   IoApiHdl              ioBusHdl,           /**< [in]  The bus handle. */
   IoBusStatisticsState *busState            /**< [out] The current state of bus statistics. */
   );

/******************************************************************************/
/**
 *  @brief Start bus statistics.
 *
 *  Starting bus statistics. ioBusHdl is delivered by IoApiGetBus or
 *  IoApiGetIoHdl (where ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success.
 *         IoApiStateNotSupported, if function is not supported for given bus.
 *         IoApiStateInvalidParam, if given ioBusHdl is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiStartBusStatistics(
   IoApiHdl ioBusHdl                         /**< [in]  The bus handle. */
   );

/******************************************************************************/
/**
 *  @brief Stop bus statistics.
 *
 *  Stopping bus statistics. ioBusHdl is delivered by IoApiGetBus or
 *  IoApiGetIoHdl (where ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success.
 *         IoApiStateNotSupported, if function is not supported for given bus.
 *         IoApiStateInvalidParam, if given ioBusHdl is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiStopBusStatistics(
   IoApiHdl ioBusHdl                         /**< [in]  The bus handle. */
   );

/******************************************************************************/
/**
 *  @brief Reset bus statistics.
 *
 *  Reseting bus statistics. ioBusHdl is delivered by IoApiGetBus or
 *  IoApiGetIoHdl (where ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success.
 *         IoApiStateNotSupported, if function is not supported for given bus.
 *         IoApiStateInvalidParam, if given ioBusHdl is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiResetBusStatistics(
   IoApiHdl ioBusHdl                         /**< [in]  The bus handle. */
   );

typedef uint32_t IoBusMonitorState;       /**< Current state of bus monitor. */
enum {
   IoBusMonitorStateNotSupported = 0,     /**< Bus monitor not supported. */
   IoBusMonitorStateStarted      = 1,     /**< Bus monitor is started. */
   IoBusMonitorStateStopped      = 2,     /**< Bus monitor is stopped. */
   IoBusMonitorStateSavingFile   = 3,     /**< Bus monitor is stopped, because the control
                                               writes data to a file. The bus monitor can not
                                               be started in this state. */
   IoBusMonitorStateSavedFile    = 4      /**< Bus monitor was stopped automatically, because
                                               the control wrote data to a file. The bus
                                               monitor can be restarted with the function
                                               IoApiStartBusMonitor. */
};

/******************************************************************************/
/**
 *  @brief Get current state of bus monitor
 *
 *  Get current state of bus monitor (Is bus monitor supported/started/
 *  stopped/restartable?). ioBusHdl is delivered by IoApiGetBus or
 *  IoApiGetIoHdl (where ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success, busState contains the current state of bus
 *         monitor.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetBusMonitorState(
   IoApiHdl              ioBusHdl,           /**< [in]  The bus handle. */
   IoBusMonitorState    *busState            /**< [out] The current state of bus monitor. */
   );

/******************************************************************************/
/**
 *  @brief Start bus monitor.
 *
 *  Starting bus monitor. ioBusHdl is delivered by IoApiGetBus or
 *  IoApiGetIoHdl (where ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success.
 *         IoApiStateNotSupported, if function is not supported for given bus
 *                                 or in current state.
 *         IoApiStateInvalidParam, if given ioBusHdl is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiStartBusMonitor(
   IoApiHdl ioBusHdl                         /**< [in]  The bus handle. */
   );

/******************************************************************************/
/**
 *  @brief Stop bus monitor.
 *
 *  Stopping bus monitor. ioBusHdl is delivered by IoApiGetBus or
 *  IoApiGetIoHdl (where ioDeviceName must be the name of a bus device).
 *
 * @return State information about the call.
 *         IoApiStateOk on success.
 *         IoApiStateNotSupported, if function is not supported for given bus.
 *         IoApiStateInvalidParam, if given ioBusHdl is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiStopBusMonitor(
   IoApiHdl ioBusHdl                         /**< [in]  The bus handle. */
   );

/******************************************************************************/
/**
 *  @brief Get bus time of next cycle
 *
 *  Get bus time of next cycle (if supported).
 *
 * @return State information about the call.
 *         IoApiStateOk on success.
 *         IoApiStateNotSupported, if function is not supported for given bus.
 *         IoApiStateInvalidParam, if given ioBusHdl is invalid.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetBusTimeOfNextCycle(
   IoApiHdl ioBusHdl,           /**< [in]  The bus handle. */
   int periodNs,                /**< [in]  Period in ns. */
   uint64_t *busTimeNs          /**< [out] Bus time at next period in ns. */
   );

/******************************************************************************/
/**
 *  @brief Reads the cycle time of an IO node and its bus.
 *
 *  Reads the cycle time of an IO node (bus, device, end point) and its bus.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidHandle, if ioNodeHdl points to an invalid device.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetCycleTime(
   IoApiHdl     ioNodeHdl,                   /**< [in]  IO node handle. */
   IoApiTime   *busCycleTime,                /**< [out] Cycle time of the bus of the given IO node. */
   uint32_t    *busCycleCount,               /**< [out] Number of bus cycles between two updates of the given IO node. */
   uint32_t    *phaseShift                   /**< [out] Number of bus cycles the given IO node is shifted (0 to busCycleCount-1). */
   );

/******************************************************************************/
/**
 *  @brief Reads the current phase of an IO node.
 *
 *  Reads the cycle phase of an IO node in bus cycles since
 *  the last update of the given IO node (0 to busCycleCount-1).
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidHandle, if ioNodeHdl points to an invalid device.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetCyclePhase(
   IoApiHdl     ioNodeHdl,                   /**< [in]  IO node handle. */
   uint32_t    *cyclePhase                   /**< [out] Number of bus cycles since last update of the IO node. */
   );

/******************************************************************************/
/**
 *  @brief Reads the age of the IO node value.
 *
 *  Reads the age of the IO node value in ticks and microseconds.
 *  The age is the time span since the last update
 *  of the given IO node (0 to busCycleCount-1).
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateInvalidHandle, if ioNodeHdl points to an invalid device.
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetAge(
   IoApiHdl     ioNodeHdl,                   /**< [in]  IO node handle. */
   uint32_t    *systemTicks                  /**< [out] Number of ticks since last update of the IO node. */
   );

/******************************************************************************/
/**
 *  @brief Get name of endpoint by bit offset in CoDeSys-Memory and direction.
 *
 *  Get name of endpoint by bit offset in CoDeSys-Memory and direction.
 *  Supported only for data endpoints mapped to CoDeSys-Memory, not for STAT endpoints.
 *
 * @return State information about the call.
 *         IoApiStateOk, if operation has been finished.
 *         IoApiStateNoData, if no endpoint exists at provided bit offset
 *         IoApiStateNotSupported, if no CoDeSys memory is available
 *         IoApiStateInvalidParam, if no string has been provided
 *         IoApiStateNotOk, if function call failed
 */
IoApiState IoApiGetEpName(
   uint32_t       epBitOffset,               /**< [in] bit offset of endpoint */
   IoApiDirection direction,                 /**< [in] direction of endpoint (in/out) @see IoApiDirection */
   unsigned int   maxEpNameLen,              /**< [in]  Maximal length of the pEpName string */
   char         **epName                     /**< [out] An ASCII string containing the name of corresponding endpoint */
   );

/** Predefined ids of parameters.*/
typedef uint32_t IoApiParamId;
enum {
   /** 'no' parameter, <null> */
   IoApiParamIdNone             = 0,

   /** Endpoint 'gain' parameter (RW)
       Handle: endpoint
       Data type: IoApiParamTypeREAL
       Note: After writing this parameter parameter eIoSysParamEpOffset has
             to be written as well to take over this param. This is because
             gain and offset are only valid as combination. */
   IoApiParamIdEpGain                                        = 1,

   /** Endpoint 'offset' parameter (RW)
       Handle: endpoint
       Data type: IoApiParamTypeREAL
       Note: Before writing this parameter parameter IoApiParamIdEpGain has to
             be written because gain and offset are only valid as a
             combination. Both parameters become active when IoApiParamIdEpOffset
             is written. */
   IoApiParamIdEpOffset                                      = 2,

   /** Device hardware name (R)
       Handle: device
       Data type: IoApiParamTypeSTRING(256) */
   IoApiParamIdDeviceHwName                                  = 3,

   /** Device type (R)
       Handle: device
       Data type: IoApiParamTypeSTRING(256) */
   IoApiParamIdDeviceType                                    = 4
};

/** Predefined attributes of parameters.*/
typedef uint32_t IoApiParamAttr;
enum {
   /** no attribute, <null> */
   IoApiParamAttrNone = 0
};

/** Parameter data type.*/
typedef uint32_t IoApiParamType;
enum {
   /** 'no'type, reserved */
   IoApiParamTypeNone      = 100,
   /** signed integer types */
   IoApiParamTypeSINT      = 110,
   IoApiParamTypeINT       = 111,
   IoApiParamTypeDINT      = 112,
   IoApiParamTypeLINT      = 113,
   /** unsigned integer types  */
   IoApiParamTypeUSINT     = 120,
   IoApiParamTypeUINT      = 121,
   IoApiParamTypeUDINT     = 122,
   IoApiParamTypeULINT     = 123,
   /** bool type */
   IoApiParamTypeBOOL      = 131,
   /** bit types */
   IoApiParamTypeBYTE      = 141,
   IoApiParamTypeWORD      = 142,
   IoApiParamTypeDWORD     = 143,
   IoApiParamTypeLWORD     = 144,
   /** real types */
   IoApiParamTypeREAL      = 151,
   IoApiParamTypeLREAL     = 152,
   /** string types */
   IoApiParamTypeSTRING    = 171,
   IoApiParamTypeWSTRING   = 172
};

/******************************************************************************/
/**
 * @brief Read a parameter asynchronously.
 *
 * Start to read a parameter.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk: the operation has been finished.
 *         IoApiStateInvalidHandle: invalid handle
 *         IoApiStateInvalidParam: parameter not valid or not supported
 *         IoApiStateInvalidAttr: attribute not valid or not supported
 *         IoApiStateWrongDataTypeReq: wrong data type requested
 *         IoApiStateQueueOverrun: queue overrun
 *         IoApiStateNotSupported: access not supported in the current device state
 *         IoApiStatePending: the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped: the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk: success.
 *         IoApiStateInvalidHandle: invalid handle
 *         IoApiStateInvalidParam: parameter not valid or not supported
 *         IoApiStateInvalidAttr: attribute not valid or not supported
 *         IoApiStateWrongDataTypeReq: wrong data type requested
 *         IoApiStateQueueOverrun: queue overrun
 *         IoApiStateNotSupported: access not supported in the current device state
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvalidBufSize, if buffer size is too small for data type.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
*/
IoApiState IoApiReadParameterAsyncStart(
   IoApiHdl hdl,           /**< [in]  Handle of the endpoint, device or bus. */
   IoApiParamId paramNr,   /**< [in]  Parameter to be read. */
   IoApiParamAttr attr,    /**< [in]  Parameter attribute to be read. */
   IoApiParamType type,    /**< [in]  Data type of parameter/attribute to be read. */
   unsigned int bufLen,    /**< [in]  buffer length of pValue */
   void *pValue,           /**< [out] Parameter or attribute value read. */
   IoApiOverlapped  *ov    /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
);

/******************************************************************************/
/**
 * @brief Write a parameter asynchronously.
 *
 * Start to write a parameter.
 * Poll for result with the function IoApiAsyncGetResult().
 *
 *    The function IoApiAsyncGetResult() can have the following return states:
 *         IoApiStateOk: the operation has been finished.
 *         IoApiStateInvalidHandle: invalid handle
 *         IoApiStateInvalidParam: parameter not valid or not supported
 *         IoApiStateInvalidAttr: attribute not valid or not supported
 *         IoApiStateWrongDataTypeReq: wrong data type requested
 *         IoApiStateOutOfRange: invalid value to write
 *         IoApiStateWrongCallOrder: invalid order when writing parameters
 *         IoApiStateQueueOverrun: queue overrun
 *         IoApiStateNotSupported: access not supported in the current device state
 *         IoApiStatePending: the operation has been submitted but is not
 *         yet finished.
 *         IoApiStateInvOverlapped: the used IoApiOverlapped is corrupt.
 *         IoApiStateNotOk, if an error occurred.
 *
 * @return State information about the asynchronous operation.
 *         IoApiStateOk: success.
 *         IoApiStateInvalidHandle: invalid handle
 *         IoApiStateInvalidParam: parameter not valid or not supported
 *         IoApiStateInvalidAttr: attribute not valid or not supported
 *         IoApiStateWrongDataTypeReq: wrong data type requested
 *         IoApiStateOutOfRange: invalid value to write
 *         IoApiStateWrongCallOrder: invalid order when writing parameters
 *         IoApiStateQueueOverrun: queue overrun
 *         IoApiStateNotSupported: access not supported in the current device state
 *         IoApiStateInvalidBufSize, if buffer size is too small for data type.
 *         IoApiStatePending, if the operation has been submitted.
 *         IoApiStateInvOverlapped, if used IoApiOverlapped is uninitialized or already in use.
 *         IoApiStateNotOk, if an error occurred.
*/
IoApiState IoApiWriteParameterAsyncStart(
   IoApiHdl hdl,             /**< [in]  Handle of the endpoint, device or bus. */
   IoApiParamId paramNr,     /**< [in]  Parameter to be written. */
   IoApiParamAttr paramAttr, /**< [in]  Parameter attribute to be written. */
   IoApiParamType paramType, /**< [in]  Data type of parameter/attribute to be written. */
   unsigned int bufLen,      /**< [in]  buffer length of pValue */
   void *pValue,             /**< [in]  Parameter or attribute value to be written.*/
   IoApiOverlapped  *ov      /**< [out] This function fills an IoApiOverlapped object which can be passed to IoApiAsyncGetResult(). */
);

#ifdef __cplusplus
}
#endif

#endif
