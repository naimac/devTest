/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief General types in BPApi
*
*   General types in BPApi
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_TYPES_H
#define PACKAGE_API_TYPES_H

#include "stddef.h"    /* for wchar_t */
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/** State information */
typedef uint32_t BPApiState;
enum {
   /* common error codes */
   BPApiStateOk                                  = 0x0,            /**< Command successful */
   BPApiStateStringChopped                       = 0x81800001ul,   /**< String buffer is too short, string cut off. */
   BPApiStateInternalError                       = 0x81000000ul,   /**< Internal error */
   BPApiStateNotOk                               = 0x81000001ul,   /**< Command not successful */
   BPApiStateParamError                          = 0x81000002ul,   /**< Error in actual parameters */
   BPApiStateComNotRunning                       = 0x81000003ul,   /**< Communication-Layer is not available */
   BPApiStateFuncNotFound                        = 0x81000004ul,   /**< Function unavailable via Comm-Layer */
   BPApiStateNotImplementedYet                   = 0x81000005ul,   /**< Function not implemented yet */
   BPApiStateDiskSpaceFull                       = 0x81000006ul,   /**< Disk space is full */
   BPApiStateInitError                           = 0x81000007ul,   /**< Error initializing */
   BPApiStateInvalidHandle                       = 0x81000008ul,   /**< Invalid handle */
   BPApiStateOutOfMemory                         = 0x81000009ul,   /**< Can not create object; out of memory */
   BPApiStateRequestTimeout                      = 0x8100000Aul,   /**< Timeout during function call */
   BPApiStateInvalidMultiByteChar                = 0x8100000Bul,   /**< Unicode <-> ASCII Conversion Error */

   /* additional error codes of BpApiStaRep */
   BPApiStateStaRepAlreadyStarted                = 0x81000100ul,   /**< Statereport already in progress. */
   BPApiStateStaRepInvalidDestPath               = 0x81000101ul,   /**< Invalid destination path for Statereport. */
   BPApiStateStaRepNotInit                       = 0x81000102ul,   /**< Statereport not initialized. */
   BPApiStateStaRepMissing                       = 0x81000103ul,   /**< Statereport is missing. */

   /* additional error codes of BpApiRepSys */
   BPApiStateRepSysFunctionFaild                 = 0x81000201ul,   /**< Function failed. */
   BPApiStateRepSysInvalidWideChar               = 0x81000202ul,   /**< Invalid wide char in string. */
   BPApiStateRepSysInvalidMultiByteChar          = 0x81000203ul,   /**< Invalid multi byte char in string. */
   BPApiStateRepSysInvalidHandle                 = 0x81000204ul,   /**< No message for this handle found. */
   BPApiStateRepSysUnknownParamKind              = 0x81000205ul,   /**< Unknown parameter kind. */
   BPApiStateRepSysBufferTooSmall                = 0x81000206ul,   /**< String buffer for a number is too short. */
   BPApiStateRepSysNotImplemented                = 0x81000207ul,   /**< Function not implemented yet. */
   BPApiStateRepSysIllegalArguments              = 0x81000208ul,   /**< Wrong Arguments. */
   BPApiStateRepSysVarNotFound                   = 0x81000209ul,   /**< variable could not be found. */
   BPApiStateRepSysInvalidVarType                = 0x8100020Aul,   /**< variable data type is not supported. */
   BPApiStateRepSysProtVarAlreadySet             = 0x8100020Bul,   /**< protocol variable has already been set. */
   BPApiStateRepSysProvNotSupported              = 0x8100020Cul,   /**< variable provider does not support this functionality. */
   BPApiStateRepSysInvalidParamType              = 0x8100020EUL,   /**< parameter type of message is invalid */

   /* additional error codes of BPApiDevice */
   BPApiStateDeviceCommandTemporarilyUnavailable = 0x81000401ul,   /**< Command is currently not available. */
   BPApiStateDeviceCommandPermanentlyUnavailable = 0x81000402ul,   /**< Command is unknown/not supported. */

   /* additional error codes of BpApiVar and BpApiVarTxt */
   BPApiStateVarNotFound                         = 0x81000501ul,   /**< Variable not found */
   BPApiStateVarNoChildren                       = 0x81000502ul,   /**< No children available */
   BPApiStateNoMoreNodes                         = 0x81000503ul,   /**< End of nodes reached */
   BPApiStateNoAccess                            = 0x81000504ul,   /**< No read/write rights */
   BPApiStatePropNotFound                        = 0x81000505ul,   /**< Property not found */

   /* additional error codes of BpApiRecipes */
   BPApiStateRecipes_PartsFailed                 = 0x81800601ul,   /**< Read/Write failed for some variables */
   BPApiStateRecipes_NothingToDo                 = 0x81800602ul,   /**< Empty Recipe definition */
   BPApiStateRecipes_Changed                     = 0x81800603ul,   /**< Recipe changed in variable server */
   BPApiStateRecipes_Unchanged                   = 0x81800604ul,   /**< Recipe was not change in variable server*/
   BPApiStateRecipes_StartSucceeded              = 0x81800605ul,   /**< Asynchronous operation in progress */
   BPApiStateRecipes_RecipeNotFound              = 0x81000601ul,   /**< Recipe name cannot be found in variable server */
   BPApiStateRecipes_InvalidPath                 = 0x81000602ul,   /**< Invalid path passed as parameter */
   BPApiStateRecipes_InvalidName                 = 0x81000603ul,   /**< Invalid file name passed as parameter */
   BPApiStateRecipes_RecipeNoAccess              = 0x81000606ul,   /**< Access to specified recipe (currently) not allowed */
   BPApiStateRecipes_CRC_Error                   = 0x81000607ul,   /**< Invalid CRC in recipe file */
   BPApiStateRecipes_DataBase_Error              = 0x81000608ul,   /**< Invalid database file */

   /* additional error codes of BPApiProvider */
   BPApiProviderFileNotFound                     = 0x81000701ul,   /**< File path not found*/
   BPApiProviderInvalidFile                      = 0x81000702ul,   /**< clf file is invalid*/
   BPApiProviderLoadError                        = 0x81000703ul,   /**< Library cannot be loaded*/
   BPApiProviderCRCMismatch                      = 0x81000704ul    /**< clf file is invalid or doesn't match to binary object */
};

#define BPApiIsError(state) (((state)&0xFF000000ul)==0x81000000ul) /**< Check if state is an error state */

/** Timestamp structure */
typedef struct BPApiTime {
   uint32_t sec;                                 /**< seconds */
   uint32_t nsec;                                /**< nanoseconds (0 - 999999999) */
} BPApiTime;


/** Protocol data structure in ASCII */
typedef struct BPApiVarProtocolData {
   const char *userName;                         /**< 'Who' wants to write these values */
   const char *hostName;                         /**< Information about host */
   uint32_t    hostType;                         /**< 1: Unknown; 2: Visu; 3: Control */
} BPApiVarProtocolData;

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_TYPES_H_INCLUDED */
