/*------------------------------------------------------------------------------
*                             (c) 2016 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief  Interface for functions exported to OPC-UA
*
*   Interface for OPC-UA-enabled functions
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_OPCUA_FCTS_H
#define PACKAGE_API_OPCUA_FCTS_H

#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** function prototype (Note: return codes 0x80xxxxxx are reserved by system!) */
typedef int (*BPApiOpcUaFctsType)(...);

/******************************************************************************/
/**
 * @brief Register a function exported to OPC-UA
 *
 * register a function that can be called by OPC-UA clients
 *
 * @retval BPApiStateOk           function registered
 * @retval BPApiStateParamError   already registered, invalid signature, null pointer
 * @retval BPApiStateNotOk        register failed (system resources...)
 *
 * @note The signature defines the input/output parameter types as follows:
 *
 *     signature := [ <inputparameter> ] [ ">" <outputparameter> ].
 *     parameter := upperCaseTypeLetter | A | U | P | <number>lowerCaseTypeLetter.
 *     upperCaseTypeLetter := I | X | B | W | D | Q | R | L.
 *     
 *     Input parameter types:
 *     I = int32_t
 *     X = bool
 *     B = uint8_t (byte)
 *     W = uint16_t (word)
 *     D = uint32_t (double word)
 *     Q = uint64_t (quad word)
 *     R = float (real)
 *     L = double (long real)
 *     A = const char* (ASCII-encoded string)
 *     U = const uint16_t* (UTF16-encoded string)
 *     P = const void *data, unsigned int size (BLOB)
 *     
 *     Output parameter types:
 *     I = int32_t*
 *     X = bool*
 *     B = uint8_t*
 *     W = uint16_t*
 *     D = uint32_t*
 *     Q = uint64_t*
 *     R = real*
 *     L = double*
 *     A = char* (max. 256 bytes for ASCII-encoded string)
 *     U = uint16_t* (max. 512 bytes for UTF16-encoded string)
 *     P = void *data, unsigned int *size (max. *size bytes for BLOB, *size<=512)
 *
 *     <number>lowerCaseTypeLetter defines one-dimensional array of bool/numeric type.
 *
 *     Example: "A>D" describes a function with parameter list "const char *in, uint32_t *out".
 */
BPApiState BPApiOpcUaFctsRegister(
   const char        *fctName,        /**< [in] function name exported to OPC-UA */
   const char        *fctSignature,   /**< [in] function signature, see note */
   BPApiOpcUaFctsType fctPointer      /**< [in] function pointer */
   );

/******************************************************************************/
/**
 * @brief Unregisters a function registered using \em BPApiOpcUaFctsRegister
 *
 * unregisters a previously registered function
 *
 * @retval BPApiStateOk           function unregistered
 * @retval BPApiStateParamError   no registration matching the arguments found
 */
BPApiState BPApiOpcUaFctsUnregister(
   const char        *fctName,        /**< [in] registered function name */
   const char        *fctSignature,   /**< [in] registered function signature */
   BPApiOpcUaFctsType fctPointer      /**< [in] registered function pointer */
   );

#ifdef __cplusplus
}
#endif

#endif /* PACKAGE_API_OPCUA_FCTS_H */
