/*------------------------------------------------------------------------------
*                             (c) 2016 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief  Interface for events exported to OPC-UA
*
*   Interface for OPC-UA-enabled events
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_PUBLIC_EVTS_H
#define PACKAGE_API_PUBLIC_EVTS_H

#include "BPApiVariables.h"

#ifdef __cplusplus
extern "C" {
#endif

/** event field definition type */
typedef struct BPApiOpcUaEvtsField_ {
   const char   *name;   /**< field name */
   BPApiVarType  type;   /**< field datatype (BPApiVarTypeXxx) */
} BPApiOpcUaEvtsField;

/** event handle type */
typedef uint32_t BPApiOpcUaEvtsHdl;

/******************************************************************************/
/**
 * @brief Register an event exported to OPC-UA
 *
 * register an event that can be used to notify OPC-UA clients
 *
 * @retval BPApiStateOk            event registered
 * @retval BPApiStateParamError    already registered or invalid arguments
 * @retval BPApiStateOutOfMemory   out of memory in intermediate operation
 * @retval BPApiStateNotOk         register failed (system resources...)
 *
 * @note Supported field datatypes:
 *    \em BPApiVarTypeBOOL to \em BPApiVarTypeLWORD, and
 *    \em BPApiVarTypeSTRING to \em BPApiVarTypeWSTRING.
 */
BPApiState BPApiOpcUaEvtsRegister(
   const char                *name,         /**< [in] event name */
   const BPApiOpcUaEvtsField *fields,       /**< [in] event data fields */
   int                        fieldCount,   /**< [in] number of event data fields */
   BPApiOpcUaEvtsHdl         *hdl           /**< [out] handle of registered event */
   );

/******************************************************************************/
/**
 * @brief Unregister an event exported to OPC-UA
 *
 * unregister a previously registered event
 *
 * @retval BPApiStateOk              event unregistered
 * @retval BPApiStateInvalidHandle   invalid event handle
 */
BPApiState BPApiOpcUaEvtsUnregister(
   BPApiOpcUaEvtsHdl hdl   /**< [in] handle of registered event */
   );

/******************************************************************************/
/**
 * @brief Fire an event
 *
 * fire an event and notify OPC-UA clients that will receive the given arguments
 *
 * @retval BPApiStateOk              event fired
 * @retval BPApiStateInvalidHandle   invalid event handle
 * @retval BPApiStateParamError      invalid argument(s)
 * @retval BPApiStateOutOfMemory     out of memory in internal step
 * @retval BPApiStateNotOk           fire operation failed
 *
 * @note The size of all fields together with event name and message (including
 * terminating zeros) passed to \em BPApiOpcUaEvtsFire must not exceed 981 Bytes.
 */
BPApiState BPApiOpcUaEvtsFire(
   BPApiOpcUaEvtsHdl  hdl,         /**< [in] handle of registered event */
   int                severity,    /**< [in] severity of event (uint16_t according to OPC-UA) */
   const char        *msgText,     /**< [in] message associated with event (UTF-8) */
   const char        *msgLocale,   /**< [in] locale of message (e.g. "en-US") */
   ...                             /**< [in] event data (must match field data types and order) */
   );

#ifdef __cplusplus
}
#endif

#endif /* PACKAGE_API_PUBLIC_EVTS_H */
