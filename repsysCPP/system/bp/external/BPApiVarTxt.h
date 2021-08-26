/*------------------------------------------------------------------------------
*                             (c) 2013 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Text-Interface for Variables
*
*   Text-Interface for Variables
*
*   Read and write values of Variables as text. Only basic data types can be
*   read or written. All values are converted into a text.
*   The variables need to be identified by their fully qualified access path,
*   e.g. APPL.prog.structVar.member for a 'member' in a structure instance
*   'structVar' located in functional unit or application 'prog'.
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_VARTXT_H
#define PACKAGE_API_VARTXT_H

#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/
/**
 * @brief Read a variable value as a text
 *
 * Read the value of the variable with the specified variable name as a text into destination.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateVarNotFound if 'varName' cannot be found,<BR>
 *          ::BPApiStateNoAccess if it is not allowed to read the variable value,<BR>
 *          ::BPApiStateParamError if 'varName' or 'destination' are NULL, or if size < 64 byte,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotImplementedYet if variable type does not support this action,<BR>
 *          other errorCodes for internal errors
 */
BPApiState BPApiVarTxtRead (
   const char *varName,                          /**< [in]  The variable name. */
   char *destination,                            /**< [out] The destination for the read operation */
   int32_t size                                  /**< [in]  The size of the destination buffer. */
);


/******************************************************************************/
/**
 * @brief Read a property of a variable as a text
 *
 * Read the property of the variable with the specified property name as a text into destination.
 *
 * Currently supported property names of variables of CoDeSys3 applications:<BR>
 *    "AccessKind", "UniqueId",<BR>
 *    "ShortText", "LongText", "HelpText",<BR>
 *    "FormatId", "PrecommaISO", "PostcommaISO", "TextLength", "FormatType", "FormatText",<BR>
 *    "UnitId", "Divisor", "Multiplier", "Transform", "UnitTextISO", "UnitTextImp",<BR>
 *    "RelUnitId", "RelDivisor", "RelMultiplier", "RelTransform", "RelUnitTextISO", "RelUnitTextImp",<BR>
 *    "Visibility", "DisplayLevel", "InputLevel", "SecurityCheck", "UpdateCycle", "LowerLimit", "UpperLimit"<BR>
 *
 * Currently supported property names of variables of KEBA IEC applications:<BR>
 *    "AlarmClass", "AlarmAcknowledge", "AlarmProtocol", "NrOfAlarmSetEvents",<BR>
 *    "AlarmSetEventElem", "NrOfAlarmResetEvents", "AlarmResetEventElem", "HWPath",<BR>
 *    "RefToType", "NrOfEnums", "Enumelem", "TypeOf", "FormatId", "FormatIdFile",<BR>
 *    "PrecommaISO", "PostcommaISO", "FormatType", "UnitId", "UnitIdFile", "Divisor",<BR>
 *    "Multiplier", "Transform", "RelUnitId", "RelUnitIdFile", "RelDivisor", "RelMultiplier",<BR>
 *    "RelTransform", "Visibility", "DisplayLevel", "InputLevel", "SecurityCheck",<BR>
 *    "UpdateCycle", "AccessKind", "SegmentType", "CheckBandwidth", "PropertiesFile",<BR>
 *    "PlausLimits", "Default"<BR>
 *
 * Currently supported property names of variables of KEBA TC applications:<BR>
 *    "TcAttributes"<BR>
 *
 * System variables can offer a property with name "GetProps" which can be used to 
 * query available property names of a variable, e.g. "UnitTextISO".<BR>
 *
 * currently supported tokens:<BR>
 *    "langId"
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateVarNotFound if 'varName' cannot be found,<BR>
 *          ::BPApiStateNoAccess if it is not allowed to read the property value,<BR>
 *          ::BPApiStatePropNotFound if property cannot be found,<BR>
 *          ::BPApiStateParamError if 'varName' or 'destination' are NULL, or if size < 64 byte,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotImplementedYet if variable type does not support this action,<BR>
 *           other errorCodes for internal errors
 */
BPApiState BPApiVarTxtReadProperty (
   const char *varName,                          /**< [in]  The variable name. */
   const char *propName,                         /**< [in]  The property name. */
   const char *token,                            /**< [in]  The token (e.g "langId=en"). */
   char *destination,                            /**< [out] The destination for the read operation. */
   int32_t size                                  /**< [in]  The size of the destination buffer. */
);


/******************************************************************************/
/**
 * @brief Write a variable value as a text
 *
 * Write a text value to the variable with the name specified by varName.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateVarNotFound if 'varName' cannot be found,<BR>
 *          ::BPApiStateNoAccess if it is not allowed to write the variable value,<BR>
 *          ::BPApiStateParamError if 'varName' or 'source' are NULL, or if source value has wrong type,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotImplementedYet if variable type does not support this action,<BR>
 *          other errorCodes for internal errors
 */
BPApiState BPApiVarTxtWrite (
   const char *varName,                          /**< [in] The variable name. */
   const char *source                            /**< [in] The source for the write operation. */
   );


/******************************************************************************/
/**
 * @brief Write a variable value as a text and protocol this operation
 *
 * Write a text value to the variable with the name specified by varName and
 * protocol this operation.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateVarNotFound if 'varName' cannot be found,<BR>
 *          ::BPApiStateNoAccess if it is not allowed to write the variable value,<BR>
 *          ::BPApiStateParamError if 'varName', 'source' or 'protocolInfo' are NULL, or if source value has wrong type,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotImplementedYet if variable type does not support this action,<BR>
 *          other errorCodes for internal errors
 */
BPApiState BPApiVarTxtWriteWithProtocol (
   const char *varName,                          /**< [in] The variable name. */
   const char *source,                           /**< [in] The source for the write operation. */
   const BPApiVarProtocolData * protocolInfo     /**< [in] protocol data; if a NULL pointer is passed, the function returns BPApiStateParamError. */
   );


#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_VARTXT_H_INCLUDED */
