/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief  Interface for Statereport
*
*   Interface for Statereport
*
*   Generates runtime information about the realtime process.
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_STAREP_H
#define PACKAGE_API_STAREP_H

#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif


/** A type indicating the result of BPApiStaRepWriteCallbackFunc. */
typedef int32_t BPApiStaRepWriteCallbackState;
enum {
   BPApiStaRepWriteCallbackStateOk              = 0x0,           /** < Write callback successful. */
   BPApiStaRepWriteCallbackStateNotOk           = 0x80000001ul,  /** < Write callback not successful. */
   BPApiStaRepWriteCallbackStateInvalidPath     = 0x80000002ul,  /** < Invalid path. */
   BPApiStaRepWriteCallbackStateFileOpenFailed  = 0x80000003ul,  /** < File open failed. */
   BPApiStaRepWriteCallbackStateFileWriteFailed = 0x80000004ul   /** < File write failed. */
};

/** Statereport write callback function */
typedef BPApiStaRepWriteCallbackState (*BPApiStaRepWriteCallbackFunc)(const char*, void*);

/** Statereport trigger callback function */
typedef void (*BPApiStaRepTriggerCallbackFunc)(void*);

/******************************************************************************/
/**
 * @brief Add component to statereport (ASCII)
 *
 * Add a function to be called when a Statereport is triggered in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepAddComponentA (
   const char *compName,                          /**< [in] Name of registering component. */
   BPApiStaRepWriteCallbackFunc writefunc,        /**< [in] The function to be called. */
   void *funcArg                                  /**< [in] Argument for function call.*/
   );

/******************************************************************************/
/**
 * @brief Add component to statereport (Unicode)
 *
 * Add a function to be called when a Statereport is triggered in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepAddComponentW (
   const wchar_t *compName,                       /**< [in] Name of registering component. */
   BPApiStaRepWriteCallbackFunc writefunc,        /**< [in] The function to be called. */
   void *funcArg                                  /**< [in] Argument for function call.*/
   );

/******************************************************************************/
/**
 * @brief Add component to statereport (ASCII)
 *
 * Add a write function and a trigger function to be called when a Statereport
 * is triggered in ASCII. The trigger function will be called before all write
 * functions.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepAddComponentExtA (
   const char *compName,                          /**< [in] Name of registering component. */
   BPApiStaRepWriteCallbackFunc writefunc,        /**< [in] The function to be called. */
   BPApiStaRepTriggerCallbackFunc triggerFunc,    /**< [in] The trigger function to be called. */
   void *funcArg                                  /**< [in] Argument for function call.*/
   );

/******************************************************************************/
/**
 * @brief Add component to statereport (Unicode)
 *
 * Add a write function and a trigger function to be called when a Statereport
 * is triggered in Unicode. The trigger function will be called before all write
 * functions.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepAddComponentExtW (
   const wchar_t *compName,                       /**< [in] Name of registering component. */
   BPApiStaRepWriteCallbackFunc writeFunc,        /**< [in] The write function to be called. */
   BPApiStaRepTriggerCallbackFunc triggerFunc,    /**< [in] The trigger function to be called. */
   void *funcArg                                  /**< [in] Argument for function call.*/
   );

/******************************************************************************/
/**
 * @brief Remove component from Statereport (ASCII)
 *
 * Remove a component from Statereport in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepRemoveComponentA (
   const char *compName                           /**< [in] Name of component to be unregistered. */
   );

/******************************************************************************/
/**
 * @brief Remove component from Statereport (Unicode)
 *
 * Remove a component from Statereport in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepRemoveComponentW (
   const wchar_t *compName                        /**< [in] Name of component to be unregistered. */
   );

/** A type indicating the mode of path selection for writing a Statusreport. */
typedef int32_t BPApiStaRepDest;
enum {
   BPApiStaRepDestDefaultPathName  = 0x0,         /** < Default Statusreport path and
                                                        filename of system. */
   BPApiStaRepDestUserPathName     = 0x1          /** < Use selected Statusreport path
                                                        and filename. */
};

/******************************************************************************/
/**
 * @brief Triggers a Statereport (ASCII)
 *
 * Triggers a Statereport in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepWriteA (
   BPApiStaRepDest dest,                          /**< [in] Destination for writing Statusreport. */
   const char *starepPath,                        /**< [in] Output path in ASCII for Statusreport
                                                       (if no default path is used). */
   const char *filename                           /**< [in] The filename in ASCII for the
                                                       zipped Version of the Statusreport
                                                       (if no default filename is used). */
   );

/******************************************************************************/
/**
 * @brief Triggers a Statereport (unicode)
 *
 * Triggers a Statereport in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepWriteW (
   BPApiStaRepDest dest,                          /**< [in] Destination for writing Statusreport. */
   const wchar_t *starepPath,                     /**< [in] Output path in unicode for Statusreport
                                                       (if no default path is used). */
   const wchar_t *filename                        /**< [in] The filename in unicode for the
                                                       zipped Version of the Statusreport
                                                       (if no default filename is used). */
   );

/** A type indicating the state of Statusreport write. */
typedef int32_t BPApiStaRepWriteState;
enum {
   BPApiStaRepWriteStateOk        = 0x0,          /** < Statusreport write successful. */
   BPApiStaRepWriteStateInProgess = 0x00000001ul, /** < Statusreport write in progress. */
   BPApiStaRepWriteStateNotStarted= 0x80000001ul, /** < No Statusreport write started. */
   BPApiStaRepWriteStateError     = 0x80000002ul  /** < Statusreport write failed. */
};

/******************************************************************************/
/**
 * @brief State of completing Statereport (ASCII)
 *
 * Queries the state of a Statereport in progress.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepGetWriteStateA (
   int32_t *progress,                             /**< [out] Returns a value in percent indicating
                                                       the copy progress. 100 denotes a
                                                       finished copy execution. */
   BPApiStaRepWriteState *state,                  /**< [out] Returns a state value.  */
   char *destination,                             /**< [out] Returns the destination path
                                                       for the copy operation. */
   uint32_t destSize                              /**< [in]  Size of destination buffer. */
   );

/******************************************************************************/
/**
 * @brief State of completing Statereport (Unicode)
 *
 * Queries the state of a Statereport in progress.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepGetWriteStateW (
   int32_t *progress,                             /**< [out] Returns a value in percent indicating
                                                       the copy progress. 100 denotes a
                                                       finished copy execution. */
   BPApiStaRepWriteState *state,                  /**< [out] Returns a state value. */
   wchar_t *destination,                          /**< [out] Returns the destination path in
                                                       unicode for the copy operation. */
   uint32_t destSize                              /**< [in]  Size of destination buffer. */
   );

/** A type indicating the mode of path selection for writing a Statusreport. */
typedef int32_t BPApiStaRepCopySource;
enum {
   BPApiStaRepCopySourceLatest       = 0x0,       /** < Latest Statusreport of system. */
   BPApiStaRepCopySourceUserPathName = 0x1        /** < Use selected Statusreport path
                                                        and filename. */
};

/** A type indicating the mode of path selection for copying a Statusreport. */
typedef int32_t BPApiStaRepCopyMode;
enum {
   BPApiStaRepCopyModeDestinationPath  = 0x0,     /** < Use destination path. */
   BPApiStaRepCopyModeUSBDevice        = 0x1      /** < Use usb device. */
};

/******************************************************************************/
/**
 * @brief Triggers copying a Statereport (ASCII)
 *
 * Triggers copying of a Statereport in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepCopyA (
   BPApiStaRepCopySource copySource,              /**< [in] The Source mode. */
   const char           *starepPath,              /**< [in] Path to Starep. */
   const char           *filename,                /**< [in] Filename of Starep, concatenated with starepPath. */
   const char           *destPath,                /**< [in] The destination path. */
   BPApiStaRepCopyMode   copyMode                 /**< [in] The copy mode. */
   );

/******************************************************************************/
/**
 * @brief Triggers copying a Statereport (Unicode)
 *
 * Triggers copying of a Statereport in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepCopyW (
   BPApiStaRepCopySource copySource,              /**< [in] The Source mode. */
   const wchar_t        *starepPath,              /**< [in] Path in unicode to Starep. */
   const wchar_t        *filename,                /**< [in] Filename in unicode of Starep. Internally concatenated with starepPath. */
   const wchar_t        *destPath,                /**< [in] The destination path in unicode. */
   BPApiStaRepCopyMode   copyMode                 /**< [in] The copy mode. */
   );

/******************************************************************************/
/**
 * @brief State of copying Statereport (ASCII)
 *
 * Queries the state when copying a Statereport in ASCII.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepGetCopyStateA (
   int32_t    *progress,                          /**< [out] Returns a value in percent indicating the copy progress. 100 denotes a finished copy execution. */
   BPApiState *state,                             /**< [out] Returns a state value. */
   char       *destination,                       /**< [out] Returns the destination path for the copy operation. */
   uint32_t    destSize                           /**< [in] Size of destination buffer. */
   );

/******************************************************************************/
/**
 * @brief State of copying Statereport (Unicode)
 *
 * Queries the state when copying a Statereport in Unicode.
 *
 * @return Information about the call's state.
 */
BPApiState BPApiStaRepGetCopyStateW (
   int32_t    *progress,                          /**< [out] Returns a value in percent indicating the copy progress. 100 denotes a finished copy execution. */
   BPApiState *state,                             /**< [out] Returns a state value. */
   wchar_t    *destination,                       /**< [out] Returns the destination path in unicode for the copy operation. */
   uint32_t    destSize                           /**< [in] Size of destination buffer. */
   );

/** @cond */
#ifdef UNICODE
   #define BPApiStaRepWrite           BPApiStaRepWriteW
   #define BPApiStaRepGetWriteState   BPApiStaRepGetWriteStateW
   #define BPApiStaRepAddComponent    BPApiStaRepAddComponentW
   #define BPApiStaRepAddComponentExt BPApiStaRepAddComponentExtW
   #define BPApiStaRepRemoveComponent BPApiStaRepRemoveComponentW
   #define BPApiStaRepCopy            BPApiStaRepCopyW
   #define BPApiStaRepGetCopyState    BPApiStaRepGetCopyStateW
#else
   #define BPApiStaRepWrite           BPApiStaRepWriteA
   #define BPApiStaRepGetWriteState   BPApiStaRepGetWriteStateA
   #define BPApiStaRepAddComponent    BPApiStaRepAddComponentA
   #define BPApiStaRepAddComponentExt BPApiStaRepAddComponentExtA
   #define BPApiStaRepRemoveComponent BPApiStaRepRemoveComponentA
   #define BPApiStaRepCopy            BPApiStaRepCopyA
   #define BPApiStaRepGetCopyState    BPApiStaRepGetCopyStateA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_STAREP_H_INCLUDED */
