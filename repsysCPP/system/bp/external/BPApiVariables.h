/*------------------------------------------------------------------------------
*                             (c) 2011 by KEBA AG
*                                www.keba.com
*                                Linz/Austria
*                             All rights reserved
*-------------------------------------------------------------------------------
*/
/** @file
*   @brief Interface for Variables
*
*   Interface for Variables
*
*   Read and write values of Variables.
*   The variables need to be identified by their fully qualified access path,
*   e.g. APPL.prog.structVar.member for a 'member' in a structure instance
*   'structVar' located in functional unit or application 'prog'.
*/
/*------------------------------------------------------------------------------
*/

#ifndef PACKAGE_API_VARIABLES_H
#define PACKAGE_API_VARIABLES_H

#include "BPApiTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/** A type indicating a variable handle. */
typedef uint32_t BPApiVarHdl;
enum {
   BPApiVarInvalidHdl = 0xffffffff, /** invalid variable handle */
};
/** @deprecated invalid variable handle (compatiblity) */
#define BpApiVarInvalidHdl BPApiVarInvalidHdl

/** A type indicating a variable browse handle. */
typedef uint32_t BPApiVarBrowseHdl;
enum {
   BPApiVarInvalidBrowseHdl = 0xffffffff, /** invalid variable browse handle */
};
/** @deprecated invalid variable browse handle (compatiblity) */
#define BpApiVarInvalidBrowseHdl BPApiVarInvalidBrowseHdl

/** Variable data type definition */
typedef uint32_t BPApiVarType;
enum {
   BPApiVarTypeINVALID        =  0,   /**< No data type available / invalid type */

   BPApiVarTypeBOOL           =  1,   /**< Boolean stored in a single byte (0=false, 1=true) */

   BPApiVarTypeSINT           =  2,   /**< 8 bit signed integer */
   BPApiVarTypeINT            =  3,   /**< 16 bit signed integer */
   BPApiVarTypeDINT           =  4,   /**< 32 bit signed integer */
   BPApiVarTypeLINT           =  5,   /**< 64 bit signed integer */
   BPApiVarTypeUSINT          =  6,   /**< 8 bit unsigned integer */
   BPApiVarTypeUINT           =  7,   /**< 16 bit unsigned integer */
   BPApiVarTypeUDINT          =  8,   /**< 32 bit unsigned integer */
   BPApiVarTypeULINT          =  9,   /**< 64 bit unsigned integer */

   BPApiVarTypeSINT8          =  2,   /**< 8 bit signed integer */
   BPApiVarTypeSINT16         =  3,   /**< 16 bit signed integer */
   BPApiVarTypeSINT32         =  4,   /**< 32 bit signed integer */
   BPApiVarTypeSINT64         =  5,   /**< 64 bit signed integer */
   BPApiVarTypeUINT8          =  6,   /**< 8 bit unsigned integer */
   BPApiVarTypeUINT16         =  7,   /**< 16 bit unsigned integer */
   BPApiVarTypeUINT32         =  8,   /**< 32 bit unsigned integer */
   BPApiVarTypeUINT64         =  9,   /**< 64 bit unsigned integer */

   BPApiVarTypeREAL           = 10,   /**< single precision floating point number */
   BPApiVarTypeLREAL          = 11,   /**< double precision floating point number */

   BPApiVarTypeFLOAT          = 10,   /**< single precision floating point number */
   BPApiVarTypeDOUBLE         = 11,   /**< double precision floating point number */

   BPApiVarTypeBYTE           = 12,   /**< 8 bit bit field (IEC61131-3 only) */
   BPApiVarTypeWORD           = 13,   /**< 16 bit bit field (IEC61131-3 only) */
   BPApiVarTypeDWORD          = 14,   /**< 32 bit bit field (IEC61131-3 only) */
   BPApiVarTypeLWORD          = 15,   /**< 64 bit bit field (IEC61131-3 only) */

   BPApiVarTypeDATE           = 16,   /**< DATE          as BpApiTime  */
   BPApiVarTypeTIME           = 17,   /**< DURATION      as BpApiTime */
   BPApiVarTypeTIME_OF_DAY    = 18,   /**< TIME_OF_DAY   as BpApiTime */
   BPApiVarTypeDATE_AND_TIME  = 19,   /**< DATE_AND_TIME as BpApiTime */

   BPApiVarTypeENUM           = 20,   /**< enumeration (Kemro IEC61131-3 only) */

   BPApiVarTypeSTRING         = 22,   /**< ASCII string */
   BPApiVarTypeWSTRING        = 23,   /**< wide character string */

   BPApiVarTypeARRAY          = 24,   /**< array */
   BPApiVarTypeSTRUCT         = 25,   /**< struct */

   BPApiVarTypeDATE64us       = 54,   /**< DATE64          as 64 bit signed integer in us */
   BPApiVarTypeTIME64us       = 55,   /**< TIME64          as 64 bit signed integer in us */
   BPApiVarTypeTOD64us        = 56,   /**< TIME_OF_DAY64   as 64 bit signed integer in us */
   BPApiVarTypeDT64us         = 57,   /**< DATE_AND_TIME64 as 64 bit signed integer in us */

   BPApiVarTypeDIRECTORY      = 990   /**< directory (structural node) */
};


/** Protocol data structure in Unicode */
typedef struct BPApiVarProtocolDataW {
   const wchar_t *userName;           /**< 'Who' wants to write these values (in Unicode) */
   const wchar_t *hostName;           /**< Information about host in Unicode */
   uint32_t       hostType;           /**< 1: Unknown; 2: Visu; 3: Control */
} BPApiVarProtocolDataW;


/** Browse directory data structure */
typedef struct BPApiVarDirEntry {
   BPApiVarType         type;         /**< contains the type of the returned child */
   int                  hasValue;     /**< if node has a readable value, then the content of 'hasValue' is 1, otherwise it is 0 */
   int                  hasChild;     /**< if node has child nodes, then the content of 'hasChild' is 1, otherwise it is 1 */
   const char *         name;         /**< name of the child entry */
   const char *         delimiter;    /**< separator character to be placed between 'parentName' and 'childName' to build up a valid path */
} BPApiVarDirEntry;

/******************************************************************************/
/**
 * @brief Opens handle from name (ASCII).
 *
 * Opens handle from variable name in ASCII.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarOpenHdlA (
   const char *varName,                          /**< [in]  The variable name. */
   BPApiVarHdl *var                              /**< [out] Returns the handle */
   );

/******************************************************************************/
/**
 * @brief Opens handle from name (Unicode).
 *
 * Opens handle from variable name in Unicode.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarOpenHdlW (
   const wchar_t *varName,                       /**< [in]  The variable name in Unicode. */
   BPApiVarHdl *var                              /**< [out] Returns the handle */
   );

/******************************************************************************/
/**
 * @brief Opens handle from name (ASCII), without pinning involved references.
 *
 * Opens handle from variable name in ASCII. In case of involved references
 * (MAPTO, REFTO) reading returns the current value (instead of the value
 * pinned during open, as with BPApiVarOpenHdlA).
 *
 * @return State information about the call.
 */
BPApiState BPApiVarOpenHdlUnpinnedA(
   const char *varName,                          /**< [in]  The variable name. */
   BPApiVarHdl *var                              /**< [out] Returns the handle */
);

/******************************************************************************/
/**
 * @brief Opens handle from name (Unicode), without pinning involved references.
 *
 * Opens handle from variable name in Unicode. In case of involved references
 * (MAPTO, REFTO) reading returns the current value (instead of the value
 * pinned during open, as with BPApiVarOpenHdlW).
 *
 * @return State information about the call.
 */
BPApiState BPApiVarOpenHdlUnpinnedW(
   const wchar_t *varName,                       /**< [in]  The variable name in Unicode. */
   BPApiVarHdl *var                              /**< [out] Returns the handle */
);

/******************************************************************************/
/**
 * @brief Write a variable
 *
 * Write a variable to the specified destination from source.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarWrite (
   BPApiVarHdl destination,                      /**< [in] The Destination for the write operation */
   void *source,                                 /**< [in] The source of the write operation. */
   int32_t size                                  /**< [in] The size of the data behind the source pointer. */
   );

/******************************************************************************/
/**
 * @brief Write a variable and protocol this operation (ASCII)
 *
 * Write a variable to the specified destination from source and protocol this
 * operation in ASCII.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarWriteWithProtocolA (
   BPApiVarHdl destination,                      /**< [in] The Destination for the write operation */
   void *source,                                 /**< [in] The source of the write operation. */
   int32_t size,                                 /**< [in] The size of the data behind the source pointer. */
   const BPApiVarProtocolData * protocolInfo     /**< [in] protocol data; if a NULL pointer is passed, the function returns BPApiStateParamError. */
   );

/******************************************************************************/
/**
 * @brief Write a variable and protocol this operation (Unicode)
 *
 * Write a variable to the specified destination from source and protocol this
 * operation in Unicode.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarWriteWithProtocolW (
   BPApiVarHdl destination,                      /**< [in] The Destination for the write operation */
   void *source,                                 /**< [in] The source of the write operation. */
   int32_t size,                                 /**< [in] The size of the data behind the source pointer. */
   const BPApiVarProtocolDataW * protocolInfo    /**< [in] protocol data; if a NULL pointer is passed, the function returns BPApiStateParamError. */
   );

/******************************************************************************/
/**
 * @brief Read a variable
 *
 * Read a variable from the specified source into destination.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarRead (
   void *destination,                            /**< [out] The Destination for the read operation */
   BPApiVarHdl source,                           /**< [in]  The source of the read operation. */
   int32_t size                                  /**< [in]  The size of the data behind the destination pointer. */
);

/******************************************************************************/
/**
 * @brief Get Variable Type
 *
 * Returns the type of the variable, the handle points to.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarGetType (
   BPApiVarHdl hdl,                              /**< [in]  The handle of the variable. */
   BPApiVarType *varType                         /**< [out] Returns the type of the variable hdl points to.*/
   );

/******************************************************************************/
/**
 * @brief Get Variable Name
 *
 * Returns the name (absolute path) of the variable, the handle points to.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateInvalidHandle if 'hdl' is invalid,<BR>
 *          ::BPApiStateOutOfMemory if buffer is too small to hold all data,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiVarGetNameA (
   BPApiVarHdl hdl,                              /**< [in]  The handle of the variable. */
   char *varName,                                /**< [out] Returns the variable name of the variable hdl points to. */
   int32_t varNameSize                           /**< [in] size of 'varName' buffer in bytes. */
   );

/******************************************************************************/
/**
 * @brief Get Variable Name
 *
 * Returns the name (absolute path) of the variable, the handle points to.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateInvalidHandle if 'hdl' is invalid,<BR>
 *          ::BPApiStateOutOfMemory if buffer is too small to hold all data,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiVarGetNameW (
   BPApiVarHdl hdl,                              /**< [in]  The handle of the variable. */
   wchar_t *varName,                             /**< [out] Returns the variable name of the variable hdl points to. */
   int32_t varNameSize                           /**< [in] size of 'varName' buffer in wchar_t elements. */
   );

/******************************************************************************/
/**
 * @brief Get Map Target Variable
 *
 * Returns an newly-opened (pinned) handle of the map target variable.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarGetMapTarget(
   BPApiVarHdl hdl,                              /**< [in]  The handle of the REFTO/MAPTO variable. */
   BPApiVarHdl *targetHdl                        /**< [out] Returns the handle of the map target.*/
);

/******************************************************************************/
/**
 * @brief Closes handle
 *
 * Closes and frees this handle. In order to avoid memory leaks.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarCloseHdl (
   BPApiVarHdl *hdl                              /**< [in/out] Invalidate this hdl. Returns BpApiVarInvalidHdl. */
   );

/******************************************************************************/
/**
 * @brief Opens the given directory, structure or array
 *
 * This method opens the directory related to the given parentName.
 * The returned BPApiVarBrowseHdl can be used to read the directory.
 *
 * ATTENTION:  Every opened BPApiVarBrowseHdl must be closed.
 *             If handles are left open, memory leaks will occur!
 *
 *
 * @return  ::BPApiStateOk on success, browseHdl will be not zero,<BR>
 *          ::BPApiStateVarNoChildren if parent has no children,<BR>
 *          ::BPApiStateVarNotFound if 'parentName' cannot be found,<BR>
 *          ::BPApiStateParamError if 'browseHdl' is NULL,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateOutOfMemory if memory allocation fails,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiVarOpenDir(
   const char         * parentName,              /**< [in]  full parent path, may be NULL or an empty string for the root node */
   BPApiVarBrowseHdl  * browseHdl                /**< [out] browse handle for BPApiVarReadDir() calls.
                                                            Close this handle with BPApiVarCloseDir() when browsing of children is finished. */
);

/******************************************************************************/
/**
 * @brief Reads next entry of an opened BPApiVarBrowseHdl
 *
 * This method reads the opened directory or structure related to the given BPApiVarBrowseHdl.
 * First call will deliver the first child of the directory.
 * Every other call will deliver every next sibling of the first child until no more siblings are available.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateVarNoChildren if parent has no more children,<BR>
 *          ::BPApiStateInvalidHandle if 'browseHdl' is invalid or already closed by BPApiVarCloseDir(),<BR>
 *          ::BPApiStateParamError if 'entry' is NULL,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateNotOk, ::BPApiStateInternalError for other errors
 */
BPApiState BPApiVarReadDir(
   BPApiVarBrowseHdl  * browseHdl,               /**< [in]  browse handle returned by BPApiVarOpenDir() call */
   BPApiVarDirEntry ** entry                     /**< [out] returns a pointer to BPApiVarDirEntry, or NULL in case of an error */
);

/******************************************************************************/
/**
 * @brief Closes an opened BPApiBrowseHdl
 *
 * This method must be called to close an opened BPApiVarBrowseHdl.
 *
 * @return  ::BPApiStateOk on success,<BR>
 *          ::BPApiStateComNotRunning if BPApi isn't running,<BR>
 *          ::BPApiStateInvalidHandle for invalid or already closed 'browseHdl',<BR>
 *          ::BPApiStateNotOk for other errors
 */
BPApiState BPApiVarCloseDir(
   BPApiVarBrowseHdl  * browseHdl                /**< [in]  BPApiVarBrowseHdl to close */
);

/******************************************************************************/
/**
 * @brief Create variable node (ASCII).
 *
 * Create variable server node.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarCreateA (
   const char *parentName,                       /**< [in]  Full parent path, may be NULL or an empty string for the root node. */
   const char *varName,                          /**< [in]  The variable name to be created. */
   BPApiVarType varType,                         /**< [in]  The variable type. */
   void *varValueSource,                         /**< [in]  The source pointer of the value. */
   int32_t varValueSize                          /**< [in]  The size of the data behind the source pointer. */
   );

/******************************************************************************/
/**
 * @brief Create variable node (Unicode).
 *
 * Create variable server node.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarCreateW (
   const wchar_t *parentName,                    /**< [in]  Full parent path, may be NULL or an empty string for the root node. */
   const wchar_t *varName,                       /**< [in]  The variable name to be created. */
   BPApiVarType varType,                         /**< [in]  The variable type. */
   void *varValueSource,                         /**< [in]  The source pointer of the value. */
   int32_t varValueSize                          /**< [in]  The size of the data behind the source pointer. */
   );

/******************************************************************************/
/**
 * @brief Delete variable node (ASCII).
 *
 * Delete variable server node.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarDeleteA (
   const char *varName                           /**< [in]  The variable name. */
   );

/******************************************************************************/
/**
 * @brief Delete variable node (Unicode).
 *
 * Delete variable server node.
 *
 * @return State information about the call.
 */
BPApiState BPApiVarDeleteW (
   const wchar_t *varName                        /**< [in]  The variable name. */
   );

/** @cond */
#ifdef UNICODE
   #define BPApiVarCreate              BPApiVarCreateW
   #define BPApiVarDelete              BPApiVarDeleteW
   #define BPApiVarOpenHdl             BPApiVarOpenHdlW
   #define BPApiVarWriteWithProtocol   BPApiVarWriteWithProtocolW
   #define BPApiVarGetName             BPApiVarGetNameW
#else
   #define BPApiVarCreate              BPApiVarCreateA
   #define BPApiVarDelete              BPApiVarDeleteA
   #define BPApiVarOpenHdl             BPApiVarOpenHdlA
   #define BPApiVarWriteWithProtocol   BPApiVarWriteWithProtocolA
   #define BPApiVarGetName             BPApiVarGetNameA
#endif
/** @endcond */

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* PACKAGE_API_VARIABLES_H_INCLUDED */
