/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/

/** @file
*   @brief IoApi base type definitions
*
*   IoApi standard return code definitions and declaration of the IoApiHandle
*/

#ifndef IOAPI_H_
#define IOAPI_H_

#include <stdint.h>
#include "IoSercosApiTypes.h"

typedef uint32_t IoApiState;  /**< State information */
enum {
   IoApiStateOk               = 0x0,               /**< Command successful */
   IoApiStateNotOk            = 0x00000001UL,      /**< Command not successful */

   IoApiStateInvalidHandle    = 0x00000002UL,      /**< illegal I/O handle */
   IoApiStateInvalidAddr      = 0x00000003UL,      /**< illegal data address */
   IoApiStateNotReady         = 0x00000004UL,      /**< I/O end point not ready */

   IoApiStateInvalidName      = 0x00000005UL,      /**< illegal param name */
   IoApiStateInvalidType      = 0x00000006UL,      /**< illegal usage (read/write) */

   IoApiStatePending          = 0x00000007UL,      /**< operation in progress */
   IoApiStateTimeout          = 0x00000008UL,      /**< operation timed out */

   IoApiStateQueueOverrun     = 0x00000009UL,      /**< Queue overrun occurred */

   IoApiStateInvalidParam     = 0x0000000AUL,      /**< Parameter is invalid */
   IoApiStateNotSupported     = 0x0000000BUL,      /**< Requested function is not supported */

   IoApiStateInvOverlapped    = 0x0000000CUL,      /**< the used overlapped struct is not initialized
                                                         or is already in use for another call */
   IoApiStateNoData           = 0x0000000DUL,      /**< no data available */
   IoApiStateWrongDataTypeReq = 0x0000000EUL,      /**< Wrong data type requested */
   IoApiStateOutOfRange       = 0x0000000FUL,      /**< Invalid value to write */

   IoApiStateWrongCallOrder   = 0x00000020UL,      /**< Invalid order of function calls */
   IoApiStateInvalidAttr      = 0x00000021UL,      /**< Attribute not valid */
   IoApiStateInvalidBufSize   = 0x00000022UL       /**< Invalid buffer size. */
};

typedef uint32_t IoApiDirection;
enum {
   IoApiDirectionInput        = 1,     /**< I/O Input Direction */
   IoApiDirectionOutput       = 2      /**< I/O Output Direction */
};

typedef uint32_t IoApiVarType;
enum {
   IoApiVarTypeINVALID        =  0,    /**< No data type available / invalid type */

   IoApiVarTypeBOOL           =  1,   /**< Boolean stored in a single byte (0=false, 1=true) */

   IoApiVarTypeSINT           =  2,   /**< 8 bit signed integer */
   IoApiVarTypeINT            =  3,   /**< 16 bit signed integer */
   IoApiVarTypeDINT           =  4,   /**< 32 bit signed integer */
   IoApiVarTypeLINT           =  5,   /**< 64 bit signed integer */
   IoApiVarTypeUSINT          =  6,   /**< 8 bit unsigned integer */
   IoApiVarTypeUINT           =  7,   /**< 16 bit unsigned integer */
   IoApiVarTypeUDINT          =  8,   /**< 32 bit unsigned integer */
   IoApiVarTypeULINT          =  9,   /**< 64 bit unsigned integer */

   IoApiVarTypeSINT8          =  2,   /**< 8 bit signed integer */
   IoApiVarTypeSINT16         =  3,   /**< 16 bit signed integer */
   IoApiVarTypeSINT32         =  4,   /**< 32 bit signed integer */
   IoApiVarTypeSINT64         =  5,   /**< 64 bit signed integer */
   IoApiVarTypeUINT8          =  6,   /**< 8 bit unsigned integer */
   IoApiVarTypeUINT16         =  7,   /**< 16 bit unsigned integer */
   IoApiVarTypeUINT32         =  8,   /**< 32 bit unsigned integer */
   IoApiVarTypeUINT64         =  9,   /**< 64 bit unsigned integer */

   IoApiVarTypeREAL           = 10,   /**< single precision floating point number */
   IoApiVarTypeLREAL          = 11,   /**< double precision floating point number */

   IoApiVarTypeFLOAT          = 10,   /**< single precision floating point number */
   IoApiVarTypeDOUBLE         = 11,   /**< double precision floating point number */

   IoApiVarTypeBYTE           = 12,   /**< 8 bit bit field (IEC61131-3 only) */
   IoApiVarTypeWORD           = 13,   /**< 16 bit bit field (IEC61131-3 only) */
   IoApiVarTypeDWORD          = 14,   /**< 32 bit bit field (IEC61131-3 only) */
   IoApiVarTypeLWORD          = 15,   /**< 64 bit bit field (IEC61131-3 only) */

   IoApiVarTypeSTRING         = 22,   /**< ASCII string */

   IoApiVarTypeSINTArray      = 102,  /**< 8 bit signed integer array */
   IoApiVarTypeINTArray       = 103,  /**< 16 bit signed integer array */
   IoApiVarTypeDINTArray      = 104,  /**< 32 bit signed integer array */
   IoApiVarTypeLINTArray      = 105,  /**< 64 bit signed integer array */
   IoApiVarTypeUSINTArray     = 106,  /**< 8 bit unsigned integer array */
   IoApiVarTypeUINTArray      = 107,  /**< 16 bit unsigned integer array */
   IoApiVarTypeUDINTArray     = 108,  /**< 32 bit unsigned integer array */
   IoApiVarTypeULINTArray     = 109,  /**< 64 bit unsigned integer array */

   IoApiVarTypeSINT8Array     = 102,  /**< 8 bit signed integer array */
   IoApiVarTypeSINT16Array    = 103,  /**< 16 bit signed integer array */
   IoApiVarTypeSINT32Array    = 104,  /**< 32 bit signed integer array */
   IoApiVarTypeSINT64Array    = 105,  /**< 64 bit signed integer array */
   IoApiVarTypeUINT8Array     = 106,  /**< 8 bit unsigned integer array */
   IoApiVarTypeUINT16Array    = 107,  /**< 16 bit unsigned integer array */
   IoApiVarTypeUINT32Array    = 108,  /**< 32 bit unsigned integer array */
   IoApiVarTypeUINT64Array    = 109,  /**< 64 bit unsigned integer array */

   IoApiVarTypeREALArray      = 110,  /**< single precision floating point number array */
   IoApiVarTypeLREALArray     = 111,  /**< double precision floating point number array */

   IoApiVarTypeFLOATArray     = 110,  /**< single precision floating point number array */
   IoApiVarTypeDOUBLEArray    = 111,  /**< double precision floating point number array */

   IoApiVarTypeBYTEArray      = 112,  /**< 8 bit bit field (IEC61131-3 only) array */
   IoApiVarTypeWORDArray      = 113,  /**< 16 bit bit field (IEC61131-3 only) array */
   IoApiVarTypeDWORDArray     = 114,  /**< 32 bit bit field (IEC61131-3 only) array */
   IoApiVarTypeLWORDArray     = 115   /**< 64 bit bit field (IEC61131-3 only) array */
};

typedef struct _hIoApiHdl *IoApiHdl;  /**< IoApi handle */

/** Timestamp structure */
typedef struct IoApiTime {
   uint32_t sec;     /**< seconds (since 1.1.1970) */
   uint32_t nsec;    /**< nanoseconds (0 - 999999999) */
} IoApiTime;

#endif
