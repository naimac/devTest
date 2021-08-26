/*------------------------------------------------------------------------------
*                             (c) 2016 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoSercosApi base type definitions
*
*   IoSercosApi standard return code definitions and declaration of types.
*/

#ifndef IOSERCOSTYPESAPI_H_
#define IOSERCOSTYPESAPI_H_

#include <stdint.h>


/******************************************************************************/
/**
 *  @brief Return code definition
 *
 *  Return code definition of Sercos functions.
 *  These return codes extend the IoApiState which is defined in IoApiTypes.h.
 */
enum {
  IoSercosApiStateInvalidIdent      = 0x00000401UL, /**< Invalid IDN */
  IoSercosApiStateReadError         = 0x00000402UL, /**< Reading from drive returns an error. */
  IoSercosApiStateWriteError        = 0x00000403UL, /**< Writing to drive returns an error. */
  IoSercosApiStateSetParamModeError = 0x00000404UL, /**< Change to param mode failed. */
  IoSercosApiStateBufSizeTooSmall   = 0x00000405UL, /**< Buffer is too small. */
  IoSercosApiStateLengthError       = 0x00000406UL, /**< Length-Error (Writing list parameter). */
  IoSercosApiStateChangePhaseError  = 0x00000407UL  /**< Phase change is not possible (stopped). */
};


/******************************************************************************/
/**
 *  Type definition
 */

typedef uint32_t IoSercosElement; /**< Each parameter contains 7 elements (element 1 to element 7). */
enum {
   IoSercosElementIdentNr        = 1, /**< Ident-Number. */
   IoSercosElementName           = 2, /**< Name of operation data. */
   IoSercosElementAttribut       = 3, /**< Attributes of operation data. */
   IoSercosElementUnit           = 4, /**< Operation data unit. */
   IoSercosElementMinInputValue  = 5, /**< Minimum input value of operation data. */
   IoSercosElementMaxInputValue  = 6, /**< Maximum input value of operation data. */
   IoSercosElementValue          = 7  /**< Operation data. */
};

typedef int32_t IoSercosPriority;    /**< Read/Write priority. */
enum {
  IoSercosPriorityHigh    = 0,      /**< The high priority is intended for single parameter access, where a fast response time is required. They should not be used for cyclical parameter access, nor for list parameters, otherwise requests by low-priority clients can (for example, visualization, tools) lead to reduced performance or even total loss of response. */
  IoSercosPriorityLow     = 1       /**< The low priority is provided for accessing list parameters and for cyclic requests. However, requests with this low priority do not interrupt any other requests of the same priority to enable a secure reading of list parameters. */
};


#endif  /* IOSERCOSTYPESAPI_H_ */
