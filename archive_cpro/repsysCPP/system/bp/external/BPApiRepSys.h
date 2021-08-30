/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Interface for Reportsystem
*
*   Interface for Reportsystem
*
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_REPSYS_H
#define PACKAGE_API_REPSYS_H

#include <stdarg.h>
#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/** A handle for a reportsystem message. */
typedef uint32_t BPApiRepSysMsgHdl;

/** A type indicating the msg class. */
typedef uint32_t BPApiRepSysMsgClass;
enum {
   BPApiRepSysMsgClassErrorFatal        = 0x00000001ul,           /**< Class 1, fatal error */
   BPApiRepSysMsgClassError             = 0x00000002ul,           /**< Class 2, error */
   BPApiRepSysMsgClassErrorMinor        = 0x00000004ul,           /**< Class 3, error minor */
   BPApiRepSysMsgClassWarning           = 0x00000008ul,           /**< Class 4, warning */
   BPApiRepSysMsgClassInfo              = 0x00000010ul,           /**< Class 5, info */
   BPApiRepSysMsgClassErrorApp          = 0x00000020ul,           /**< Class 6, application error */
   BPApiRepSysMsgClass7                 = 0x00000040ul,           /**< Class 7 */
   BPApiRepSysMsgClass8                 = 0x00000080ul,           /**< Class 8 */
   BPApiRepSysMsgClass9                 = 0x00000100ul,           /**< Class 9 */
   BPApiRepSysMsgClass10                = 0x00000200ul,           /**< Class 10 */
   BPApiRepSysMsgClass11                = 0x00000400ul,           /**< Class 11 */
   BPApiRepSysMsgClass12                = 0x00000800ul,           /**< Class 12 */
   BPApiRepSysMsgClass13                = 0x00001000ul,           /**< Class 13 */
   BPApiRepSysMsgClass14                = 0x00002000ul,           /**< Class 14 */
   BPApiRepSysMsgClass15                = 0x00004000ul,           /**< Class 15 */
   BPApiRepSysMsgClass16                = 0x00008000ul,           /**< Class 16 */
   BPApiRepSysMsgClass17                = 0x00010000ul,           /**< Class 17 */
   BPApiRepSysMsgClass18                = 0x00020000ul,           /**< Class 18 */
   BPApiRepSysMsgClass19                = 0x00040000ul,           /**< Class 19 */
   BPApiRepSysMsgClass20                = 0x00080000ul,           /**< Class 20 */
   BPApiRepSysMsgClass21                = 0x00100000ul,           /**< Class 21 */
   BPApiRepSysMsgClass22                = 0x00200000ul,           /**< Class 22 */
   BPApiRepSysMsgClass23                = 0x00400000ul,           /**< Class 23 */
   BPApiRepSysMsgClass24                = 0x00800000ul,           /**< Class 24 */
   BPApiRepSysMsgClass25                = 0x01000000ul,           /**< Class 25 */
   BPApiRepSysMsgClass26                = 0x02000000ul,           /**< Class 26 */
   BPApiRepSysMsgClass27                = 0x04000000ul,           /**< Class 27 */
   BPApiRepSysMsgClass28                = 0x08000000ul,           /**< Class 28 */
   BPApiRepSysMsgClass29                = 0x10000000ul,           /**< Class 29 */
   BPApiRepSysMsgClass30                = 0x20000000ul,           /**< Class 30 */
   BPApiRepSysMsgClass31                = 0x40000000ul,           /**< Class 31 */
   BPApiRepSysMsgClass32                = 0x80000000ul,           /**< Class 32 */
   BPApiRepSysMsgClassAll               = 0xFFFFFFFFul            /**< All classes */
};

/** The message state. */
typedef uint32_t BPApiRepSysMsgState;
enum {
   BPApiRepSysMsgStateUndefined         = 0,                      /**< Undefined message state. */
   BPApiRepSysMsgStateInactiveMsg       = 1,                      /**< Inactive msg, history msg state. */
   BPApiRepSysMsgStateResetMsg          = 2,                      /**< Reset msg, history msg state. */
   BPApiRepSysMsgStateQuitMsg           = 3,                      /**< Quit msg, history msg state. */
   BPApiRepSysMsgStateToReset           = 4,                      /**< Msg to reset, active alarm msg state. */
   BPApiRepSysMsgStateToQuit            = 5,                      /**< Msg to quit, active alarm msg state. */
   BPApiRepSysMsgStateToResetAndQuit    = 6,                      /**< Msg to reset and quit, active alarm msg state. */
   BPApiRepSysMsgStateToResetOrQuit     = 7                       /**< Msg to reset, active alarm msg state. */
};

/** The message parameter type. */
typedef uint32_t BPApiRepSysMsgParamType;
enum {
   BPApiRepSysMsgParamType_Int          = 0,
   BPApiRepSysMsgParamType_Float        = 1,
   BPApiRepSysMsgParamType_String       = 2,
   BPApiRepSysMsgParamType_Memory       = 3,
   BPApiRepSysMsgParamType_WString      = 4,
   BPApiRepSysMsgParamType_UINT32       = 5,
   BPApiRepSysMsgParamType_Real         = 6,
   BPApiRepSysMsgParamType_UINT64       = 7
};

/******************************************************************************/
/**
 * @brief Set message (ASCII)
 *
 * Set a message in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysSetMsgA (
   BPApiRepSysMsgClass classId,                      /**< [in] The class id. */
   uint32_t compNr,                                  /**< [in] The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in] The instance number. */
   uint32_t msgNr,                                   /**< [in] The message number. */
   const char *format,                               /**< [in] The formated msg string. */
   ...                                               /**< [in] The open argument list. */
   );

/******************************************************************************/
/**
 * @brief Set message (Unicode)
 *
 * Set a message in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysSetMsgW (
   BPApiRepSysMsgClass classId,                      /**< [in] The class id. */
   uint32_t compNr,                                  /**< [in] The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in] The instance number. */
   uint32_t msgNr,                                   /**< [in] The message number. */
   const wchar_t *format,                            /**< [in] The formated msg string */
   ...                                               /**< [in] The open argument list. */
   );

/******************************************************************************/
/**
 * @brief Set message (ASCII) with argument list
 *
 * Set a message in ASCII. Use argument list.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysSetMsgListA (
   BPApiRepSysMsgClass classId,                      /**< [in] The class id. */
   uint32_t compNr,                                  /**< [in] The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in] The instance number. */
   uint32_t msgNr,                                   /**< [in] The message number. */
   const char *format,                               /**< [in] The formated msg string */
   va_list list                                      /**< [in] The open argument list. */
   );

/******************************************************************************/
/**
 * @brief Set message (Unicode) with argument list.
 *
 * Set a message in Unicode. Use argument list.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysSetMsgListW (
   BPApiRepSysMsgClass classId,                      /**< [in] The class id. */
   uint32_t compNr,                                  /**< [in] The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in] The instance number. */
   uint32_t msgNr,                                   /**< [in] The message number. */
   const wchar_t *format,                            /**< [in] The formated msg string */
   va_list list                                      /**< [in] The open argument list. */
   );

/******************************************************************************/
/**
 * @brief Reset message
 *
 * Reset a dedicated message.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysResetMsg (
   BPApiRepSysMsgClass classId,                      /**< [in] The class id. */
   uint32_t compNr,                                  /**< [in] The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in] The instance number. */
   uint32_t msgNr                                    /**< [in] The message number. */
   );

/******************************************************************************/
/**
 * @brief Quit message
 *
 * Quit a dedicated message.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysQuitMsg (
   BPApiRepSysMsgClass classId,                      /**< [in] The class id. */
   uint32_t compNr,                                  /**< [in] The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in] The instance number. */
   uint32_t msgNr                                    /**< [in] The message number. */
   );

/******************************************************************************/
/**
 * @brief Return language (ASCII)
 *
 * Returns the current language of the messages in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetLanguageA (
   char *name,                                       /**< [out] Returns the current language. */
   uint32_t bufLen                                   /**< [in]  The length of the name buffer. */
   );

/******************************************************************************/
/**
 * @brief Return language (Unicode)
 *
 * Returns the current language of the messages in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetLanguageW (
   wchar_t *name,                                    /**< [out] Returns the current language. */
   uint32_t bufLen                                   /**< [in]  The length of the name buffer. */
   );

/******************************************************************************/
/**
 * @brief Set language (ASCII)
 *
 * Set the language of messages in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysSetLanguageA (
   char *name                                        /**< [in] The language, which should be set. */
   );

/******************************************************************************/
/**
 * @brief Set language (Unicode)
 *
 * Set the language  of messages in unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysSetLanguageW (
   wchar_t *name                                     /**< [in] The language, which should be set. */
   );

/******************************************************************************/
/**
 * @brief Return message handle
 *
 * Returns the handle to a specified message.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetMsg (
   BPApiRepSysMsgClass classId,                      /**< [in]  The class id. */
   uint32_t compNr,                                  /**< [in]  The component number of the msgs origin. */
   uint32_t instNr,                                  /**< [in]  The instance number. */
   uint32_t msgNr,                                   /**< [in]  The message number. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of first alarm message
 *
 * Returns the handle to the first alarm message
 *  of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetFirstMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of next alarm message
 *
 * Returns the handle to the next alarm message
 *  of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetNextMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [in/out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of previous alarm message
 *
 * Returns the handle to the previous alarm message
 *  of the specified message class  mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetPrevMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [in/out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of last alarm message
 *
 * Returns the handle to the last alarm message
 *  of the specified message class  mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetLastMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return alarm message count
 *
 * Returns the alarm message count of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetMsgCount (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   uint32_t *count                                   /**< [out] Returns the message count. */
   );

/******************************************************************************/
/**
 * @brief Return handle of first history message
 *
 * Returns the handle to the first history message
 *  of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetFirstHistoryMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of next history message
 *
 * Returns the handle to the next history message
 *  of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetNextHistoryMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [in/out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of previous history message
 *
 * Returns the handle to the previous history message
 *  of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetPrevHistoryMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [in/out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return handle of last history message
 *
 * Returns the handle to the last history message
 *  of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetLastHistoryMsg (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   BPApiRepSysMsgHdl *msgHdl                         /**< [out] Returns the message handle. */
   );

/******************************************************************************/
/**
 * @brief Return history message count
 *
 * Returns the history message count of the specified message class mask.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetHistoryMsgCount (
   uint32_t classMask,                               /**< [in]  The message class mask. */
   uint32_t *count                                   /**< [out] Returns the message count. */
   );

/******************************************************************************/
/**
 * @brief Return information about handle
 *
 * Returns a handle's msg numbers, time and number of paramters.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetMsgDataValues (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   BPApiRepSysMsgClass *classId,                     /**< [out] Returns the class id. */
   uint32_t *compNr,                                 /**< [out] Returns the component number of the msgs origin. */
   uint32_t *instNr,                                 /**< [out] Returns the instance number. */
   uint32_t *msgNr,                                  /**< [out] Returns the message number. */
   BPApiTime *timeStamp,                             /**< [out] Returns the timestamp. */
   uint32_t *paramCount,                             /**< [out] Returns the parameter count. */
   BPApiRepSysMsgState *msgState                     /**< [out] Returns the message state. */
   );

/******************************************************************************/
/**
* @brief Return information about handle
*
* Returns a handle's msg numbers, time and number of paramters.
*
* @return Information about the call's state.
*/
BPApiState BPApiRepSysGetMsgDataValues2(
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   BPApiRepSysMsgClass *classId,                     /**< [out] Returns the class id. */
   uint32_t *compNr,                                 /**< [out] Returns the component number of the msgs origin. */
   uint32_t *instNr,                                 /**< [out] Returns the instance number. */
   uint32_t *msgNr,                                  /**< [out] Returns the message number. */
   BPApiTime *timeStamp,                             /**< [out] Returns the timestamp. */
   uint32_t *paramCount,                             /**< [out] Returns the parameter count. */
   BPApiRepSysMsgState *msgState,                    /**< [out] Returns the message state. */
   uint32_t *protocolVar                             /**< [out] Returns the protocol variable value */
);

/******************************************************************************/
/**
 * @brief Return parameter type of the message
 *
 * Returns the type of a parameter of the message.
 *
 * @return Result information about the call.\n
 *         BPApiStateRepSysInvalidHandle     if msgHdl is invalid\n
 *         BPApiStateRepSysIllegalArguments  if paramNr is out of range\n
 *         BPApiStateOk                      on success. paramType has been set.
 */
BPApiState BPApiRepSysGetMsgParamType (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   uint32_t paramNr,                                 /**< [in]  The parameter number. */
   BPApiRepSysMsgParamType *paramType                /**< [out] Returns the parameter type. */
   );

/******************************************************************************/
/**
 * @brief Return parameter of the message (ASCII)
 *
 * Returns a parameter of the message in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetMsgParamValueA (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   uint32_t paramNr,                                 /**< [in]  The parameter number. */
   char *buffer,                                     /**< [out] Returns the parameter. */
   uint32_t bufLen                                   /**< [in]  The length of the buffer. */
   );

/******************************************************************************/
/**
 * @brief Return parameter of the message (Unicode)
 *
 * Returns a parameter of the message in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysGetMsgParamValueW (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   uint32_t paramNr,                                 /**< [in]  The parameter number. */
   wchar_t *buffer,                                  /**< [out] Returns the parameter. */
   uint32_t bufLen                                   /**< [in]  The length of the buffer. */
   );

/******************************************************************************/
/**
 * @brief Return int parameter value of the message
 *
 * Returns the binary value of a parameter of the message.
 *
 * @return Result information about the call.\n
 *         BPApiStateRepSysInvalidHandle     if msgHdl is invalid\n
 *         BPApiStateRepSysIllegalArguments  if paramNr is out of range\n
 *         BPApiStateRepSysInvalidParamType  if paramNr has not int type\n
 *         BPApiStateOk                      on success. paramValue has been set.
 */
BPApiState BPApiRepSysGetMsgParamValueInt (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   uint32_t paramNr,                                 /**< [in]  The parameter number. */
   int32_t *paramValue                               /**< [out] Returns the parameter value. */
   );

/******************************************************************************/
/**
 * @brief Return float parameter value of the message
 *
 * Returns the binary value of a parameter of the message.
 *
 * @return Result information about the call.\n
 *         BPApiStateRepSysInvalidHandle     if msgHdl is invalid\n
 *         BPApiStateRepSysIllegalArguments  if paramNr is out of range\n
 *         BPApiStateRepSysInvalidParamType  if paramNr has not float type\n
 *         BPApiStateOk                      on success. paramValue has been set.
 */
BPApiState BPApiRepSysGetMsgParamValueFloat (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   uint32_t paramNr,                                 /**< [in]  The parameter number. */
   float *paramValue                                 /**< [out] Returns the parameter value. */
   );

/******************************************************************************/
/**
 * @brief Return memory parameter value of the message
 *
 * Returns the binary value of a parameter of the message.
 *
 * @return Result information about the call.\n
 *         BPApiStateRepSysInvalidHandle     if msgHdl is invalid\n
 *         BPApiStateRepSysIllegalArguments  if paramNr is out of range\n
 *         BPApiStateRepSysInvalidParamType  if paramNr has not memory type\n
 *         BPApiStateRepSysBufferTooSmall    if *bufLen is smaller than binary value\n
 *         BPApiStateOk                      on success. buffer contents and bufLen have been set.
 */
BPApiState BPApiRepSysGetMsgParamValueMemory (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   uint32_t paramNr,                                 /**< [in]  The parameter number. */
   char *buffer,                                     /**< [out] Returns the parameter value. */
   uint32_t *bufLen                                  /**< [in,out] The length of the buffer, returns the parameter value length. */
   );

/******************************************************************************/
/**
 * @brief Return message text (ASCII)
 *
 * Returns the message text in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysFormatMsgA (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   char *buffer,                                     /**< [out] Returns the message text. */
   uint32_t bufLen                                   /**< [in]  The length of the buffer. */
   );

/******************************************************************************/
/**
 * @brief Return message text (Unicode)
 *
 * Returns the message text in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiRepSysFormatMsgW (
   BPApiRepSysMsgHdl msgHdl,                         /**< [in]  The message handle. */
   wchar_t *buffer,                                  /**< [out] Returns the message text. */
   uint32_t bufLen                                   /**< [in]  The length of the buffer. */
   );

/******************************************************************************/
/**
 * @brief Set the protocol variable
 *
 * Set the protocol variable, which is delivered with each message.
 * @return State information about the call.\n
 *         BPApiStateOk on success. The protocol variable has been set.\n
 *         BPApiStateRepSysIllegalArguments, if the protocol variable is 0.\n
 *         BPApiStateRepSysVarNotFound, if the protocol variable could not be found.\n
 *         BPApiStateRepSysInvalidVarType, in case the variable data type is not supported.\n
 *         BPApiStateRepSysProvNotSupported, if the variable provider does not support this functionality.\n
 *         BPApiStateRepSysAlreadySet, if the protocol variable has already been set.\n
 *         BPApiStateInternalError, if an internal error occurred.
 */
BPApiState BPApiRepSysRegisterProtocolVariableA (
   const char       *protVar             /**< [in]  name of variable (ASCII), fully qualified access path (e.g., �APPL.MEM.var1�) */
);

/******************************************************************************/
/**
 * @brief Set the protocol variable
 *
 * Set the protocol variable, which is delivered with each message.
 * @return State information about the call.\n
 *         BPApiStateOk on success. The protocol variable has been set.\n
 *         BPApiStateRepSysIllegalArguments, if the protocol variable is 0.\n
 *         BPApiStateRepSysVarNotFound, if the protocol variable could not be found.\n
 *         BPApiStateRepSysInvalidVarType, in case the variable data type is not supported.\n
 *         BPApiStateRepSysProvNotSupported, if the variable provider does not support this functionality.\n
 *         BPApiStateRepSysAlreadySet, if the protocol variable has already been set.\n
 *         BPApiStateInternalError, if an internal error occurred.
 */
BPApiState BPApiRepSysRegisterProtocolVariableW (
   const wchar_t     *protVar           /**< [in]  name of variable (Unicode), fully qualified access path (e.g., �APPL.MEM.var1�) */
);

/******************************************************************************/
/**
 * @brief Unregister the protocol variable
 *
 * Unregister the protocol variable. Hence the protocol variable will return the default value (0).
 * @return State information about the call.\n
 *         BPApiStateOk on success. The protocol variable is not set anymore.\n
 *         BPApiStateNotOk, if the protocol variable was not set before.\n
 *         BPApiStateInternalError, if an internal error occurred.
 */
BPApiState BPApiRepSysUnregisterProtocolVariable (void
   );

/** @cond */
#ifdef UNICODE
   #define BPApiRepSysSetMsg                   BPApiRepSysSetMsgW
   #define BPApiRepSysSetMsgList               BPApiRepSysSetMsgListW
   #define BPApiRepSysGetLanguage              BPApiRepSysGetLanguageW
   #define BPApiRepSysSetLanguage              BPApiRepSysSetLanguageW
   #define BPApiRepSysGetMsgParamValue         BPApiRepSysGetMsgParamValueW
   #define BPApiRepSysFormatMsg                BPApiRepSysFormatMsgW
   #define BPApiRepSysRegisterProtocolVariable BPApiRepSysRegisterProtocolVariableW
#else
   #define BPApiRepSysSetMsg                   BPApiRepSysSetMsgA
   #define BPApiRepSysSetMsgList               BPApiRepSysSetMsgListA
   #define BPApiRepSysGetLanguage              BPApiRepSysGetLanguageA
   #define BPApiRepSysSetLanguage              BPApiRepSysSetLanguageA
   #define BPApiRepSysGetMsgParamValue         BPApiRepSysGetMsgParamValueA
   #define BPApiRepSysFormatMsg                BPApiRepSysFormatMsgA
   #define BPApiRepSysRegisterProtocolVariable BPApiRepSysRegisterProtocolVariableA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_REPSYS_H_INCLUDED */
