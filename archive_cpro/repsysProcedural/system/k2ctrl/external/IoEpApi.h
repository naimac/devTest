/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief Interface for accessing Io end points
*
*   Interface for reading/writing Io end points
*/

#ifndef IOEPAPI_H_
#define IOEPAPI_H_

#include "IoApiTypes.h"

typedef struct _hIoEpApiHdl *IoEpApiHdl;

/******************************************************************************/
/**
 *  @brief Return code definition
 *
 *  Return code definition for I/O end point access functions
 */
enum {
   IoApiStateIntUnnamedShMem   = 0x00000107UL,  /**< unnamed shared memory (direction check not possible) */
   IoApiStateIntInvTypInfo     = 0x00000108UL,  /**< invalid type information */
   IoApiStateIntInvAxisShMem   = 0x00000109UL,  /**< invalid axis shared memory */
   IoApiStateIntError          = 0x00000110UL,  /**< internal error occured */
   IoApiStateUnsupportedType   = 0x00000111UL   /**< unsupported type */
};


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
*  IO end point access
*/

/******************************************************************************/
/**
 *  @brief Delivers an IO end point handle.
 *
 * Delivers an IO end point handle named by the name of the IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidName, if no end point with given name can be found.
 *         IoApiStateIntUnnamedShMem, if end point is within an unnamed shared memory.
 *         IoApiStateIntInvTypInfo, if type information is not readable.
 *         IoApiStateUnsupportedType, if end point type is not supported.
 *         IoApiStateIntError, if internal error occurred.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if the end point could be delivered.
 */
IoApiState IoApiGetIoEpHdl(
   const char *ioEpName,              /**< [in]  The name of the IO end point. */
   IoEpApiHdl *ioEpHdl                /**< [out] Returns the IO end point handle. */
   );


/******************************************************************************/
/**
 *  @brief Delivers type and direction of an IO end point
 *
 * Delivers type and direction of an IO end point identified by epHdl.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateOk, if the end point type could be delivered.
 */
IoApiState IoApiGetIoEpType(
   IoEpApiHdl  epHdl,                     /**< [in]  End point handle. */
   IoApiVarType *epType,                  /**< [out] End point type. */
   IoApiDirection *epDir                  /**< [out] End point data direction. */
   );

/*-----------------------------------------------------------------------------
*  Digital IO end point
*/

/******************************************************************************/
/**
 *  @brief Reading from a digital IO end point.
 *
 *  Reading from a digital IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadDIo(
   IoEpApiHdl  ioEpHdl,             /**< [in]  IO end point handle. */
   uint8_t    *pValue               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a digital IO
 *
 *  Writing a digital IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteDIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint8_t    value                       /**< [in]  Data value. */
   );

/*-----------------------------------------------------------------------------
*  Analog IO end point
*/

/******************************************************************************/
/**
 *  @brief Reading from an analog IO end point.
 *
 *  Reading from an analog IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float      *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing an analog IO end point.
 *
 *  Writing an analog IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   float      value                       /**< [in]  Data value. */
   );

/*-----------------------------------------------------------------------------
*  Axis IO end point
*/

/******************************************************************************/
/**
 *  @brief Reading the state word
 *
 *  Reading the state word from an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoState(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t   *pValue                     /**< [out] State word. */
   );

/******************************************************************************/
/**
 *  @brief Writing the state word
 *
 *  Writing the state word to an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoState(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint32_t   value                       /**< [in]  State word. */
   );

/******************************************************************************/
/**
 *  @brief Reading the control word
 *
 *  Reading the control word from an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoControl(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t   *pValue                     /**< [out] Control word. */
   );

/******************************************************************************/
/**
 *  @brief Writing the control word
 *
 *  Writing the control word to an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoControl(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint32_t   value                       /**< [in]  Control word. */
   );

/******************************************************************************/
/**
 *  @brief Reading the actual position value
 *
 *  Reading the actual position value from an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoActPos(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t   *pValue                     /**< [out] Position data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the actual position value
 *
 *  Writing the actual position value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoActPos(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint32_t   value                       /**< [in]  Position data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the actual velocity value
 *
 *  Reading the actual velocity value from an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoActVeloc(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float      *pValue                     /**< [out] Velocity data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the actual velocity value
 *
 *  Writing the actual velocity value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoActVeloc(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   float      value                       /**< [in]  Velocity data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the actual torque value
 *
 *  Reading the actual torque value from an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoActTorque(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float      *pValue                     /**< [out] Torque data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the actual torque value
 *
 *  Writing the actual torque value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoActTorque(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float       value                      /**< [in]  Torque data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the actual auxiliary value
 *
 *  Reading the actual auxiliary value from an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoActAux(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   int         auxIdx,                    /**< [in]  Index of auxiliary (0 - 4). */
   uint32_t   *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the actual auxiliary value
 *
 *  Writing the actual auxiliary value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoActAux(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   int        auxIdx,                     /**< [in]  Index of auxiliary (0 - 4) */
   uint32_t   value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the position set value
 *
 *  Reading the position set value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoSetPos(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t   *pValue                     /**< [out] Position data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the set value for a position
 *
 *  Writing the set value for a position to an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoSetPos(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint32_t   value                       /**< [in]  Position data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the velocity set value
 *
 *  Reading the velocity set value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoSetVeloc(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float      *pValue                     /**< [out] Velocity data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the set value for a velocity
 *
 *  Writing the set value for a velocity to an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoSetVeloc(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   float      value                       /**< [in]  Velocity data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the torque set value
 *
 *  Reading the torque set value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoSetTorque(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float      *pValue                     /**< [out] Torque data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the set value for a torque
 *
 *  Writing the set value for a torque to an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoSetTorque(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   float      value                       /**< [in]  Torque data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading the auxiliary set value
 *
 *  Reading the auxiliary set value of an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisIoSetAux(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   int         auxIdx,                    /**< [in]  Index of auxiliary (0 - 4) */
   uint32_t   *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing the set value for auxiliary
 *
 *  Writing the set value for auxiliary to an axis IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisIoSetAux(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   int        auxIdx,                     /**< [in]  Index of auxiliary (0 - 4). */
   uint32_t   value                       /**< [in]  Data value. */
   );

/*-----------------------------------------------------------------------------
*  Type related IO end point
*/

/******************************************************************************/
/**
 *  @brief Reading a SINT value
 *
 *  Reading a SINT value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadSINTIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   int8_t     *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a SINT value
 *
 *  Writing a SINT value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteSINTIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   int8_t     value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a INT value
 *
 *  Reading a INT value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadINTIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   int16_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a INT value
 *
 *  Writing a INT value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteINTIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   int16_t    value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a DINT value
 *
 *  Reading a DINT value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadDINTIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   int32_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a DINT value
 *
 *  Writing a DINT value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteDINTIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   int32_t    value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a USINT value
 *
 *  Reading a USINT value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUSINTIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint8_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a USINT value
 *
 *  Writing a USINT value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUSINTIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint8_t    value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a UINT value
 *
 *  Reading a UINT value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUINTIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint16_t   *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a UINT value
 *
 *  Writing a UINT value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUINTIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint16_t   value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a UDINT value
 *
 *  Reading a UDINT value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUDINTIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t   *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a UDINT value
 *
 *  Writing a UDINT value to an IO end point
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUDINTIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint32_t   value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a BOOL value
 *
 *  Reading a BOOL value from an IO end point
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadBOOLIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint8_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a BOOL value
 *
 *  Writing a BOOL value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteBOOLIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   uint8_t    value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a REAL value
 *
 *  Reading a REAL value from an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadREALIo(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   float      *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing a REAL value
 *
 *  Writing a REAL value to an IO end point.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteREALIo(
   IoEpApiHdl ioEpHdl,                    /**< [in]  IO end point handle. */
   float      value                       /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading array size.
 *
 *  Reading the configured array size of an array end point.
 *
 * @return State information about the operation.
 *         IoApiStateOk, if the operation has been finished successful.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotOk, if an error occurred.
 */
IoApiState IoApiGetArraySize(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t   *pArraySize                 /**< [out] Configured array size of end point. */
   );

/*-----------------------------------------------------------------------------
*  Type related array IO end point
*/

/******************************************************************************/
/**
 *  @brief Reading from a digital array IO end point.
 *
 *  Reading all array elements of a digital array IO end point.
 *  The pValueBuffer must be big enough to fit the configured array size of the
 *  end point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadDIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   uint8_t    *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a digital array IO end point.
 *
 *  Reading a single element from a digital array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadDIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   uint8_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a digital array end point.
 *
 *  Writing all array elements of a digital array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteDIoArray(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arraySize,              /**< [in]  Size of array. */
   const uint8_t *pValueBuffer            /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a digital array end point.
 *
 *  Writing a single element to a digital array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteDIoIdx(
   IoEpApiHdl    ioEpHdl,                 /**< [in]  IO end point handle. */
   uint32_t      arrayIdx,                /**< [in]  Index of array to which should be written. */
   const uint8_t value                    /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from an analog array IO end point.
 *
 *  Reading all array elements of an array cycle IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   float      *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of an analog array IO end point.
 *
 *  Reading a single element from an analog array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   float      *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to an analog array IO end point.
 *
 *  Writing all array elements of an analog array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAIoArray(
   IoEpApiHdl   ioEpHdl,                  /**< [in]  IO end point handle. */
   uint32_t     arraySize,                /**< [in]  Size of array. */
   const float *pValueBuffer              /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of an analog array IO end point.
 *
 *  Writing a single element to an analog array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array to which should be written. */
   const float value                      /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a SINT array IO end point.
 *
 *  Reading all array elements of a SINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadSINTIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   int8_t     *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a SINT array IO end point.
 *
 *  Reading a single element from a SINT array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadSINTIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   int8_t     *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a SINT array end point.
 *
 *  Writing all array elements of a SINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteSINTIoArray(
   IoEpApiHdl    ioEpHdl,                 /**< [in]  IO end point handle. */
   uint32_t      arraySize,               /**< [in]  Size of array. */
   const int8_t *pValueBuffer             /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a SINT array end point.
 *
 *  Writing a single element to a SINT array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteSINTIoIdx(
   IoEpApiHdl   ioEpHdl,                  /**< [in]  IO end point handle. */
   uint32_t     arrayIdx,                 /**< [in]  Index of array to which should be written. */
   const int8_t value                     /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from an INT array IO end point.
 *
 *  Reading all array elements of an INT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadINTIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   int16_t    *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of an INT array IO end point.
 *
 *  Reading a single element from an INT array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadINTIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   int16_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to an INT array end point.
 *
 *  Writing all array elements of an INT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteINTIoArray(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arraySize,              /**< [in]  Size of array. */
   const int16_t *pValueBuffer            /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of an INT array end point.
 *
 *  Writing a single element to an INT array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteINTIoIdx(
   IoEpApiHdl    ioEpHdl,                 /**< [in]  IO end point handle. */
   uint32_t      arrayIdx,                /**< [in]  Index of array to which should be written. */
   const int16_t value                    /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a DINT array IO end point.
 *
 *  Reading all array elements of a DINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadDINTIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   int32_t    *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a DINT array IO end point.
 *
 *  Reading a single element from a DINT array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadDINTIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   int32_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a DINT array end point.
 *
 *  Writing all array elements of a DINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteDINTIoArray(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arraySize,              /**< [in]  Size of array. */
   const int32_t *pValueBuffer            /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a DINT array end point.
 *
 *  Writing a single element to a DINT array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteDINTIoIdx(
   IoEpApiHdl    ioEpHdl,                 /**< [in]  IO end point handle. */
   uint32_t      arrayIdx,                /**< [in]  Index of array to which should be written. */
   const int32_t value                    /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a USINT array IO end point.
 *
 *  Reading all array elements of a USINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUSINTIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   uint8_t    *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a USINT array IO end point.
 *
 *  Reading a single element from a USINT array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUSINTIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   uint8_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a USINT array end point.
 *
 *  Writing all array elements of a USINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUSINTIoArray(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arraySize,              /**< [in]  Size of array. */
   const uint8_t *pValueBuffer            /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a USINT array end point.
 *
 *  Writing a single element to a USINT array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUSINTIoIdx(
   IoEpApiHdl    ioEpHdl,                 /**< [in]  IO end point handle. */
   uint32_t      arrayIdx,                /**< [in]  Index of array to which should be written. */
   const uint8_t value                    /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a UINT array IO end point.
 *
 *  Reading all array elements of a UINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUINTIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   uint16_t   *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a UINT array IO end point.
 *
 *  Reading a single element from a UINT array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUINTIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   uint16_t   *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a UINT array end point.
 *
 *  Writing all array elements of a UINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUINTIoArray(
   IoEpApiHdl      ioEpHdl,               /**< [in]  IO end point handle. */
   uint32_t        arraySize,             /**< [in]  Size of array. */
   const uint16_t *pValueBuffer           /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a UINT array end point.
 *
 *  Writing a single element to a UINT array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUINTIoIdx(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arrayIdx,               /**< [in]  Index of array to which should be written. */
   const uint16_t value                   /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a UDINT array IO end point.
 *
 *  Reading all array elements of a UDINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUDINTIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   uint32_t   *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a UDINT array IO end point.
 *
 *  Reading a single element from a UDINT array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadUDINTIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   uint32_t   *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a UDINT array end point.
 *
 *  Writing all array elements of a UDINT array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUDINTIoArray(
   IoEpApiHdl      ioEpHdl,               /**< [in]  IO end point handle. */
   uint32_t        arraySize,             /**< [in]  Size of array. */
   const uint32_t *pValueBuffer           /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a UDINT array end point.
 *
 *  Writing a single element to a UDINT array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteUDINTIoIdx(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arrayIdx,               /**< [in]  Index of array to which should be written. */
   const uint32_t value                   /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a BOOL array IO end point.
 *
 *  Reading all array elements of a BOOL array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadBOOLIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   uint8_t    *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a BOOL array IO end point.
 *
 *  Reading a single element from a BOOL array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadBOOLIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   uint8_t    *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a BOOL array end point.
 *
 *  Writing all array elements of a BOOL array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteBOOLIoArray(
   IoEpApiHdl     ioEpHdl,                /**< [in]  IO end point handle. */
   uint32_t       arraySize,              /**< [in]  Size of array. */
   const uint8_t *pValueBuffer            /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a BOOL array end point.
 *
 *  Writing a single element to a BOOL array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteBOOLIoIdx(
   IoEpApiHdl    ioEpHdl,                 /**< [in]  IO end point handle. */
   uint32_t      arrayIdx,                /**< [in]  Index of array to which should be written. */
   const uint8_t value                    /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a REAL array IO end point.
 *
 *  Reading all array elements of a REAL array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadREALIoArray(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arraySize,                 /**< [in]  Size of array. */
   float      *pValueBuffer               /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading a single element of a REAL array IO end point.
 *
 *  Reading a single element from a REAL array IO end point. The
 *  element within the array is specified by arrayIdx and must be smaller than
 *  or equal the configured size - 1 that can be read by
 *  IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadREALIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array from which should be read. */
   float      *pValue                     /**< [out] Data value. */
   );

/******************************************************************************/
/**
 *  @brief Writing to a REAL array array end point.
 *
 *  Writing all array elements of a REAL array IO end point. The
 *  pValueBuffer must be big enough to fit the configured array size of the end
 *  point.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteREALIoArray(
   IoEpApiHdl   ioEpHdl,                  /**< [in]  IO end point handle. */
   uint32_t     arraySize,                /**< [in]  Size of array. */
   const float *pValueBuffer              /**< [in]  Data value. */
   );

/******************************************************************************/
/**
 *  @brief Reading from a single element of a REAL array end point.
 *
 *  Writing a single element to a REAL array IO end point. The element
 *  within the array is specified by arrayIdx and must be smaller than or equal
 *  the configured size - 1 that can be read by IoApiGetArraySize.
 *
 * @return State information about the operation.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateInvalidType, if end point type is not valid (see IoApiVarType).
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidParam, if array size does not match.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteREALIoIdx(
   IoEpApiHdl  ioEpHdl,                   /**< [in]  IO end point handle. */
   uint32_t    arrayIdx,                  /**< [in]  Index of array to which should be written. */
   const float value                      /**< [in]  Data value. */
   );

typedef struct {
   float pos;                             /**< Position information of an axis */
   float veloc;                           /**< Velocity information of an axis */
   float torque;                          /**< Torque information of an axis */
   float aux[5];                          /**< Auxiliary information of an axis */
   float dPosZero;                        /**< Distance to zero information of an axis */
} IoEpApiAxisValues;

/******************************************************************************/
/**
 *  @brief Burst read of axis actual values.
 *
 *  Reads structure of all axis actual values.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisActValues(
   IoEpApiHdl         ioEpHdl,            /**< [in]  IO end point handle. */
   IoEpApiAxisValues *actVals             /**< [out] Structure of actual values. */
   );

/******************************************************************************/
/**
 *  @brief Burst read of axis set values.
 *
 *  Reads structure of all axis set values.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiReadAxisSetValues(
   IoEpApiHdl         ioEpHdl,            /**< [in]  IO end point handle. */
   IoEpApiAxisValues *setVals             /**< [out] Structure of set values. */
   );

/******************************************************************************/
/**
 *  @brief Burst write of axis actual values.
 *
 *  Writes structure of all axis actual values.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisActValues(
   IoEpApiHdl        ioEpHdl,             /**< [in]  IO end point handle. */
   IoEpApiAxisValues actVals              /**< [in]  Structure of actual values. */
   );

/******************************************************************************/
/**
 *  @brief Burst write of axis set values.
 *
 *  Writes structure of all axis set values.
 *
 * @return State information about the call.
 *         IoApiStateInvalidHandle, if epHdl points to no end point.
 *         IoApiStateInvalidAddr, if an invalid output address has been given.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateOk, if end point access was successful.
 */
IoApiState IoApiWriteAxisSetValues(
   IoEpApiHdl        ioEpHdl,             /**< [in]  IO end point handle. */
   IoEpApiAxisValues setVals              /**< [in]  Structure of set values. */
   );


/******************************************************************************/
/**
 *  @brief Requests the actual state of an IO end point
 *
 * Requests the actual state of an IO end point identified by epHdl.
 *
 * @return State information about the call.
 *         IoApiStateOk, if state check was successful.
 *         IoApiStateNotOk, if an error occurred.
 *         IoApiStateNotReady, if end point is not ready for access.
 *         IoApiStateInvalidHandle, if the handle is not valid.
 */
IoApiState IoApiGetIoEpState(
   IoEpApiHdl   epHdl,           /**< [in]  End point handle. */
   IoApiState  *epState          /**< [out] State of the requested end point. */
   );

#ifdef __cplusplus
}
#endif

#endif /* IOAPI_H_ */
